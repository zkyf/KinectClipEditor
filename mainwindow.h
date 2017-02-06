#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>

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
		void Pause();
		void Next();
		void Prev();
		void ToHead();
		void ToEnd();
		void SetHead();
		void SetEnd();
		void Close();
		void Save(QString);
		void GoTo(int);

public slots:
		void SetGraphicsViewContent(int, int, uchar*);
		void GetStreamInfo(int, int, int, int);
	private slots:
		void on_buttonOpen_clicked();
		void on_buttonPlay_clicked();
		void on_buttonPause_clicked();
		void on_buttonSetHead_clicked();
		void on_buttonToHead_clicked();
		void on_buttonPrev_clicked();
		void on_buttonNext_clicked();
		void on_buttonToEnd_clicked();
		void on_buttonSetEnd_clicked();
		void on_slider_sliderMoved(int position);
		void on_buttonSave_clicked();
		void on_buttonClose_clicked();
};

#endif // MAINWINDOW_H
