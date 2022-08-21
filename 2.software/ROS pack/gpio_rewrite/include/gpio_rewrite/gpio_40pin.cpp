#include "gpio_rewrite/gpio_40pin.h"

gpio_40pin::gpio_40pin():timer_(io_, boost::posix_time::microseconds(10000))
{
	timer_.async_wait(boost::bind(&gpio_40pin::pwm_back, this));
}

void gpio_40pin::gpio_init(int board_num)
{
	gpio = board_num;
	snprintf(value_buf, sizeof(value_buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
	snprintf(direction_buf, sizeof(direction_buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
}

void gpio_40pin::gpio_export()
{
	char buf[MAX_BUF];
	int fd = open(SYSFS_GPIO_DIR "/gpio%d/direction", O_WRONLY);
	if (fd < 0) {
		close(fd);
		fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
		len = snprintf(buf, sizeof(buf), "%d", gpio);
		write(fd, buf, len);
		close(fd);
	}else{
		close(fd);
	}
}

void gpio_40pin::gpio_unexport()
{
	char buf[MAX_BUF];
	int fd = open(SYSFS_GPIO_DIR "/gpio%d/direction", O_WRONLY);
	if (fd < 0) {
		close(fd);
	}else{
		close(fd);
		fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
		len = snprintf(buf, sizeof(buf), "%d", gpio);
		write(fd, buf, len);
		close(fd);
	}
}

void gpio_40pin::gpio_set_dir(int out_flag)
{
	int fd = open(direction_buf, O_WRONLY);
	if (out_flag)
		write(fd, "out", 4);
	else
		write(fd, "in", 3);
	close(fd);
}

void gpio_40pin::gpio_set_value(int value)
{
	int fd = open(value_buf, O_WRONLY);
	if (value)
		write(fd, "1", 2);
	else
		write(fd, "0", 2);
	close(fd);
}

void gpio_40pin::pwm_back()
{
	if (state == 0)
	{
		timer_.expires_at(timer_.expires_at() + boost::posix_time::microseconds(low_time));
		gpio_set_value(0);
		state = 1;
	}
	else
	{
		timer_.expires_at(timer_.expires_at() + boost::posix_time::microseconds(high_time));
		gpio_set_value(1);
		state = 0;
	}
	timer_.async_wait(boost::bind(&gpio_40pin::pwm_back, this));
}

void gpio_40pin::gpio_pwm(int frequency_,float Duty_ratio_)
{
	frequency = frequency_;
	Duty_ratio = Duty_ratio_;

	high_time = (1000000/frequency)*Duty_ratio;
	low_time = (1000000/frequency) - high_time;
	printf("%d__%d\n",high_time,low_time);
	io_.run();
} 
         
        //void gpio_get_value();   
        //void gpio_set_edge(); 

       
         

