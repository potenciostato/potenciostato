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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/LIBUSB_Binary/MinGW32/dll/ -llibusb-1.0.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/LIBUSB_Binary/MinGW32/dll/ -llibusb-1.0.dll

INCLUDEPATH += $$PWD/LIBUSB_Binary/MinGW32/dll
DEPENDPATH += $$PWD/LIBUSB_Binary/MinGW32/dll

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
    README.md
