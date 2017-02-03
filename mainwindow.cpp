#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetGraphicsViewContent(int width, int height, uchar* data)
{
	QGraphicsScene* scene = new QGraphicsScene();
	scene->addPixmap(
				QPixmap::fromImage(
					QImage(data, width, height,
								 QImage::Format_RGB888)));
	ui->graphicsView->setScene(scene);
	ui->graphicsView->adjustSize();
	ui->graphicsView->show();
}