

#ifndef APIENTRY
#define APIENTRY
#endif
#define W32SUT_16

#include "windefs.h"
#include <w32sut.h>
#include "serdll.h"


//#define DEBUGIFY
#include "debugify.h"

static int remote_debug=0;
#define RMT_DBG(x) if (remote_debug) printf_dbg x


int FAR PASCAL
LibMain (HANDLE hLibInst, WORD wDataSeg,
	 WORD cbHeapSize, LPSTR lpszCmdLine)
{
  return (1);
}				// LibMain()

DWORD FAR PASCAL __export
UTInit (UT16CBPROC lpfnUT16CallBack, LPVOID lpBuf)
{
  return (1);			// Return Success

}				// UTInit()


DWORD FAR PASCAL __export
UTProc (DWORD * lpArgs, DWORD dwFunc)
{
  RMT_DBG(("YIBBLE\n"));
  switch (dwFunc)
    {
    case BUILDCOMMDCB:
      RMT_DBG(("BuildCommDCB String=%s\n Buffer=%0lX ",
		    (LPSTR) lpArgs[0], (LPVOID) lpArgs[1]));

      return BuildCommDCB ((LPCSTR) lpArgs[0],
			   (LPVOID) lpArgs[1]);

    case OPENCOMM:
      {

	int i;
	DCB dcb;
	char *dev = (LPSTR) lpArgs[0];
	char *comm_string = (LPSTR) lpArgs[3];
	int j;
	memset (&dcb, 0, sizeof (dcb));
	RMT_DBG(( "NEW OpenComm String=%s Count1=%d Count2=%d %s\n",
		      (LPSTR) lpArgs[0], (UINT) lpArgs[1],
		      (UINT) lpArgs[2], (LPSTR) lpArgs[3]));

	i = OpenComm (dev, 512, 512);
	RMT_DBG(( "IRET %d %s\n", i, dev));

	if (i < 0)
	  return i;
#if 1
	BuildCommDCB (comm_string, &dcb);
	dcb.Id = i;
	dcb.fBinary = 1;
	dcb.fOutxCtsFlow = 0;
	dcb.fOutxDsrFlow = 0;
	dcb.fOutX = 0;
	dcb.fInX = 0;
	j = SetCommState (&dcb);
	if (remote_debug)
	  {
	    int j;
	    unsigned char *p = &dcb;
	    for (j = 0; j < sizeof (dcb); j++)
		RMT_DBG(( "%02x ", p[j]));
	    RMT_DBG(( "\n"));
	  }
	if (j)
	  OutputDebugString ("SetCmmstate failed\n");

	RMT_DBG(( "IRET %d\n", i));
#endif
	return i;
      }


    case CLOSECOMM:
      RMT_DBG(( "Close ComId=%d\n", (int) lpArgs[0]));
      return (CloseComm ((int) lpArgs[0]));


    case READCOMM:
      RMT_DBG(( "ReadComm ComId=%d Buffer=%0lX Count=%d", (int) lpArgs[0],
		    (LPSTR) lpArgs[1], (int) lpArgs[2]));
      return ReadComm ((int) lpArgs[0],
		       (LPSTR) lpArgs[1],
		       (int) lpArgs[2]);

    case WRITECOMM:
      RMT_DBG(( "WriteComm ComId=%d Buffer=%0lX %c Count=%d\n",
		    (int) lpArgs[0],
		    (LPSTR) lpArgs[1], ((LPSTR) lpArgs[1])[0],
		    (int) lpArgs[2]));

      return (WriteComm ((int) lpArgs[0],
			 (LPSTR) lpArgs[1],
			 (int) lpArgs[2]));



    case FLUSHCOMM:
      RMT_DBG(( "FlushComm ComId=%d Queue=\n",
		    (int) lpArgs[0], (int) lpArgs[1]));
      return FlushComm ((int) lpArgs[0], (int) lpArgs[1]);

    case TRANSMITCOMMCHAR:
      RMT_DBG(( "Transmit Comm Char ComId=%d Char=%c\n",
		    (int) lpArgs[0], (char) lpArgs[1]));
      return UngetCommChar ((int) lpArgs[0], (char) lpArgs[1]);

    case SETCOMMSTATE:
      RMT_DBG(( "SetCommState Buffer=%0lX \n", (LPVOID) lpArgs[0]));
      return SetCommState ((LPVOID) lpArgs[0]);


    case GETCOMMSTATE:
      RMT_DBG(( "GetCommState Comm Id=%d Buffer=%0lX \n",
		(int) lpArgs[0], (LPVOID) lpArgs[1]));
      return (GetCommState ((int) lpArgs[0],
			    (LPVOID) lpArgs[1]));


    case GETCOMMERROR:
      {
	int x;
	COMSTAT *foo = (LPVOID *) lpArgs[1];
	COMSTAT local;
	RMT_DBG(( "GetCommError Comm Id=%d Buffer=%0lX \n",
		      (int) lpArgs[0], (LPVOID) lpArgs[1]));
	x = GetCommError ((int) lpArgs[0], &local);
	RMT_DBG(( "GC returns %x %d\n",
		      x, local.status, local.cbInQue));
	return x;
      }

    case GETCOMMREADY:
      {
	int x;
	COMSTAT local;
	int cid = lpArgs[0];
	RMT_DBG(( "GC with %d", cid));

	x = GetCommError (cid, &local);

	if (remote_debug)
	  {
	    if (local.status)
	      RMT_DBG(( "GC returns %x %d\n", local.status, local.cbInQue));
	  }


	if (local.cbInQue)
	  {
	    char *buf = (char *) lpArgs[1];
	    char c;
	    int len = ReadComm (cid, buf, local.cbInQue);
	    if (len < 0)
	      {
		int err;
		len = -len;
		err = GetCommError (cid, NULL);
		GetCommEventMask (cid, 0xffff);
		RMT_DBG(( "error %x\n", err));
	      }
	    buf[len] = 0;
	    RMT_DBG(( "FP %d$%d %s\n",
			  len, local.cbInQue, buf));
	    return len;
	  }
	  RMT_DBG(("ECR\n"));

	return 0;
      }


    }

  return ((DWORD) - 1L);
}
