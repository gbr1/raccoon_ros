#include <ros/ros.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <moebiustech_stm32_ros/Status.h>

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
            setLed(green,"0");
            setLed(yellow,"0");
            setLed(red,"1");
        }
    }
}



int main(int argc, char** argv){
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
    return 0;
}