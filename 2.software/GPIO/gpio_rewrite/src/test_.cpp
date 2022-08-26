#include "rclcpp/rclcpp.hpp"
#include "gpio_rewrite/gpio_40pin.h"
#include <memory>
#include <stdio.h>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
	
	gpio_40pin GPIO37;

	GPIO37.gpio_init(GPIO_37);
	GPIO37.gpio_export();
	GPIO37.gpio_set_dir(1);
	if (strcmp(argv[1], "high") == 0)
	{
		GPIO37.gpio_set_value(1);
	}
	else if(strcmp(argv[1], "low") == 0)
	{
		GPIO37.gpio_set_value(0);
	}
	else
	{
		RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "You did not set the level parameter");
	}
	
	GPIO37.gpio_unexport();
  	rclcpp::shutdown();
}