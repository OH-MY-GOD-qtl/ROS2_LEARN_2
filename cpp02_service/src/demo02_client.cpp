#include <base_interfaces_demo/srv/add_ints.hpp>
#include <rclcpp/rclcpp.hpp>

using base_interfaces_demo::srv::AddInts;
using namespace std::chrono_literals;

class MinimalClient : public rclcpp::Node
{
public:
    MinimalClient() : Node("minimal_client")
    {
        client = this->create_client<AddInts>("add_ints");
        RCLCPP_INFO(this->get_logger(), "Client 'add_ints' is ready.");
    }
    bool connect_server()
    {
        while (!client->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_INFO(
                    this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return false;
            }
            RCLCPP_INFO(this->get_logger(), "Service not available, waiting again...");
        }
        return true;
    }
    rclcpp::Client<AddInts>::FutureAndRequestId send_request(int32_t num1, int32_t num2)
    {
        auto request = std::make_shared<AddInts::Request>();
        request->num1 = num1;
        request->num2 = num2;
        RCLCPP_INFO(this->get_logger(), "Sending request: num1=%d, num2=%d", num1, num2);
        return client->async_send_request(request);
    }

private:
    rclcpp::Client<AddInts>::SharedPtr client;
};

int main(int argc, char * argv[])
{
    if (argc != 3) {
        RCLCPP_INFO(
            rclcpp::get_logger("rclcpp"), "Please provide two integers as command line arguments.");
        return 1;
    }
    rclcpp::init(argc, argv);
    auto client = std::make_shared<MinimalClient>();
    bool flag = client->connect_server();
    if (!flag) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service connection failed!");
        return 0;
    }
    auto response = client->send_request(atoi(argv[1]), atoi(argv[2]));
    if (rclcpp::spin_until_future_complete(client, response) == rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result: %d", response.get()->sum);
    } else {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Failed to call service 'add_ints'.");
    }
    rclcpp::shutdown();
    return 0;
}