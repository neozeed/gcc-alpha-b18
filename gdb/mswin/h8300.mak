# makefile to create h8300 target for wingdb
# from mswin directory, run:
#	nmake -f h8300.mak
# change settings in config.mak as needed for your environment

# target specific extras for config.mak
TARGET=h8300
TARGET_CFLAGS= -D TARGET_H8300 
TARGET_LFLAGS= 
TARGET_LFLAGS32=

# target specific extras for common.mak
TARGET_DEPS16=$(OUTDIR)\w95e7k16.dll $(OUTDIR)\w31e7k16.dll 
TARGET_DEPS=$(OUTDIR)\w95e7kpc.dll $(OUTDIR)\w31e7kpc.dll
#TARGET_DEPS= $(TARGET_DEPS) $(OUTDIR)\$(SIM).exe

!include "config.mak"
  

TARGET_OBJS= \
	$(INTDIR)/coff-h8300.obj \
	$(INTDIR)/compile.obj \
	$(INTDIR)/cpu-h8300.obj \
	$(INTDIR)/h8300-dis.obj \
	$(INTDIR)/h8300-tdep.obj \
	$(INTDIR)/reloc16.obj \
	$(INTDIR)/remote-e7000.obj \
	$(INTDIR)/remote-hms.obj \
	$(INTDIR)/remote-sim.obj \
	$(INTDIR)/ser-e7kpc.obj \
	$(INTDIR)/stab-syms.obj \
	$(INTDIR)/version.obj 

TARGET_SBRS=  \
	$(INTDIR)/coff-h8300.sbr \
	$(INTDIR)/compile.sbr \
	$(INTDIR)/cpu-h8300.sbr \
	$(INTDIR)/h8300-dis.sbr \
	$(INTDIR)/h8300-tdep.sbr \
	$(INTDIR)/reloc16.sbr \
	$(INTDIR)/remote-e7000.sbr \
	$(INTDIR)/remote-hms.sbr \
	$(INTDIR)/remote-sim.sbr \
	$(INTDIR)/ser-e7kpc.sbr \
	$(INTDIR)/stab-syms.sbr \
	$(INTDIR)/version.sbr 

!include "common.mak"

# ======= rules for e7kpc support =========
# build dlls for e7000pc support on Windows
!include "e7kpc.mak"

# ======= rules for simulator =========
# simulator

TARGET_LIBLIB_OBJS= \
	$(INTDIR)\alloca.obj \
	$(INTDIR)\bcopy.obj 

#these top 2 were already separate...
TARGET_LIBBFD_OBJS=  \
	$(INTDIR)\ecoff.obj \
	$(INTDIR)\ecofflink.obj \
	$(INTDIR)\coff-h8300.obj \
	$(INTDIR)\coffgen.obj

GENCODE=engine.c
!include "sim.mak"

$(INTDIR)\sim\run.obj : $(SRCDIR)\sim\common\run.c
$(INTDIR)\sim\callback.obj : $(SRCDIR)\gdb\callback.c
$(INTDIR)\sim\interp.obj : $(SRCDIR)\sim\$(TARGET)\interp.c $(SRCDIR)\gdb\mswin\prebuilt\$(TARGET)\engine.c

