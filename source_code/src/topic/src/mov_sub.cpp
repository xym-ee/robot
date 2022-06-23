#include "ros/ros.h"
#include "topic/move.h"


void sub_cb(const topic::move::ConstPtr& msg_p)
{
    ROS_INFO("status:%d, v:%d, r:%d", msg_p->status,msg_p->velocity,msg_p->rotate);
}


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "mov_sub");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<topic::move>("move_msg", 1000, sub_cb);

    ros::spin();

    return 0;
}



