#include "ros/ros.h"
#include "std_msgs/String.h" 
#include <sstream>

int main(int argc, char  *argv[])
{
    ros::init(argc,argv,"topic_publish");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("topic_name",10);
    std_msgs::String msg;
    std::string msg_front = "test_msg:"; 
    int count = 0; 
    ros::Rate r(1);

    while (ros::ok())
    {
        std::stringstream ss;
        ss << msg_front << count;
        msg.data = ss.str();
        pub.publish(msg);
        ROS_INFO("send messages:%s", msg.data.c_str());
        r.sleep();
        count++;
        ros::spinOnce();
    }
    return 0;
}







