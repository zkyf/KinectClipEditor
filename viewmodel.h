#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "MatStream.h"
#include <Windows.h>
#include <QString>
#include <QMessageBox>
#include <QThread>
#include <QDebug>

#include <string>
#include <vector>
using namespace std;

class ViewModel : public QThread
{
	Q_OBJECT
	public:
    ViewModel();

		class Exceptions
		{
			public:
				class Unknown{};
		};

		void stop();

	protected:
		void run();

	private:
		MatStream stream;
		MatStreamHeader header;
		cv::Mat nowFrame;
		QString fileName;
		int nowHead;
		int nowEnd;
		int nowPos;
		int lastPos;
		int totalLen;
		bool playing;
		bool running;
		bool opened;

	signals:
		void NewFrame(int width, int height, uchar* data);
		void StreamInfo(int nowHead, int nowEnd, int nowPos, int totalLen);

	public slots:
		void Play();
		void Pause();
		void Goto(int pos);
		void SetHead(int head);
		void SetEnd(int end);
		void Save(QString newFileName);
		void Open(QString newFileName);
		void Close();
		void Next();
		void Prev();
};

#endif // VIEWMODEL_H
