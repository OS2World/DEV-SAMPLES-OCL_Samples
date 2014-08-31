# makefile
# Created by IBM WorkFrame/2 MakeMake at 17:16:05 on 6 July 1997
#
# The actions included in this make file are:
#  Compile::Resource Compiler
#  Compile::C++ Compiler (OCL/UICL - Dynamic)
#  Link::Linker (OCL/UICL - Production)
#  Bind::Resource Bind

.SUFFIXES: .cpp .obj .rc .res 

.all: \
    .\ocl_ani2.exe

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r -x2 %s %|dpfF.RES

{D:\c_dev\ocl_ani2}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r -x2 %s %|dpfF.RES

.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

{D:\c_dev\ocl_ani2}.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

.\ocl_ani2.exe: \
    .\ocl_ani2.obj \
    .\person.obj \
    .\application.obj \
    .\ocl_ani2.res
    @echo " Link::Linker (OCL/UICL - Production) "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /exepack:2 /pmtype:pm /packd /optfunc"
     /Feocl_ani2.exe 
     .\ocl_ani2.obj
     .\person.obj
     .\application.obj
<<
    rc.exe .\ocl_ani2.res ocl_ani2.exe

!include "makefile.DEP"