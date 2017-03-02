mkdir doxygensourses
copy trscore.h doxygensourses\trscore.h
copy testinfo.h doxygensourses\testinfo.h
copy suiteinfo.h doxygensourses\suiteinfo.h
cd doxygensourses
doxygen -g Doxyfile
doxygen Doxyfile
mkdir ..\html
mkdir ..\html\search
copy html ..\html\
copy html\search ..\html\search
cd ..
rmdir /Q /S doxygensourses
html\index.html