#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
		//ui->graphicsView->hide();
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
//	ui->graphicsView->setScene(scene);
//	ui->graphicsView->adjustSize();
//	ui->graphicsView->show();
	ui->graph->setPixmap(
				QPixmap::fromImage(
					QImage(data, width, height,
								 QImage::Format_RGB888))
				);
}

void MainWindow::GetStreamInfo(int nowHead, int nowEnd, int nowPos, int totalLen)
{
	ui->labelHeadPos->setNum(nowHead);
	ui->labelEndPos->setNum(nowEnd);
	ui->labelNowPos->setNum(nowPos);
	ui->labelTotalLen->setNum(totalLen);

	ui->slider->setRange(0, totalLen);
	ui->slider->setValue(nowPos);
}

void MainWindow::on_buttonOpen_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
				this, tr("Open file"), ".",
				tr("All file(*.*)")
				);
	emit Open(fileName);
}

void MainWindow::on_buttonPlay_clicked()
{
	emit Play();
}

void MainWindow::on_buttonPause_clicked()
{
	emit Pause();
}

void MainWindow::on_buttonSetHead_clicked()
{
	emit SetHead();
}

void MainWindow::on_buttonToHead_clicked()
{
	emit ToHead();
}

void MainWindow::on_buttonPrev_clicked()
{
	emit Prev();
}

void MainWindow::on_buttonNext_clicked()
{
	emit Next();
}

void MainWindow::on_buttonToEnd_clicked()
{
	emit ToEnd();
}

void MainWindow::on_buttonSetEnd_clicked()
{
	emit SetEnd();
}

void MainWindow::on_slider_sliderMoved(int position)
{
	emit GoTo(position);
}

void MainWindow::on_buttonSave_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(
				this, tr("Open file"), ".",
				tr("All file(*.*)")
				);
	emit Save(fileName);
}

void MainWindow::on_buttonClose_clicked()
{
		emit Close();
}
