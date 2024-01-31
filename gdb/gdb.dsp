# Microsoft Developer Studio Project File - Name="gdb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (ALPHA) Console Application" 0x0603

CFG=gdb - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gdb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gdb.mak" CFG="gdb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gdb - Win32 Release" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "gdb - Win32 Debug" (based on "Win32 (ALPHA) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gdb - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaRel"
# PROP BASE Intermediate_Dir "AlphaRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaRel"
# PROP Intermediate_Dir "AlphaRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gt0 /GX /O2 /I "." /I "./config" /I "./../include/opcode" /I "./../readline" /I "../bfd" /I "./../bfd" /I "./../mmalloc" /I "./../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D NO_MMALLOC=1 /D "ALMOST_STDC" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:ALPHA
# ADD LINK32 ../alpharel/bfd.lib ../alpharel/libiberty.lib ../alpharel/opcodes.lib ../alpharel/readline.lib /nologo /base:"0x2aa00000" /subsystem:console /machine:ALPHA

!ELSEIF  "$(CFG)" == "gdb - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaDbg"
# PROP BASE Intermediate_Dir "AlphaDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaDbg"
# PROP Intermediate_Dir "AlphaDbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gt0 /GX /Zi /Od /I "." /I "./config" /I "./../include/opcode" /I "./../readline" /I "../bfd" /I "./../bfd" /I "./../mmalloc" /I "./../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D NO_MMALLOC=1 /D "ALMOST_STDC" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:ALPHA
# ADD LINK32 ../alphadbg/bfd.lib ../alphadbg/readline.lib ../alphadbg/opcodes.lib ../alphadbg/libiberty.lib /nologo /base:"0x2aa00000" /subsystem:console /debug /machine:ALPHA

!ENDIF 

# Begin Target

# Name "gdb - Win32 Release"
# Name "gdb - Win32 Debug"
# Begin Source File

SOURCE=".\ada-exp.tab.c"
DEP_CPP_ADA_E=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-lang.h"\
	".\ada-lex.c"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\parser-defs.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ada-lang.c"
DEP_CPP_ADA_L=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-lang.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\parser-defs.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_ADA_L=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ada-tasks.c"
DEP_CPP_ADA_T=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-tasks.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ada-typeprint.c"
DEP_CPP_ADA_TY=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-lang.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\typeprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_ADA_TY=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ada-valprint.c"
DEP_CPP_ADA_V=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-lang.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\tm.h"\
	".\valprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_ADA_V=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\alpha-tdep.c"
DEP_CPP_ALPHA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\alphant-nat.c"
DEP_CPP_ALPHAN=\
	"..\bfd\bfd.h"\
	"..\bfd\libcoff.h"\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\internal.h"\
	"..\include\coff\nt_alpha.h"\
	"..\include\coff\pe.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\annotate.c
DEP_CPP_ANNOT=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdbtypes.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\bcache.c
DEP_CPP_BCACH=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb_string.h"\
	".\nm.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\blockframe.c
DEP_CPP_BLOCK=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\breakpoint.c
DEP_CPP_BREAK=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-tasks.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbthread.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_BREAK=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\buildsym.c
DEP_CPP_BUILD=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\c-exp.tab.c"
DEP_CPP_C_EXP=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\parser-defs.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\c-lang.c"
DEP_CPP_C_LAN=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\c-typeprint.c"
DEP_CPP_C_TYP=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\typeprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_C_TYP=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\c-valprint.c"
DEP_CPP_C_VAL=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\tm.h"\
	".\valprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_C_VAL=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ch-exp.c"
DEP_CPP_CH_EX=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\ch-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\parser-defs.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ch-lang.c"
DEP_CPP_CH_LA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\ch-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ch-typeprint.c"
DEP_CPP_CH_TY=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\ch-lang.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\typeprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_CH_TY=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\ch-valprint.c"
DEP_CPP_CH_VA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\ch-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\tm.h"\
	".\typeprint.h"\
	".\valprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_CH_VA=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\coffread.c
DEP_CPP_COFFR=\
	"..\bfd\bfd.h"\
	"..\bfd\libcoff.h"\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\internal.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\buildsym.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb-stabs.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\command.c
DEP_CPP_COMMA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\include\wait.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbtypes.h"\
	".\nm.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\complaints.c
DEP_CPP_COMPL=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\command.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdbcmd.h"\
	".\nm.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\copying.c
DEP_CPP_COPYI=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdbcmd.h"\
	".\nm.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\corefile.c
DEP_CPP_COREF=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\cp-valprint.c"
DEP_CPP_CP_VA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbtypes.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_CP_VA=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\dbxread.c
DEP_CPP_DBXRE=\
	"..\bfd\bfd.h"\
	"..\bfd\libaout.h"\
	"..\include\ansidecl.h"\
	"..\include\aout\aout64.h"\
	"..\include\aout\stab.def"\
	"..\include\aout\stab_gnu.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\buildsym.h"\
	".\command.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb-stabs.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\partial-stab.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_DBXRE=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\dcache.c
DEP_CPP_DCACH=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\dcache.h"\
	".\defs.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\nm.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\demangle.c
DEP_CPP_DEMAN=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\nm.h"\
	".\tm.h"\
	".\xm.h"\
	
NODEP_CPP_DEMAN=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\dwarf2read.c
DEP_CPP_DWARF=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\elf\dwarf2.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_DWARF=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\dwarfread.c
DEP_CPP_DWARFR=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\elf\dwarf.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
NODEP_CPP_DWARFR=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\elfread.c
DEP_CPP_ELFRE=\
	"..\bfd\bfd.h"\
	"..\bfd\elf-bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\elf\common.h"\
	"..\include\elf\external.h"\
	"..\include\elf\internal.h"\
	"..\include\elf\mips.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb-stabs.h"\
	".\gdb_string.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
NODEP_CPP_ELFRE=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\environ.c
DEP_CPP_ENVIR=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\environ.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\nm.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\eval.c
DEP_CPP_EVAL_=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\f-lang.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_EVAL_=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\exec.c
DEP_CPP_EXEC_=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xcoffsolib.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\expprint.c
DEP_CPP_EXPPR=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\f-exp.tab.c"
DEP_CPP_F_EXP=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\f-lang.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\parser-defs.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\f-lang.c"
DEP_CPP_F_LAN=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\f-lang.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\f-typeprint.c"
DEP_CPP_F_TYP=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\f-lang.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\typeprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_F_TYP=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\f-valprint.c"
DEP_CPP_F_VAL=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\f-lang.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\tm.h"\
	".\valprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_F_VAL=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\findvar.c
DEP_CPP_FINDV=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\floatformat.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\gdbtypes.c
DEP_CPP_GDBTY=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_GDBTY=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\gnu-regex.c"
DEP_CPP_GNU_R=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb_string.h"\
	".\gnu-regex.h"\
	".\nm.h"\
	".\tm.h"\
	".\xm.h"\
	
NODEP_CPP_GNU_R=\
	".\buffer.h"\
	".\lisp.h"\
	".\syntax.h"\
	
# End Source File
# Begin Source File

SOURCE=.\infcmd.c
DEP_CPP_INFCM=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\environ.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\inflow.c
DEP_CPP_INFLO=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-tasks.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbthread.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\serial.h"\
	".\signals.h"\
	".\symtab.h"\
	".\target.h"\
	".\terminal.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\infrun.c
DEP_CPP_INFRU=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\include\wait.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-tasks.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbthread.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\init.c
DEP_CPP_INIT_=\
	"..\include\ansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\language.c
DEP_CPP_LANGU=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\m2-exp.tab.c"
DEP_CPP_M2_EX=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\m2-lang.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\parser-defs.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\m2-lang.c"
DEP_CPP_M2_LA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\m2-lang.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\m2-typeprint.c"
DEP_CPP_M2_TY=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\m2-lang.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_M2_TY=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\m2-valprint.c"
DEP_CPP_M2_VA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdbtypes.h"\
	".\m2-lang.h"\
	".\nm.h"\
	".\symtab.h"\
	".\tm.h"\
	".\valprint.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\main.c
DEP_CPP_MAIN_=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\getopt.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\call-cmds.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\top.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\maint.c
DEP_CPP_MAINT=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_MAINT=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\mdebugread.c
DEP_CPP_MDEBU=\
	"..\bfd\bfd.h"\
	"..\bfd\libaout.h"\
	"..\include\ansidecl.h"\
	"..\include\aout\aout64.h"\
	"..\include\aout\stab.def"\
	"..\include\aout\stab_gnu.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\ecoff.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb-stabs.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\partial-stab.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_MDEBU=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\mem-break.c"
DEP_CPP_MEM_B=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\minsyms.c
DEP_CPP_MINSY=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb-stabs.h"\
	".\gdb_string.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
NODEP_CPP_MINSY=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\mipsread.c
DEP_CPP_MIPSR=\
	"..\bfd\bfd.h"\
	"..\bfd\libcoff.h"\
	"..\bfd\libecoff.h"\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\ecoff.h"\
	"..\include\coff\internal.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\elf\common.h"\
	"..\include\elf\mips.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb-stabs.h"\
	".\gdb_string.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\nlmread.c
DEP_CPP_NLMRE=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb-stabs.h"\
	".\gdb_string.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\objfiles.c
DEP_CPP_OBJFI=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\gdb-stabs.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\os9kread.c
DEP_CPP_OS9KR=\
	"..\bfd\bfd.h"\
	"..\bfd\libaout.h"\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\os9k.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\buildsym.h"\
	".\command.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb-stabs.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_OS9KR=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\parse.c
DEP_CPP_PARSE=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-lang.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\printcmd.c
DEP_CPP_PRINT=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\valprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_PRINT=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=".\remote-utils.c"
DEP_CPP_REMOT=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\dcache.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\remote-utils.h"\
	".\serial.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\remote.c
DEP_CPP_REMOTE=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\include\wait.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\dcache.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb-stabs.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbthread.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\serial.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=".\scm-exp.c"
DEP_CPP_SCM_E=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\scm-lang.h"\
	".\scm-tags.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\scm-lang.c"
DEP_CPP_SCM_L=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\c-lang.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\scm-lang.h"\
	".\scm-tags.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=".\scm-valprint.c"
DEP_CPP_SCM_V=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\parser-defs.h"\
	".\scm-lang.h"\
	".\scm-tags.h"\
	".\symtab.h"\
	".\tm.h"\
	".\valprint.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\serial.c
DEP_CPP_SERIA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\debugify.h"\
	".\defs.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\nm.h"\
	".\serial.h"\
	".\tm.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\source.c
DEP_CPP_SOURC=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\gnu-regex.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stabsread.c
DEP_CPP_STABS=\
	"..\bfd\bfd.h"\
	"..\bfd\libaout.h"\
	"..\include\ansidecl.h"\
	"..\include\aout\aout64.h"\
	"..\include\aout\stab.def"\
	"..\include\aout\stab_gnu.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\buildsym.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb-stabs.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\stabsread.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\xm.h"\
	
NODEP_CPP_STABS=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stack.c
DEP_CPP_STACK=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_STACK=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\symfile.c
DEP_CPP_SYMFI=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\complaints.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb-stabs.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_SYMFI=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\symmisc.c
DEP_CPP_SYMMI=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\symtab.c
DEP_CPP_SYMTA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-lang.h"\
	".\bcache.h"\
	".\call-cmds.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\gnu-regex.h"\
	".\language.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_SYMTA=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\target.c
DEP_CPP_TARGE=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\include\wait.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\thread.c
DEP_CPP_THREA=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\environ.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdbcmd.h"\
	".\gdbthread.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\top.c
DEP_CPP_TOP_C=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	"..\readline\chardefs.h"\
	"..\readline\history.h"\
	"..\readline\keymaps.h"\
	"..\readline\readline.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\call-cmds.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_stat.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\signals.h"\
	".\symtab.h"\
	".\target.h"\
	".\terminal.h"\
	".\tm.h"\
	".\top.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\typeprint.c
DEP_CPP_TYPEP=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_TYPEP=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\utils.c
DEP_CPP_UTILS=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\floatformat.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	"..\readline\chardefs.h"\
	"..\readline\keymaps.h"\
	"..\readline\readline.h"\
	".\annotate.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\language.h"\
	".\nm.h"\
	".\serial.h"\
	".\signals.h"\
	".\target.h"\
	".\tm.h"\
	".\xm.h"\
	
NODEP_CPP_UTILS=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\valarith.c
DEP_CPP_VALAR=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_VALAR=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\valops.c
DEP_CPP_VALOP=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-lang.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_VALOP=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\valprint.c
DEP_CPP_VALPR=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\annotate.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\valprint.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_VALPR=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\values.c
DEP_CPP_VALUE=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\demangle.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\mmalloc\mmalloc.h"\
	".\bcache.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbtypes.h"\
	".\language.h"\
	".\nm.h"\
	".\scm-lang.h"\
	".\scm-tags.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	
NODEP_CPP_VALUE=\
	"..\include\gansidecl.h"\
	
# End Source File
# Begin Source File

SOURCE=.\version.c
# End Source File
# Begin Source File

SOURCE=".\win32-nat.c"
DEP_CPP_WIN32=\
	"..\bfd\bfd.h"\
	"..\include\ansidecl.h"\
	"..\include\coff\sym.h"\
	"..\include\coff\symconst.h"\
	"..\include\dis-asm.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	"..\include\obstack.h"\
	"..\include\progress.h"\
	"..\include\wait.h"\
	"..\mmalloc\mmalloc.h"\
	".\ada-tasks.h"\
	".\bcache.h"\
	".\breakpoint.h"\
	".\buildsym.h"\
	".\command.h"\
	".\config.h"\
	".\config\alpha\nm-cygwin32.h"\
	".\config\alpha\tm-alpha.h"\
	".\config\alpha\tm-cygwin32.h"\
	".\config\alpha\xm-cygwin32.h"\
	".\defs.h"\
	".\expression.h"\
	".\frame.h"\
	".\gdb_string.h"\
	".\gdbcmd.h"\
	".\gdbcore.h"\
	".\gdbthread.h"\
	".\gdbtypes.h"\
	".\inferior.h"\
	".\nm.h"\
	".\objfiles.h"\
	".\symfile.h"\
	".\symtab.h"\
	".\target.h"\
	".\tm.h"\
	".\value.h"\
	".\xm.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# End Target
# End Project
