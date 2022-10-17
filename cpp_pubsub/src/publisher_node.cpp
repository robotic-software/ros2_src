#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;


class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher();
  void timer_callback(); 

private:
  rclcpp::TimerBase::SharedPtr                        _timer;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _publisher;
  int                                                 _count;

};

MinimalPublisher::MinimalPublisher() : Node("minimal_publisher") { 
  _publisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
  _timer = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
}

void MinimalPublisher::timer_callback() {
  auto message = std_msgs::msg::String();
  message.data = "Hello, world! " + std::to_string(_count++);
  
  RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
  _publisher->publish(message);
  
}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
