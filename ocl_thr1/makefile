# makefile
# Created by IBM WorkFrame/2 MakeMake at 18:51:04 on 1 July 1997
#
# The actions included in this make file are:
#  Compile::Resource Compiler
#  Compile::C++ Compiler (OCL/UICL - Dynamic)
#  Link::Linker (OCL/UICL - Production)
#  Bind::Resource Bind

.SUFFIXES: .cpp .obj .rc .res 

.all: \
    .\ocl_thr1.exe

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r -x2 %s %|dpfF.RES

{D:\c_dev\ocl_thr}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r -x2 %s %|dpfF.RES

.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

{D:\c_dev\ocl_thr}.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

.\ocl_thr1.exe: \
    .\ocl_thr1.obj \
    .\ocl_thr1.res \
    makefile
    @echo " Link::Linker (OCL/UICL - Production) "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /exepack:2 /pmtype:pm /packd /optfunc"
     /Feocl_thr1.exe 
     .\ocl_thr1.obj
<<
    rc.exe .\ocl_thr1.res ocl_thr1.exe

.\ocl_thr1.res: \
    D:\c_dev\ocl_thr\ocl_thr1.rc \
    {D:\c_dev\ocl_thr;$(INCLUDE)}ocl_thr1.dlg \
    {D:\c_dev\ocl_thr;$(INCLUDE)}ocl_thr1.h \
    {D:\c_dev\ocl_thr;$(INCLUDE)}boxes.ico \
    makefile

.\ocl_thr1.obj: \
    D:\c_dev\ocl_thr\ocl_thr1.cpp \
    {D:\c_dev\ocl_thr;$(INCLUDE);}ocl_thr1.h \
    makefile
