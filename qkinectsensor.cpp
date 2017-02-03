#include "qkinectsensor.h"

QKinectSensor::QKinectSensor()
{
	sensor = new KinectSensor();
	types = FrameSourceTypes_None;
	hr = false;
	if(!sensor)
	{
		throw Exceptions::NewSensor();
	}
}

HRESULT QKinectSensor::Init(FrameSourceTypes _types)
{
	if(!sensor) return E_HANDLE;
	HRESULT hr = sensor->init(_types);
	if(SUCCEEDED(hr))
	{
		running = true;
		types = _types;
	}
	return hr;
}

void QKinectSensor::run()
{
	if(!running)
	{
		throw Exceptions::SensorNotRunning();
	}
	while(running)
	{
		HRESULT hr = sensor->update();
		if(FAILED(hr)) continue;
		bool flag = false;
		if(types | FrameSourceTypes_Color)
		{
			cv::Mat newMat = sensor->getColorMat();
			if(!newMat.empty())
			{
				lastColorFrame = newMat.clone();
				flag = true;
			}
		}
		if(types | FrameSourceTypes_Infrared)
		{
			cv::Mat newMat = sensor->getInfraMat();
			if(!newMat.empty())
			{
				lastInfraFrame = newMat.clone();
				flag = true;
			}
		}
		if(types | FrameSourceTypes_Depth)
		{
			cv::Mat newMat = sensor->getDepthMat();
			if(!newMat.empty())
			{
				lastDepthFrame = newMat.clone();
				flag = true;
			}
		}
		if(flag)
		{
			emit KinectNewFrameArrived();
		}
	}
}
