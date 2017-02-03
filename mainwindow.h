#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

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

	signals:
		void Open(QString);
		void Play();

public slots:
		void SetGraphicsViewContent(int, int, uchar*);
	private slots:
		void on_buttonOpen_clicked();
		void on_buttonPlay_clicked();
};

#endif // MAINWINDOW_H
