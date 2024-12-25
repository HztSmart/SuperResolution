#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QImage>

#include "./SuperResolution/SuperResolution.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QString imgPath = "D:/QtTool/SuperResolutionDome/Model/dog.jpg";
//    QString modelPath = "D:/QtTool/SuperResolutionDome/Model/FSRCNN_x2.pb";

//    Mat img=cv::imread(imgPath.toStdString());
//    Mat img2 = SuperResolution::qImageToMat(QImage(imgPath));
//    Mat result;
//    result = SuperResolution::upscaleWithSuperRes(img, 2, "fsrcnn", modelPath);

//    cv::dnn_superres::DnnSuperResImpl super;
//    super.readModel(modelPath.toStdString());       // 加载模型
//    super.setModel("edsr", 4);                      // 模型类型和放大倍数
//    super.upsample(img, result);                    // 超分辨率处理

//    QImage image = SuperResolution::matToQImage(result);
//    w.showImage(image);
//    cv::imshow("img", img);
//    cv::imshow("result", result);
    return a.exec();
}
