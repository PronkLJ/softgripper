// This program subscribes to the /voltage topic and sends its data to the Arduino via the defined serial port.

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <string>
#include <fstream>
#include <sstream>

class GripperController : public rclcpp::Node
{
public:
    GripperController()
    : Node("gripper_controller")
    {
        // Define serial port for Arduino. Change port when necessary
        this->declare_parameter<std::string>("serial_port", "/dev/ttyACM0");
        this->get_parameter("serial_port", serial_port_);

        serial_stream_.open(serial_port_);
        if (!serial_stream_.is_open()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open serial port: %s", serial_port_.c_str());
            rclcpp::shutdown();
            return;
        }

        RCLCPP_INFO(this->get_logger(), "Serial port opened: %s", serial_port_.c_str());

        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "voltage", 10, std::bind(&GripperController::voltage_callback, this, std::placeholders::_1)
        );
    }

    ~GripperController()
    {
        if (serial_stream_.is_open()) {
            serial_stream_.close();
        }
    }

private:
    void voltage_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        float voltage = msg->data;

        // Checks if voltage is within range. Too much air pressure can damage soft grippers.
        if (voltage < 0.0 || voltage > 2.0) {
            RCLCPP_WARN(this->get_logger(), "Voltage out of range: %f", voltage);
            return;
        }

        std::ostringstream command;
        command << "SET " << voltage << "\n";
        serial_stream_ << command.str();
        serial_stream_.flush();

        RCLCPP_INFO(this->get_logger(), "Sent command: %s", command.str().c_str());
    }

    std::string serial_port_;
    std::ofstream serial_stream_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GripperController>());
    rclcpp::shutdown();
    return 0;
}
