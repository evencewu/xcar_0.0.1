#include <memory>
#include "geometry_msgs/msg/twist.hpp"
#include "ai_msgs/msg/perception_targets.hpp"
#include "ai_msgs/msg/target.hpp"
#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

//订阅cmd_vel
class gesture_move_sub : public rclcpp::Node
{
  public:
    gesture_move_sub()
    : Node("gesture_move_sub")
    {
      subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "cmd_vel", 10, std::bind(&gesture_move_sub::topic_callback, this, _1));
    }

  private:
    void topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "linear: %f-%f-%f", msg->linear.x, msg->linear.y, msg->linear.z);
      RCLCPP_INFO(this->get_logger(), "angular: %f-%f-%f", msg->angular.x, msg->angular.y, msg->angular.z);
    }
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};
//订阅
//class gesture_sub : public rclcpp::Node
//{
//  public:
//    gesture_sub()
//    : Node("gesture_sub")
//    {
//      subscription_ = this->create_subscription<ai_msgs::msg::PerceptionTargets>(
//      "hobot_hand_gesture_detection", 10, std::bind(&gesture_sub::topic_callback, this, _1));
//    }
//
//  private:
//    void topic_callback(const ai_msgs::msg::PerceptionTargets::SharedPtr msg) const
//    {
//      RCLCPP_INFO(this->get_logger(), "targets.type: %s", msg->targets.type);
//    }
//    rclcpp::Subscription<ai_msgs::msg::PerceptionTargets>::SharedPtr subscription_;
//};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<gesture_move_sub>());

  //rclcpp::spin(std::make_shared<gesture_sub>());
  rclcpp::shutdown();
  return 0;
}