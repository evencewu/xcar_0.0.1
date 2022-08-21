#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <stdio.h>

int access (const char *__name, int __type);

bool file_exists(const char *filename)
{
    return (access(filename, 0) == 0);
}

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	//判断GPIO是否启用
    const char * filename = "/sys/class/gpio/gpio26/direction";
	if(file_exists(filename) == 1)
	{
		
	}
	else if(file_exists(filename) == 0)
	{
		system("echo 26 > /sys/class/gpio/export");
	}
	
	/*设置LED引脚为输出模式*/
	system("echo out > /sys/class/gpio/gpio26/direction");

	/*设置LED引脚电平*/
	if (strcmp(argv[1], "high") == 0)
	{
		system("echo '1' > /sys/class/gpio/gpio26/value");
	}
	else if(strcmp(argv[1], "low") == 0)
	{
		system("echo '0' > /sys/class/gpio/gpio26/value");
	}else
	{
		RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "You did not set the level parameter");
	}
	

  	rclcpp::shutdown();
}