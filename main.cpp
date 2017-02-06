#include "mainwindow.h"
#include "viewmodel.h"
#include <QApplication>
#include <QEventLoop>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	ViewModel viewModel;

	QObject::connect(
				&viewModel, &ViewModel::NewFrame,
				&w, &MainWindow::SetGraphicsViewContent,
				Qt::QueuedConnection);
	QObject::connect(
				&viewModel, &ViewModel::StreamInfo,
				&w, &MainWindow::GetStreamInfo,
				Qt::QueuedConnection);

	QObject::connect(
				&w, &MainWindow::Open,
				&viewModel, &ViewModel::Open,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::Save,
				&viewModel, &ViewModel::Save,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::Play,
				&viewModel, &ViewModel::Play,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::Pause,
				&viewModel, &ViewModel::Pause,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::Prev,
				&viewModel, &ViewModel::Prev,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::Next,
				&viewModel, &ViewModel::Next,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::ToHead,
				&viewModel, &ViewModel::ToHead,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::ToEnd,
				&viewModel, &ViewModel::ToEnd,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::GoTo,
				&viewModel, &ViewModel::Goto,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::SetHead,
				&viewModel, &ViewModel::SetHead,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::SetEnd,
				&viewModel, &ViewModel::SetEnd,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::Close,
				&viewModel, &ViewModel::Close,
				Qt::QueuedConnection);


	w.show();
	viewModel.start();

	int returnValue = a.exec();
	viewModel.exit();
	return returnValue;
}
