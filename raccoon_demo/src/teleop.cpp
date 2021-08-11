/*
 * The MIT License
 *
 * Copyright (c) 2021 Giovanni di Dio Bruno https://gbr1.github.io
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <stdlib.h>


geometry_msgs::Twist twist;

bool publish=false;
bool buttonpressed = false;


void joyCallback(const sensor_msgs::Joy::ConstPtr& msg){
    //L+R+ZL+ZR
    if (msg->buttons[4] && msg->buttons[5] && msg->buttons[6] && msg->buttons[7]){
       //shutdown
       ROS_INFO("[JOY COMMAND: SHUTDOWN]");
       system("shutdown -P now"); 
    }

    //select
    if (msg->buttons[8]){
    }

    //start
    if (msg->buttons[7]){
        //reset map
        ROS_INFO("[JOY COMMAND: reset RTAB memory]");
        system("rosservice call /rtabmap/reset");
        system("rosservice call /rtabmap/reset_odom");
    }

    //ZR
    if (msg->buttons[7]){
        //turn off screen
    }

    //ZL
    if (msg->buttons[6]){
        //turn on screen
    }

    if (msg->buttons[2]){
        buttonpressed=true;
        twist.angular.z = 5.0*msg->axes[0];
        twist.linear.x = 1.0*msg->axes[1];
        publish=true;
    }else{
        if (msg->buttons[0]){
            buttonpressed=true;
            twist.angular.z = 3.0*msg->axes[0];
            twist.linear.x = 0.7*msg->axes[1]; 
            publish=true;   
        }
        else{
            if (msg->buttons[1]){
                buttonpressed=true;
                twist.angular.z = 1.0*msg->axes[0];
                twist.linear.x = 0.3*msg->axes[1]; 
                publish=true;   
            }
            else{
                if (buttonpressed){
                    twist.angular.z = 0;
                    twist.linear.x = 0; 
                    publish=true; 
                    buttonpressed=false;
                }
            }
        }
    }
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "raccoon_teleop");
    
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe<sensor_msgs::Joy>("/joy", 10, joyCallback);
    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("/joy_teleop/cmd_vel",1);

    ros::Rate loop_rate(50);

    ROS_INFO("LB+RB+SELECT+START shutdown");
    ROS_INFO("START reset rtabmap");
    ROS_INFO("A normal, X extreme, B slow");

    twist.angular.z = 0;
    twist.linear.x = 0;
    while(ros::ok()){
        /*
        if (publish){
            pub.publish(twist);
            publish=false;
        }*/
        pub.publish(twist);

        ros::spinOnce();
        loop_rate.sleep();
    }
}