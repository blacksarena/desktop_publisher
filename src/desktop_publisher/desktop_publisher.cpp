#include "desktop_publisher/desktop_publisher.hpp"

using namespace desktop_publisher_node;

DesktopPublisher::DesktopPublisher()
{
}

void DesktopPublisher::onInit()
{
    ros::NodeHandle nh = getNodeHandle();
    _timer = nh.createTimer(ros::Duration(0.1), boost::bind(&DesktopPublisher::timerCb, this, _1));
    _it = new image_transport::ImageTransport(nh);
    _image_pub = new image_transport::Publisher(_it->advertise("clip_image", 10));
    _cw = new CaptureWindow;
    _cw->show();
}

void DesktopPublisher::timerCb(const ros::TimerEvent& event)
{
    cv::Mat conv = _cw->getCaptureImage();
    // ここがおかしい
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgra8", conv).toImageMsg();

    //cv::imshow("test", conv);
    _image_pub->publish(msg);
}

/*#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/image_encodings.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

const cv::Size clip_size(800, 480);

cv::Mat convertQImageToCvMat(const QSize &image_size, const QImage &source, int image_type = CV_8UC4)
{
    cv::Mat mat(image_size.height(), image_size.width(), image_type, (void*)source.bits());
    return mat;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "image_converter");
    QApplication a(argc, argv);
    QPixmap pix = QGuiApplication::primaryScreen()->grabWindow(0, 100, 100, clip_size.width, clip_size.height);
    QImage clip_desktop = pix.toImage();
    cv::Mat clip(convertQImageToCvMat(QSize(800, 480), clip_desktop));
    //cv::Mat clip(clip_size, CV_8UC4, clip_desktop.bits());
    cv::imshow("test", clip);
    cv::waitKey(0);
	//ros::spin();
	return 0;
}*/