#include "mainwindow.h"
#include "viewmodel.h"
#include <QApplication>
#include <QEventLoop>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
		QEventLoop loop;
		MainWindow w;
		ViewModel viewModel;

		QObject::connect(
					&viewModel, &ViewModel::NewFrame,
					&w, &MainWindow::SetGraphicsViewContent,
					Qt::QueuedConnection);
		QObject::connect(
					&w, &MainWindow::Open,
					&viewModel, &ViewModel::Open,
					Qt::QueuedConnection);
		QObject::connect(
					&w, &MainWindow::Play,
					&viewModel, &ViewModel::Play,
					Qt::QueuedConnection);
		QObject::connect(
					&viewModel, &ViewModel::finished,
					&loop, &QEventLoop::quit,
					Qt::QueuedConnection);

    w.show();
		loop.exec();
		viewModel.start();

    return a.exec();
}
