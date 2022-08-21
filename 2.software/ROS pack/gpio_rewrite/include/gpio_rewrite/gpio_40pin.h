#ifndef __GPIO_40PIN_H__
#define __GPIO_40PIN_H__

#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <time.h>


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF	64
#define RET_OK 0

#define GPIO_1 NULL
#define GPIO_2 NULL
#define GPIO_3 9
#define GPIO_4 NULL
#define GPIO_5 8
#define GPIO_6 NULL
#define GPIO_7 101
#define GPIO_8 111
#define GPIO_9 NULL
#define GPIO_10 112

#define GPIO_11 6
#define GPIO_12 18
#define GPIO_13 27
#define GPIO_14 NULL
#define GPIO_15 30
#define GPIO_16 27
#define GPIO_17 NULL
#define GPIO_18 7
#define GPIO_19 12
#define GPIO_20 NULL

#define GPIO_21 13
#define GPIO_22 29
#define GPIO_23 14
#define GPIO_24 15
#define GPIO_25 NULL
#define GPIO_26 28
#define GPIO_27 106
#define GPIO_28 107
#define GPIO_29 119
#define GPIO_30 NULL

#define GPIO_31 118
#define GPIO_32 25
#define GPIO_33 4
#define GPIO_34 NULL
#define GPIO_35 103
#define GPIO_36 3
#define GPIO_37 105
#define GPIO_38 104
#define GPIO_39 NULL
#define GPIO_40 108

class gpio_40pin
{
    public:
        gpio_40pin();
        void gpio_init(int board_num);

        void gpio_set_dir(int out_flag);
        void gpio_export();
        void gpio_unexport(); 

        void gpio_set_value(int value);    
        void gpio_get_value();   
        void gpio_set_edge(); 

        void gpio_pwm(int frequency_,float Duty_ratio_); 
        void pwm_back();   

    private:
        boost::asio::io_service io_;
        boost::asio::deadline_timer timer_;

        bool state;
        int gpio;

        int value_fd;
        int len;
        char direction_buf[MAX_BUF];
        char value_buf[MAX_BUF];

        int frequency;
        float Duty_ratio;

        int high_time;
        int low_time;
};

#endif
