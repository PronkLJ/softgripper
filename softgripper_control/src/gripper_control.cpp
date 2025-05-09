#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <chrono>
#include <string>
#include <memory>

using namespace std::chrono_literals;

class GripperCommander : public rclcpp::Node
{
public:
    GripperCommander(float voltage)
    : Node("gripper_commander")
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float32>("voltage", 10);
        auto msg = std_msgs::msg::Float32();
        msg.data = voltage;
        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published voltage: %.2f", voltage);
    }

private:
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    std::string mode;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--mode" && i + 1 < argc) {
            mode = argv[i + 1];
            break;
        }
    }

    if (mode != "open" && mode != "closed") {
        std::cerr << "Usage: " << argv[0] << " --mode [open|closed]" << std::endl;
        return 1;
    }

    float voltage = (mode == "open") ? 0.0f : 1.5f;

    auto node = std::make_shared<GripperCommander>(voltage);

    // Spin briefly to allow the message to be published
    rclcpp::spin_some(node);

    // Short sleep ensures publish gets flushed before shutdown
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    rclcpp::shutdown();
    return 0;
}
