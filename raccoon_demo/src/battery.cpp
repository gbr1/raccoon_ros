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
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <moebiustech_stm32_ros/Status.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const char * red = "/sys/class/leds/upboard:red:/brightness";
const char * green = "/sys/class/leds/upboard:green:/brightness";
const char * yellow = "/sys/class/leds/upboard:yellow:/brightness";
const char * blue= "/sys/class/leds/upboard:blue:/brightness";


void setLed(const char * led, const char * val){
    ofstream led_file;
    led_file.open(led);
    led_file << val;
    led_file.close();
}

void battery_check(const moebiustech_stm32_ros::Status::ConstPtr& msg){
    float batt = msg->battery_voltage;
    if (batt>=10.9){
        setLed(green,"1");
        setLed(yellow,"0");
        setLed(red,"0");
    }
    else{
        if (batt>=10.4){
            setLed(green,"0");
            setLed(yellow,"1");
            setLed(red,"0");
        }
        else{
            if (batt>=10.0){
                setLed(green,"0");
                setLed(yellow,"0");
                setLed(red,"1");
            }
            else{
                ROS_WARN("LOW BATTERY - SECURITY SHUTDOWN");
                system("shutdown -P now"); 
            }
        }
        
    }
}



int main(int argc, char** argv){
    try{
        ros::init(argc, argv, "raccoon_battery");
        ros::NodeHandle nh;
        ros::Subscriber sub=nh.subscribe<moebiustech_stm32_ros::Status>("/moebiustech_stm32/status", 10, battery_check);

        while(!ros::ok){
            setLed(blue,"0");
        }
        setLed(blue,"1");

        ros::spin();

        setLed(red,"0");
        setLed(green,"0");
        setLed(yellow,"0");
        setLed(blue,"0");
    }
    catch(const std::exception& e){
        setLed(red,"0");
        setLed(green,"0");
        setLed(yellow,"0");
        setLed(blue,"0");
    }
    return 0;
    
}