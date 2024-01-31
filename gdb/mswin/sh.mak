
# makefile to create sh target for wingdb
# from mswin directory, run:
#	nmake -f sh.mak
# output files will be copied to OUTDIR (see settings below)

# target specific extras for config.mak

TARGET=sh
TARGET_CFLAGS= -D TARGET_SH 
TARGET_LFLAGS= 
TARGET_LFLAGS32= 

# target specific extras for common.mak
TARGET_DEPS16=$(OUTDIR)\w95e7k16.dll $(OUTDIR)\w31e7k16.dll 
TARGET_DEPS=$(OUTDIR)\w95e7kpc.dll $(OUTDIR)\w31e7kpc.dll
#TARGET_DEPS=$(TARGET_DEPS) $(OUTDIR)\$(SIM).exe
!include "config.mak"

TARGET_OBJS= \
	$(INTDIR)/sh-tdep.obj \
	$(INTDIR)/interp.obj \
	$(INTDIR)/table.obj \
	$(INTDIR)/sh-dis.obj \
	$(INTDIR)/cpu-sh.obj \
	$(INTDIR)/coff-sh.obj \
        $(INTDIR)/stab-syms.obj \
	$(INTDIR)/remote-sim.obj \
	$(INTDIR)/version.obj \
	$(INTDIR)/sh3-rom.obj \
	$(INTDIR)/remote-e7000.obj \
	$(INTDIR)/ser-e7kpc.obj


TARGET_SBRS= \
	$(INTDIR)/sh-tdep.sbr \
	$(INTDIR)/interp.sbr \
	$(INTDIR)/table.sbr \
	$(INTDIR)/sh-dis.sbr \
	$(INTDIR)/cpu-sh.sbr \
	$(INTDIR)/coff-sh.sbr \
        $(INTDIR)/stab-syms.sbr \
	$(INTDIR)/remote-sim.sbr \
	$(INTDIR)/version.sbr \
	$(INTDIR)/sh3-rom.sbr \
	$(INTDIR)/remote-e7000.sbr \
	$(INTDIR)/ser-e7kpc.sbr

!include "common.mak"

# ======= rules for e7kpc support =========
# build dlls for e7000pc support on Windows
!include "e7kpc.mak"


# ======= rules for simulator =========
# simulator

TARGET_LIBLIB_OBJS= \
        $(INTDIR)\bcopy.obj

#these top 2 were already separate...
TARGET_LIBBFD_OBJS=  \
	$(INTDIR)/table.obj \
	$(INTDIR)/cpu-sh.obj \
	$(INTDIR)/coff-sh.obj \
	$(INTDIR)/cofflink.obj \
	$(INTDIR)/coffgen.obj 

TARGET_SIM_OBJS= \
	$(INTDIR)/stubs.obj


GENCODE=code.c
!include "sim.mak"

$(INTDIR)\sim\run.obj : $(SRCDIR)\sim\common\run.c
$(INTDIR)\sim\callback.obj : $(SRCDIR)\gdb\callback.c
$(INTDIR)\sim\interp.obj : $(SRCDIR)\sim\$(TARGET)\interp.c $(SRCDIR)\gdb\mswin\prebuilt\$(TARGET)\$(GENCODE)

