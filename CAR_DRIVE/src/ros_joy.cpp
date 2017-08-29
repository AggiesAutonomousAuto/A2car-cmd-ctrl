#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>

using namespace std;

class CmdCtrl
{

	public:
		CmdCtrl();

	private:
		void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

		ros::NodeHandle nh_;
		ros::Publisher  vel_pub_;
		ros::Subscriber joy_sub_;
		ros::Subscriber image_data_sub_;
};


CmdCtrl::CmdCtrl()
{
	vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
	joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &CmdCtrl::joyCallback, this);
}

void CmdCtrl::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	geometry_msgs::Twist twist;
	twist.linear.x = joy->axes[5]; //velocity
	twist.linear.z = joy->buttons[0];
	twist.linear.y = joy->buttons[1];
	twist.angular.z = joy->axes[0];
	vel_pub_.publish(twist);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "command_control");
	CmdCtrl command_control;
	ros::spin();
}
