#-------------------------------------------------
#
# Project created by QtCreator 2024-11-15T15:45:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperResolution
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

include("./SuperResolution/SuperResolution.pri")


#OPENCV_LIB_PATH = D:/work/OpenCV_x64_lib_Debug
##OPENCV_LIB_PATH = D:/QtTool/install

#INCLUDEPATH += $${OPENCV_LIB_PATH}/include
#LIBS += -L$${OPENCV_LIB_PATH}/x64/vc15/lib
#LIBS += -lopencv_core470d
#LIBS += -lopencv_dnn470d
#LIBS += -lopencv_dnn_superres470d
#LIBS += -lopencv_highgui470d
#LIBS += -lopencv_imgproc470d
#LIBS += -lopencv_imgcodecs470d
#LIBS += -lopencv_img_hash470d

#LIBS += -lopencv_core460
#LIBS += -lopencv_dnn460
#LIBS += -lopencv_dnn_superres460
#LIBS += -lopencv_highgui460
#LIBS += -lopencv_imgproc460


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
