QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    LIBUSB_Binary/examples/source/stdint.h \
    LIBUSB_Binary/include/libusb-1.0/libusb.h \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/libusb.h \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb.h \
    /usr/include/libusb-1.0/libusb.h \
    /usr/local/include/libusb-1.0/libusb.h \
    globales.h \
    libusb.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/LIBUSB_Binary/MinGW32/dll/ -llibusb-1.0.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/LIBUSB_Binary/MinGW32/dll/ -llibusb-1.0.dll

LIBS += -L/usr/local/lib -lusb-1.0

INCLUDEPATH += /usr/local/include/libusb-1.0
DEPENDPATH += /usr/local/include/libusb-1.0

#INCLUDEPATH += $$PWD/LIBUSB_Binary/MinGW32/dll
#DEPENDPATH += $$PWD/LIBUSB_Binary/MinGW32/dll


DISTFILES += \
    LIBUSB_Binary/MS32/dll/libusb-1.0.dll \
    LIBUSB_Binary/MS32/dll/libusb-1.0.lib \
    LIBUSB_Binary/MS32/dll/libusb-1.0.pdb \
    LIBUSB_Binary/MS32/static/libusb-1.0.lib \
    LIBUSB_Binary/MS64/dll/libusb-1.0.dll \
    LIBUSB_Binary/MS64/dll/libusb-1.0.lib \
    LIBUSB_Binary/MS64/dll/libusb-1.0.pdb \
    LIBUSB_Binary/MS64/static/libusb-1.0.lib \
    LIBUSB_Binary/MinGW32/dll/libusb-1.0.dll \
    LIBUSB_Binary/MinGW32/dll/libusb-1.0.dll.a \
    LIBUSB_Binary/MinGW32/static/libusb-1.0.a \
    LIBUSB_Binary/MinGW64/dll/libusb-1.0.dll \
    LIBUSB_Binary/MinGW64/dll/libusb-1.0.dll.a \
    LIBUSB_Binary/MinGW64/static/libusb-1.0.a \
    LIBUSB_Binary/README.txt \
    LIBUSB_Binary/examples/bin32/fxload.exe \
    LIBUSB_Binary/examples/bin32/listdevs.exe \
    LIBUSB_Binary/examples/bin32/xusb.exe \
    LIBUSB_Binary/examples/bin64/fxload.exe \
    LIBUSB_Binary/examples/bin64/listdevs.exe \
    LIBUSB_Binary/examples/bin64/xusb.exe \
    LIBUSB_Binary/libusb-1.0.23.7z \
    LIBUSB_Binary/libusb-1.0.def \
    README.md \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2017.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2015.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2015.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2015.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2017.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_2015.sln \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2013.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2015.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2013.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2019.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2017.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_2017.sln \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2017.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2019.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2013.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2015.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2019.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2013.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2013.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2013.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2017.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/testlibusb_2015.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_2019.sln \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2019.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2019.vcxproj.filters \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_2013.sln \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_static_2017.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/msvc/libusb_dll_2019.vcxproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/.libs/libusb-1.0.la \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/.libs/libusb-1.0.so \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/.libs/libusb-1.0.lai \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/.libs/libusb-1.0.so.0 \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/.libs/libusb-1.0.so.0.3.0 \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/.libs/libusb-1.0.a \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/libusb-1.0.la \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/libusbi.h \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/libusb-1.0.rc \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/libusb-1.0.def \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb/libusb.h \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb-1.0.pc.in \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/libusb-1.0.pc \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/tests/libusb_testlib.h \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/android/jni/libusb.mk \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/Xcode/libusb.xcodeproj \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/Xcode/libusb_release.xcconfig \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/Xcode/libusb_debug.xcconfig \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb-1.0.24/Xcode/libusb.xcconfig \
    /home/zero/Desktop/UTN/6/Proyecto final/LPC/proyecto-final/qt/libusb.h \
    /lib/i386-linux-gnu/libusb-0.1.so.4 \
    /lib/i386-linux-gnu/libusb-0.1.so.4.4.4 \
    /lib/i386-linux-gnu/libusb-1.0.so.0 \
    /lib/i386-linux-gnu/libusb-1.0.so.0.1.0 \
    /lib/x86_64-linux-gnu/libusb-0.1.so.4 \
    /lib/x86_64-linux-gnu/libusb-0.1.so.4.4.4 \
    /lib/x86_64-linux-gnu/libusb-1.0.so.0 \
    /lib/x86_64-linux-gnu/libusb-1.0.so.0.1.0 \
    /usr/include/libusb-1.0 \
    /usr/include/libusb-1.0/libusb.h \
    /usr/local/include/libusb-1.0 \
    /usr/local/include/libusb-1.0/libusb.h \
    /usr/local/lib/libusb-1.0.la \
    /usr/local/lib/libusb-1.0.so \
    /usr/local/lib/pkgconfig/libusb-1.0.pc \
    /usr/local/lib/libusb-1.0.so.0 \
    /usr/local/lib/libusb-1.0.so.0.3.0 \
    /usr/local/lib/libusb-1.0.a



