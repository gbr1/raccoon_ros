# raccoon_ros

## How to run your UP RACCOON

Open terminal and launch:<br>
`roslaunch raccoon_bringup bringup.launch`

## Setup
Go into your workspace source folder (e.g. catkin_ws/src): <br>
`cd ~/catkin_ws/src` <br>
clone this repository: <br>
`git clone http://github.com/gbr1/raccoon_ros.git` <br>
return in catkin_ws: <br>
`cd ..` <br>
check dependencies: <br>
`rosdep install --from-paths src --ignore-src -r -y` <br>
make: <br>
`catkin_make` <br>
install: <br>
`catkin_make install` <br>

## Other nodes and launch files

To simulate in Gazebo: <br>
`roslaunch raccoon_gazebo raccoon_gazebo_full.launch` <br>
To run autonomous navigation: <br>
`roslaunch raccoon_navigation explore.launch` <br>

<br>

To enable battery control: <br>
`rosrun raccoon_demo battery_node` <br>
*Note: when battery is low (10.8V) the robot will automatically shutdown. To use this node you must be on an UP2 and have onboard leds working.*

To run teleop control: <br>
`rosrun raccoon_demo teleop_node` <br>
*Note: this node was designed to be used on the demo model with an X mode joypad, so if you use it is possible to obtain have issues with the navigation stack *


## Dependencies
* [moebiustech_stm32_ros](https://github.com/gbr1/moebiustech_stm32_ros)
* [realsense2_camera](https://github.com/intel-ros/realsense)

>__Copyright (c) 2021 Giovanni di Dio Bruno under MIT license__
