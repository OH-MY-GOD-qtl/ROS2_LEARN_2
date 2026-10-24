#include <base_interfaces_demo/msg/student.hpp>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;
using base_interfaces_demo::msg::Student;

class MinimalPublisher : public rclcpp::Node
{
public:
    MinimalPublisher() : Node("minimal_publisher"), count_(0)
    {
        publisher_ = this -> create_publisher<Student>("topic_stu", 10);
        timer_ = this -> create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }
private:
    void timer_callback()
    {
        auto stu = Student();
        stu.name = "qtl";
        stu.age = 20;
        stu.height = 1.82;
        RCLCPP_INFO(this -> get_logger(), "Publishing: name: '%s', age: '%d', height: '%.2f'", stu.name.c_str(), stu.age, stu.height);
        publisher_ -> publish(stu);
    }
    rclcpp::Publisher<Student>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
}
