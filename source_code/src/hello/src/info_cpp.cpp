#include <ros/ros.h>



int main(int argc, char *argv[])
{
    ros::init(argc, argv, "node_name");
    
    ros::NodeHandle nh;

    ros::Rate rate(1);

    int count = 0;

    while (ros::ok())
    {
        ROS_INFO("count:%d",count++);
        rate.sleep();
    }  
    return 0;
}




