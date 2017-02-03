#include "viewmodel.h"

ViewModel::ViewModel()
{
	nowHead = 0;
	nowEnd = 0;
	nowPos = 0;
	lastPos = -1;
	totalLen = 0;
	playing = false;
	running = true;
	opened = false;
	nowFrame = cv::Mat();
}

void ViewModel::stop()
{
	if(opened)
	{
		stream.Close();
	}
	running = false;
	playing = false;
}

void ViewModel::run()
{
	while(running)
	{
		if(!opened)
		{
			nowFrame = cv::Mat(nowFrame.size(), CV_8UC3, cv::Scalar::all(0));
		}
		else if(nowFrame.empty() || lastPos!=nowPos)
		{
			nowFrame = stream.Read();
			lastPos = nowPos;
			nowPos = nowPos+1;
			if(nowPos>=totalLen) nowPos = nowHead;
			cv::cvtColor(nowFrame, nowFrame, CV_BGR2RGB);
		}
		emit NewFrame(header.width, header.height, nowFrame.data);
	}
}

void ViewModel::Play()
{
	if(!opened) return;
	playing = true;
}

void ViewModel::Pause()
{
	if(!opened) return;
	playing = false;
}

void ViewModel::Goto(int pos)
{
	if(!opened) return;
	if(pos>=0 && pos<totalLen)
	{
		nowPos = pos;
	}
}

void ViewModel::SetHead(int head)
{
	if(!opened) return;
	if(head>=0 && head<=nowEnd)
	{
		nowHead = head;
	}
}

void ViewModel::SetEnd(int end)
{
	if(!opened) return;
	if(end<totalLen && end>=nowHead)
	{
		nowEnd = end;
	}
}

void ViewModel::Save(QString newFileName)
{
	if(!opened)
	{
		return;
	}
	MatStream target;
	MatStreamHeader newHeader;
	newHeader = header;
	newHeader.frameNum = 0;
	target.SetHead(newHeader);
	target.Open(
				string((const char*)
							 newFileName.toLocal8Bit()), MatStream::Op::out);
	stream.SeekMat(nowHead);
	for(int i =nowHead; i<=nowEnd;i++)
	{
		cv::Mat frame;
		frame = stream.Read();
		target.Write(frame);
	}
	target.Close();
}

void ViewModel::Open(QString newFileName)
{
	if(opened)
	{
		Close();
	}
	string fileName((const char*)newFileName.toLocal8Bit());
	stream.Open(fileName, MatStream::Op::in);
	header = stream.GetHead();
	totalLen = header.frameNum;
	nowHead = 0;
	nowPos = 0;
	nowEnd = totalLen-1;
	opened = true;
	playing = false;
	qDebug("ViewModel::Open\n");
	qDebug("Header:\n");
	qDebug("totalLen=%d\n\n", totalLen);
}

void ViewModel::Close()
{
	if(opened)
	{
		opened = false;
		playing = false;
		stream.Close();
	}
}

void ViewModel::Next()
{

}

void ViewModel::Prev()
{

}
