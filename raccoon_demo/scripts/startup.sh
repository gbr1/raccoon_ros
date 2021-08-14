#!/bin/bash
source /opt/ros/kinetic/setup.bash
source ~/catkin_ws/devel/setup.bash
source /opt/intel/openvino_2021/bin/setupvars.sh

roslaunch raccoon_demo demo.launch
