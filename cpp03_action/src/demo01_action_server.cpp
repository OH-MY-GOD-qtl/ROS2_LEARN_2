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
            std::bind(&MinimalActionServer::hanedl_cancel, this, _1),
            std::bind(&MinimalActionServer::handel_accepted, this, _1));
        RCLCPP_INFO(this->get_logger(), "Action server 'get_sum' is ready.");
    }

private:
    rclcpp_action::Server<Progress>::SharedPtr action_server_;
    rclcpp_action::GoalResponse handel_goal(
        const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const Progress::Goal> goal)
    {
        (void)uuid;
        RCLCPP_INFO(this->get_logger(), "Received goal request with num=%ld", goal->num);
        if (goal->num < 1) {
            return rclcpp_action::GoalResponse::REJECT;
        }
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse hanedl_cancel(
        const std::shared_ptr<GoalHandleProgress> goal_handle)
    {
        (void)goal_handle;
        RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    
    void execute(const std::shared_ptr<GoalHandleProgress> goal_handle)
    {
        RCLCPP_INFO(this->get_logger(), "Executing goal");
        rclcpp::Rate loop_rate(10.0);
        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<Progress::Feedback>();
        auto result = std::make_shared<Progress::Result>();
        int64_t sum = 0;
    }
};