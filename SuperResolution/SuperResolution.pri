SOURCES += \
        $$PWD\SuperResolution.cpp \

HEADERS += \
        $$PWD\SuperResolution.h


OPENCV_LIB_PATH = D:/QtTool/SuperResolutionDome/OpenCV_x64_lib
#OPENCV_LIB_PATH = D:/QtTool/install

INCLUDEPATH += $${OPENCV_LIB_PATH}/include
LIBS += -L$${OPENCV_LIB_PATH}/x64/vc15/lib
LIBS += -L$${OPENCV_LIB_PATH}/x64/vc15/bin
LIBS += -lopencv_core470
LIBS += -lopencv_dnn470
LIBS += -lopencv_dnn_superres470
LIBS += -lopencv_highgui470
LIBS += -lopencv_imgproc470
LIBS += -lopencv_imgcodecs470
LIBS += -lopencv_img_hash470

#LIBS += -lopencv_core460
#LIBS += -lopencv_dnn460
#LIBS += -lopencv_dnn_superres460
#LIBS += -lopencv_highgui460
#LIBS += -lopencv_imgproc460
