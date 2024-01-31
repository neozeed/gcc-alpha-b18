/* sys/termios.h */

#ifndef	_SYS_TERMIOS_H
#define _SYS_TERMIOS_H

#define TCOOFF	0
#define TCOON	1
#define TCIOFF	2
#define TCION	3

#define TCGETA   5
#define TCSETA   6
#define TCSETAW	 7
#define TCSETAF	 8

#define TCIFLUSH	0
#define TCOFLUSH	1
#define TCIOFLUSH	2
#define TCFLSH          3

#define TCSAFLUSH	1
#define TCSANOW		2
#define TCSADRAIN	3
#define TCSADFLUSH	4

#define TIOCPKT		6

#define TIOCPKT_DATA		 0
#define TIOCPKT_FLUSHREAD	 1
#define TIOCPKT_FLUSHWRITE	 2
#define TIOCPKT_STOP		 4
#define TIOCPKT_START		 8
#define TIOCPKT_NOSTOP		16
#define TIOCPKT_DOSTOP		32

#define FIONBIO 0x8004667e /* To be compatible with socket version */

#define CTRL(ch)	((ch)&0x1F)

#define CNUL	0
#define CDEL	0177
#define CESC	'\\'
#define CINTR	CTRL('C')
#define CQUIT	034
#define CERASE	CTRL('H')
#define CKILL	CTRL('U')
#define CEOT	CTRL('D')
#define CEOL	0
#define CEOL2	0
#define CEOF	CTRL('D')
#define CSTART	CTRL('Q')
#define CSTOP	CTRL('S')
#define CSWTCH	032
#define NSWTCH	0
#define CSUSP	CTRL('Z')
#define CDSUSP	CTRL('Y')
#define CRPRNT	CTRL('R')
#define CFLUSH	CTRL('O')
#define CWERASE	CTRL('W')
#define CLNEXT	CTRL('V')

/* iflag bits */
#define IGNBRK  0000001
#define BRKINT  0000002
#define IGNPAR  0000004
#define IMAXBEL 0000010
#define INPCK   0000020
#define ISTRIP  0000040
#define INLCR   0000100
#define IGNCR   0000200
#define ICRNL   0000400
#define IXON	0002000
#define IXOFF	0010000
#define IUCLC   0040000
#define IXANY   0100000
#define PARMRK  0200000

/* oflag bits */

#define OPOST	0000001
#define OLCUC	0000002
#define OCRNL	0000004
#define ONLCR	0000010
#define ONOCR	0000020
#define ONLRET	0000040
#define OFILL	0000100
#define CRDLY	0000600
#define CR0	   0000
#define CR1	   0200
#define CR2	   0400
#define CR3	   0600
#define NLDLY	0001000
#define	NL0	  00000
#define NL1	  01000
#define	BSDLY	0002000
#define BS0	  00000
#define BS1	  02000
#define TABDLY	0014000
#define TAB0	 000000
#define TAB1	 004000
#define TAB2	 010000
#define TAB3	 014000
#define XTABS	0014000
#define VTDLY	0020000
#define VT0	 000000
#define VT1	 020000
#define FFDLY	0040000
#define FF0	 000000
#define FF1	 040000
#define OFDEL	0100000

/* cflag bits */

#define CLOCAL	004000
#define CREAD	000200
#define CSIZE	000060
#define CS5	0
#define CS6	020
#define CS7	040
#define CS8	060
#define CSTOPB	000100
#define HUPCL	002000
#define PARENB	000400
#define PARODD	001000
#define CRTSXOFF	010000000000
#define CRTSCTS	020000000000

/* lflag bits */
#define ISIG	0x0001
#define ICANON	0x0002
#define ECHO	0x0004
#define ECHOE	0x0008
#define ECHOK	0x0010
#define ECHONL	0x0020
#define NOFLSH	0x0040
#define TOSTOP	0x0080
#define IEXTEN	0x0100
#define FLUSHO	0x0200
#define ECHOKE	0x0400
#define ECHOCTL	0x0800

#define VDISCARD	1
#define VEOL		2
#define VEOL2   	3
#define VEOF		4
#define VERASE		5
#define VINTR		6
#define VKILL		7
#define VLNEXT 		8
#define VMIN		9
#define VQUIT		10
#define VREPRINT 	11
#define VSTART		12
#define VSTOP		13
#define VSUSP		14
#define VSWTC 		15
#define VTIME		16
#define VWERASE 	17

#define NCCS 		18

/* Baud rate values.  These must fit in speed_t, which is unsigned
   char.  */
#define CBAUD	000037
#define B0	000000
#define B50	000001
#define B75	000002
#define B110	000003
#define B134	000004
#define B150	000005
#define B200	000006
#define B300	000007
#define B600	000010
#define B1200	000011
#define B1800	000012
#define B2400	000013
#define B4800	000014
#define B9600	000015
#define B19200	000016
#define B38400	000017
#define B57600	000020
#define B115200	000021

typedef unsigned char cc_t;
typedef unsigned short tcflag_t;
typedef unsigned char speed_t;

struct termios {
	tcflag_t	c_iflag;
	tcflag_t	c_oflag;
	tcflag_t	c_cflag;
	tcflag_t	c_lflag;
	char		c_line;
	cc_t		c_cc[NCCS];
	speed_t		c_ispeed;
	speed_t		c_ospeed;
};

#define termio termios

#define cfgetospeed(tp)		((tp)->c_ospeed)
#define cfgetispeed(tp)		((tp)->c_ispeed)
#define cfsetospeed(tp,s)	(((tp)->c_ospeed = (s)), 0)
#define cfsetispeed(tp,s)	(((tp)->c_ispeed = (s)), 0)

#ifdef __cplusplus
extern "C" {
#endif

int tcgetattr (int, struct termios *);
int tcsetattr (int, int, const struct termios *);
int tcsendbreak (int, int);
int tcdrain (int);
int tcflush (int, int);
int tcflow (int, int);

#ifdef __cplusplus
}
#endif

/* Extra stuff to make porting stuff easier.  */
struct winsize
{
  unsigned short ws_row, ws_col;
  unsigned short ws_xpixel, ws_ypixel;
};

#define TIOCGWINSZ (('T' << 8) | 1)
#define TIOCSWINSZ (('T' << 8) | 2)

#endif	/* _SYS_TERMIOS_H */
