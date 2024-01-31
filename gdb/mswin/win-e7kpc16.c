
/* 
 * win-e7kpc16.c
 * 
 * Source for w95e7k16.dll and w31e7k16.dll.
 * 
 * Writes to physical memory to interface with the Hitachi
 * e7000pc.
*/

#include "win-e7kpc.h"
#define ANSI_PROTOTYPES

//#define DEBUGIFY
#include "debugify.h"

    /* typedefs in 16-bit land:
     * typedef unsigned short      WORD;
     * typedef unsigned long       DWORD;
     */
     typedef WORD ushort;
     typedef DWORD ulong;

#ifdef _WIN95

 short CALLBACK set_mem (short offset, short data)
    {
    WORD FAR * lpUMB = MAKELP( selUMB, offset );
    DBG(("set_mem(offset=x%x,data=x%x), lpUMB=x%x\n", offset, data, lpUMB));
    /* lpUMB looks like:
     * [ *lpUMB *(lpUMB+1) ] in memory.
     * So, since we want to poke the byte at lpUMB, 
     * we want to preserve *(lpUMB+1).
     */
    *lpUMB = ((WORD)(data & 0xff)) | ((*lpUMB) & 0xff00);
    DBG(("set_mem(offset=x%x,data=x%x), *lpUMB=x%x\n", offset, data, *lpUMB));
    return 0;
    }

 short CALLBACK get_mem (short offset)
    {
    short data=0;
    WORD FAR * lpUMB = MAKELP( selUMB, offset );
    DBG(("set_mem(offset=x%x), lpUMB=x%x\n", offset, lpUMB));
    data = *lpUMB; /* gets 2 bytes */
    data &= 0xff;	/* but we just want the first byte */
    DBG(("set_mem(offset=x%x), data=x%x, *lpUMB=x%x\n", offset, data, *lpUMB));
    return (data & 0xff);
    }
#endif /* _WIN95 */

#ifdef _WIN32s

#ifndef APIENTRY
#define APIENTRY
#endif
#define W32SUT_16

#include "windefs.h"
#include <w32sut.h>
    

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
  unsigned offset=0;
  unsigned data=0;
  WORD FAR * lpUMB = NULL;

  DBG(("UTProc\n"));
  switch (dwFunc)
    {
    case SETMEM:
      {
	/* takes 2 parms: mem offset & data */
	/* for now, lpArgs[1] is just a single byte */
	offset = ((unsigned) lpArgs[0]) & 0xffff;
	data = ((unsigned) lpArgs[1]) & 0xff;
	lpUMB = MAKELP( selUMB, offset );
	DBG(("UTProc(..,SETMEM): offset=x%x(arg[0]=x%x) data=x%x(arg[1]=x%x) lpUMB=0x%x\n",
		      offset, lpArgs[0], data, lpArgs[1], lpUMB));
	/* only want to modify byte at lpUMB */
	*lpUMB = ((WORD)(data & 0xff)) | ((*lpUMB) & 0xff00);
	DBG(("UTProc(..,SETMEM): *lpUMB=x%x(calc=x%x)\n", *lpUMB, ((WORD)(data & 0xff)) | ((*lpUMB) & 0xff00)));
	return 0;
      }
      break;
    case GETMEM:
      {
	/* takes 1 parm: mem offset */
	/* for now, data is just a single byte */
	offset = (unsigned) lpArgs[0] & 0xffff;
	lpUMB = MAKELP( selUMB, offset );
	data = *lpUMB;
	data &= 0xff;
	DBG(("UTProc(..,GETMEM): offset=x%x(arg[0]=x%x) data=x%x(*lpUMB=x%x) lpUMB=0x%x\n",
		      offset, lpArgs[0], data, *lpUMB, lpUMB));
        return data;
      }
      break;
    }
  return ((DWORD) - 1L);
}

#endif /* _WIN32s */
