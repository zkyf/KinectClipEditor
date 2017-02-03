#include "mainwindow.h"
#include <QApplication>
#define _USE_OPENCV
#include "EasyKinect.h"

int main(int argc, char *argv[])
{
    cv::Mat mat(480, 640, CV_8UC3, cv::Scalar::all(255));
    cv::imshow("mat", mat);
    cv::waitKey();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
