#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "./SuperResolution/SuperResolution.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showImage(QImage &img);

public slots:
    void showMat(Mat img);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    SuperResolution *superResol;
    QThread *thread;

};

#endif // MAINWINDOW_H
