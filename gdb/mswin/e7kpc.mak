
# makefile to create wingdb dlls for the e7000 pc target
# from mswin directory, run:
#	nmake -f e7kpc.mak

# target specific extras for config.mak

!IF "$(TARGET)" == ""
TARGET=sh
TARGET_CFLAGS= -D TARGET_SH 
!ENDIF

# target specific extras for common.mak
TARGET_DEPS16=$(TARGET_DEPS16) $(OUTDIR)\w95e7k16.dll $(OUTDIR)\w31e7k16.dll 
TARGET_DEPS=$(TARGET_DEPS) $(OUTDIR)\w95e7kpc.dll $(OUTDIR)\w31e7kpc.dll
!IF !$(CONFIG_INCLUDED)
!include "config.mak"
!ENDIF

# additional rules
DOBJS=$(INTDIR)\debugify.obj 
DOBJS16=$(INTDIR)\debugi16.obj 

# ======= build 32-bit dll for e7000pc support on Win95 =========
#         win95 uses qt_thunks to thunk to wvve7k16.dll

$(INTDIR)\w95e7kpc.lib $(OUTDIR)\w95e7kpc.exp: $(INTDIR)\w95e7kpc.obj $(MSWINDIR)\w95e7kpc.def $(MSVCENV)
        @echo ======= Building w95e7kpc.lib & w95e7kpc.exp =========
     $(IMPLIB) -machine:$(CPU) -def:$(MSWINDIR)\w95e7kpc.def $(INTDIR)\w95e7kpc.obj -out:$*.lib

WLIBS= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
	advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
	odbccp32.lib 
WOPTS= /NOLOGO /DEBUG /SUBSYSTEM:windows /INCREMENTAL:no /MACHINE:I386 

$(OUTDIR)\w95e7kpc.dll: $(INTDIR)\w95e7kpc.obj $(INTDIR)\w95thunk.lib $(MSWINDIR)\w95e7kpc.def $(DOBJS)
        @echo ======== Linking $(OUTDIR)\w95e7kpc.dll ========
	$(LINK32) @<<
	$(WOPTS)
	-dll -base:0x20600000 
	/PDB:$(OUTDIR)/"w95e7kpc.pdb" /MAP:$(OUTDIR)\w95e7kpc.map 
	/DEF:"$(MSWINDIR)\w95e7kpc.def" /IMPLIB:$(INTDIR)/"w95e7kpc.lib"
	/OUT:$(OUTDIR)\w95e7kpc.dll $(INTDIR)\w95e7kpc.obj 
	$(MSWINDIR)\w32sut32.lib mpr.lib
	$(DOBJS)
	$(INTDIR)\w95thunk.lib $(MSVC)\lib\thunk32.lib
	$(WLIBS) 
<<

$(INTDIR)\w95e7kpc.obj: $(MSWINDIR)\win-e7kpc.c $(MSWINDIR)\win-e7kpc.h 
        @echo ======= Building w95e7kpc.obj =========
	$(CC) @<<
  $(GDB_CFLAGS) $(CFLAGS) -D _WIN95 $(MSWINDIR)\win-e7kpc.c /Fo$(INTDIR)\w95e7kpc.obj
<<

$(INTDIR)\w95thunk.lib: $(MSWINDIR)\w95thunk.def 
        @echo ======== Creating $(INTDIR)\w95thunk.lib ========
	$(IMPLIB) /MACHINE:IX86 /DEF:$(MSWINDIR)\w95thunk.DEF -out:$(INTDIR)\w95thunk.lib


# ======= build 32-bit dll for e7000pc support on Win32s =========
#         win32s uses universal thunks to thunk to w31e7k16.dll

$(INTDIR)\w31e7kpc.lib $(OUTDIR)\w31e7kpc.exp: $(INTDIR)\w31e7kpc.obj $(MSWINDIR)\w31e7kpc.def $(MSVCENV)
        @echo ======= Building w31e7kpc.lib & w31e7kpc.exp =========
     $(IMPLIB) -machine:$(CPU) -def:$(MSWINDIR)\w31e7kpc.def $(INTDIR)\w31e7kpc.obj -out:$*.lib

WLIBS= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
	advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
	odbccp32.lib 
WOPTS= /NOLOGO /DEBUG /SUBSYSTEM:windows /INCREMENTAL:no /MACHINE:I386 

#Had to define a main in win-e7kpc.c since libc gets included.
#Tried using linker options:
#/NODEFAULTLIB:libc.lib msvcrt.lib
#but this requires msvcrt20.dll which is incompatible with win32s
$(OUTDIR)\w31e7kpc.dll: $(INTDIR)\w31e7kpc.obj $(MSWINDIR)\w31e7kpc.def $(DOBJS)
        @echo ======== Linking $(OUTDIR)\w31e7kpc.dll ========
	$(LINK32) @<<
	$(WOPTS)
	-dll -entry:DllMain -base:0x20600000
	/PDB:$(OUTDIR)/"w31e7kpc.pdb" /MAP:$(OUTDIR)\w31e7kpc.map 
	/DEF:"$(MSWINDIR)\w31e7kpc.def" /IMPLIB:$(INTDIR)/"w31e7kpc.lib"
	/OUT:$@ $(INTDIR)\w31e7kpc.obj 
	$(DOBJS)
	$(MSWINDIR)\w32sut32.lib mpr.lib
	$(WLIBS) 
<<

$(INTDIR)\w31e7kpc.obj: $(MSWINDIR)\win-e7kpc.c $(MSWINDIR)\win-e7kpc.h 
        @echo ======= Building w31e7kpc.obj =========
	$(CC) @<<
  $(GDB_CFLAGS) $(CFLAGS) -D _WIN32s $(MSWINDIR)\win-e7kpc.c /Fo$(INTDIR)\w31e7kpc.obj
<<

# ======= build 16-bit dll for e7000pc support on Win95 =========

$(INTDIR)\w95e7k16.obj: $(MSWINDIR)\win-e7kpc16.c $(MSWINDIR)\win-e7kpc.h $(MSVCENV16)
        @echo ======== Building $(INTDIR)\w95e7k16.obj ========
	copy $(MSWINDIR)\win-e7kpc16.c $(INTDIR)\w95e7k16.c
	$(SETMSVC16)
	$(DSET)
        echo >NUL @<<$(INTDIR)\w95e7k16.CRF
$(GDB_CFLAGS16) -D _WIN95
$(CFLAGS16)
$(INTDIR)\w95e7k16.c
<<
	copy $(INTDIR)\w95e7k16.CRF $(INTDIR)\w95e7k16.SAV
        $(CC16) @$(INTDIR)\w95e7k16.CRF
        $(SETMSVC)
	$(DSET)

$(OUTDIR)\w95e7k16.dll: $(INTDIR)\w95e7k16.obj $(MSWINDIR)\w95e7k16.def $(MSVCENV16) $(DOBJS16)
        @echo ======== Linking $(OUTDIR)\w95e7k16.dll ========
	$(SETMSVC16)
	$(LINK16) @<<
	$(LFLAGS16) /MAP:$(OUTDIR)\w95e7k16.map $(INTDIR)\w95e7k16.obj $(DOBJS16), $(OUTDIR)\w95e7k16.dll, , $(TARGET_LIBS_DLL16) , $(MSWINDIR)\w95e7k16.def
<<
	$(SETMSVC)

$(INTDIR)\w95e7k16.lib: $(MSWINDIR)\w95e7k16.def 
        @echo ======== Creating $(INTDIR)\w95e7k16.lib ========
	$(IMPLIB) /MACHINE:IX86 /DEF:$(MSWINDIR)\w95e7k16.def -out:$(INTDIR)\w95e7k16.lib

# ======= build 16-bit dll for e7000pc support on Win95 && Win32s =========

$(INTDIR)\w31e7k16.obj: $(MSWINDIR)\win-e7kpc16.c $(MSWINDIR)\win-e7kpc.h $(MSVCENV16)
        @echo ======== Building $(INTDIR)\w31e7k16.obj ========
	copy $(MSWINDIR)\win-e7kpc16.c $(INTDIR)\w31e7k16.c
	$(SETMSVC16)
	$(DSET)
        echo >NUL @<<$(INTDIR)\w31e7k16.CRF
$(GDB_CFLAGS16) -D _WIN32s
$(CFLAGS16)
$(INTDIR)\w31e7k16.c
<<
	copy $(INTDIR)\w31e7k16.CRF $(INTDIR)\w31e7k16.SAV
        $(CC16) @$(INTDIR)\w31e7k16.CRF
        $(SETMSVC)
	$(DSET)

$(OUTDIR)\w31e7k16.dll: $(INTDIR)\w31e7k16.obj $(MSWINDIR)\w31e7k16.def $(MSVCENV16) $(DOBJS16)
        @echo ======== Linking $(OUTDIR)\w31e7k16.dll ========
	$(SETMSVC16)
	$(LINK16) $(LFLAGS16) /MAP:$(OUTDIR)\w31e7k16.map $(INTDIR)\w31e7k16.obj $(DOBJS16), $(OUTDIR)\w31e7k16.dll, , $(TARGET_LIBS_DLL16) , $(MSWINDIR)\w31e7k16.def
	$(SETMSVC)

$(INTDIR)\w31e7k16.lib: $(MSWINDIR)\w31e7k16.def 
        @echo ======== Creating $(INTDIR)\w31e7k16.lib ========
	$(IMPLIB) /MACHINE:IX86 /DEF:$(MSWINDIR)\w31e7k16.def -out:$(INTDIR)\w31e7k16.lib

# ================== test program for e7000 pc ==========================
TESTDIR=$(OUTDIR)\test
!IF "$(HOST)" == "WIN95"
WvvE7KPC=w95e7kpc
WvvE7K16=w95e7k16
E7KPC_CFLAGS=$(CFLAGS) -D _WIN95
E7KPC_CFLAGS16=$(CFLAGS16) -D _WIN95
E7KPC_LFLAGS=$(LFLAGS) $(INTDIR)\w95thunk.lib $(MSVC)\lib\thunk32.lib -subsystem:console -entry:mainCRTStartup 
!ELSE
!IF "$(HOST)" == "WIN31"
WvvE7KPC=w31e7kpc
WvvE7K16=w31e7k16
E7KPC_CFLAGS=$(CFLAGS) -D _WIN32s
E7KPC_CFLAGS16=$(CFLAGS16) -D _WIN32s
E7KPC_LFLAGS=$(LFLAGS) $(MSVC)\lib\thunk32.lib -subsystem:windows
!ELSE
!IF "$(HOST)" == "WINNT"
!MESSAGE e7000pc support not supported on NT
E7KPC_CFLAGS=$(CFLAGS) -D _WINNT
E7KPC_CFLAGS16=$(CFLAGS16) -D _WINNT
!ENDIF
!ENDIF
!ENDIF
!IF "$(DEBUG)" == "_DEBUG"
E7KPC_CFLAGS=$(E7KPC_CFLAGS) /Zi -D _DEBUG /FR$(TESTDIR)\$(WvvE7KPC).sbr /Fd$(TESTDIR)\$(WvvE7KPC).pdb
E7KPC_CFLAGS16=$(E7KPC_CFLAGS16) /Zi -D _DEBUG /FR$(TESTDIR)\$(WvvE7K16).sbr /Fd$(TESTDIR)\$(WvvE7K16).pdb
E7KPC_LFLAGS=$(E7KPC_LFLAGS) /DEBUG /PDB:$(TESTDIR)\$(WvvE7KPC).pdb /MAP:$(TESTDIR)\$(WvvE7KPC).map 
E7KPC_LFLAGS16=$(E7KPC_LFLAGS16) /PDB:$(TESTDIR)\$(WvvE7K16).pdb 
#E7KPC_LFLAGS16=$(E7KPC_LFLAGS16) /DEBUG /PDB:$(TESTDIR)\$(WvvE7K16).pdb /MAP:$(TESTDIR)\$(WvvE7K16).map 
!ENDIF

# test get_mem & put_mem for e7000pc
test : $(MSVCENV) $(TESTDIR)\$(WvvE7KPC).exe $(MSVCENV16) $(TESTDIR)\$(WvvE7K16).dll

$(TESTDIR) : $(OUTDIR)
	-mkdir $(OUTDIR)\test

$(TESTDIR)\$(WvvE7KPC).obj: $(MSWINDIR)\win-e7kpc.c $(MSWINDIR)\win-e7kpc.h 
        @echo ======= Building $(TESTDIR)\$(WvvE7KPC).obj =========
	$(CC) @<<
  $(GDB_CFLAGS) $(E7KPC_CFLAGS) -D "STAND_ALONE" $(MSWINDIR)\win-e7kpc.c /Fo$(TESTDIR)\$(WvvE7KPC).obj"
<<

$(TESTDIR)\$(WvvE7K16).obj: $(MSWINDIR)\win-e7kpc16.c $(MSWINDIR)\win-e7kpc.h $(MSVCENV16)
        @echo ======= Building $(TESTDIR)\$(WvvE7K16).obj =========
	copy $(MSWINDIR)\win-e7kpc16.c $(TESTDIR)\$(WvvE7K16).c
	$(SETMSVC16)
	$(DSET)
	echo EFLAGS $(E7KPC_CFLAGS16) 
        echo >NUL @<<$(TESTDIR)\$(WvvE7K16).CRF
$(E7KPC_CFLAGS16) -D STAND_ALONE 
/Fo$(TESTDIR)\$(WvvE7K16).obj $(TESTDIR)\$(WvvE7K16).c 
<<
	copy $(TESTDIR)\$(WvvE7K16).CRF $(TESTDIR)\$(WvvE7K16).SAV
        $(CC16) @$(TESTDIR)\$(WvvE7K16).CRF
        $(SETMSVC)
	$(DSET)

$(TESTDIR)\$(WvvE7K16).dll: $(TESTDIR)\$(WvvE7K16).obj $(MSWINDIR)\$(WvvE7K16).def $(MSVCENV16) $(DOBJS16)
        @echo ======== Linking $(TESTDIR)\$(WvvE7K16).dll ========
	$(SETMSVC16)
	echo EFLAGS $(E7KPC_LFLAGS16) 
	echo LFLAGS $(LFLAGS16) 
        echo >NUL @<<$(TESTDIR)\$(WvvE7K16).CRF
$(LFLAGS16) $(E7KPC_LFLAGS16) $(TESTDIR)\$(WvvE7K16).obj $(DOBJS16), 
$(TESTDIR)\$(WvvE7K16).dll, 
$(TESTDIR)\$(WvvE7K16).map,
$(TARGET_LIBS_DLL16) , 
$(MSWINDIR)\$(WvvE7K16).def
<<
	$(LINK16) @$(TESTDIR)\$(WvvE7K16).CRF
	$(SETMSVC)


$(TESTDIR)\$(WvvE7KPC).exe: $(TESTDIR)\$(WvvE7KPC).obj $(MSVC)/lib/kernel32.lib $(MSVC)/lib/user32.lib  $(DOBJS)
        @echo ======== Linking $(TESTDIR)\$(WvvE7KPC).exe ========
	$(LINK32) @<<
	$(E7KPC_LFLAGS) $(TESTDIR)\$(WvvE7KPC).obj $(DOBJS) /out:$(TESTDIR)\$(WvvE7KPC).exe $(MSVC)/lib/kernel32.lib $(MSVC)/lib/user32.lib 
<<

