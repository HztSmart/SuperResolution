#include"SuperResolution.h"
#include <QThread>

SuperResolution::SuperResolution(QObject *parent)
    :QObject(parent)
{
    qRegisterMetaType<Mat>("Mat");
//    QString modelPath = "D:/QtTool/SuperResolutionDome/Model/LapSRN_x2.pb";
//    setSuperConfig("lapsrn", 2, modelPath);
}

SuperResolution::~SuperResolution()
{

}

void SuperResolution::setModelFile(const QString &modelFile)
{
    QFileInfo info(modelFile);
    if(info.exists()){
        QStringList strlist = info.baseName().split("_");   //拆分文件名获取倍率和类型
        if(strlist.size() == 2){
            int salce = strlist[1].right(1).toInt();    //模型倍率
            QString modelType = strlist[0].toLower();   //模型类型
            if(modelType.contains("-")){
                QString temp = modelType.split("-")[0];
                modelType = temp.toLower();
            }
            setSuperConfig(modelType, salce, modelFile);
            qDebug() << "model type: " << modelType << "rate:" << salce;
        }

    }else {
        qDebug() << "Model file is not exist!";
    }
}

Mat SuperResolution::upscaleWithSuperRes(const Mat &input, int scale,
                                          const QString &modelName, const QString &modelPath)
{
    cv::dnn_superres::DnnSuperResImpl super;
    super.readModel(modelPath.toStdString());          // 加载模型
    super.setModel(modelName.toStdString(), scale);    // 模型类型和放大倍数
    Mat output;
    super.upsample(input, output);                     // 超分辨率处理
    return output;
}

void SuperResolution::setInputImage(const QString &inPath)
{
    inputImage = inPath;
//    upsample();
}

void SuperResolution::setSuperConfig(const QString &modelName, int scale, const QString &modelPath)
{
    resImpl.readModel(modelPath.toStdString());
    resImpl.setModel(modelName.toStdString(), scale);
}

QImage SuperResolution::matToQImage(const Mat mat)
{
    if (mat.empty()) {
        return QImage().copy();
    }

    cv::Mat rgbMat;
    if (mat.channels() == 1) {
        cv::cvtColor(mat, rgbMat, cv::COLOR_GRAY2RGB);
    } else if (mat.channels() == 3) {
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
    } else if (mat.channels() == 4) {
        cv::cvtColor(mat, rgbMat, cv::COLOR_BGRA2RGBA);
    } else {
        return QImage().copy();
    }

    return QImage(rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step[0], QImage::Format_RGB888).copy();
}

Mat SuperResolution::qImageToMat(const QImage &qImage)
{
   if (qImage.isNull()) {
       return cv::Mat();
   }

   switch (qImage.format()) {
        case QImage::Format_RGB32: {
            cv::Mat tmp(qImage.height(), qImage.width(), CV_8UC4, (uchar*)qImage.bits(), qImage.bytesPerLine());
            cv::Mat bgrMat;
            cv::cvtColor(tmp, bgrMat, cv::COLOR_BGRA2BGR);
            return bgrMat;
        }
        case QImage::Format_RGB888: {
            cv::Mat tmp(qImage.height(), qImage.width(), CV_8UC3, (uchar*)qImage.bits(), qImage.bytesPerLine());
            cv::Mat bgrMat;
            cv::cvtColor(tmp, bgrMat, cv::COLOR_RGB2BGR);
            return bgrMat;
        }
        case QImage::Format_Grayscale8: {
            return cv::Mat(qImage.height(), qImage.width(), CV_8UC1, (uchar*)qImage.bits(), qImage.bytesPerLine());
        }
        default: {
            return cv::Mat();
        }
    }
}

/*线程内输出图像*/
void SuperResolution::upsample()
{
    Mat img = imread(inputImage.toStdString());

    resImpl.upsample(img, outImg);
    Mat output = outImg;
    QImage outImg = matToQImage(output);

    emit superComplete(output);
    emit sendImage(outImg.copy());
//    output.release();
//    img.release();

}

void SuperResolution::saveOutputImage(const QString &imgName)
{
    if(imgName.isNull()){
        qDebug() << "Save file path is null!";
        return;
    }

    if(outImg.empty()){
        qDebug() << "No output image!";
        return;
    }

    if(!imwrite(imgName.toStdString(), outImg)){
        qDebug() << "Failed to save file";
        return;
    }
    outImg.release();   //释放图像数据
    if(outImg.empty()){
        qDebug() << "Mat clear over!";
    }
}
