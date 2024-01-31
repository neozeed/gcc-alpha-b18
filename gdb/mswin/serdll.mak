
#====================== serdll.mak ============================

# Make file for serdll32.c -> serdll32.dll
# and for serdll16.c -> serdll16.dll

!include "config.mak"

all: $(MSVCENV) $(SER_DEPS) $(MSVCENV16) $(SER_DEPS16)

#====================== WinNT serial support ============================

!IF "$(HOST)" == "WINNT" || "$(HOST)" == "WIN31"


sernt: $(MSVCENV) $(SER_DEPSNT)

# Update the object file if necessary
# $* - path/name of target
# $@ - path/name.ext of target
# $< - path/name.ext of dep

#!IF "$(INCLUDE)" == "$(INCLUDE32)"
!include <ntwin32.mak>
#!include "$(MSVC32)\INCLUDE\ntwin32.mak"
#!include "$(MSVC32)\INCLUDE\win32.mak"
#!ELSE
#guilibs= msvcrt.lib oldnames.lib user32.lib gdi32.lib comdlg32.lib\
# winspool.lib kernel32.lib advapi32.lib
#!ENDIF

$(INTDIR)\serdllnt.obj: $(MSWINDIR)\serdll32.c $(MSWINDIR)\serdll32.h $(MSVCENV)
	@echo ======= building serdllnt.obj =========
	copy $(MSWINDIR)\serdll32.c $(INTDIR)\serdllnt.c
    $(cc) $(cflags) -DBUILD_DLL $(cvarsdll) $(cdebug) $(COMMON_INCS) $(INTDIR)\serdllnt.c /Fo$@ $(CCOPTS)


$(OUTDIR)\serdllnt.lib $(OUTDIR)\serdllnt.exp: $(INTDIR)\serdllnt.obj $(MSWINDIR)\serdllnt.def $(MSVCENV)
	@echo ======= building serdllnt.lib and serdllnt.exp =========
     $(implib) -machine:$(CPU) -def:$(MSWINDIR)\serdllnt.def $(INTDIR)\serdllnt.obj -out:$*.lib

$(OUTDIR)\serdllnt.dll: $(INTDIR)\serdllnt.obj $(MSWINDIR)\serdllnt.def $(OUTDIR)\serdllnt.exp $(MSVCENV)
	@echo ======= building serdllnt.dll =========
    $(link) $(conflags) $(ldebug) -dll -entry:DllInit$(DLLENTRY) -base:0x20800000 -out:$@ $(OUTDIR)\serdllnt.exp $(INTDIR)\serdllnt.obj $(guilibsdll) $(MSWINDIR)\w32sut32.lib mpr.lib

$(OUTDIR)\serdll32.lib $(OUTDIR)\serdll32.exp: $(INTDIR)\serdllnt.obj $(MSWINDIR)\serdll32.def $(MSVCENV)
	@echo ======= building serdll32.lib and serdll32.exp =========
     $(implib) -machine:$(CPU) -def:$(MSWINDIR)\serdll32.def $(INTDIR)\serdllnt.obj -out:$*.lib

serdll32.dll: $(OUTDIR)\serdll32.dll
$(OUTDIR)\serdll32.dll: $(OUTDIR)\serdllnt.dll
	copy $(OUTDIR)\serdllnt.dll $(OUTDIR)\serdll32.dll

!ENDIF ###"$(HOST)" == "WINNT" || "$(HOST)" == "WIN31"
#========================================================================

#====================== Win3.1 with Win32s serial support ==================
!IF "$(HOST)" == "WIN31"

PROJ16 = serdll16
#CC16 = $(MSVC16)\bin\cl -I. $(COMMON_INCS) /Fo$(INTDIR)\serdll16.obj /Fr$(INTDIR)\serdll16.sbr
CC16_WIN31 = -I. $(COMMON_INCS) /Fo$(INTDIR)\serdll16.obj /Fr$(INTDIR)\serdll16.sbr

CFLAGS_D_WDLL16 = /nologo /W3 /G2 /Zi /D_DEBUG /Od /GD $(MEMMOD16) /Fd$(OUTDIR)\"serdll16.PDB" $(CCOPTS)
CFLAGS_R_WDLL16 = /nologo /W3 /O1 /DNDEBUG /GD $(MEMMOD16) $(CCOPTS)
LFLAGS_D_WDLL16 = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /NOE /ALIGN:16 /MAP:FULL /DEBUG 
LFLAGS_R_WDLL16 = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /NOE /ALIGN:16 /MAP:FULL

LIBS_D_WDLL16 = oldnames libw commdlg ldllcew
LIBS_R_WDLL16 = oldnames libw commdlg ldllcew

RCFLAGS16 = /nologo
RESFLAGS16 = /nologo

DEFFILE16 = $(MSWINDIR)\$(PROJ16).DEF

!if "$(DEBUG)" == "_DEBUG"
CFLAGS16 = $(CFLAGS_D_WDLL16)
LFLAGS16 = $(LFLAGS_D_WDLL16)
LIBS16 = $(LIBS_D_WDLL16)
MAPFILE = $(PROJ16).map 
RCDEFINES16 = $(D_RCDEFINES16)
SER_DEPS31=$(SER_DEPS31) $(OUTDIR)\$(PROJ16).BSC
DOBJS=$(INTDIR)\debugi16.obj
!else
CFLAGS16 = $(CFLAGS_R_WDLL16)
LFLAGS16 = $(LFLAGS_R_WDLL16)
LIBS16 = $(LIBS_R_WDLL16)
MAPFILE = nul
!endif

!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS16 = $(INTDIR)\$(PROJ16).SBR


ser16:  $(MSVCENV16) $(SER_DEPS31)


#rem $(CC16) $(CFLAGS16) $(CUSEPCHFLAG16) /c $(MSWINDIR)\$(PROJ16).c
$(INTDIR)\$(PROJ16).OBJ: $(MSWINDIR)\$(PROJ16).c $(MSVCENV16)
	@echo ======= building serdll16.obj =========
	$(SETMSVC16)
	$(CC16) @<<
$(CC16_WIN31) /c $(MSWINDIR)\$(PROJ16).C $(CFLAGS16) $(CUSEPCHFLAG16) $(CCOPTS)
<<
	$(SETMSVC)


#don't need this:        $(RC16) $(RESFLAGS16) $@
$(OUTDIR)\$(PROJ16).DLL:: $(INTDIR)\$(PROJ16).OBJ $(OBJS_EXT) $(DEFFILE16) $(DOBJS)
	@echo ======= building serdll16.dll =========
	$(SETMSVC16)
	echo >NUL @<<$(PROJ16).CRF
$(INTDIR)\$(PROJ16).OBJ $(DOBJS) +
$(OBJS_EXT)
$(OUTDIR)\$(PROJ16).DLL
$(MAPFILE)
$(MSWINDIR)\W32SUT16.LIB+
$(LIBS16)
$(DEFFILE16);
<<
	$(LINK16) $(LFLAGS16) @$(PROJ16).CRF
	$(SETMSVC)

$(OUTDIR)\$(PROJ16).LIB: $(OUTDIR)\$(PROJ16).DLL $(DEFFILE16) $(MSVCENV16)
	@echo ======= building serdll16.lib =========
	$(SETMSVC16)
	$(IMPLIB16) /nowep $(OUTDIR)\$(PROJ16).LIB $(OUTDIR)\$(PROJ16).DLL
	$(SETMSVC)


run: $(OUTDIR)\$(PROJ16).DLL
	$(SETMSVC16)
	$(OUTDIR)\$(PROJ16) $(RUNFLAGS16)
	$(SETMSVC)


$(OUTDIR)\$(PROJ16).BSC: $(SBRS16) $(MSVCENV16)
	@echo ======= building serdll16.bsc =========
	$(SETMSVC16)
	$(BSCMAKE16) @<<
/o$@ $(SBRS16)
<<
	$(SETMSVC)

!ENDIF ###"$(HOST)" == "WIN31"
#========================================================================


#====================== Win95 serial support ============================
!IF "$(HOST)" == "WIN95"

!IF "$(CFG)" == ""
CFG=Win32 Debug
!ENDIF 

#MTL=MkTypLib.exe
#CPP=cl.exe
#RSC=rc.exe

# /MT was included in the options below...
#SER_CFLAGS=/MT $(SER_CFLAGS)

SER_DEPS95 = $(MSVCENV) $(OUTDIR)/serdll95.dll 
!IF  "$(CFG)" == "Win32 Debug"
SER_DEPS95 = $(SER_DEPS95) $(OUTDIR)/serdll95.bsc
DFLAGS=/DEBUG /PDB:$(OUTDIR)/"serdll95.pdb" 
!ENDIF

ser95: $(SER_DEPS95)

!IF  "$(CFG)" == "Win32 Release"

MTL_PROJ=/nologo /D "NDEBUG" /win32 
CPP_PROJ=/nologo $(SER_CFLAGS) /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"serdll95.pch" /Fo$(INTDIR)/ /c $(COMMON_INCS)
#BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o$(OUTDIR)/"serdll95.bsc" 
BSC32_SBRS= \
	$(INTDIR)/serdll95.sbr

$(OUTDIR)/serdll95.bsc : $(OUTDIR)  $(BSC32_SBRS) $(MSVCENV)
	@echo ======= building serdll95.bsc =========
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

#LINK32=link.exe
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /MACHINE:I386 /DEF:"$(MSWINDIR)\serdll95.def"\
 /OUT:$(OUTDIR)/"serdll95.dll" /IMPLIB:$(OUTDIR)/"serdll95.lib" 

#-entry:DllInit $(guilibsdll)
LINK32_FLAGS2= -out:$@ $(OUTDIR)\serdll95.exp /IMPLIB:$(OUTDIR)/"serdll95.lib"\
 /NOLOGO /SUBSYSTEM:windows /INCREMENTAL:no\
 /MACHINE:I386 /DEF:"$(MSWINDIR)\serdll95.def" $(guilibsdll) 

LIBBIES=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
odbccp32.lib 

DEF_FILE=$(MSWINDIR)\serdll95.def
LINK32_OBJS= \
	$(INTDIR)/serdll95.obj
!IF "$(DEBUG)" == "_DEBUG"
LINK32_OBJS= $(LINK32_OBJS) $(INTDIR)\debugify.obj
!ENDIF

$(OUTDIR)\serdll95.lib $(OUTDIR)\serdll95.exp: $(INTDIR)\serdll95.obj $(MSWINDIR)\serdll95.def $(MSVCENV)
	@echo ======= building serdll95.lib and serdll95.exp =========
     $(IMPLIB) -machine:$(CPU) -def:$(MSWINDIR)\serdll95.def $(INTDIR)\serdll95.obj -out:$*.lib

$(OUTDIR)/serdll95.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS) $(MSVCENV)
	@echo ======= building serdll95.dll =========
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
  -dll -base:0x28000000 $(MSWINDIR)\w32sut32.lib mpr.lib 
<<




!ELSEIF  "$(CFG)" == "Win32 Debug"

MTL_PROJ=/nologo /D "_DEBUG" /win32 
CPP_PROJ=/nologo $(SER_CFLAGS) /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"serdll95.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"serdll95.pdb" /c $(COMMON_INCS)
#BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o$(OUTDIR)/"serdll95.bsc" 
BSC32_SBRS= \
	$(INTDIR)/serdll95.sbr

$(OUTDIR)/serdll95.bsc : $(OUTDIR)  $(BSC32_SBRS) $(MSVCENV)
	@echo ======= building serdll95.bsc =========
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

#LINK32=link.exe
LIBBIES=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib 

#-entry:DllInit $(guilibsdll)
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"serdll95.pdb" /DEBUG /MACHINE:I386 /DEF:"$(MSWINDIR)\serdll95.def"\
 /OUT:$(OUTDIR)/"serdll95.dll" /IMPLIB:$(OUTDIR)/"serdll95.lib" 

DEF_FILE=$(MSWINDIR)\serdll95.def
LINK32_OBJS= \
	$(INTDIR)/serdll95.obj \
	$(INTDIR)\debugify.obj

$(OUTDIR)/serdll95.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS) $(MSVCENV)
	@echo ======= building serdll95.dll =========
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
  -dll -base:0x28000000 $(MSWINDIR)\w32sut32.lib mpr.lib 
<<

!ENDIF #"$(CFG)" == "Win32 Debug"

$(OUTDIR)\serdll32.lib $(OUTDIR)\serdll32.exp: $(INTDIR)\serdll95.obj $(MSWINDIR)\serdll32.def $(MSVCENV)
	@echo ======= building serdll32.lib and serdll32.exp =========
     $(IMPLIB) -machine:$(CPU) -def:$(MSWINDIR)\serdll32.def $(INTDIR)\serdll95.obj -out:$*.lib

# put back; build serdll95, then copy to serdll32
# serdll32.dll should always be Win3.1 or WfW and must be the NT version
$(OUTDIR)\serdll32.dll: $(OUTDIR)\serdll95.dll
	copy $(OUTDIR)\serdll95.dll $(OUTDIR)\serdll32.dll

{$(MSWINDIR)}.c{$(INTDIR)}.obj:
   $(CPP) $(CPP_PROJ) $(CCOPTS) $<  

{$(MSWINDIR)}.cpp{$(INTDIR)}.obj:
   $(CPP) $(CPP_PROJ) $(CCOPTS) $<  

{$(MSWINDIR)}.cxx{$(INTDIR)}.obj: 
   $(CPP) $(CPP_PROJ) $(CCOPTS) $<  

SOURCE=$(MSWINDIR)\serdll32.c

$(INTDIR)/serdll95.obj : $(SOURCE) $(INTDIR) $(MSVCENV)
    $(CPP) @<<
   $(CPP_PROJ) -DBUILD_DLL $(CCOPTS) -I $(PREDIR) -I $(PREDIR)/$(TARGET) $(MSWINDIR)\serdll32.c /Fo$(INTDIR)\serdll95.obj
<<

!ENDIF ###"$(HOST)" == "WIN95"
#========================================================================

$(MSVCENV):
	@set INIT=$(MSVC32)\;
	@set PATH=$(PATH32)
	@set INCLUDE=$(INCLUDE32)
	@set LIB=$(LIB32)

$(MSVCENV16):
	@set INIT=$(MSVC16)\;
	@set PATH=$(PATH16)
	@set INCLUDE=$(INCLUDE16)
	@set LIB=$(LIB16)


#==================== sertest ===================================

SERTEST=sertest
TESTDIR=$(OUTDIR)\test

SERTEST_OBJS= \
    $(TESTDIR)\sertest.obj \
    $(TESTDIR)\serstub.obj \
    $(INTDIR)\serial.obj \
    $(INTDIR)\vasprintf.obj \
    $(INTDIR)\ser-win32s.obj \
    $(INTDIR)\debugo.obj 

!IF "$(DEBUG)" == "_DEBUG"
SERTEST_OBJS= $(SERTEST_OBJS) $(INTDIR)\debugify.obj
#SERTEST_DEBUG=/Fd$(OUTDIR)\sertest.pdb
#SERTEST_LDEBUG=-PDB:$(OUTDIR)\sertest.pdb -DEBUG -MAP:$(OUTDIR)\sertest.map   
!ENDIF

!IF "$(HOST)" == "WIN95"
SERDLL=serdll95
!ELSE
SERDLL=serdllnt
!ENDIF 
#$(TESTDIR)\(SERDLL).obj : 
#	$(guilibs) $(MSVC)\lib\msacm32.lib
guilibs= msvcrt.lib oldnames.lib user32.lib gdi32.lib comdlg32.lib\
	winspool.lib kernel32.lib advapi32.lib

SERTEST_LIBS= \
    $(MSVC)\lib\oldnames.lib\
    $(MSVC)\lib\user32.lib\
    $(MSVC)\lib\kernel32.lib


TESTDLL=0

!IF "$(HOST)" == "WIN31" || "$(TESTDLL)" == "0"
SERTEST_LFLAGS=$(SERTEST_LFLAGS) /SUBSYSTEM:windows 
!ELSE
SERTEST_LFLAGS=$(SERTEST_LFLAGS) /SUBSYSTEM:console 
!ENDIF
!IF "$(HOST)" == "WIN31" 
SERDEPS16=$(SERDEPS16) $(OUTDIR)\serdll16.dll
!ENDIF

SERTEST_CFLAGS=$(SERTEST_CFLAGS) $(COMMON_INCS) -I $(MSWINDIR)\prebuilt\$(TARGET)
!IF "$(TESTDLL)" == "1"
SERTEST_LFLAGS=$(SERTEST_LFLAGS) $(OUTDIR)\$(SERDLL).lib
SERTEST_CFLAGS=$(SERTEST_CFLAGS) -DBUILD_DLL -DTESTDLL
SERDEPS=$(SERDEPS) $(OUTDIR)\$(SERDLL).dll
!ELSE
SERTEST_OBJS=$(SERTEST_OBJS) $(TESTDIR)\$(SERDLL).obj
SERTEST_CFLAGS=$(SERTEST_CFLAGS) /DSTATIC_LINK
SERTEST_LIBS= $(SERTEST_LIBS) $(MSVC32)\mfc\lib\mfc30d.lib
!ENDIF

sertest : $(OUTDIR) $(INTDIR) $(TESTDIR) $(MSVCENV) $(TESTDIR)\$(SERTEST).exe $(SERTEST_DEPS) $(MSVCENV16) $(SERTEST_DEPS16)

$(TESTDIR) : $(OUTDIR)
	-mkdir $(TESTDIR)

#$(SERTEST_LIBS)
$(TESTDIR)\$(SERTEST).exe : $(TESTDIR) $(INTDIR) $(SERTEST_OBJS) 
        @echo ======= linking $(OUTDIR)\$(SERTEST).exe ======
    $(LINK32) @<<
  $(SERTEST_LFLAGS) $(LFLAGS) $(SERTEST_OBJS) $(SERTEST_LIBS) $(TARGET_LFLAGS) /OUT:$(TESTDIR)\$(SERTEST).exe 
<<

$(TESTDIR)\sertest.obj : $(SRCDIR)\gdb\mswin\sertest.c
	$(CPP) @<<
$(GDB_CFLAGS) $(CFLAGS) $(CCOPTS) $(SERTEST_CFLAGS) $(SRCDIR)\gdb\mswin\sertest.c /Fo$(TESTDIR)/
<<

$(TESTDIR)\serstub.obj : $(SRCDIR)\gdb\mswin\serstub.c
	$(CPP) @<<
$(GDB_CFLAGS) $(CFLAGS) $(CCOPTS) $(SRCDIR)\gdb\mswin\serstub.c /Fo$(TESTDIR)/
<<

$(INTDIR)\debugo.obj : $(SRCDIR)\gdb\mswin\debugo.c
	$(CPP) @<<
$(GDB_CFLAGS) $(CFLAGS) $(CCOPTS) $(SRCDIR)\gdb\mswin\debugo.c
<<

$(INTDIR)\vasprintf.obj : $(SRCDIR)\libiberty\vasprintf.c
	$(CPP) @<<
$(GDB_CFLAGS) $(CFLAGS) $(CCOPTS) $(SRCDIR)\libiberty\vasprintf.c
<<

$(INTDIR)\serial.obj : $(SRCDIR)\gdb\serial.c
	$(CPP) @<<
$(GDB_CFLAGS) $(CFLAGS) $(CCOPTS) $(SRCDIR)\gdb\serial.c
<<

$(INTDIR)\ser-win32s.obj : $(SRCDIR)\gdb\mswin\ser-win32s.c
	$(CPP) @<<
$(GDB_CFLAGS) $(CFLAGS) $(CCOPTS) $(SRCDIR)\gdb\mswin\ser-win32s.c
<<

!IF "$(HOST)" == "WIN95"
SERDLL_CFLAGS= $(CPP_PROJ) $(CCOPTS) -I $(PREDIR) -I $(PREDIR)/$(TARGET) $(SERTEST_CFLAGS)

!ELSE
!include <ntwin32.mak>
SERDLL_CFLAGS= $(cflags) $(cdebug) $(CCOPTS) $(SERTEST_CFLAGS) 
#$(cvarsdll) 
!ENDIF

$(TESTDIR)\$(SERDLL).obj: $(MSWINDIR)\serdll32.c $(MSWINDIR)\serdll32.h $(MSVCENV)
	@echo ======= building $(TESTDIR)\$(SERDLL).obj =========
	$(CPP) @<<
$(SERDLL_CFLAGS) $(MSWINDIR)\serdll32.c /Fo$(TESTDIR)\$(SERDLL).obj
<<

