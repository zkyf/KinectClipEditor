#ifndef QKINECTSENSOR_H
#define QKINECTSENSOR_H

#define _USE_OPENCV
#include "EasyKinect.h"
#include <Windows.h>
#include <QString>

class QKinectSensor : public QThread
{
	public:
		struct Exceptions
		{
			struct Unknown { QString msg; };
			struct NewSensor : public Unknown {};
			struct SensorNotRunning : public Unknown {};
		};

		QKinectSensor();
		HRESULT Init(FrameSourceTypes);
		void run();
		void stop();
		cv::Mat lastColorFrame;
		cv::Mat lastInfraFrame;
		cv::Mat lastDepthFrame;

	private:
		KinectSensor* sensor;
		volatile bool running;
		FrameSourceTypes types;

	signals:
		void KinectNewFrameArrived();
};

#endif // QKINECTSENSOR_H
