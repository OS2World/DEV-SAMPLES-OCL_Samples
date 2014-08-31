# makefile
# Created by IBM WorkFrame/2 MakeMake at 1:02:45 on 19 June 1997
#
# The actions included in this make file are:
#  Compile::Resource Compiler
#  Compile::C++ Compiler (OCL/UICL - Dynamic)
#  Link::Linker (OCL/UICL - Production)
#  Bind::Resource Bind

.SUFFIXES: .cpp .obj .rc .res 

.all: \
    .\ocl_ani1.exe

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

{d:\c_dev\be_ball}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r %s %|dpfF.RES

.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

{d:\c_dev\be_ball}.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

.\ocl_ani1.exe: \
    .\ocl_ani1.obj \
    .\ocl_ani1.res \
    makefile
    @echo " Link::Linker (OCL/UICL - Production) "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /exepack:2 /pmtype:pm /packd /optfunc"
     /Feocl_ani1.exe 
     .\ocl_ani1.obj
<<
    rc.exe .\ocl_ani1.res ocl_ani1.exe

.\ocl_ani1.res: \
    d:\c_dev\be_ball\ocl_ani1.rc \
    {d:\c_dev\be_ball;$(INCLUDE)}ocl_ani1.dlg \
    {d:\c_dev\be_ball;$(INCLUDE)}ocl_ani1.h \
    {d:\c_dev\be_ball;$(INCLUDE)}cap.ico \
    makefile

.\ocl_ani1.obj: \
    d:\c_dev\be_ball\ocl_ani1.cpp \
    {d:\c_dev\be_ball;$(INCLUDE);}ocl_ani1.hpp \
    {d:\c_dev\be_ball;$(INCLUDE);}ocl_ani1.h \
    makefile
