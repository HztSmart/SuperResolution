#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    superResol = new SuperResolution;
    thread = new QThread();
    superResol->moveToThread(thread);

    connect(superResol, &SuperResolution::superComplete, this, &MainWindow::showMat);
//    connect(superResol, &SuperResolution::sendImage, this, [=](QImage img){
//        QImage temp = img.copy();
//        ui->label->setPixmap(QPixmap::fromImage(temp));
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showImage(QImage &img)
{

}

void MainWindow::showMat(Mat img)
{
    QImage image = SuperResolution::matToQImage(img);
//    QMetaObject::invokeMethod(superResol, "matToQImage", Qt::QueuedConnection , Q_ARG(Mat, img), Q_RETURN_ARG(QImage, image));

//    imshow("img", img);
    QString saveName = "./test.png";
    QMetaObject::invokeMethod(superResol, "saveOutputImage", Qt::QueuedConnection, Q_ARG(QString, saveName));
    ui->label->setPixmap(QPixmap::fromImage(image));
    if(thread->isRunning()){
        thread->quit();
        thread->wait();
        qDebug() << __FUNCTION__;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString imgPath = "D:/QtTool/SuperResolutionDome/Model/image.png";
    QString modelName = "D:/QtTool/SuperResolutionDome/Model/ESPCN_x4.pb";
    if(!thread->isRunning()){
        superResol->setModelFile(modelName);
        superResol->setInputImage(imgPath);
//        QMetaObject::invokeMethod(superResol, "setInputImage", Qt::QueuedConnection , Q_ARG(QString, imgPath));
        thread->start();
        QMetaObject::invokeMethod(superResol, "upsample", Qt::QueuedConnection);
//        superResol->setInputImage(imgPath);
//        superResol->upsample();
    }
}
