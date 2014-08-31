# makefile
# Created by IBM WorkFrame/2 MakeMake at 18:41:56 on 21 June 1997
#
# The actions included in this make file are:
#  Compile::Resource Compiler
#  Compile::C++ Compiler (OCL/UICL - Dynamic)
#  Link::Linker (OCL/UICL - Production)
#  Bind::Resource Bind

.SUFFIXES: .cpp .obj .rc .res 

.all: \
    .\ocl_con1.exe

.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r -x2 %s %|dpfF.RES

{d:\c_dev\ocl_con1}.rc.res:
    @echo " Compile::Resource Compiler "
    rc.exe -r -x2 %s %|dpfF.RES

.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

{d:\c_dev\ocl_con1}.cpp.obj:
    @echo " Compile::C++ Compiler (OCL/UICL - Dynamic) "
    icc.exe /Fi /Si /O /Gm /Gd /G5 /Gu /C %s

.\ocl_con1.exe: \
    .\ocl_con1.obj \
    .\ocl_con1.res \
    makefile
    @echo " Link::Linker (OCL/UICL - Production) "
    @echo " Bind::Resource Bind "
    icc.exe @<<
     /B" /exepack:2 /pmtype:pm /packd /optfunc"
     /Feocl_con1.exe 
     .\ocl_con1.obj
<<
    rc.exe .\ocl_con1.res ocl_con1.exe

.\ocl_con1.res: \
    d:\c_dev\ocl_con1\ocl_con1.rc \
    {d:\c_dev\ocl_con1;$(INCLUDE)}ocl_con1.dlg \
    {d:\c_dev\ocl_con1;$(INCLUDE)}ocl_con1.h \
    {d:\c_dev\ocl_con1;$(INCLUDE)}person4.ico \
    {d:\c_dev\ocl_con1;$(INCLUDE)}person3.ico \
    {d:\c_dev\ocl_con1;$(INCLUDE)}person2.ico \
    {d:\c_dev\ocl_con1;$(INCLUDE)}person.ico \
    {d:\c_dev\ocl_con1;$(INCLUDE)}people.ico \
    {d:\c_dev\ocl_con1;$(INCLUDE)}boxes.ico \
    makefile

.\ocl_con1.obj: \
    d:\c_dev\ocl_con1\ocl_con1.cpp \
    {d:\c_dev\ocl_con1;$(INCLUDE);}ocl_con1.h \
    makefile
