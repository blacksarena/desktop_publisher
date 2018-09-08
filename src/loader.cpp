#include "ros/ros.h"
#include "nodelet/loader.h"
#include <signal.h>
#include <thread>

#include <QtWidgets/QtWidgets>

void signalhandler(int sig)
{
    qApp->quit();
}

void rosSpin()
{
	while(ros::ok()){
		ros::spin();
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "desktop_publisher");
	std::thread th = std::thread(&rosSpin);
	th.detach();
	QApplication a(argc, argv);
    signal(SIGQUIT, signalhandler);
    signal(SIGINT, signalhandler);
    signal(SIGTERM, signalhandler);
    signal(SIGHUP, signalhandler);
	nodelet::Loader nodelet;
	nodelet::M_string remap(ros::names::getRemappings());
	nodelet::V_string nargv;
	std::string nodelet_name = ros::this_node::getName();
	nodelet.load(nodelet_name, "desktop_publisher_node/DesktopPublisher", remap, nargv);
	return a.exec();
}