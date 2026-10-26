#include <base_interfaces_demo/action/progress.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

using namespace std::placeholders;
using base_interfaces_demo::action::Progress;
using GoalHandleProgress = rclcpp_action::ServerGoalHandle<Progress>;

class MinimalActionServer : public rclcpp::Node
{
public:
    explicit MinimalActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
    : Node("minimal_action_server", options)
    {
        this->action_server_ = rclcpp_action::create_server<Progress>(
            this, "get_sum", std::bind(&MinimalActionServer::handel_goal, this, _1, _2),
            std::bind(&MinimalActionServer::hanedl_cancle, this, _1),
            std::bind(&MinimalActionServer::handel_accepted, this, _1));
        RCLCPP_INFO(this->get_logger(), "Action server 'get_sum' is ready.");   
    }
private:
    rclcpp_action::Server<Progress>::SharedPtr action_server_;
    rclcpp_action::GoalResponse handel_goal()
};