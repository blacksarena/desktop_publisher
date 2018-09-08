#ifndef DESKTOPPUBLISHER_HPP
#define DESKTOPPUBLISHER_HPP

#include "ros/ros.h"
#include "nodelet/nodelet.h"
#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/image_encodings.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "capture_window.hpp"

namespace desktop_publisher_node
{
	class DesktopPublisher : public nodelet::Nodelet
	{
		public:
			DesktopPublisher();

		private:
			virtual void onInit();
			void timerCb(const ros::TimerEvent& event);

			//ros::Subscriber _sub;
			//ros::Publisher _pub;
			ros::Timer _timer;
			CaptureWindow *_cw;
			image_transport::ImageTransport *_it;
			image_transport::Publisher *_image_pub;
	};
} // namespace desktop_publisher

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(desktop_publisher_node::DesktopPublisher, nodelet::Nodelet);

#endif// DESKTOPPUBLISHER_HPP
