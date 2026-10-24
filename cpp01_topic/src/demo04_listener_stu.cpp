#include <rclcpp/rclcpp.hpp>
#include <base_interfaces_demo/msg/student.hpp>

using std::placeholders::_1;
using base_interfaces_demo::msg::Student;

class MinimalSubscriber : public rclcpp::Node{
public:
    MinimalSubscriber() : Node("minimal_subscriber")
    {
        subscription_ = this -> create_subscription<Student>("topic_stu", 10, std::bind(&MinimalSubscriber::timer_callback, this, _1));
    }
private:
    void timer_callback(const Student &msg) const
    {
        RCLCPP_INFO(this -> get_logger(), "subscription message: name=%s, age=%d, height=%.2f", msg.name.c_str(), msg.age, msg.height);
    }
    rclcpp::Subscription<Student>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
}