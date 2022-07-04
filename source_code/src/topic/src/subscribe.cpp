#include "ros/ros.h"
#include "std_msgs/String.h"

void doMsg(const std_msgs::String::ConstPtr& msg_p)
{
    ROS_INFO("new message:%s",msg_p->data.c_str());
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"topic_subscribe");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("topic_name",10,doMsg);

    ros::spin();

    return 0;
}
