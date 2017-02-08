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
	loading = false;
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
			qDebug("opened running\n");
			if(loading) continue;
			lastPos = nowPos;
			qDebug("nowPos = %d\n", nowPos);
			nowFrame = frames[nowPos].clone();
			if(playing) nowPos = nowPos+1;
			if(nowPos>nowEnd)
			{
				nowPos = nowHead;
			}
			nowFrame.convertTo(nowFrame, CV_8U, 1/10.0);
			cv::cvtColor(nowFrame, nowFrame, CV_GRAY2RGB);
			Sleep(40);
			emit NewFrame(header.width, header.height, nowFrame.data);
			SendStreamInfo();
		}
	}
}

void ViewModel::Play()
{
	if(!opened) return;
	Next();
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

void ViewModel::SetHead()
{
	if(!opened) return;
	if(nowPos>=0 && nowPos<=nowEnd)
	{
		nowHead = nowPos;
	}
	SendStreamInfo();
}

void ViewModel::SetEnd()
{
	if(!opened) return;
	if(nowPos<totalLen && nowPos>=nowHead)
	{
		nowEnd = nowPos;
	}
	SendStreamInfo();
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
	if(stream.Fail()) return;
	header = stream.GetHead();
	totalLen = header.frameNum;
	nowHead = 0;
	nowPos = 0;
	nowEnd = totalLen-1;
	opened = true;
	playing = false;
	loading = true;
	for(int i =0; i<totalLen; i++)
	{
		cv::Mat newFrame;
		newFrame = stream.Read();
		frames.push_back(newFrame.clone());
	}
	loading = false;
	if(!loading) qDebug("Loaded!\n");
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
		frames.clear();
		stream.Close();
		nowPos = 0;
		nowHead = 0;
		nowEnd = 0;
		lastPos = -1;
		totalLen = 0;
		SendStreamInfo();
	}
}

void ViewModel::Next()
{
	if(!opened) return;
	nowPos++;
	if(nowPos>nowEnd) nowPos = nowHead;
	SendStreamInfo();
}

void ViewModel::Prev()
{
	if(!opened) return;
	nowPos--;
	if(nowPos<nowHead) nowPos = nowEnd;
	SendStreamInfo();
}

void ViewModel::ToHead()
{
	if(!opened) return;
	nowPos = nowHead;
	SendStreamInfo();
}

void ViewModel::ToEnd()
{
	if(!opened) return;
	nowPos = nowEnd;
	SendStreamInfo();
}

void ViewModel::SendStreamInfo()
{
	if(!opened) return;
	emit StreamInfo(nowHead, nowEnd, nowPos, totalLen);
}
