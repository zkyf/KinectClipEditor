#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define _USE_OPENCV
#include "EasyKinect.h"
#include "viewmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
		explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
		ViewModel viewModel;

public slots:
		void SetGraphicsViewContent(int, int, uchar*);
};

#endif // MAINWINDOW_H
