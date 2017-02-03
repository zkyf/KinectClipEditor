#include "viewmodel.h"

ViewModel::ViewModel()
{
	nowHead = 0;
	nowEnd = 0;
	nowPos = 0;
	totalLen = 0;
	playing = false;
	running = false;
}

void ViewModel::stop()
{
	if(running)
	{
		stream.Close();
	}
}

void ViewModel::run()
{

}

void ViewModel::Play()
{
	if(!running) return;
	playing = true;
}

void ViewModel::Stop()
{
	if(!running) return;
	playing = false;
}

void ViewModel::Goto(int pos)
{
	if(!running) return;
	if(pos>=0 && pos<totalLen)
	{
		nowPos = pos;
	}
}

void ViewModel::SetHead(int head)
{
	if(!running) return;
	if(head>=0 && head<=nowEnd)
	{
		nowHead = head;
	}
}

void ViewModel::SetEnd(int end)
{
	if(!running) return;
	if(end<totalLen && end>=nowHead)
	{
		nowEnd = end;
	}
}

void ViewModel::Save(QString newFileName)
{
	MatStream target;
	vector<cv::Mat>
}
