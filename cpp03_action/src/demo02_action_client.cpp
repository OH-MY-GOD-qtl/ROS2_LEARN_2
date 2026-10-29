#include <base_interfaces_demo/action/progress.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

using base_interfaces_demo::action::Progress;
using GoalHandleProgress = rclcpp_action::ClientGoalHandle<Progress>;
using namespace std::placeholders;

class MinimalActionClient : public rclcpp::Node
{
public:
    explicit MinimalActionClient(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
    : Node("minimal_action_client", options)
    {
        this->client_ptr_ = rclcpp_action::create_client<Progress>(this, "get_sum");
    }

    void send_goal(int64_t num)
    {
        if (!this->client_ptr_) {
            RCLCPP_ERROR(this->get_logger(), "Action client not initialized");
        }
        if (!this->client_ptr_->wait_for_action_server(std::chrono::seconds(10))) {
            RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
            return;
        }
        auto goal_msg = Progress::Goal();
        goal_msg.num = num;
        RCLCPP_INFO(this->get_logger(), "Sending goal request with num=%ld", num);

        auto send_goal_options = rclcpp_action::Client<Progress>::SendGoalOptions();
        send_goal_options.goal_response_callback =
            std::bind(&MinimalActionClient::goal_response_callback, this, _1);
        send_goal_options.feedback_callback =
            std::bind(&MinimalActionClient::feedback_callback, this, _1, _2);
        send_goal_options.result_callback =
            std::bind(&MinimalActionClient::result_callback, this, _1);
        auto goal_handle_future = this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
    }

private:
    rclcpp_action::Client<Progress>::SharedPtr client_ptr_;
    void goal_response_callback(GoalHandleProgress::SharedPtr goal_handle)
    {
        if (!goal_handle) {
            RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
        } else {
            RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
        }
    };
    void feedback_callback(
        GoalHandleProgress::SharedPtr, const std::shared_ptr<const Progress::Feedback> feedback)
    {
        RCLCPP_INFO(this->get_logger(), "Received feedback: progress=%.2f", feedback->progress);
    };
    void result_callback(const GoalHandleProgress::WrappedResult & result)
    {
        switch (result.code) {
            case rclcpp_action::ResultCode::SUCCEEDED:
                RCLCPP_INFO(this->get_logger(), "Goal succeeded with sum=%ld", result.result->sum);
                break;
            case rclcpp_action::ResultCode::ABORTED:
                RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
                break;
            case rclcpp_action::ResultCode::CANCELED:
                RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
                break;
            default:
                RCLCPP_ERROR(this->get_logger(), "Unknown result code");
                break;
        }
    };
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto action_client = std::make_shared<MinimalActionClient>();
    action_client->send_goal(10);
    rclcpp::spin(action_client);
    rclcpp::shutdown();
    return 0;
}