#include <rclcpp/rclcpp.hpp>
#include <base_interfaces_demo/srv/add_ints.hpp>

using base_interfaces_demo::srv::AddInts;
using std::placeholders::_1;
using std::placeholders::_2;

class MinimalService : public rclcpp::Node
{
public:
    MinimalService() : Node("minimal_service")
    {
        server = this->create_service<AddInts>("add_ints", std::bind(&MinimalService::add, this, _1, _2));
        RCLCPP_INFO(this->get_logger(), "Service 'add_ints' is ready.");
    }
private:
    rclcpp::Service<AddInts>::SharedPtr server;
    void add(const AddInts::Request::SharedPtr req, AddInts::Response::SharedPtr res)
    {
        res->sum = req->num1 + req->num2;
        RCLCPP_INFO(this->get_logger(), "Incoming request: num1=%d, num2=%d, sum=%d", req->num1, req->num2, res->sum);
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalService>());
    rclcpp::shutdown();
}