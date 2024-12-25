#ifndef SURPERRESOLUTION
#define SURPERRESOLUTION

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QFileInfo>
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/dnn_superres.hpp"

using namespace std;
using namespace cv;
using namespace dnn;
using namespace dnn_superres;

#define MODEL_EDSR    "edsr"
#define MODEL_ESPCN   "espcn"
#define MODEL_FSRCNN  "fsrcnn"
#define MODEL_LAPSRN  "lapsrn"

class SuperResolution : public QObject{
    Q_OBJECT
public:
    SuperResolution(QObject *parent = nullptr);
    ~SuperResolution();

    Q_INVOKABLE void setModelFile(const QString &modelFile);
    Q_INVOKABLE void setInputImage(const QString &inPath);
    Q_INVOKABLE void setSuperConfig(const QString &modelName, int scale, const QString& modelPath);
    Q_INVOKABLE void upsample();
    Q_INVOKABLE void saveOutputImage(const QString &imgName);
    /**
     * @brief upscaleWithSuperRes
     * @param input     输入图像
     * @param scale     放大倍率
     * @param modelName 模型名
     * @param modelPath 模型路径
     */
    static Mat upscaleWithSuperRes(const Mat &input, int scale,
                                   const QString& modelName, const QString& modelPath);
    static QImage matToQImage(const cv::Mat mat);
    static Mat qImageToMat(const QImage& qImage);

signals:
    void superComplete(Mat);
    void sendImage(QImage);

private:
    cv::dnn_superres::DnnSuperResImpl resImpl;
    QString inputImage;

    Mat outImg;  //输出图像
};

#endif

