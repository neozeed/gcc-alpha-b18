/* Remote debugging interface for MIPS remote debugging protocol.
   Copyright 1993, 1994, 1995 Free Software Foundation, Inc.
   Contributed by Cygnus Support.  Written by Ian Lance Taylor
   <ian@cygnus.com>.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include "defs.h"
#include "inferior.h"
#include "bfd.h"
#include "symfile.h"
#include "wait.h"
#include "gdbcmd.h"
#include "gdbcore.h"
#include "serial.h"
#include "target.h"
#include "remote-utils.h"
#include "gdb_string.h"

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef ANSI_PROTOTYPES
#include <stdarg.h>
#else
#include <varargs.h>
#endif

/* Microsoft C's stat.h doesn't define all the POSIX file modes.  */
#ifndef S_IROTH
#define S_IROTH S_IREAD
#endif

extern void mips_set_processor_type_command PARAMS ((char *, int));


/* Prototypes for local functions.  */

static int mips_readchar PARAMS ((int timeout));

static int mips_receive_header PARAMS ((unsigned char *hdr, int *pgarbage,
					int ch, int timeout));

static int mips_receive_trailer PARAMS ((unsigned char *trlr, int *pgarbage,
					 int *pch, int timeout));

static int mips_cksum PARAMS ((const unsigned char *hdr,
			       const unsigned char *data,
			       int len));

static void mips_send_packet PARAMS ((const char *s, int get_ack));

static void mips_send_command PARAMS ((const char *cmd, int prompt));

static int mips_receive_packet PARAMS ((char *buff, int throw_error,
					int timeout));

static CORE_ADDR mips_request PARAMS ((int cmd, CORE_ADDR addr,
				 CORE_ADDR data, int *perr, int timeout,
				 char *buff));

static void mips_initialize PARAMS ((void));

static void mips_open PARAMS ((char *name, int from_tty));

static void pmon_open PARAMS ((char *name, int from_tty));

static void ddb_open PARAMS ((char *name, int from_tty));

static void lsi_open PARAMS ((char *name, int from_tty));

static void mips_close PARAMS ((int quitting));

static void mips_detach PARAMS ((char *args, int from_tty));

static void mips_resume PARAMS ((int pid, int step,
				 enum target_signal siggnal));

static int mips_wait PARAMS ((int pid, struct target_waitstatus *status));

static int pmon_wait PARAMS ((int pid, struct target_waitstatus *status));

static int mips_map_regno PARAMS ((int regno));

static void mips_fetch_registers PARAMS ((int regno));

static void mips_prepare_to_store PARAMS ((void));

static void mips_store_registers PARAMS ((int regno));

static unsigned int mips_fetch_word PARAMS ((CORE_ADDR addr));

static int mips_store_word PARAMS ((CORE_ADDR addr, unsigned int value,
				    char *old_contents));

static int mips_xfer_memory PARAMS ((CORE_ADDR memaddr, char *myaddr, int len,
				     int write, struct target_ops *ignore));

static void mips_files_info PARAMS ((struct target_ops *ignore));

static void mips_create_inferior PARAMS ((char *execfile, char *args,
					  char **env));

static void mips_mourn_inferior PARAMS ((void));

static int pmon_makeb64 PARAMS ((unsigned long v, char *p, int n, int *chksum));

static int pmon_zeroset PARAMS ((int recsize, char **buff, int *amount,
                                 unsigned int *chksum));

static int pmon_checkset PARAMS ((int recsize, char **buff, int *value));

static void pmon_make_fastrec PARAMS ((char **outbuf, unsigned char *inbuf,
                                       int *inptr, int inamount, int *recsize,
                                       unsigned int *csum, unsigned int *zerofill));

static int pmon_check_ack PARAMS ((char *mesg));

static void pmon_start_download PARAMS ((void));

static void pmon_end_download PARAMS ((int final, int bintotal));

static void pmon_download PARAMS ((char *buffer, int length));

static void pmon_load_fast PARAMS ((char *file));

static void mips_load PARAMS ((char *file, int from_tty));

static int mips_make_srec PARAMS ((char *buffer, int type, CORE_ADDR memaddr,
				   unsigned char *myaddr, int len));

static int common_breakpoint PARAMS ((int cmd, CORE_ADDR addr, CORE_ADDR mask,
				      char *flags));

/* Forward declarations.  */
extern struct target_ops mips_ops;
extern struct target_ops pmon_ops;
extern struct target_ops ddb_ops;

/* The MIPS remote debugging interface is built on top of a simple
   packet protocol.  Each packet is organized as follows:

   SYN	The first character is always a SYN (ASCII 026, or ^V).  SYN
	may not appear anywhere else in the packet.  Any time a SYN is
	seen, a new packet should be assumed to have begun.

   TYPE_LEN
	This byte contains the upper five bits of the logical length
	of the data section, plus a single bit indicating whether this
	is a data packet or an acknowledgement.  The documentation
	indicates that this bit is 1 for a data packet, but the actual
	board uses 1 for an acknowledgement.  The value of the byte is
		0x40 + (ack ? 0x20 : 0) + (len >> 6)
	(we always have 0 <= len < 1024).  Acknowledgement packets do
	not carry data, and must have a data length of 0.

   LEN1 This byte contains the lower six bits of the logical length of
	the data section.  The value is
	 	0x40 + (len & 0x3f)

   SEQ	This byte contains the six bit sequence number of the packet.
	The value is
		0x40 + seq
	An acknowlegment packet contains the sequence number of the
	packet being acknowledged plus 1 modulo 64.  Data packets are
	transmitted in sequence.  There may only be one outstanding
	unacknowledged data packet at a time.  The sequence numbers
	are independent in each direction.  If an acknowledgement for
	the previous packet is received (i.e., an acknowledgement with
	the sequence number of the packet just sent) the packet just
	sent should be retransmitted.  If no acknowledgement is
	received within a timeout period, the packet should be
	retransmitted.  This has an unfortunate failure condition on a
	high-latency line, as a delayed acknowledgement may lead to an
	endless series of duplicate packets.

   DATA	The actual data bytes follow.  The following characters are
	escaped inline with DLE (ASCII 020, or ^P):
		SYN (026)	DLE S
		DLE (020)	DLE D
		^C  (003)	DLE C
		^S  (023)	DLE s
		^Q  (021)	DLE q
	The additional DLE characters are not counted in the logical
	length stored in the TYPE_LEN and LEN1 bytes.

   CSUM1
   CSUM2
   CSUM3
	These bytes contain an 18 bit checksum of the complete
	contents of the packet excluding the SEQ byte and the
	CSUM[123] bytes.  The checksum is simply the twos complement
	addition of all the bytes treated as unsigned characters.  The
	values of the checksum bytes are:
		CSUM1: 0x40 + ((cksum >> 12) & 0x3f)
		CSUM2: 0x40 + ((cksum >> 6) & 0x3f)
		CSUM3: 0x40 + (cksum & 0x3f)

   It happens that the MIPS remote debugging protocol always
   communicates with ASCII strings.  Because of this, this
   implementation doesn't bother to handle the DLE quoting mechanism,
   since it will never be required.  */

/* The SYN character which starts each packet.  */
#define SYN '\026'

/* The 0x40 used to offset each packet (this value ensures that all of
   the header and trailer bytes, other than SYN, are printable ASCII
   characters).  */
#define HDR_OFFSET 0x40

/* The indices of the bytes in the packet header.  */
#define HDR_INDX_SYN 0
#define HDR_INDX_TYPE_LEN 1
#define HDR_INDX_LEN1 2
#define HDR_INDX_SEQ 3
#define HDR_LENGTH 4

/* The data/ack bit in the TYPE_LEN header byte.  */
#define TYPE_LEN_DA_BIT 0x20
#define TYPE_LEN_DATA 0
#define TYPE_LEN_ACK TYPE_LEN_DA_BIT

/* How to compute the header bytes.  */
#define HDR_SET_SYN(data, len, seq) (SYN)
#define HDR_SET_TYPE_LEN(data, len, seq) \
  (HDR_OFFSET \
   + ((data) ? TYPE_LEN_DATA : TYPE_LEN_ACK) \
   + (((len) >> 6) & 0x1f))
#define HDR_SET_LEN1(data, len, seq) (HDR_OFFSET + ((len) & 0x3f))
#define HDR_SET_SEQ(data, len, seq) (HDR_OFFSET + (seq))

/* Check that a header byte is reasonable.  */
#define HDR_CHECK(ch) (((ch) & HDR_OFFSET) == HDR_OFFSET)

/* Get data from the header.  These macros evaluate their argument
   multiple times.  */
#define HDR_IS_DATA(hdr) \
  (((hdr)[HDR_INDX_TYPE_LEN] & TYPE_LEN_DA_BIT) == TYPE_LEN_DATA)
#define HDR_GET_LEN(hdr) \
  ((((hdr)[HDR_INDX_TYPE_LEN] & 0x1f) << 6) + (((hdr)[HDR_INDX_LEN1] & 0x3f)))
#define HDR_GET_SEQ(hdr) ((unsigned int)(hdr)[HDR_INDX_SEQ] & 0x3f)

/* The maximum data length.  */
#define DATA_MAXLEN 1023

/* The trailer offset.  */
#define TRLR_OFFSET HDR_OFFSET

/* The indices of the bytes in the packet trailer.  */
#define TRLR_INDX_CSUM1 0
#define TRLR_INDX_CSUM2 1
#define TRLR_INDX_CSUM3 2
#define TRLR_LENGTH 3

/* How to compute the trailer bytes.  */
#define TRLR_SET_CSUM1(cksum) (TRLR_OFFSET + (((cksum) >> 12) & 0x3f))
#define TRLR_SET_CSUM2(cksum) (TRLR_OFFSET + (((cksum) >>  6) & 0x3f))
#define TRLR_SET_CSUM3(cksum) (TRLR_OFFSET + (((cksum)      ) & 0x3f))

/* Check that a trailer byte is reasonable.  */
#define TRLR_CHECK(ch) (((ch) & TRLR_OFFSET) == TRLR_OFFSET)

/* Get data from the trailer.  This evaluates its argument multiple
   times.  */
#define TRLR_GET_CKSUM(trlr) \
  ((((trlr)[TRLR_INDX_CSUM1] & 0x3f) << 12) \
   + (((trlr)[TRLR_INDX_CSUM2] & 0x3f) <<  6) \
   + ((trlr)[TRLR_INDX_CSUM3] & 0x3f))

/* The sequence number modulos.  */
#define SEQ_MODULOS (64)

/* PMON commands to load from the serial port or UDP socket.  */
#define LOAD_CMD	"load -b -s tty0\r"
#define LOAD_CMD_UDP	"load -b -s udp\r"

enum mips_monitor_type {
  /* IDT/SIM monitor being used: */
  MON_IDT,
  /* PMON monitor being used: */
  MON_PMON, /* 3.0.83 [COGENT,EB,FP,NET] Algorithmics Ltd. Nov  9 1995 17:19:50 */
  MON_DDB,  /* 2.7.473 [DDBVR4300,EL,FP,NET] Risq Modular Systems,  Thu Jun 6 09:28:40 PDT 1996 */
  MON_LSI,  /* 4.3.12 [EB,FP], LSI LOGIC Corp. Tue Feb 25 13:22:14 1997 */
  /* Last and unused value, for sizing vectors, etc. */
  MON_LAST
};
static enum mips_monitor_type mips_monitor = MON_LAST;

/* The monitor prompt text.  If the user sets the PMON prompt
   to some new value, the GDB `set monitor-prompt' command must also
   be used to inform GDB about the expected prompt.  Otherwise, GDB
   will not be able to connect to PMON in mips_initialize().
   If the `set monitor-prompt' command is not used, the expected
   default prompt will be set according the target:
	target		prompt
	-----		-----
	pmon		PMON> 
	ddb		NEC010>
	lsi		PMON>
*/
static char *mips_monitor_prompt;

/* Set to 1 if the target is open.  */
static int mips_is_open;

/* Currently active target description (if mips_is_open == 1) */
static struct target_ops *current_ops;

/* Set to 1 while the connection is being initialized.  */
static int mips_initializing;

/* Set to 1 while the connection is being brought down.  */
static int mips_exiting;

/* The next sequence number to send.  */
static unsigned int mips_send_seq;

/* The next sequence number we expect to receive.  */
static unsigned int mips_receive_seq;

/* The time to wait before retransmitting a packet, in seconds.  */
static int mips_retransmit_wait = 3;

/* The number of times to try retransmitting a packet before giving up.  */
static int mips_send_retries = 10;

/* The number of garbage characters to accept when looking for an
   SYN for the next packet.  */
static int mips_syn_garbage = 1050;

/* The time to wait for a packet, in seconds.  */
static int mips_receive_wait = 5;

/* Set if we have sent a packet to the board but have not yet received
   a reply.  */
static int mips_need_reply = 0;

/* Handle used to access serial I/O stream.  */
static serial_t mips_desc;

/* UDP handle used to download files to target.  */
static serial_t udp_desc;
static int udp_in_use;

/* TFTP filename used to download files to DDB board, in the form
   host:filename.  */
static char *tftp_name;		/* host:filename */
static char *tftp_localname;	/* filename portion of above */
static int tftp_in_use;
static FILE *tftp_file;

/* Counts the number of times the user tried to interrupt the target (usually
   via ^C.  */
static int interrupt_count;

/* If non-zero, means that the target is running. */
static int mips_wait_flag = 0;

/* If non-zero, monitor supports breakpoint commands. */
static monitor_supports_breakpoints = 0;

/* Data cache header.  */

#if 0	/* not used (yet?) */
static DCACHE *mips_dcache;
#endif

/* Non-zero means that we've just hit a read or write watchpoint */
static int hit_watchpoint;

static void
close_ports()
{
  mips_is_open = 0;
  SERIAL_CLOSE (mips_desc);

  if (udp_in_use)
    {
      SERIAL_CLOSE (udp_desc);
      udp_in_use = 0;
    }
  tftp_in_use = 0;
}
    
/* Handle low-level error that we can't recover from.  Note that just
   error()ing out from target_wait or some such low-level place will cause
   all hell to break loose--the rest of GDB will tend to get left in an
   inconsistent state.  */

static NORETURN void
#ifdef ANSI_PROTOTYPES
mips_error (char *string, ...)
#else
mips_error (va_alist)
     va_dcl
#endif
{
  va_list args;

#ifdef ANSI_PROTOTYPES
  va_start (args, string);
#else
  char *string;
  va_start (args);
  string = va_arg (args, char *);
#endif
 
  target_terminal_ours ();
  wrap_here("");			/* Force out any buffered output */
  gdb_flush (gdb_stdout);
  if (error_pre_print)
    fprintf_filtered (gdb_stderr, error_pre_print);
  vfprintf_filtered (gdb_stderr, string, args);
  fprintf_filtered (gdb_stderr, "\n");
  va_end (args);
  gdb_flush (gdb_stderr);

  /* Clean up in such a way that mips_close won't try to talk to the
     board (it almost surely won't work since we weren't able to talk to
     it).  */
  close_ports ();

  printf_unfiltered ("Ending remote MIPS debugging.\n");
  target_mourn_inferior ();

  return_to_top_level (RETURN_ERROR);
}

/* putc_readable - print a character, displaying non-printable chars in
   ^x notation or in hex.  */

static void
putc_readable (ch)
     int ch;
{
  if (ch == '\n')
    putchar_unfiltered ('\n');
  else if (ch == '\r')
    printf_unfiltered ("\\r");
  else if (ch < 0x20)	/* ASCII control character */
    printf_unfiltered ("^%c", ch + '@');
  else if (ch >= 0x7f)	/* non-ASCII characters (rubout or greater) */
    printf_unfiltered ("[%02x]", ch & 0xff);
  else
    putchar_unfiltered (ch);
}


/* puts_readable - print a string, displaying non-printable chars in
   ^x notation or in hex.  */

static void
puts_readable (string)
     char *string;
{
  int c;

  while ((c = *string++) != '\0')
    putc_readable (c);
}


/* Wait until STRING shows up in mips_desc.  Returns 1 if successful, else 0 if
   timed out.  TIMEOUT specifies timeout value in seconds.
*/

int
mips_expect_timeout (string, timeout)
     char *string;
     int timeout;
{
  char *p = string;

  if (remote_debug)
    {
      printf_unfiltered ("Expected \"");
      puts_readable (string);
      printf_unfiltered ("\", got \"");
    }

  immediate_quit = 1;
  while (1)
    {
      int c;

/* Must use SERIAL_READCHAR here cuz mips_readchar would get confused if we
   were waiting for the mips_monitor_prompt... */

      c = SERIAL_READCHAR (mips_desc, timeout);

      if (c == SERIAL_TIMEOUT)
	{
	  if (remote_debug)
	    printf_unfiltered ("\": FAIL\n");
	  return 0;
	}

      if (remote_debug)
	putc_readable (c);

      if (c == *p++)
	{	
	  if (*p == '\0')
	    {
	      immediate_quit = 0;
	      if (remote_debug)
	      printf_unfiltered ("\": OK\n");
	      return 1;
	    }
	}
      else
	{
	  p = string;
	  if (c == *p)
	    p++;
	}
    }
}

/* Wait until STRING shows up in mips_desc.  Returns 1 if successful, else 0 if
   timed out.  The timeout value is hard-coded to 2 seconds.  Use
   mips_expect_timeout if a different timeout value is needed.
*/

int
mips_expect (string)
     char *string;
{
    return mips_expect_timeout (string, 2);
}

/* Read the required number of characters into the given buffer (which
   is assumed to be large enough). The only failure is a timeout. */
int
mips_getstring (string, n)
     char *string;
     int n;
{
  char *p = string;
  int c;

  immediate_quit = 1;
  while (n > 0)
    {
      c = SERIAL_READCHAR (mips_desc, 2);

      if (c == SERIAL_TIMEOUT) {
        fprintf_unfiltered (stderr, "Failed to read %d characters from target (TIMEOUT)\n", n);
	return 0;
      }

      *p++ = c;
      n--;
    }

  return 1;
}

/* Read a character from the remote, aborting on error.  Returns
   SERIAL_TIMEOUT on timeout (since that's what SERIAL_READCHAR
   returns).  FIXME: If we see the string mips_monitor_prompt from
   the board, then we are debugging on the main console port, and we
   have somehow dropped out of remote debugging mode.  In this case,
   we automatically go back in to remote debugging mode.  This is a
   hack, put in because I can't find any way for a program running on
   the remote board to terminate without also ending remote debugging
   mode.  I assume users won't have any trouble with this; for one
   thing, the IDT documentation generally assumes that the remote
   debugging port is not the console port.  This is, however, very
   convenient for DejaGnu when you only have one connected serial
   port.  */

static int
mips_readchar (timeout)
     int timeout;
{
  int ch;
  static int state = 0;
  int mips_monitor_prompt_len = strlen (mips_monitor_prompt);

#ifdef MAINTENANCE_CMDS
  {
    int i;

    i = timeout;
    if (i == -1 && watchdog > 0)
     i = watchdog;
  }
#endif

  if (state == mips_monitor_prompt_len)
    timeout = 1;
  ch = SERIAL_READCHAR (mips_desc, timeout);
#ifdef MAINTENANCE_CMDS
  if (ch == SERIAL_TIMEOUT && timeout == -1) /* Watchdog went off */
    {
      target_mourn_inferior ();
      error ("Watchdog has expired.  Target detached.\n");
    }
#endif
  if (ch == SERIAL_EOF)
    mips_error ("End of file from remote");
  if (ch == SERIAL_ERROR)
    mips_error ("Error reading from remote: %s", safe_strerror (errno));
  if (remote_debug > 1)
    {
      /* Don't use _filtered; we can't deal with a QUIT out of
	 target_wait, and I think this might be called from there.  */
      if (ch != SERIAL_TIMEOUT)
	printf_unfiltered ("Read '%c' %d 0x%x\n", ch, ch, ch);
      else
	printf_unfiltered ("Timed out in read\n");
    }

  /* If we have seen mips_monitor_prompt and we either time out, or
     we see a @ (which was echoed from a packet we sent), reset the
     board as described above.  The first character in a packet after
     the SYN (which is not echoed) is always an @ unless the packet is
     more than 64 characters long, which ours never are.  */
  if ((ch == SERIAL_TIMEOUT || ch == '@')
      && state == mips_monitor_prompt_len
      && ! mips_initializing
      && ! mips_exiting)
    {
      if (remote_debug > 0)
	/* Don't use _filtered; we can't deal with a QUIT out of
	   target_wait, and I think this might be called from there.  */
	printf_unfiltered ("Reinitializing MIPS debugging mode\n");

      mips_need_reply = 0;
      mips_initialize ();

      state = 0;

      /* At this point, about the only thing we can do is abort the command
	 in progress and get back to command level as quickly as possible. */

      error ("Remote board reset, debug protocol re-initialized.");
    }

  if (ch == mips_monitor_prompt[state])
    ++state;
  else
    state = 0;

  return ch;
}

/* Get a packet header, putting the data in the supplied buffer.
   PGARBAGE is a pointer to the number of garbage characters received
   so far.  CH is the last character received.  Returns 0 for success,
   or -1 for timeout.  */

static int
mips_receive_header (hdr, pgarbage, ch, timeout)
     unsigned char *hdr;
     int *pgarbage;
     int ch;
     int timeout;
{
  int i;

  while (1)
    {
      /* Wait for a SYN.  mips_syn_garbage is intended to prevent
	 sitting here indefinitely if the board sends us one garbage
	 character per second.  ch may already have a value from the
	 last time through the loop.  */
      while (ch != SYN)
	{
	  ch = mips_readchar (timeout);
	  if (ch == SERIAL_TIMEOUT)
           return -1;
	  if (ch != SYN)
	    {
	      /* Printing the character here lets the user of gdb see
		 what the program is outputting, if the debugging is
		 being done on the console port.  Don't use _filtered;
		 we can't deal with a QUIT out of target_wait.  */
	      if (! mips_initializing || remote_debug > 0)
		{
		  putc_readable (ch);
		  gdb_flush (gdb_stdout);
		}

	      ++*pgarbage;
	      if (mips_syn_garbage > 0
		  && *pgarbage > mips_syn_garbage)
		mips_error ("Debug protocol failure:  more than %d characters before a sync.", 
			    mips_syn_garbage);
	    }
	}

      /* Get the packet header following the SYN.  */
      for (i = 1; i < HDR_LENGTH; i++)
	{
	  ch = mips_readchar (timeout);
	  if (ch == SERIAL_TIMEOUT)
            return -1;
	  /* Make sure this is a header byte.  */
	  if (ch == SYN || ! HDR_CHECK (ch))
	    break;

	  hdr[i] = ch;
	}

      /* If we got the complete header, we can return.  Otherwise we
	 loop around and keep looking for SYN.  */
      if (i >= HDR_LENGTH)
        return 0;
    }
}

/* Get a packet header, putting the data in the supplied buffer.
   PGARBAGE is a pointer to the number of garbage characters received
   so far.  The last character read is returned in *PCH.  Returns 0
   for success, -1 for timeout, -2 for error.  */

static int
mips_receive_trailer (trlr, pgarbage, pch, timeout)
     unsigned char *trlr;
     int *pgarbage;
     int *pch;
     int timeout;
{
  int i;
  int ch;

  for (i = 0; i < TRLR_LENGTH; i++)
    {
      ch = mips_readchar (timeout);
      *pch = ch;
      if (ch == SERIAL_TIMEOUT)
	return -1;
      if (! TRLR_CHECK (ch))
	return -2;
      trlr[i] = ch;
    }
  return 0;
}

/* Get the checksum of a packet.  HDR points to the packet header.
   DATA points to the packet data.  LEN is the length of DATA.  */

static int
mips_cksum (hdr, data, len)
     const unsigned char *hdr;
     const unsigned char *data;
     int len;
{
  register const unsigned char *p;
  register int c;
  register int cksum;

  cksum = 0;

  /* The initial SYN is not included in the checksum.  */
  c = HDR_LENGTH - 1;
  p = hdr + 1;
  while (c-- != 0)
    cksum += *p++;
  
  c = len;
  p = data;
  while (c-- != 0)
    cksum += *p++;

  return cksum;
}

/* Send a packet containing the given ASCII string.  */

static void
mips_send_packet (s, get_ack)
     const char *s;
     int get_ack;
{
  /* unsigned */ int len;
  unsigned char *packet;
  register int cksum;
  int try;

  len = strlen (s);
  if (len > DATA_MAXLEN)
    mips_error ("MIPS protocol data packet too long: %s", s);

  packet = (unsigned char *) alloca (HDR_LENGTH + len + TRLR_LENGTH + 1);

  packet[HDR_INDX_SYN] = HDR_SET_SYN (1, len, mips_send_seq);
  packet[HDR_INDX_TYPE_LEN] = HDR_SET_TYPE_LEN (1, len, mips_send_seq);
  packet[HDR_INDX_LEN1] = HDR_SET_LEN1 (1, len, mips_send_seq);
  packet[HDR_INDX_SEQ] = HDR_SET_SEQ (1, len, mips_send_seq);

  memcpy (packet + HDR_LENGTH, s, len);

  cksum = mips_cksum (packet, packet + HDR_LENGTH, len);
  packet[HDR_LENGTH + len + TRLR_INDX_CSUM1] = TRLR_SET_CSUM1 (cksum);
  packet[HDR_LENGTH + len + TRLR_INDX_CSUM2] = TRLR_SET_CSUM2 (cksum);
  packet[HDR_LENGTH + len + TRLR_INDX_CSUM3] = TRLR_SET_CSUM3 (cksum);

  /* Increment the sequence number.  This will set mips_send_seq to
     the sequence number we expect in the acknowledgement.  */
  mips_send_seq = (mips_send_seq + 1) % SEQ_MODULOS;

  /* We can only have one outstanding data packet, so we just wait for
     the acknowledgement here.  Keep retransmitting the packet until
     we get one, or until we've tried too many times.  */
  for (try = 0; try < mips_send_retries; try++)
    {
      int garbage;
      int ch;

      if (remote_debug > 0)
	{
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  packet[HDR_LENGTH + len + TRLR_LENGTH] = '\0';
	  printf_unfiltered ("Writing \"%s\"\n", packet + 1);
	}

      if (SERIAL_WRITE (mips_desc, packet,
			HDR_LENGTH + len + TRLR_LENGTH) != 0)
	mips_error ("write to target failed: %s", safe_strerror (errno));

      if (! get_ack)
	return;

      garbage = 0;
      ch = 0;
      while (1)
	{
	  unsigned char hdr[HDR_LENGTH + 1];
	  unsigned char trlr[TRLR_LENGTH + 1];
	  int err;
	  unsigned int seq;

	  /* Get the packet header.  If we time out, resend the data
	     packet.  */
	  err = mips_receive_header (hdr, &garbage, ch, mips_retransmit_wait);
	  if (err != 0)
	    break;

	  ch = 0;

	  /* If we get a data packet, assume it is a duplicate and
	     ignore it.  FIXME: If the acknowledgement is lost, this
	     data packet may be the packet the remote sends after the
	     acknowledgement.  */
	  if (HDR_IS_DATA (hdr)) {
            int i;

            /* Ignore any errors raised whilst attempting to ignore
               packet. */

            len = HDR_GET_LEN (hdr);

            for (i = 0; i < len; i++)
              {
                int rch;

                rch = mips_readchar (2);
                if (rch == SYN)
                  {
                    ch = SYN;
                    break;
                  }
                if (rch == SERIAL_TIMEOUT)
                  break;
                /* ignore the character */
              }

            if (i == len)
              (void) mips_receive_trailer (trlr, &garbage, &ch, 2);

            /* We don't bother checking the checksum, or providing an
               ACK to the packet. */
	    continue;
          }

	  /* If the length is not 0, this is a garbled packet.  */
	  if (HDR_GET_LEN (hdr) != 0)
	    continue;

	  /* Get the packet trailer.  */
	  err = mips_receive_trailer (trlr, &garbage, &ch,
				      mips_retransmit_wait);

	  /* If we timed out, resend the data packet.  */
	  if (err == -1)
	    break;

	  /* If we got a bad character, reread the header.  */
	  if (err != 0)
	    continue;

	  /* If the checksum does not match the trailer checksum, this
	     is a bad packet; ignore it.  */
	  if (mips_cksum (hdr, (unsigned char *) NULL, 0)
	      != TRLR_GET_CKSUM (trlr))
	    continue;

	  if (remote_debug > 0)
	    {
	      hdr[HDR_LENGTH] = '\0';
	      trlr[TRLR_LENGTH] = '\0';
	      /* Don't use _filtered; we can't deal with a QUIT out of
		 target_wait, and I think this might be called from there.  */
	      printf_unfiltered ("Got ack %d \"%s%s\"\n",
			       HDR_GET_SEQ (hdr), hdr + 1, trlr);
	    }

	  /* If this ack is for the current packet, we're done.  */
	  seq = HDR_GET_SEQ (hdr);
	  if (seq == mips_send_seq)
	    return;

	  /* If this ack is for the last packet, resend the current
	     packet.  */
	  if ((seq + 1) % SEQ_MODULOS == mips_send_seq)
	    break;

	  /* Otherwise this is a bad ack; ignore it.  Increment the
	     garbage count to ensure that we do not stay in this loop
	     forever.  */
	  ++garbage;
	}
    }

  mips_error ("Remote did not acknowledge packet");
}

/* Receive and acknowledge a packet, returning the data in BUFF (which
   should be DATA_MAXLEN + 1 bytes).  The protocol documentation
   implies that only the sender retransmits packets, so this code just
   waits silently for a packet.  It returns the length of the received
   packet.  If THROW_ERROR is nonzero, call error() on errors.  If not,
   don't print an error message and return -1.  */

static int
mips_receive_packet (buff, throw_error, timeout)
     char *buff;
     int throw_error;
     int timeout;
{
  int ch;
  int garbage;
  int len;
  unsigned char ack[HDR_LENGTH + TRLR_LENGTH + 1];
  int cksum;

  ch = 0;
  garbage = 0;
  while (1)
    {
      unsigned char hdr[HDR_LENGTH];
      unsigned char trlr[TRLR_LENGTH];
      int i;
      int err;

      if (mips_receive_header (hdr, &garbage, ch, timeout) != 0)
	{
	  if (throw_error)
	    mips_error ("Timed out waiting for remote packet");
	  else
	    return -1;
	}

      ch = 0;

      /* An acknowledgement is probably a duplicate; ignore it.  */
      if (! HDR_IS_DATA (hdr))
	{
          len = HDR_GET_LEN (hdr);
          /* Check if the length is valid for an ACK, we may aswell
             try and read the remainder of the packet: */
          if (len == 0)
            {
              /* Ignore the error condition, since we are going to
                 ignore the packet anyway. */
              (void) mips_receive_trailer (trlr, &garbage, &ch, timeout);
            }
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    printf_unfiltered ("Ignoring unexpected ACK\n");
	  continue;
	}

      len = HDR_GET_LEN (hdr);
      for (i = 0; i < len; i++)
	{
	  int rch;

	  rch = mips_readchar (timeout);
	  if (rch == SYN)
	    {
	      ch = SYN;
	      break;
	    }
	  if (rch == SERIAL_TIMEOUT)
	    {
	      if (throw_error)
		mips_error ("Timed out waiting for remote packet");
	      else
		return -1;
	    }
	  buff[i] = rch;
	}

      if (i < len)
	{
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    printf_unfiltered ("Got new SYN after %d chars (wanted %d)\n",
			     i, len);
	  continue;
	}

      err = mips_receive_trailer (trlr, &garbage, &ch, timeout);
      if (err == -1)
	{
	  if (throw_error)
	    mips_error ("Timed out waiting for packet");
	  else
	    return -1;
	}
      if (err == -2)
	{
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    printf_unfiltered ("Got SYN when wanted trailer\n");
	  continue;
	}

      /* If this is the wrong sequence number, ignore it.  */
      if (HDR_GET_SEQ (hdr) != mips_receive_seq)
	{
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  if (remote_debug > 0)
	    printf_unfiltered ("Ignoring sequence number %d (want %d)\n",
			     HDR_GET_SEQ (hdr), mips_receive_seq);
	  continue;
	}

      if (mips_cksum (hdr, buff, len) == TRLR_GET_CKSUM (trlr))
        break;

      if (remote_debug > 0)
	/* Don't use _filtered; we can't deal with a QUIT out of
	   target_wait, and I think this might be called from there.  */
	printf_unfiltered ("Bad checksum; data %d, trailer %d\n",
			 mips_cksum (hdr, buff, len),
			 TRLR_GET_CKSUM (trlr));

      /* The checksum failed.  Send an acknowledgement for the
	 previous packet to tell the remote to resend the packet.  */
      ack[HDR_INDX_SYN] = HDR_SET_SYN (0, 0, mips_receive_seq);
      ack[HDR_INDX_TYPE_LEN] = HDR_SET_TYPE_LEN (0, 0, mips_receive_seq);
      ack[HDR_INDX_LEN1] = HDR_SET_LEN1 (0, 0, mips_receive_seq);
      ack[HDR_INDX_SEQ] = HDR_SET_SEQ (0, 0, mips_receive_seq);

      cksum = mips_cksum (ack, (unsigned char *) NULL, 0);

      ack[HDR_LENGTH + TRLR_INDX_CSUM1] = TRLR_SET_CSUM1 (cksum);
      ack[HDR_LENGTH + TRLR_INDX_CSUM2] = TRLR_SET_CSUM2 (cksum);
      ack[HDR_LENGTH + TRLR_INDX_CSUM3] = TRLR_SET_CSUM3 (cksum);

      if (remote_debug > 0)
	{
	  ack[HDR_LENGTH + TRLR_LENGTH] = '\0';
	  /* Don't use _filtered; we can't deal with a QUIT out of
	     target_wait, and I think this might be called from there.  */
	  printf_unfiltered ("Writing ack %d \"%s\"\n", mips_receive_seq,
			   ack + 1);
	}

      if (SERIAL_WRITE (mips_desc, ack, HDR_LENGTH + TRLR_LENGTH) != 0)
	{
	  if (throw_error)
	    mips_error ("write to target failed: %s", safe_strerror (errno));
	  else
	    return -1;
	}
    }

  if (remote_debug > 0)
    {
      buff[len] = '\0';
      /* Don't use _filtered; we can't deal with a QUIT out of
	 target_wait, and I think this might be called from there.  */
      printf_unfiltered ("Got packet \"%s\"\n", buff);
    }

  /* We got the packet.  Send an acknowledgement.  */
  mips_receive_seq = (mips_receive_seq + 1) % SEQ_MODULOS;

  ack[HDR_INDX_SYN] = HDR_SET_SYN (0, 0, mips_receive_seq);
  ack[HDR_INDX_TYPE_LEN] = HDR_SET_TYPE_LEN (0, 0, mips_receive_seq);
  ack[HDR_INDX_LEN1] = HDR_SET_LEN1 (0, 0, mips_receive_seq);
  ack[HDR_INDX_SEQ] = HDR_SET_SEQ (0, 0, mips_receive_seq);

  cksum = mips_cksum (ack, (unsigned char *) NULL, 0);

  ack[HDR_LENGTH + TRLR_INDX_CSUM1] = TRLR_SET_CSUM1 (cksum);
  ack[HDR_LENGTH + TRLR_INDX_CSUM2] = TRLR_SET_CSUM2 (cksum);
  ack[HDR_LENGTH + TRLR_INDX_CSUM3] = TRLR_SET_CSUM3 (cksum);

  if (remote_debug > 0)
    {
      ack[HDR_LENGTH + TRLR_LENGTH] = '\0';
      /* Don't use _filtered; we can't deal with a QUIT out of
	 target_wait, and I think this might be called from there.  */
      printf_unfiltered ("Writing ack %d \"%s\"\n", mips_receive_seq,
		       ack + 1);
    }

  if (SERIAL_WRITE (mips_desc, ack, HDR_LENGTH + TRLR_LENGTH) != 0)
    {
      if (throw_error)
	mips_error ("write to target failed: %s", safe_strerror (errno));
      else
	return -1;
    }

  return len;
}

/* Optionally send a request to the remote system and optionally wait
   for the reply.  This implements the remote debugging protocol,
   which is built on top of the packet protocol defined above.  Each
   request has an ADDR argument and a DATA argument.  The following
   requests are defined:

   \0	don't send a request; just wait for a reply
   i	read word from instruction space at ADDR
   d	read word from data space at ADDR
   I	write DATA to instruction space at ADDR
   D	write DATA to data space at ADDR
   r	read register number ADDR
   R	set register number ADDR to value DATA
   c	continue execution (if ADDR != 1, set pc to ADDR)
   s	single step (if ADDR != 1, set pc to ADDR)

   The read requests return the value requested.  The write requests
   return the previous value in the changed location.  The execution
   requests return a UNIX wait value (the approximate signal which
   caused execution to stop is in the upper eight bits).

   If PERR is not NULL, this function waits for a reply.  If an error
   occurs, it sets *PERR to 1 and sets errno according to what the
   target board reports.  */

static CORE_ADDR 
mips_request (cmd, addr, data, perr, timeout, buff)
     int cmd;
     CORE_ADDR addr;
     CORE_ADDR data;
     int *perr;
     int timeout;
     char *buff;
{
  char myBuff[DATA_MAXLEN + 1];
  int len;
  int rpid;
  char rcmd;
  int rerrflg;
  int rresponse;

  if (buff == (char *) NULL)
    buff = myBuff;

  if (cmd != '\0')
    {
      if (mips_need_reply)
	fatal ("mips_request: Trying to send command before reply");
      sprintf (buff, "0x0 %c 0x%s 0x%s", cmd, paddr_nz (addr), paddr_nz (data));
      mips_send_packet (buff, 1);
      mips_need_reply = 1;
    }

  if (perr == (int *) NULL)
    return 0;

  if (! mips_need_reply)
    fatal ("mips_request: Trying to get reply before command");

  mips_need_reply = 0;

  len = mips_receive_packet (buff, 1, timeout);
  buff[len] = '\0';

  if (sscanf (buff, "0x%x %c 0x%x 0x%x",
	      &rpid, &rcmd, &rerrflg, &rresponse) != 4
      || (cmd != '\0' && rcmd != cmd))
    mips_error ("Bad response from remote board");

  if (rerrflg != 0)
    {
      *perr = 1;

      /* FIXME: This will returns MIPS errno numbers, which may or may
	 not be the same as errno values used on other systems.  If
	 they stick to common errno values, they will be the same, but
	 if they don't, they must be translated.  */
      errno = rresponse;

      return 0;
    }

  *perr = 0;
  return rresponse;
}

static void
mips_initialize_cleanups (arg)
     PTR arg;
{
  mips_initializing = 0;
}

static void
mips_exit_cleanups (arg)
     PTR arg;
{
  mips_exiting = 0;
}

static void
mips_send_command (cmd, prompt)
     const char *cmd;
     int prompt;
{
  SERIAL_WRITE (mips_desc, cmd, strlen(cmd));
  mips_expect (cmd);
  mips_expect ("\n");
  if (prompt)
    mips_expect (mips_monitor_prompt);
}

/* Enter remote (dbx) debug mode: */
static void
mips_enter_debug ()
{
  /* Reset the sequence numbers, ready for the new debug sequence: */
  mips_send_seq = 0;
  mips_receive_seq = 0;

  if (mips_monitor != MON_IDT)
    mips_send_command ("debug\r", 0);
  else /* assume IDT monitor by default */
    mips_send_command ("db tty0\r", 0);

  SERIAL_WRITE (mips_desc, "\r", sizeof "\r" - 1);

  /* We don't need to absorb any spurious characters here, since the
     mips_receive_header will eat up a reasonable number of characters
     whilst looking for the SYN, however this avoids the "garbage"
     being displayed to the user. */
  if (mips_monitor != MON_IDT)
    mips_expect ("\r");
  
  {
    char buff[DATA_MAXLEN + 1];
    if (mips_receive_packet (buff, 1, 3) < 0)
      mips_error ("Failed to initialize (didn't receive packet).");
  }
}

/* Exit remote (dbx) debug mode, returning to the monitor prompt: */
static int
mips_exit_debug ()
{
  int err;
  struct cleanup *old_cleanups = make_cleanup (mips_exit_cleanups, NULL);

  mips_exiting = 1;

  if (mips_monitor != MON_IDT)
    {
      /* The DDB (NEC) and MiniRISC (LSI) versions of PMON exit immediately,
         so we do not get a reply to this command: */
      mips_request ('x', (unsigned int) 0, (unsigned int) 0, NULL,
		mips_receive_wait, NULL);
      mips_need_reply = 0;
      if (!mips_expect (" break!"))
        return -1;
    }
  else
    mips_request ('x', (unsigned int) 0, (unsigned int) 0, &err,
                  mips_receive_wait, NULL);

  if (mips_monitor == MON_IDT && !mips_expect ("Exiting remote debug"))
    return -1;
    
  if (mips_monitor == MON_DDB)
    {
      if (!mips_expect ("\n"))
        return -1;
    }
  else
    if (!mips_expect ("\r\n"))
      return -1;

  if (!mips_expect (mips_monitor_prompt))
    return -1;

  do_cleanups (old_cleanups);

  return 0;
}

/* Initialize a new connection to the MIPS board, and make sure we are
   really connected.  */

static void
mips_initialize ()
{
  int err;
  struct cleanup *old_cleanups = make_cleanup (mips_initialize_cleanups, NULL);
  int j;

  /* What is this code doing here?  I don't see any way it can happen, and
     it might mean mips_initializing didn't get cleared properly.
     So I'll make it a warning.  */

  if (mips_initializing)
    {
      warning ("internal error: mips_initialize called twice");
      return;
    }

  mips_wait_flag = 0;
  mips_initializing = 1;

  /* At this point, the packit protocol isn't responding.  We'll try getting
     into the monitor, and restarting the protocol.  */

  /* Force the system into the monitor.  After this we *should* be at
     the mips_monitor_prompt.  */
  if (mips_monitor != MON_IDT)
    j = 0; /* start by checking if we are already at the prompt */
  else
    j = 1; /* start by sending a break */
  for (; j <= 4; j++)
    {
      switch (j)
	{
        case 0:                 /* First, try sending a CR */
          SERIAL_FLUSH_INPUT (mips_desc);
	  SERIAL_WRITE (mips_desc, "\r", 1);
          break;
	case 1:			/* First, try sending a break */
	  SERIAL_SEND_BREAK (mips_desc);
	  break;
	case 2:			/* Then, try a ^C */
	  SERIAL_WRITE (mips_desc, "\003", 1);
	  break;
	case 3:			/* Then, try escaping from download */
	  {
            if (mips_monitor != MON_IDT)
              {
                char tbuff[7];

                /* We shouldn't need to send multiple termination
                   sequences, since the target performs line (or
                   block) reads, and then processes those
                   packets. In-case we were downloading a large packet
                   we flush the output buffer before inserting a
                   termination sequence. */
                SERIAL_FLUSH_OUTPUT (mips_desc);
                sprintf (tbuff, "\r/E/E\r");
                SERIAL_WRITE (mips_desc, tbuff, 6);
              }
            else
              {
                char srec[10];
                int i;

                /* We are possibly in binary download mode, having
                   aborted in the middle of an S-record.  ^C won't
                   work because of binary mode.  The only reliable way
                   out is to send enough termination packets (8 bytes)
                   to fill up and then overflow the largest size
                   S-record (255 bytes in this case).  This amounts to
                   256/8 + 1 packets.
                   */

                mips_make_srec (srec, '7', 0, NULL, 0);

                for (i = 1; i <= 33; i++)
                  {
                    SERIAL_WRITE (mips_desc, srec, 8);

                    if (SERIAL_READCHAR (mips_desc, 0) >= 0)
                      break;	/* Break immediatly if we get something from
				   the board. */
                  }
              }
          }
	  break;
	case 4:
	  mips_error ("Failed to initialize.");
	}

      if (mips_expect (mips_monitor_prompt))
	break;
    }

  if (mips_monitor != MON_IDT)
    {
      /* Ensure the correct target state: */
      if (mips_monitor != MON_LSI)
	mips_send_command ("set regsize 64\r", -1);
      mips_send_command ("set hostport tty0\r", -1);
      mips_send_command ("set brkcmd \"\"\r", -1);
      /* Delete all the current breakpoints: */
      mips_send_command ("db *\r", -1);
      /* NOTE: PMON does not have breakpoint support through the
         "debug" mode, only at the monitor command-line. */
    }

  mips_enter_debug ();

  /* Clear all breakpoints: */
  if (mips_monitor == MON_IDT && common_breakpoint ('b', -1, 0, NULL) == 0)
    monitor_supports_breakpoints = 1;
  else
    monitor_supports_breakpoints = 0;

  do_cleanups (old_cleanups);

  /* If this doesn't call error, we have connected; we don't care if
     the request itself succeeds or fails.  */

  mips_request ('r', (unsigned int) 0, (unsigned int) 0, &err,
		mips_receive_wait, NULL);
  set_current_frame (create_new_frame (read_fp (), read_pc ()));
  select_frame (get_current_frame (), 0);
}

/* Open a connection to the remote board.  */
static void
common_open (ops, name, from_tty, new_monitor, new_monitor_prompt)
     struct target_ops *ops;
     char *name;
     int from_tty;
     enum mips_monitor_type new_monitor;
     char *new_monitor_prompt;
{
  char *ptype;
  char *serial_port_name;
  char *remote_name = 0;
  char *local_name = 0;
  char **argv;

  if (name == 0)
    error (
"To open a MIPS remote debugging connection, you need to specify what serial\n\
device is attached to the target board (e.g., /dev/ttya).\n"
"If you want to use TFTP to download to the board, specify the name of a\n"
"temporary file to be used by GDB for downloads as the second argument.\n"
"This filename must be in the form host:filename, where host is the name\n"
"of the host running the TFTP server, and the file must be readable by the\n"
"world.  If the local name of the temporary file differs from the name as\n"
"seen from the board via TFTP, specify that name as the third parameter.\n");

  /* Parse the serial port name, the optional TFTP name, and the
     optional local TFTP name.  */
  if ((argv = buildargv (name)) == NULL)
    nomem(0);
  make_cleanup (freeargv, (char *) argv);

  serial_port_name = strsave (argv[0]);
  if (argv[1])				/* remote TFTP name specified? */
    {
      remote_name = argv[1];
      if (argv[2])			/* local TFTP filename specified? */
	local_name = argv[2];
    }

  target_preopen (from_tty);

  if (mips_is_open)
    unpush_target (current_ops);

  /* Open and initialize the serial port.  */
  mips_desc = SERIAL_OPEN (serial_port_name);
  if (mips_desc == (serial_t) NULL)
    perror_with_name (serial_port_name);

  if (baud_rate != -1)
    {
      if (SERIAL_SETBAUDRATE (mips_desc, baud_rate))
        {
          SERIAL_CLOSE (mips_desc);
          perror_with_name (serial_port_name);
        }
    }

  SERIAL_RAW (mips_desc);

  /* Open and initialize the optional download port.  If it is in the form
     hostname#portnumber, it's a UDP socket.  If it is in the form
     hostname:filename, assume it's the TFTP filename that must be
     passed to the DDB board to tell it where to get the load file.  */
  if (remote_name)
    {
      if (strchr (remote_name, '#'))
	{
	  udp_desc = SERIAL_OPEN (remote_name);
	  if (!udp_desc)
	    perror_with_name ("Unable to open UDP port");
	  udp_in_use = 1;
	}
      else
	{
	  /* Save the remote and local names of the TFTP temp file.  If
	     the user didn't specify a local name, assume it's the same
	     as the part of the remote name after the "host:".  */
	  if (tftp_name)
	    free (tftp_name);
	  if (tftp_localname)
	    free (tftp_localname);
	  if (local_name == NULL)
	      if ((local_name = strchr (remote_name, ':')) != NULL)
		local_name++;		/* skip over the colon */
	  if (local_name == NULL)
	    local_name = remote_name;	/* local name same as remote name */
	  tftp_name = strsave (remote_name);
	  tftp_localname = strsave (local_name);
	  tftp_in_use = 1;
	}
    }

  current_ops = ops;
  mips_is_open = 1;

  /* Reset the expected monitor prompt if it's never been set before.  */
  if (mips_monitor_prompt == NULL)
    mips_monitor_prompt = strsave (new_monitor_prompt);
  mips_monitor = new_monitor;

  mips_initialize ();

  if (from_tty)
    printf_unfiltered ("Remote MIPS debugging using %s\n", serial_port_name);

  /* Switch to using remote target now.  */
  push_target (ops);

  /* FIXME: Should we call start_remote here?  */

  /* Try to figure out the processor model if possible.  */
  ptype = mips_read_processor_type ();
  if (ptype)
    mips_set_processor_type_command (strsave (ptype), 0);

/* This is really the job of start_remote however, that makes an assumption
   that the target is about to print out a status message of some sort.  That
   doesn't happen here (in fact, it may not be possible to get the monitor to
   send the appropriate packet).  */

  flush_cached_frames ();
  registers_changed ();
  stop_pc = read_pc ();
  set_current_frame (create_new_frame (read_fp (), stop_pc));
  select_frame (get_current_frame (), 0);
  print_stack_frame (selected_frame, -1, 1);
  free (serial_port_name);
}

static void
mips_open (name, from_tty)
     char *name;
     int from_tty;
{
  common_open (&mips_ops, name, from_tty, MON_IDT, TARGET_MONITOR_PROMPT);
}

static void
pmon_open (name, from_tty)
     char *name;
     int from_tty;
{
  common_open (&pmon_ops, name, from_tty, MON_PMON, "PMON> ");
}

static void
ddb_open (name, from_tty)
     char *name;
     int from_tty;
{
  common_open (&ddb_ops, name, from_tty, MON_DDB, "NEC010>");
}

static void
lsi_open (name, from_tty)
     char *name;
     int from_tty;
{
  common_open (&ddb_ops, name, from_tty, MON_LSI, "PMON> ");
}

/* Close a connection to the remote board.  */

static void
mips_close (quitting)
     int quitting;
{
  if (mips_is_open)
    {
      /* Get the board out of remote debugging mode.  */
      (void) mips_exit_debug ();

      close_ports ();
    }
}

/* Detach from the remote board.  */

static void
mips_detach (args, from_tty)
     char *args;
     int from_tty;
{
  if (args)
    error ("Argument given to \"detach\" when remotely debugging.");

  pop_target ();

  mips_close (1);

  if (from_tty)
    printf_unfiltered ("Ending remote MIPS debugging.\n");
}

/* Tell the target board to resume.  This does not wait for a reply
   from the board.  */

static void
mips_resume (pid, step, siggnal)
     int pid, step;
     enum target_signal siggnal;
{
  int err;


  /* LSI PMON requires returns a reply packet "0x1 s 0x0 0x57f" after
     a single step, so we wait for that.  */
  mips_request (step ? 's' : 'c',
		(unsigned int) 1,
		(unsigned int) siggnal,
		mips_monitor == MON_LSI && step ? &err : (int *) NULL,
		mips_receive_wait, NULL);
}

/* Return the signal corresponding to SIG, where SIG is the number which
   the MIPS protocol uses for the signal.  */
enum target_signal
mips_signal_from_protocol (sig)
     int sig;
{
  /* We allow a few more signals than the IDT board actually returns, on
     the theory that there is at least *some* hope that perhaps the numbering
     for these signals is widely agreed upon.  */
  if (sig <= 0
      || sig > 31)
    return TARGET_SIGNAL_UNKNOWN;

  /* Don't want to use target_signal_from_host because we are converting
     from MIPS signal numbers, not host ones.  Our internal numbers
     match the MIPS numbers for the signals the board can return, which
     are: SIGINT, SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGTRAP.  */
  return (enum target_signal) sig;
}

/* Wait until the remote stops, and return a wait status.  */

static int
mips_wait (pid, status)
     int pid;
     struct target_waitstatus *status;
{
  int rstatus;
  int err;
  char buff[DATA_MAXLEN];
  int rpc, rfp, rsp;
  char flags[20];
  int nfields;

  interrupt_count = 0;
  hit_watchpoint = 0;

  /* If we have not sent a single step or continue command, then the
     board is waiting for us to do something.  Return a status
     indicating that it is stopped.  */
  if (! mips_need_reply)
    {
      status->kind = TARGET_WAITKIND_STOPPED;
      status->value.sig = TARGET_SIGNAL_TRAP;
      return 0;
    }

  /* No timeout; we sit here as long as the program continues to execute.  */
  mips_wait_flag = 1;
  rstatus = mips_request ('\000', (unsigned int) 0, (unsigned int) 0, &err, -1,
			  buff);
  mips_wait_flag = 0;
  if (err)
    mips_error ("Remote failure: %s", safe_strerror (errno));

  nfields = sscanf (buff, "0x%*x %*c 0x%*x 0x%*x 0x%x 0x%x 0x%x 0x%*x %s",
		    &rpc, &rfp, &rsp, flags);

  /* See if we got back extended status.  If so, pick out the pc, fp, sp, etc... */

  if (nfields == 7 || nfields == 9) 
    {
      char buf[MAX_REGISTER_RAW_SIZE];

      store_unsigned_integer (buf, REGISTER_RAW_SIZE (PC_REGNUM), rpc);
      supply_register (PC_REGNUM, buf);

      store_unsigned_integer (buf, REGISTER_RAW_SIZE (PC_REGNUM), rfp);
      supply_register (30, buf); /* This register they are avoiding and so it is unnamed */

      store_unsigned_integer (buf, REGISTER_RAW_SIZE (SP_REGNUM), rsp);
      supply_register (SP_REGNUM, buf);

      store_unsigned_integer (buf, REGISTER_RAW_SIZE (FP_REGNUM), 0);
      supply_register (FP_REGNUM, buf);

      if (nfields == 9)
	{
	  int i;

	  for (i = 0; i <= 2; i++)
	    if (flags[i] == 'r' || flags[i] == 'w')
	      hit_watchpoint = 1;
	    else if (flags[i] == '\000')
	      break;
	}
    }

  /* Translate a MIPS waitstatus.  We use constants here rather than WTERMSIG
     and so on, because the constants we want here are determined by the
     MIPS protocol and have nothing to do with what host we are running on.  */
  if ((rstatus & 0377) == 0)
    {
      status->kind = TARGET_WAITKIND_EXITED;
      status->value.integer = (((rstatus) >> 8) & 0377);
    }
  else if ((rstatus & 0377) == 0177)
    {
      status->kind = TARGET_WAITKIND_STOPPED;
      status->value.sig = mips_signal_from_protocol (((rstatus) >> 8) & 0377);
    }
  else
    {
      status->kind = TARGET_WAITKIND_SIGNALLED;
      status->value.sig = mips_signal_from_protocol (rstatus & 0177);
    }

  return 0;
}

static int
pmon_wait (pid, status)
     int pid;
     struct target_waitstatus *status;
{
  int rstatus;
  int err;
  char buff[DATA_MAXLEN];

  interrupt_count = 0;
  hit_watchpoint = 0;

  /* If we have not sent a single step or continue command, then the
     board is waiting for us to do something.  Return a status
     indicating that it is stopped.  */
  if (! mips_need_reply)
    {
      status->kind = TARGET_WAITKIND_STOPPED;
      status->value.sig = TARGET_SIGNAL_TRAP;
      return 0;
    }

  /* Sit, polling the serial until the target decides to talk to
     us. NOTE: the timeout value we use is used not just for the
     first character, but for all the characters. */
  mips_wait_flag = 1;
  rstatus = mips_request ('\000', (unsigned int) 0, (unsigned int) 0, &err, -1,
			  buff);
  mips_wait_flag = 0;
  if (err)
    mips_error ("Remote failure: %s", safe_strerror (errno));

  /* NOTE: The following (sig) numbers are defined by PMON:
     	SPP_SIGTRAP     5       breakpoint
        SPP_SIGINT      2
        SPP_SIGSEGV     11
        SPP_SIGBUS      10
        SPP_SIGILL      4
        SPP_SIGFPE      8
        SPP_SIGTERM     15 */

  /* On returning from a continue, the PMON monitor seems to start
     echoing back the messages we send prior to sending back the
     ACK. The code can cope with this, but to try and avoid the
     unnecessary serial traffic, and "spurious" characters displayed
     to the user, we cheat and reset the debug protocol. The problems
     seems to be caused by a check on the number of arguments, and the
     command length, within the monitor causing it to echo the command
     as a bad packet. */
  if (mips_monitor != MON_DDB && mips_monitor != MON_LSI)
    {
      mips_exit_debug ();
      mips_enter_debug ();
    }

  /* Translate a MIPS waitstatus.  We use constants here rather than WTERMSIG
     and so on, because the constants we want here are determined by the
     MIPS protocol and have nothing to do with what host we are running on.  */
  if ((rstatus & 0377) == 0)
    {
      status->kind = TARGET_WAITKIND_EXITED;
      status->value.integer = (((rstatus) >> 8) & 0377);
    }
  else if ((rstatus & 0377) == 0177)
    {
      status->kind = TARGET_WAITKIND_STOPPED;
      status->value.sig = mips_signal_from_protocol (((rstatus) >> 8) & 0377);
    }
  else
    {
      status->kind = TARGET_WAITKIND_SIGNALLED;
      status->value.sig = mips_signal_from_protocol (rstatus & 0177);
    }

  return 0;
}

/* We have to map between the register numbers used by gdb and the
   register numbers used by the debugging protocol.  This function
   assumes that we are using tm-mips.h.  */

#define REGNO_OFFSET 96

static int
mips_map_regno (regno)
     int regno;
{
  if (regno < 32)
    return regno;
  if (regno >= FP0_REGNUM && regno < FP0_REGNUM + 32)
    return regno - FP0_REGNUM + 32;
  switch (regno)
    {
    case PC_REGNUM:
      return REGNO_OFFSET + 0;
    case CAUSE_REGNUM:
      return REGNO_OFFSET + 1;
    case HI_REGNUM:
      return REGNO_OFFSET + 2;
    case LO_REGNUM:
      return REGNO_OFFSET + 3;
    case FCRCS_REGNUM:
      return REGNO_OFFSET + 4;
    case FCRIR_REGNUM:
      return REGNO_OFFSET + 5;
    default:
      /* FIXME: Is there a way to get the status register?  */
      return 0;
    }
}

/* Fetch the remote registers.  */

static void
mips_fetch_registers (regno)
     int regno;
{
  unsigned LONGEST val;
  int err;

  if (regno == -1)
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	mips_fetch_registers (regno);
      return;
    }

  if (regno == FP_REGNUM || regno == ZERO_REGNUM)
    /* FP_REGNUM on the mips is a hack which is just supposed to read
       zero (see also mips-nat.c).  */
    val = 0;
  else
    {
      /* If PMON doesn't support this register, don't waste serial
         bandwidth trying to read it.  */
      int pmon_reg = mips_map_regno (regno);
      if (regno != 0 && pmon_reg == 0)
	val = 0;
      else
	{
	  /* Unfortunately the PMON version in the Vr4300 board has been
	     compiled without the 64bit register access commands. This
	     means we cannot get hold of the full register width. */
	  if (mips_monitor == MON_DDB)
	    val = (unsigned)mips_request ('t', (unsigned int) pmon_reg,
				(unsigned int) 0, &err, mips_receive_wait, NULL);
	  else
	    val = mips_request ('r', (unsigned int) pmon_reg,
				(unsigned int) 0, &err, mips_receive_wait, NULL);
	  if (err)
	    mips_error ("Can't read register %d: %s", regno,
			safe_strerror (errno));
	}
    }

  {
    char buf[MAX_REGISTER_RAW_SIZE];

    /* We got the number the register holds, but gdb expects to see a
       value in the target byte ordering.  */
    store_unsigned_integer (buf, REGISTER_RAW_SIZE (regno), val);
    supply_register (regno, buf);
  }
}

/* Prepare to store registers.  The MIPS protocol can store individual
   registers, so this function doesn't have to do anything.  */

static void
mips_prepare_to_store ()
{
}

/* Store remote register(s).  */

static void
mips_store_registers (regno)
     int regno;
{
  int err;

  if (regno == -1)
    {
      for (regno = 0; regno < NUM_REGS; regno++)
	mips_store_registers (regno);
      return;
    }

  mips_request ('R', (unsigned int) mips_map_regno (regno),
		read_register (regno),
		&err, mips_receive_wait, NULL);
  if (err)
    mips_error ("Can't write register %d: %s", regno, safe_strerror (errno));
}

/* Fetch a word from the target board.  */

static unsigned int 
mips_fetch_word (addr)
     CORE_ADDR addr;
{
  unsigned int val;
  int err;

  /* FIXME! addr was cast to uint! */
  val = mips_request ('d', addr, (unsigned int) 0, &err,
		      mips_receive_wait, NULL);
  if (err)
    {
      /* Data space failed; try instruction space.  */
      /* FIXME! addr was cast to uint! */
      val = mips_request ('i', addr, (unsigned int) 0, &err,
			  mips_receive_wait, NULL);
      if (err)
        mips_error ("Can't read address 0x%s: %s",
	      paddr_nz (addr), safe_strerror (errno));
    }
  return val;
}

/* Store a word to the target board.  Returns errno code or zero for
   success.  If OLD_CONTENTS is non-NULL, put the old contents of that
   memory location there.  */

/* FIXME! make sure only 32-bit quantities get stored! */
static int
mips_store_word (addr, val, old_contents)
     CORE_ADDR addr;
     unsigned int val;
     char *old_contents;
{
  int err;
  unsigned int oldcontents;

  oldcontents = mips_request ('D', addr, (unsigned int) val,
			      &err,
			      mips_receive_wait, NULL);
  if (err)
    {
      /* Data space failed; try instruction space.  */
      oldcontents = mips_request ('I', addr,
				  (unsigned int) val, &err,
				  mips_receive_wait, NULL);
      if (err)
	return errno;
    }
  if (old_contents != NULL)
    store_unsigned_integer (old_contents, 4, oldcontents);
  return 0;
}

/* Read or write LEN bytes from inferior memory at MEMADDR,
   transferring to or from debugger address MYADDR.  Write to inferior
   if SHOULD_WRITE is nonzero.  Returns length of data written or
   read; 0 for error.  Note that protocol gives us the correct value
   for a longword, since it transfers values in ASCII.  We want the
   byte values, so we have to swap the longword values.  */

static int
mips_xfer_memory (memaddr, myaddr, len, write, ignore)
     CORE_ADDR memaddr;
     char *myaddr;
     int len;
     int write;
     struct target_ops *ignore;
{
  register int i;
  /* Round starting address down to longword boundary.  */
  register CORE_ADDR addr = memaddr &~ 3;
  /* Round ending address up; get number of longwords that makes.  */
  register int count = (((memaddr + len) - addr) + 3) / 4;
  /* Allocate buffer of that many longwords.  */
  register char *buffer = alloca (count * 4);

  int status;

  if (write)
    {
      /* Fill start and end extra bytes of buffer with existing data.  */
      if (addr != memaddr || len < 4)
	{
	  /* Need part of initial word -- fetch it.  */
	  store_unsigned_integer (&buffer[0], 4, mips_fetch_word (addr));
	}

      if (count > 1)
	{
	  /* Need part of last word -- fetch it.  FIXME: we do this even
	     if we don't need it.  */
	  store_unsigned_integer (&buffer[(count - 1) * 4], 4,
				  mips_fetch_word (addr + (count - 1) * 4));
	}

      /* Copy data to be written over corresponding part of buffer */

      memcpy ((char *) buffer + (memaddr & 3), myaddr, len);

      /* Write the entire buffer.  */

      for (i = 0; i < count; i++, addr += 4)
	{
	  status = mips_store_word (addr,
				    extract_unsigned_integer (&buffer[i*4], 4),
				    NULL);
	  /* Report each kilobyte (we download 32-bit words at a time) */
	  if (i % 256 == 255) 
	    {
	      printf_unfiltered ("*");
	      fflush (stdout);
	    }
	  if (status)
	    {
	      errno = status;
	      return 0;
	    }
	  /* FIXME: Do we want a QUIT here?  */
	}
      if (count >= 256)
	printf_unfiltered ("\n");
    }
  else
    {
      /* Read all the longwords */
      for (i = 0; i < count; i++, addr += 4)
	{
	  store_unsigned_integer (&buffer[i*4], 4, mips_fetch_word (addr));
	  QUIT;
	}

      /* Copy appropriate bytes out of the buffer.  */
      memcpy (myaddr, buffer + (memaddr & 3), len);
    }
  return len;
}

/* Print info on this target.  */

static void
mips_files_info (ignore)
     struct target_ops *ignore;
{
  printf_unfiltered ("Debugging a MIPS board over a serial line.\n");
}

/* Kill the process running on the board.  This will actually only
   work if we are doing remote debugging over the console input.  I
   think that if IDT/sim had the remote debug interrupt enabled on the
   right port, we could interrupt the process with a break signal.  */

static void
mips_kill ()
{
  if (!mips_wait_flag)
    return;

  interrupt_count++;

  if (interrupt_count >= 2)
    {
      interrupt_count = 0;

      target_terminal_ours ();

      if (query ("Interrupted while waiting for the program.\n\
Give up (and stop debugging it)? "))
	{
	  /* Clean up in such a way that mips_close won't try to talk to the
	     board (it almost surely won't work since we weren't able to talk to
	     it).  */
	  mips_wait_flag = 0;
	  close_ports();

	  printf_unfiltered ("Ending remote MIPS debugging.\n");
	  target_mourn_inferior ();

	  return_to_top_level (RETURN_QUIT);
	}

      target_terminal_inferior ();
    }

  if (remote_debug > 0)
    printf_unfiltered ("Sending break\n");

  SERIAL_SEND_BREAK (mips_desc);

#if 0
  if (mips_is_open)
    {
      char cc;

      /* Send a ^C.  */
      cc = '\003';
      SERIAL_WRITE (mips_desc, &cc, 1);
      sleep (1);
      target_mourn_inferior ();
    }
#endif
}

/* Start running on the target board.  */

static void
mips_create_inferior (execfile, args, env)
     char *execfile;
     char *args;
     char **env;
{
  CORE_ADDR entry_pt;

  if (args && *args)
    {
      warning ("\
Can't pass arguments to remote MIPS board; arguments ignored.");
      /* And don't try to use them on the next "run" command.  */
      execute_command ("set args", 0);
    }

  if (execfile == 0 || exec_bfd == 0)
    error ("No executable file specified");

  entry_pt = (CORE_ADDR) bfd_get_start_address (exec_bfd);

  init_wait_for_inferior ();

  /* FIXME: Should we set inferior_pid here?  */

  proceed (entry_pt, TARGET_SIGNAL_DEFAULT, 0);
}

/* Clean up after a process.  Actually nothing to do.  */

static void
mips_mourn_inferior ()
{
  if (current_ops != NULL)
    unpush_target (current_ops);
  generic_mourn_inferior ();
}

/* We can write a breakpoint and read the shadow contents in one
   operation.  */

/* The IDT board uses an unusual breakpoint value, and sometimes gets
   confused when it sees the usual MIPS breakpoint instruction.  */

#define BREAK_INSN (0x00000a0d)
#define BREAK_INSN_SIZE (4)

/* Insert a breakpoint on targets that don't have any better breakpoint
   support.  We read the contents of the target location and stash it,
   then overwrite it with a breakpoint instruction.  ADDR is the target
   location in the target machine.  CONTENTS_CACHE is a pointer to 
   memory allocated for saving the target contents.  It is guaranteed
   by the caller to be long enough to save sizeof BREAKPOINT bytes (this
   is accomplished via BREAKPOINT_MAX).  */

static int
mips_insert_breakpoint (addr, contents_cache)
     CORE_ADDR addr;
     char *contents_cache;
{
  if (monitor_supports_breakpoints)
    return common_breakpoint ('B', addr, 0x3, "f");

  return mips_store_word (addr, BREAK_INSN, contents_cache);
}

static int
mips_remove_breakpoint (addr, contents_cache)
     CORE_ADDR addr;
     char *contents_cache;
{
  if (monitor_supports_breakpoints)
    return common_breakpoint ('b', addr, 0, NULL);

  return target_write_memory (addr, contents_cache, BREAK_INSN_SIZE);
}

#if 0 /* currently not used */
/* PMON does not currently provide support for the debug mode 'b'
   commands to manipulate breakpoints. However, if we wanted to use
   the monitor breakpoints (rather than the GDB BREAK_INSN version)
   then this code performs the work needed to leave debug mode,
   set/clear the breakpoint, and then return to debug mode. */

#define PMON_MAX_BP (33) /* 32 SW, 1 HW */
static CORE_ADDR mips_pmon_bp_info[PMON_MAX_BP];
/* NOTE: The code relies on this vector being zero-initialised by the system */

static int
pmon_insert_breakpoint (addr, contents_cache)
     CORE_ADDR addr;
     char *contents_cache;
{
  int status;

  if (monitor_supports_breakpoints)
    {
      char tbuff[12]; /* space for breakpoint command */
      int bpnum;
      CORE_ADDR bpaddr;

      /* PMON does not support debug level breakpoint set/remove: */
      if (mips_exit_debug ())
        mips_error ("Failed to exit debug mode");

      sprintf (tbuff, "b %08x\r", addr);
      mips_send_command (tbuff, 0);

      mips_expect ("Bpt ");

      if (!mips_getstring (tbuff, 2))
        return 1;
      tbuff[2] = '\0'; /* terminate the string */
      if (sscanf (tbuff, "%d", &bpnum) != 1)
        {
          fprintf_unfiltered (stderr, "Invalid decimal breakpoint number from target: %s\n", tbuff);
          return 1;
        }

      mips_expect (" = ");

      /* Lead in the hex number we are expecting: */
      tbuff[0] = '0';
      tbuff[1] = 'x';

      /* FIXME!! only 8 bytes!  need to expand for Bfd64; 
         which targets return 64-bit addresses?  PMON returns only 32! */
      if (!mips_getstring (&tbuff[2], 8))
        return 1;
      tbuff[10] = '\0'; /* terminate the string */

      if (sscanf (tbuff, "0x%08x", &bpaddr) != 1)
        {
          fprintf_unfiltered (stderr, "Invalid hex address from target: %s\n", tbuff);
          return 1;
        }

      if (bpnum >= PMON_MAX_BP)
        {
          fprintf_unfiltered (stderr, "Error: Returned breakpoint number %d outside acceptable range (0..%d)\n",
                              bpnum, PMON_MAX_BP - 1);
          return 1;
        }

      if (bpaddr != addr)
        fprintf_unfiltered (stderr, "Warning: Breakpoint addresses do not match: 0x%x != 0x%x\n", addr, bpaddr);

      mips_pmon_bp_info[bpnum] = bpaddr;

      mips_expect ("\r\n");
      mips_expect (mips_monitor_prompt);

      mips_enter_debug ();

      return 0;
    }

  return mips_store_word (addr, BREAK_INSN, contents_cache);
}

static int
pmon_remove_breakpoint (addr, contents_cache)
     CORE_ADDR addr;
     char *contents_cache;
{
  if (monitor_supports_breakpoints)
    {
      int bpnum;
      char tbuff[7]; /* enough for delete breakpoint command */

      for (bpnum = 0; bpnum < PMON_MAX_BP; bpnum++)
        if (mips_pmon_bp_info[bpnum] == addr)
          break;

      if (bpnum >= PMON_MAX_BP)
        {
          fprintf_unfiltered (stderr,
	    "pmon_remove_breakpoint: Failed to find breakpoint at address 0x%s\n",
	    paddr_nz (addr));
          return 1;
        }

      if (mips_exit_debug ())
        mips_error ("Failed to exit debug mode");

      sprintf (tbuff, "db %02d\r", bpnum);

      mips_send_command (tbuff, -1);
      /* NOTE: If the breakpoint does not exist then a "Bpt <dd> not
         set" message will be returned. */

      mips_enter_debug ();

      return 0;
    }

  return target_write_memory (addr, contents_cache, BREAK_INSN_SIZE);
}
#endif

/* Compute a don't care mask for the region bounding ADDR and ADDR + LEN - 1.
   This is used for memory ref breakpoints.  */

static unsigned long
calculate_mask (addr, len)
     CORE_ADDR addr;
     int len;
{
  unsigned long mask;
  int i;

  mask = addr ^ (addr + len - 1);

  for (i = 32; i >= 0; i--)
    if (mask == 0)
      break;
    else
      mask >>= 1;

  mask = (unsigned long) 0xffffffff >> i;

  return mask;
}

/* Set a data watchpoint.  ADDR and LEN should be obvious.  TYPE is either 1
   for a read watchpoint, or 2 for a read/write watchpoint. */

int
remote_mips_set_watchpoint (addr, len, type)
     CORE_ADDR addr;
     int len;
     int type;
{
  CORE_ADDR first_addr;
  unsigned long mask;
  char *flags;

  mask = calculate_mask (addr, len);

  first_addr = addr & ~mask;

  switch (type)
    {
    case 0:			/* write */
      flags = "w";
      break;
    case 1:			/* read */
      flags = "r";
      break;
    case 2:			/* read/write */
      flags = "rw";
      break;
    default:
      abort ();
    }

  if (common_breakpoint ('B', first_addr, mask, flags))
    return -1;

  return 0;
}

int
remote_mips_remove_watchpoint (addr, len, type)
     CORE_ADDR addr;
     int len;
     int type;
{
  CORE_ADDR first_addr;
  unsigned long mask;

  mask = calculate_mask (addr, len);

  first_addr = addr & ~mask;

  if (common_breakpoint ('b', first_addr, 0, NULL))
    return -1;

  return 0;
}

int
remote_mips_stopped_by_watchpoint ()
{
  return hit_watchpoint;
}

/* This routine generates the a breakpoint command of the form:

   0x0 <CMD> <ADDR> <MASK> <FLAGS>

   Where <CMD> is one of: `B' to set, or `b' to clear a breakpoint.  <ADDR> is
   the address of the breakpoint.  <MASK> is a don't care mask for addresses.
   <FLAGS> is any combination of `r', `w', or `f' for read/write/or fetch.

   Return 0 if successful; otherwise 1.  */

static int
common_breakpoint (cmd, addr, mask, flags)
     int cmd;
     CORE_ADDR addr;
     CORE_ADDR mask;
     char *flags;
{
  int len;
  char buf[DATA_MAXLEN + 1];
  char rcmd;
  int rpid, rerrflg, rresponse;
  int nfields;

  addr = ADDR_BITS_REMOVE (addr);
  if (flags)
    sprintf (buf, "0x0 %c 0x%s 0x%s %s", cmd, paddr_nz (addr), paddr_nz (mask),
	     flags);
  else
    sprintf (buf, "0x0 %c 0x%s", cmd, paddr_nz (addr));

  mips_send_packet (buf, 1);

  len = mips_receive_packet (buf, 1, mips_receive_wait);
  buf[len] = '\0';

  nfields = sscanf (buf, "0x%x %c 0x%x 0x%x", &rpid, &rcmd, &rerrflg, &rresponse);

  if (nfields != 4
      || rcmd != cmd)
    mips_error ("common_breakpoint: Bad response from remote board: %s", buf);

  if (rerrflg != 0)
    {
      /* Ddb returns "0x0 b 0x16 0x0\000", whereas
         Cogent returns "0x0 b 0xffffffff 0x16\000": */
      if (mips_monitor == MON_DDB)
        rresponse = rerrflg;
      if (rresponse != 22) /* invalid argument */
	fprintf_unfiltered (stderr, "common_breakpoint (0x%s):  Got error: 0x%x\n",
			    paddr_nz (addr), rresponse);
      return 1;
    }

  return 0;
}

static void
send_srec (srec, len, addr)
     char *srec;
     int len;
     CORE_ADDR addr;
{
  while (1)
    {
      int ch;

      SERIAL_WRITE (mips_desc, srec, len);

      ch = mips_readchar (2);

      switch (ch)
	{
	case SERIAL_TIMEOUT:
	  error ("Timeout during download.");
	  break;
	case 0x6:		/* ACK */
	  return;
	case 0x15:		/* NACK */
	  fprintf_unfiltered (gdb_stderr, "Download got a NACK at byte %d!  Retrying.\n", addr);
	  continue;
	default:
	  error ("Download got unexpected ack char: 0x%x, retrying.\n", ch);
	}
    }
}

/*  Download a binary file by converting it to S records. */

static void
mips_load_srec (args)
     char *args;
{
  bfd *abfd;
  asection *s;
  char *buffer, srec[1024];
  unsigned int i;
  unsigned int srec_frame = 200;
  int reclen;
  static int hashmark = 1;

  buffer = alloca (srec_frame * 2 + 256);

  abfd = bfd_openr (args, 0);
  if (!abfd)
    {
      printf_filtered ("Unable to open file %s\n", args);
      return;
    }

  if (bfd_check_format (abfd, bfd_object) == 0)
    {
      printf_filtered ("File is not an object file\n");
      return;
    }

/* This actually causes a download in the IDT binary format: */
  mips_send_command (LOAD_CMD, 0);

  for (s = abfd->sections; s; s = s->next)
    {
      if (s->flags & SEC_LOAD)
	{
	  unsigned int numbytes;

	  /* FIXME!  vma too small?? */
	  printf_filtered ("%s\t: 0x%4x .. 0x%4x  ", s->name, s->vma,
			   s->vma + s->_raw_size);
	  gdb_flush (gdb_stdout);

	  for (i = 0; i < s->_raw_size; i += numbytes)
	    {
	      numbytes = min (srec_frame, s->_raw_size - i);

	      bfd_get_section_contents (abfd, s, buffer, i, numbytes);

	      reclen = mips_make_srec (srec, '3', s->vma + i, buffer, numbytes);
	      send_srec (srec, reclen, s->vma + i);

	      if (hashmark)
		{
		  putchar_unfiltered ('#');
		  gdb_flush (gdb_stdout);
		}

	    } /* Per-packet (or S-record) loop */
	  
	  putchar_unfiltered ('\n');
	} /* Loadable sections */
    }
  if (hashmark) 
    putchar_unfiltered ('\n');
  
  /* Write a type 7 terminator record. no data for a type 7, and there
     is no data, so len is 0.  */

  reclen = mips_make_srec (srec, '7', abfd->start_address, NULL, 0);

  send_srec (srec, reclen, abfd->start_address);

  SERIAL_FLUSH_INPUT (mips_desc);
}

/*
 * mips_make_srec -- make an srecord. This writes each line, one at a
 *	time, each with it's own header and trailer line.
 *	An srecord looks like this:
 *
 * byte count-+     address
 * start ---+ |        |       data        +- checksum
 *	    | |        |                   |
 *	  S01000006F6B692D746573742E73726563E4
 *	  S315000448600000000000000000FC00005900000000E9
 *	  S31A0004000023C1400037DE00F023604000377B009020825000348D
 *	  S30B0004485A0000000000004E
 *	  S70500040000F6
 *
 *	S<type><length><address><data><checksum>
 *
 *      Where
 *      - length
 *        is the number of bytes following upto the checksum. Note that
 *        this is not the number of chars following, since it takes two
 *        chars to represent a byte.
 *      - type
 *        is one of:
 *        0) header record
 *        1) two byte address data record
 *        2) three byte address data record
 *        3) four byte address data record
 *        7) four byte address termination record
 *        8) three byte address termination record
 *        9) two byte address termination record
 *       
 *      - address
 *        is the start address of the data following, or in the case of
 *        a termination record, the start address of the image
 *      - data
 *        is the data.
 *      - checksum
 *	  is the sum of all the raw byte data in the record, from the length
 *        upwards, modulo 256 and subtracted from 255.
 *
 * This routine returns the length of the S-record.
 *
 */

static int
mips_make_srec (buf, type, memaddr, myaddr, len)
     char *buf;
     int type;
     CORE_ADDR memaddr;
     unsigned char *myaddr;
     int len;
{
  unsigned char checksum;
  int i;

  /* Create the header for the srec. addr_size is the number of bytes in the address,
     and 1 is the number of bytes in the count.  */

  /* FIXME!! bigger buf required for 64-bit! */
  buf[0] = 'S';
  buf[1] = type;
  buf[2] = len + 4 + 1;		/* len + 4 byte address + 1 byte checksum */
  /* This assumes S3 style downloads (4byte addresses). There should
     probably be a check, or the code changed to make it more
     explicit. */
  buf[3] = memaddr >> 24;
  buf[4] = memaddr >> 16;
  buf[5] = memaddr >> 8;
  buf[6] = memaddr;
  memcpy (&buf[7], myaddr, len);

  /* Note that the checksum is calculated on the raw data, not the
     hexified data.  It includes the length, address and the data
     portions of the packet.  */
  checksum = 0;
  buf += 2;			/* Point at length byte */
  for (i = 0; i < len + 4 + 1; i++)
    checksum += *buf++;

  *buf = ~checksum;

  return len + 8;
}

/* The following manifest controls whether we enable the simple flow
   control support provided by the monitor. If enabled the code will
   wait for an affirmative ACK between transmitting packets. */
#define DOETXACK (1)

/* The PMON fast-download uses an encoded packet format constructed of
   3byte data packets (encoded as 4 printable ASCII characters), and
   escape sequences (preceded by a '/'):

	'K'     clear checksum
	'C'     compare checksum (12bit value, not included in checksum calculation)
	'S'     define symbol name (for addr) terminated with "," and padded to 4char boundary
	'Z'     zero fill multiple of 3bytes
	'B'     byte (12bit encoded value, of 8bit data)
	'A'     address (36bit encoded value)
	'E'     define entry as original address, and exit load

   The packets are processed in 4 character chunks, so the escape
   sequences that do not have any data (or variable length data)
   should be padded to a 4 character boundary.  The decoder will give
   an error if the complete message block size is not a multiple of
   4bytes (size of record).

   The encoding of numbers is done in 6bit fields.  The 6bit value is
   used to index into this string to get the specific character
   encoding for the value: */
static char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,.";

/* Convert the number of bits required into an encoded number, 6bits
   at a time (range 0..63).  Keep a checksum if required (passed
   pointer non-NULL). The function returns the number of encoded
   characters written into the buffer. */
static int
pmon_makeb64 (v, p, n, chksum)
     unsigned long v;
     char *p;
     int n;
     int *chksum;
{
  int count = (n / 6);

  if ((n % 12) != 0) {
    fprintf_unfiltered(stderr,"Fast encoding bitcount must be a multiple of 12bits: %dbit%s\n",n,(n == 1)?"":"s");
    return(0);
  }
  if (n > 36) {
    fprintf_unfiltered(stderr,"Fast encoding cannot process more than 36bits at the moment: %dbits\n",n);
    return(0);
  }

  /* Deal with the checksum: */
  if (chksum != NULL) {
    switch (n) {
     case 36: *chksum += ((v >> 24) & 0xFFF);
     case 24: *chksum += ((v >> 12) & 0xFFF);
     case 12: *chksum += ((v >>  0) & 0xFFF);
    }
  }

  do {
    n -= 6;
    *p++ = encoding[(v >> n) & 0x3F];
  } while (n > 0);

  return(count);
}

/* Shorthand function (that could be in-lined) to output the zero-fill
   escape sequence into the data stream. */
static int
pmon_zeroset (recsize, buff, amount, chksum)
     int recsize;
     char **buff;
     int *amount;
     unsigned int *chksum;
{
  int count;

  sprintf(*buff,"/Z");
  count = pmon_makeb64 (*amount, (*buff + 2), 12, chksum);
  *buff += (count + 2);
  *amount = 0;
  return(recsize + count + 2);
}

static int
pmon_checkset (recsize, buff, value)
     int recsize;
     char **buff;
     int *value;
{
  int count;

  /* Add the checksum (without updating the value): */
  sprintf (*buff, "/C");
  count = pmon_makeb64 (*value, (*buff + 2), 12, NULL);
  *buff += (count + 2);
  sprintf (*buff, "\n");
  *buff += 2; /* include zero terminator */
  /* Forcing a checksum validation clears the sum: */
  *value = 0;
  return(recsize + count + 3);
}

/* Amount of padding we leave after at the end of the output buffer,
   for the checksum and line termination characters: */
#define CHECKSIZE (4 + 4 + 4 + 2)
/* zero-fill, checksum, transfer end and line termination space. */

/* The amount of binary data loaded from the object file in a single
   operation: */
#define BINCHUNK (1024)

/* Maximum line of data accepted by the monitor: */
#define MAXRECSIZE (550)
/* NOTE: This constant depends on the monitor being used. This value
   is for PMON 5.x on the Cogent Vr4300 board. */

static void
pmon_make_fastrec (outbuf, inbuf, inptr, inamount, recsize, csum, zerofill)
     char **outbuf;
     unsigned char *inbuf;
     int *inptr;
     int inamount;
     int *recsize;
     unsigned int *csum;
     unsigned int *zerofill;
{
  int count = 0;
  char *p = *outbuf;

  /* This is a simple check to ensure that our data will fit within
     the maximum allowable record size. Each record output is 4bytes
     in length. We must allow space for a pending zero fill command,
     the record, and a checksum record. */
  while ((*recsize < (MAXRECSIZE - CHECKSIZE)) && ((inamount - *inptr) > 0)) {
    /* Process the binary data: */
    if ((inamount - *inptr) < 3) {
      if (*zerofill != 0)
       *recsize = pmon_zeroset (*recsize, &p, zerofill, csum);
      sprintf (p, "/B");
      count = pmon_makeb64 (inbuf[*inptr], &p[2], 12, csum);
      p += (2 + count);
      *recsize += (2 + count);
      (*inptr)++;
    } else {
      unsigned int value = ((inbuf[*inptr + 0] << 16) | (inbuf[*inptr + 1] << 8) | inbuf[*inptr + 2]);
      /* Simple check for zero data. TODO: A better check would be
         to check the last, and then the middle byte for being zero
         (if the first byte is not). We could then check for
         following runs of zeros, and if above a certain size it is
         worth the 4 or 8 character hit of the byte insertions used
         to pad to the start of the zeroes. NOTE: This also depends
         on the alignment at the end of the zero run. */
      if (value == 0x00000000) {
        (*zerofill)++;
        if (*zerofill == 0xFFF) /* 12bit counter */
         *recsize = pmon_zeroset (*recsize, &p, zerofill, csum);
      }else {
        if (*zerofill != 0)
         *recsize = pmon_zeroset (*recsize, &p, zerofill, csum);
        count = pmon_makeb64 (value, p, 24, csum);
        p += count;
        *recsize += count;
      }
      *inptr += 3;
    }
  }

  *outbuf = p;
  return;
}

static int
pmon_check_ack(mesg)
     char *mesg;
{
#if defined(DOETXACK)
  int c;

  if (!tftp_in_use)
    {
      c = SERIAL_READCHAR (udp_in_use ? udp_desc : mips_desc, 2);
      if ((c == SERIAL_TIMEOUT) || (c != 0x06))
	{
	  fprintf_unfiltered (gdb_stderr,
			      "Failed to receive valid ACK for %s\n", mesg);
	  return(-1); /* terminate the download */
	}
    }
#endif /* DOETXACK */
  return(0);
}

/* pmon_download - Send a sequence of characters to the PMON download port,
   which is either a serial port or a UDP socket.  */

static void
pmon_start_download ()
{
  if (tftp_in_use)
    {
      /* Create the temporary download file.  */
      if ((tftp_file = fopen (tftp_localname, "w")) == NULL)
	perror_with_name (tftp_localname);
    }
  else
    {
      mips_send_command (udp_in_use ? LOAD_CMD_UDP : LOAD_CMD, 0);
      mips_expect ("Downloading from ");
      mips_expect (udp_in_use ? "udp" : "tty0");
      mips_expect (", ^C to abort\r\n");
    }
}

static int
mips_expect_download (char *string)
{
  if (!mips_expect (string))
    {
      fprintf_unfiltered (gdb_stderr, "Load did not complete successfully.\n");
      if (tftp_in_use)
	remove (tftp_localname);	/* Remove temporary file */
      return 0;
    }
  else
    return 1;
}

static void
pmon_end_download (final, bintotal)
     int final;
     int bintotal;
{
  char hexnumber[9]; /* includes '\0' space */

  if (tftp_in_use)
    {
      static char *load_cmd_prefix = "load -b -s ";
      char *cmd;
      struct stat stbuf;

      /* Close off the temporary file containing the load data.  */
      fclose (tftp_file);
      tftp_file = NULL;

      /* Make the temporary file readable by the world.  */
      if (stat (tftp_localname, &stbuf) == 0)
	chmod (tftp_localname, stbuf.st_mode | S_IROTH);

      /* Must reinitialize the board to prevent PMON from crashing.  */
      mips_send_command ("initEther\r", -1);

      /* Send the load command.  */
      cmd = xmalloc (strlen (load_cmd_prefix) + strlen (tftp_name) + 2);
      strcpy (cmd, load_cmd_prefix);
      strcat (cmd, tftp_name);
      strcat (cmd, "\r");
      mips_send_command (cmd, 0);
      free (cmd);
      if (!mips_expect_download ("Downloading from "))
	return;
      if (!mips_expect_download (tftp_name))
	return;
      if (!mips_expect_download (", ^C to abort\r\n"))
	return;
    }

  /* Wait for the stuff that PMON prints after the load has completed.
     The timeout value for use in the tftp case (15 seconds) was picked
     arbitrarily but might be too small for really large downloads. FIXME. */
  if (mips_monitor == MON_LSI)
    {
      pmon_check_ack ("termination");
      mips_expect_timeout ("Entry address is ", tftp_in_use ? 15 : 2);
    }
  else
    mips_expect_timeout ("Entry Address  = ", tftp_in_use ? 15 : 2);

  sprintf (hexnumber,"%x",final);
  mips_expect (hexnumber);
  mips_expect ("\r\n");
  if (mips_monitor != MON_LSI)
    pmon_check_ack ("termination");
  mips_expect ("\r\ntotal = 0x");
  sprintf (hexnumber,"%x",bintotal);
  mips_expect (hexnumber);
  if (!mips_expect_download (" bytes\r\n"))
    return;

  if (tftp_in_use)
    remove (tftp_localname);	/* Remove temporary file */
}

static void
pmon_download (buffer, length)
     char *buffer;
     int length;
{
  if (tftp_in_use)
    fwrite (buffer, 1, length, tftp_file);
  else
    SERIAL_WRITE (udp_in_use ? udp_desc : mips_desc, buffer, length);
}

static void
pmon_load_fast (file)
     char *file;
{
  bfd *abfd;
  asection *s;
  unsigned char *binbuf;
  char *buffer;
  int reclen;
  unsigned int csum = 0;
  int hashmark = !tftp_in_use;
  int bintotal = 0;
  int final = 0;
  int finished = 0;

  buffer = (char *)xmalloc(MAXRECSIZE + 1);
  binbuf = (unsigned char *)xmalloc(BINCHUNK);

  abfd = bfd_openr(file,0);
  if (!abfd)
   {
     printf_filtered ("Unable to open file %s\n",file);
     return;
   }

  if (bfd_check_format(abfd,bfd_object) == 0)
   {
     printf_filtered("File is not an object file\n");
     return;
   }

  /* Setup the required download state: */
  mips_send_command ("set dlproto etxack\r", -1);
  mips_send_command ("set dlecho off\r", -1);
  /* NOTE: We get a "cannot set variable" message if the variable is
     already defined to have the argument we give. The code doesn't
     care, since it just scans to the next prompt anyway. */
  /* Start the download: */
  pmon_start_download();
  
  /* Zero the checksum */
  sprintf(buffer,"/Kxx\n");
  reclen = strlen(buffer);
  pmon_download (buffer, reclen);
  finished = pmon_check_ack("/Kxx");

  for (s = abfd->sections; s && !finished; s = s->next)
   if (s->flags & SEC_LOAD) /* only deal with loadable sections */
    {
      bintotal += s->_raw_size;
      final = (s->vma + s->_raw_size);

      printf_filtered ("%s\t: 0x%4x .. 0x%4x  ", s->name, (unsigned int)s->vma,
                       (unsigned int)(s->vma + s->_raw_size));
      gdb_flush (gdb_stdout);

      /* Output the starting address */
      sprintf(buffer,"/A");
      reclen = pmon_makeb64(s->vma,&buffer[2],36,&csum);
      buffer[2 + reclen] = '\n';
      buffer[3 + reclen] = '\0';
      reclen += 3; /* for the initial escape code and carriage return */
      pmon_download (buffer, reclen);
      finished = pmon_check_ack("/A");

      if (!finished)
       {
         unsigned int binamount;
         unsigned int zerofill = 0;
         char *bp = buffer;
         unsigned int i;

         reclen = 0;

         for (i = 0; ((i < s->_raw_size) && !finished); i += binamount) {
           int binptr = 0;

           binamount = min (BINCHUNK, s->_raw_size - i);

           bfd_get_section_contents (abfd, s, binbuf, i, binamount);

           /* This keeps a rolling checksum, until we decide to output
              the line: */
           for (; ((binamount - binptr) > 0);) {
             pmon_make_fastrec (&bp, binbuf, &binptr, binamount, &reclen, &csum, &zerofill);
             if (reclen >= (MAXRECSIZE - CHECKSIZE)) {
               reclen = pmon_checkset (reclen, &bp, &csum);
               pmon_download (buffer, reclen);
               finished = pmon_check_ack("data record");
               if (finished) {
                 zerofill = 0; /* do not transmit pending zerofills */
                 break;
               }

               if (hashmark) {
                 putchar_unfiltered ('#');
                 gdb_flush (gdb_stdout);
               }

               bp = buffer;
               reclen = 0; /* buffer processed */
             }
           }
         }

         /* Ensure no out-standing zerofill requests: */
         if (zerofill != 0)
          reclen = pmon_zeroset (reclen, &bp, &zerofill, &csum);

         /* and then flush the line: */
         if (reclen > 0) {
           reclen = pmon_checkset (reclen, &bp, &csum);
           /* Currently pmon_checkset outputs the line terminator by
              default, so we write out the buffer so far: */
           pmon_download (buffer, reclen);
           finished = pmon_check_ack("record remnant");
         }
       }

      putchar_unfiltered ('\n');
    }

  /* Terminate the transfer. We know that we have an empty output
     buffer at this point. */
  sprintf (buffer, "/E/E\n"); /* include dummy padding characters */
  reclen = strlen (buffer);
  pmon_download (buffer, reclen);

  if (finished) { /* Ignore the termination message: */
    SERIAL_FLUSH_INPUT (udp_in_use ? udp_desc : mips_desc);
  } else { /* Deal with termination message: */
    pmon_end_download (final, bintotal);
  }

  return;
}

/* mips_load -- download a file. */

static void
mips_load (file, from_tty)
    char *file;
    int  from_tty;
{
  /* Get the board out of remote debugging mode.  */
  if (mips_exit_debug ())
    error ("mips_load:  Couldn't get into monitor mode.");

  if (mips_monitor != MON_IDT)
   pmon_load_fast (file);
  else
   mips_load_srec (file);

  mips_initialize ();

  /* Finally, make the PC point at the start address */
  if (mips_monitor != MON_IDT)
    {
      /* Work around problem where PMON monitor updates the PC after a load
	 to a different value than GDB thinks it has. The following ensures
	 that the write_pc() WILL update the PC value: */
      register_valid[PC_REGNUM] = 0;
    }
  if (exec_bfd)
    write_pc (bfd_get_start_address (exec_bfd));

  inferior_pid = 0;		/* No process now */

/* This is necessary because many things were based on the PC at the time that
   we attached to the monitor, which is no longer valid now that we have loaded
   new code (and just changed the PC).  Another way to do this might be to call
   normal_stop, except that the stack may not be valid, and things would get
   horribly confused... */

  clear_symtab_users ();
}

/* The target vector.  */

struct target_ops mips_ops =
{
  "mips",			/* to_shortname */
  "Remote MIPS debugging over serial line",	/* to_longname */
  "\
Debug a board using the MIPS remote debugging protocol over a serial line.\n\
The argument is the device it is connected to or, if it contains a colon,\n\
HOST:PORT to access a board over a network",  /* to_doc */
  mips_open,			/* to_open */
  mips_close,			/* to_close */
  NULL,				/* to_attach */
  mips_detach,			/* to_detach */
  mips_resume,			/* to_resume */
  mips_wait,			/* to_wait */
  mips_fetch_registers,		/* to_fetch_registers */
  mips_store_registers,		/* to_store_registers */
  mips_prepare_to_store,	/* to_prepare_to_store */
  mips_xfer_memory,		/* to_xfer_memory */
  mips_files_info,		/* to_files_info */
  mips_insert_breakpoint,	/* to_insert_breakpoint */
  mips_remove_breakpoint,	/* to_remove_breakpoint */
  NULL,				/* to_terminal_init */
  NULL,				/* to_terminal_inferior */
  NULL,				/* to_terminal_ours_for_output */
  NULL,				/* to_terminal_ours */
  NULL,				/* to_terminal_info */
  mips_kill,			/* to_kill */
  mips_load,			/* to_load */
  NULL,				/* to_lookup_symbol */
  mips_create_inferior,		/* to_create_inferior */
  mips_mourn_inferior,		/* to_mourn_inferior */
  NULL,				/* to_can_run */
  NULL,				/* to_notice_signals */
  0,				/* to_thread_alive */
  0,				/* to_stop */
  process_stratum,		/* to_stratum */
  NULL,				/* to_next */
  1,				/* to_has_all_memory */
  1,				/* to_has_memory */
  1,				/* to_has_stack */
  1,				/* to_has_registers */
  1,				/* to_has_execution */
  NULL,				/* sections */
  NULL,				/* sections_end */
  OPS_MAGIC			/* to_magic */
};

/* An alternative target vector: */
struct target_ops pmon_ops =
{
  "pmon",			/* to_shortname */
  "Remote MIPS debugging over serial line",	/* to_longname */
  "\
Debug a board using the PMON MIPS remote debugging protocol over a serial\n\
line. The argument is the device it is connected to or, if it contains a\n\
colon, HOST:PORT to access a board over a network",  /* to_doc */
  pmon_open,			/* to_open */
  mips_close,			/* to_close */
  NULL,				/* to_attach */
  mips_detach,			/* to_detach */
  mips_resume,			/* to_resume */
  pmon_wait,			/* to_wait */
  mips_fetch_registers,		/* to_fetch_registers */
  mips_store_registers,		/* to_store_registers */
  mips_prepare_to_store,	/* to_prepare_to_store */
  mips_xfer_memory,		/* to_xfer_memory */
  mips_files_info,		/* to_files_info */
  mips_insert_breakpoint,	/* to_insert_breakpoint */
  mips_remove_breakpoint,	/* to_remove_breakpoint */
  NULL,				/* to_terminal_init */
  NULL,				/* to_terminal_inferior */
  NULL,				/* to_terminal_ours_for_output */
  NULL,				/* to_terminal_ours */
  NULL,				/* to_terminal_info */
  mips_kill,			/* to_kill */
  mips_load,			/* to_load */
  NULL,				/* to_lookup_symbol */
  mips_create_inferior,		/* to_create_inferior */
  mips_mourn_inferior,		/* to_mourn_inferior */
  NULL,				/* to_can_run */
  NULL,				/* to_notice_signals */
  0,				/* to_thread_alive */
  0,				/* to_stop */
  process_stratum,		/* to_stratum */
  NULL,				/* to_next */
  1,				/* to_has_all_memory */
  1,				/* to_has_memory */
  1,				/* to_has_stack */
  1,				/* to_has_registers */
  1,				/* to_has_execution */
  NULL,				/* sections */
  NULL,				/* sections_end */
  OPS_MAGIC			/* to_magic */
};

/* Another alternative target vector. This is a PMON system, but with
   a different monitor prompt, aswell as some other operational
   differences: */
struct target_ops ddb_ops =
{
  "ddb",			/* to_shortname */
  "Remote MIPS debugging over serial line",	/* to_longname */
  "\
Debug a board using the PMON MIPS remote debugging protocol over a serial\n\
line. The first argument is the device it is connected to or, if it contains\n\
a colon, HOST:PORT to access a board over a network.  The optional second\n\
parameter is the temporary file in the form HOST:FILENAME to be used for\n\
TFTP downloads to the board.  The optional third parameter is the local\n\
of the TFTP temporary file, if it differs from the filename seen by the board",
				/* to_doc */
  ddb_open,			/* to_open */
  mips_close,			/* to_close */
  NULL,				/* to_attach */
  mips_detach,			/* to_detach */
  mips_resume,			/* to_resume */
  pmon_wait,			/* to_wait */
  mips_fetch_registers,		/* to_fetch_registers */
  mips_store_registers,		/* to_store_registers */
  mips_prepare_to_store,	/* to_prepare_to_store */
  mips_xfer_memory,		/* to_xfer_memory */
  mips_files_info,		/* to_files_info */
  mips_insert_breakpoint,	/* to_insert_breakpoint */
  mips_remove_breakpoint,	/* to_remove_breakpoint */
  NULL,				/* to_terminal_init */
  NULL,				/* to_terminal_inferior */
  NULL,				/* to_terminal_ours_for_output */
  NULL,				/* to_terminal_ours */
  NULL,				/* to_terminal_info */
  mips_kill,			/* to_kill */
  mips_load,			/* to_load */
  NULL,				/* to_lookup_symbol */
  mips_create_inferior,		/* to_create_inferior */
  mips_mourn_inferior,		/* to_mourn_inferior */
  NULL,				/* to_can_run */
  NULL,				/* to_notice_signals */
  0,				/* to_thread_alive */
  0,				/* to_stop */
  process_stratum,		/* to_stratum */
  NULL,				/* to_next */
  1,				/* to_has_all_memory */
  1,				/* to_has_memory */
  1,				/* to_has_stack */
  1,				/* to_has_registers */
  1,				/* to_has_execution */
  NULL,				/* sections */
  NULL,				/* sections_end */
  OPS_MAGIC			/* to_magic */
};

/* Another alternative target vector for LSI Logic MiniRISC boards.
   This is a PMON system, but with some other operational differences.  */
struct target_ops lsi_ops =
{
  "lsi",			/* to_shortname */
  "Remote MIPS debugging over serial line",	/* to_longname */
  "\
Debug a board using the PMON MIPS remote debugging protocol over a serial\n\
line. The first argument is the device it is connected to or, if it contains\n\
a colon, HOST:PORT to access a board over a network.  The optional second\n\
parameter is the temporary file in the form HOST:FILENAME to be used for\n\
TFTP downloads to the board.  The optional third parameter is the local\n\
of the TFTP temporary file, if it differs from the filename seen by the board",
				/* to_doc */
  lsi_open,			/* to_open */
  mips_close,			/* to_close */
  NULL,				/* to_attach */
  mips_detach,			/* to_detach */
  mips_resume,			/* to_resume */
  pmon_wait,			/* to_wait */
  mips_fetch_registers,		/* to_fetch_registers */
  mips_store_registers,		/* to_store_registers */
  mips_prepare_to_store,	/* to_prepare_to_store */
  mips_xfer_memory,		/* to_xfer_memory */
  mips_files_info,		/* to_files_info */
  mips_insert_breakpoint,	/* to_insert_breakpoint */
  mips_remove_breakpoint,	/* to_remove_breakpoint */
  NULL,				/* to_terminal_init */
  NULL,				/* to_terminal_inferior */
  NULL,				/* to_terminal_ours_for_output */
  NULL,				/* to_terminal_ours */
  NULL,				/* to_terminal_info */
  mips_kill,			/* to_kill */
  mips_load,			/* to_load */
  NULL,				/* to_lookup_symbol */
  mips_create_inferior,		/* to_create_inferior */
  mips_mourn_inferior,		/* to_mourn_inferior */
  NULL,				/* to_can_run */
  NULL,				/* to_notice_signals */
  0,				/* to_thread_alive */
  0,				/* to_stop */
  process_stratum,		/* to_stratum */
  NULL,				/* to_next */
  1,				/* to_has_all_memory */
  1,				/* to_has_memory */
  1,				/* to_has_stack */
  1,				/* to_has_registers */
  1,				/* to_has_execution */
  NULL,				/* sections */
  NULL,				/* sections_end */
  OPS_MAGIC			/* to_magic */
};

void
_initialize_remote_mips ()
{
  add_target (&mips_ops);
  add_target (&pmon_ops);
  add_target (&ddb_ops);
  add_target (&lsi_ops);

  add_show_from_set (
    add_set_cmd ("timeout", no_class, var_zinteger,
		 (char *) &mips_receive_wait,
		 "Set timeout in seconds for remote MIPS serial I/O.",
		 &setlist),
	&showlist);

  add_show_from_set (
    add_set_cmd ("retransmit-timeout", no_class, var_zinteger,
		 (char *) &mips_retransmit_wait,
	 "Set retransmit timeout in seconds for remote MIPS serial I/O.\n\
This is the number of seconds to wait for an acknowledgement to a packet\n\
before resending the packet.", &setlist),
	&showlist);

  add_show_from_set (
    add_set_cmd ("syn-garbage-limit", no_class, var_zinteger,
		 (char *) &mips_syn_garbage,
"Set the maximum number of characters to ignore when scanning for a SYN.\n\
This is the maximum number of characters GDB will ignore when trying to\n\
synchronize with the remote system.  A value of -1 means that there is no limit\n\
(Note that these characters are printed out even though they are ignored.)",
		 &setlist),
		     &showlist);

  add_show_from_set
    (add_set_cmd ("monitor-prompt", class_obscure, var_string,
		  (char *) &mips_monitor_prompt,
		  "Set the prompt that GDB expects from the monitor.",
		  &setlist),
     &showlist);
}
