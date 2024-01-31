# Microsoft Developer Studio Project File - Name="bfd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (ALPHA) Static Library" 0x0604

CFG=bfd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bfd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bfd.mak" CFG="bfd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bfd - Win32 Release" (based on "Win32 (ALPHA) Static Library")
!MESSAGE "bfd - Win32 Debug" (based on "Win32 (ALPHA) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "bfd - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AlphaRel"
# PROP BASE Intermediate_Dir "AlphaRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AlphaRel"
# PROP Intermediate_Dir "AlphaRel"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gt0 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gt0 /GX /O2 /I "." /I "./../include" /D "ALMOST_STDC" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "bfd - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AlphaDbg"
# PROP BASE Intermediate_Dir "AlphaDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AlphaDbg"
# PROP Intermediate_Dir "AlphaDbg"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gt0 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gt0 /GX /Z7 /Od /I "." /I "./../include" /D "ALMOST_STDC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "bfd - Win32 Release"
# Name "bfd - Win32 Debug"
# Begin Source File

SOURCE=.\archive.c
DEP_CPP_ARCHI=\
	"..\include\ansidecl.h"\
	"..\include\aout\ar.h"\
	"..\include\aout\ranlib.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\archures.c
DEP_CPP_ARCHU=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\bfd.c
DEP_CPP_BFD_C=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\ecoff.h"\
	"..\include\coff\internal.h"\
	"..\include\coff\sym.h"\
	"..\include\elf\common.h"\
	"..\include\elf\external.h"\
	"..\include\elf\internal.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	".\bfd.h"\
	".\config.h"\
	".\elf-bfd.h"\
	".\libbfd.h"\
	".\libcoff.h"\
	".\libecoff.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\binary.c
DEP_CPP_BINAR=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\cache.c
DEP_CPP_CACHE=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\coffgen.c
DEP_CPP_COFFG=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\internal.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\libcoff.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\cofflink.c
DEP_CPP_COFFL=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\internal.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\libcoff.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\corefile.c
DEP_CPP_COREF=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=".\cpu-alpha.c"
DEP_CPP_CPU_A=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\elf.c
DEP_CPP_ELF_C=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\elf\common.h"\
	"..\include\elf\external.h"\
	"..\include\elf\internal.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\elf-bfd.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\format.c
DEP_CPP_FORMA=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\hash.c
DEP_CPP_HASH_=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\objalloc.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\ihex.c
DEP_CPP_IHEX_=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\init.c
DEP_CPP_INIT_=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\libbfd.c
DEP_CPP_LIBBF=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\linker.c
DEP_CPP_LINKE=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\genlink.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\opncls.c
DEP_CPP_OPNCL=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\objalloc.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=".\pe-nt_alpha.c"
DEP_CPP_PE_NT=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\internal.h"\
	"..\include\coff\nt_alpha.h"\
	"..\include\coff\pe.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\obstack.h"\
	".\bfd.h"\
	".\coff-nt_alpha.c"\
	".\coffcode.h"\
	".\coffswap.h"\
	".\config.h"\
	".\libbfd.h"\
	".\libcoff.h"\
	".\peicode.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_PE_NT=\
	".\Your aouthdr magic number is not being set!"\
	
# End Source File
# Begin Source File

SOURCE=".\pei-nt_alpha.c"
DEP_CPP_PEI_N=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\coff\internal.h"\
	"..\include\coff\nt_alpha.h"\
	"..\include\coff\pe.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\obstack.h"\
	".\bfd.h"\
	".\coff-nt_alpha.c"\
	".\coffcode.h"\
	".\coffswap.h"\
	".\config.h"\
	".\libbfd.h"\
	".\libcoff.h"\
	".\peicode.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_PEI_N=\
	".\Your aouthdr magic number is not being set!"\
	
# End Source File
# Begin Source File

SOURCE=.\reloc.c
DEP_CPP_RELOC=\
	"..\include\ansidecl.h"\
	"..\include\bfdlink.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\section.c
DEP_CPP_SECTI=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\srec.c
DEP_CPP_SREC_=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=".\stab-syms.c"
DEP_CPP_STAB_=\
	"..\include\ansidecl.h"\
	"..\include\aout\aout64.h"\
	"..\include\aout\stab.def"\
	"..\include\bfdlink.h"\
	".\bfd.h"\
	".\libaout.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stabs.c
DEP_CPP_STABS=\
	"..\include\ansidecl.h"\
	"..\include\aout\stab.def"\
	"..\include\aout\stab_gnu.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\syms.c
DEP_CPP_SYMS_=\
	"..\include\ansidecl.h"\
	"..\include\aout\stab.def"\
	"..\include\aout\stab_gnu.h"\
	"..\include\bfdlink.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\targets.c
DEP_CPP_TARGE=\
	"..\include\ansidecl.h"\
	"..\include\fnmatch.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	".\targmatch.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# Begin Source File

SOURCE=.\tekhex.c
DEP_CPP_TEKHE=\
	"..\include\ansidecl.h"\
	"..\include\fopen-bin.h"\
	"..\include\fopen-same.h"\
	"..\include\libiberty.h"\
	".\bfd.h"\
	".\config.h"\
	".\libbfd.h"\
	".\sysdep.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
# End Source File
# End Target
# End Project
