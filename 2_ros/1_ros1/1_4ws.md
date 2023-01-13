---
sort: 4
---
# workspace


工作空间，工程项目

- src
- build
- devel
- install


src里面是开发者要关注的。在Ubuntu直接面对一滩源文件，和使用IDE有很大不同，很多东西都是手动的。

## 工作空间

```bash
mkdir -p ~/workspace_name/src
cd ~/workspace_name/src

# 创建工作空间的指令
catkin_init_workspace
```

编译需要在工作空间的根目录下
```bash
catkin_make
```
底层实现也是基于cmake的，所以使用这么个编译命令

**设置环境变量**

需要让Linux系统知道功能包在那里，告诉系统功能包位置的
```bash
source ~/workspace_name/devel/setup.bash
```
这个指令只在当前终端有效，可以直接把这个指令放在终端配置里

在~文件夹里，ctrl+H显示隐藏文件，就有./bashrc了，加上这一句
```bash
source ~/workspace_name/devel/setup.bash
```

可以查看以下当前的环境变量
```bash
echo $ROS_PACKAGE_PATH
```

## 创建功能包

```bash
catkin_create_pkg <package_name> [depend1] [depend2] [depend3]
```

每个功能包都要有的两个文件`CMakeLists.txt`，`package.xml`


一个工程不可以有重名的功能包。

一台电脑上可以有多个工程存在，在不同工作空间下可以有同名功能包。

这就有个问题，当有同名的功能包时，ros是如何解决的。

`echo $ROS_PACKAGE_PATH`指令会输出查找功能包的路径，在一个路径里找到了就不往后找了。新设置的路径在最前面，在使用时候就表现为新功能包覆盖老功能包。

这就是工作空间覆盖机制，有时候会有潜在风险






