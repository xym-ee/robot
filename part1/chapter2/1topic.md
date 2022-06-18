---
sort: 1
---
# Topic


## 理论模型

Topic 实现模型涉及到三个东西：
- ROS Master
- Talker
- Listener

从这种通信方式的使用感觉上来讲 Talker 在说一个话题，对这个话题感兴趣的 Listerner 在偷偷的听，Talker并不知道有没有人在听。

但是底层实现为TCP协议，因此需要在底层建立连接， ROS Master 就是这个管事的，Talker 告诉 Master 在谈论的话题，Listener告诉Master感兴趣的话题，Master帮忙牵线搭桥。建立连接后，就没Master什么事了，这时候关掉这个东西也不影响通信，体会这个“牵线搭桥”作用。

Talker和Listener告诉Master的这个过程就是注册。

## C++实现

ROS master 已经有了，和计算机通信网络知识相关的TCP连接的建立也已经被封装了，很人性化，所以针对非计算机背景的机器人开发者，需要关注的关键点有三个:

- 使用ROS类实现发布方
- 使用ROS类实现接收方
- 数据(此处为普通文本)

```cpp
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char *argv[])
{   
    //设置编码
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"talker");

    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",10);

    std_msgs::String msg;

    std::string msg_front = "Hello 你好！"; //消息前缀
    int count = 0; //消息计数器

    ros::Rate r(1);

    while (ros::ok())
    {
        std::stringstream ss;
        ss << msg_front << count;
        msg.data = ss.str();
        pub.publish(msg);

        ROS_INFO("发送的消息:%s",msg.data.c_str());

        r.sleep();
        count++;

        ros::spinOnce();
    }
    return 0;
}
```

- 初始化ROS节点
- 订阅话题
- 循化等待，新消息由回调函数去处理

```cpp
#include "ros/ros.h"
#include "std_msgs/String.h"

void doMsg(const std_msgs::String::ConstPtr& msg_p){
    ROS_INFO("我听见:%s",msg_p->data.c_str());
    // ROS_INFO("我听见:%s",(*msg_p).data.c_str());
}

int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    //2.初始化 ROS 节点:命名(唯一)
    ros::init(argc,argv,"listener");
    //3.实例化 ROS 句柄
    ros::NodeHandle nh;

    //4.实例化 订阅者 对象
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("chatter",10,doMsg);
    //5.处理订阅的消息(回调函数)

    //     6.设置循环调用回调函数
    ros::spin();//循环读取接收的数据，并调用回调函数处理

    return 0;
}
```

订阅者有回调函数的概念，订阅者并不知道消息什么时候来，但是一旦有消息，就会调用这个消息处理函数。

`ros::spin()` 是循环等待函数。

编译完成后，会生成可执行文件，在devel文件夹内，可以直接在终端启动。也就是说可以从目录打开这些生成的文件，但是呢一般都是直接启动终端就运行的，所以前面会有添加环境变量这个步骤，就不用切换到这个路径了。


## 自定义 Topic 消息格式

自己做机器人，可能 ROS 提供的格式不够用，需要自己定义一个格式。

- 定义 msg 文件
- 在 package.xml 里添加功能包依赖
- 在 Cmakeists.txt 添加编译选项

定义消息格式的文件`Person.msg`
```txt
string name
uint8  sex
uint8  age

uint8 unknown = 0
uint8 male    = 1
uint8 female  = 2
```

这里想用常量类似C语言enum去描述sex属性，这个文件并不是c类型也不是py，可以认为就是个普通文本。

在package.xml文件里需要加上一些东西，来说明这个包有用到自己定义的消息格式
```xml
<build_depend>message_generation</build_depend>

<exec_depend>message_runtime</exec_depend>  
```
在CMakests里也需要添加一个依赖
```makefile
find_package(
    ...
    message_generation
    ...
)
catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)


add_message_files(FILES Person.msg)

```

这样就可以进行编译了，编译完成后会自动生成C++、Python、各种语言的东西。

这就是**语言无关的消息类型接口**，用文本表述消息类型，自动生成各种东西。

在终端里，可以查看消息类型是否定义成功：
```bash
rosmsg show Person
```



