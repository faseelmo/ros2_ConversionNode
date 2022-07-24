    #include "rclcpp/rclcpp.hpp"
    #include "sensor_msgs/msg/imu.hpp"
     
    class ConversionNode : public rclcpp::Node 
    {
    public:
        ConversionNode() : Node("unitconversion") 
        {
            subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>("imu23/imu", 10, 
            std::bind(&ConversionNode::callbackImu, this, std::placeholders::_1));
            RCLCPP_INFO(this->get_logger(), "Conversion has started");
        }
     
    private:
        void callbackImu(const sensor_msgs::msg::Imu::SharedPtr msg)
        {

            float linear_x, linear_y, linear_z;
            float angular_x, angular_y, angular_z;

            linear_x = this->linear_conversion(msg->linear_acceleration.x);
            linear_y = this->linear_conversion(msg->linear_acceleration.y);
            linear_z = this->linear_conversion(msg->linear_acceleration.z);

            angular_x = this->anngular_conversion(msg->angular_velocity.x);
            angular_y = this->anngular_conversion(msg->angular_velocity.y);
            angular_z = this->anngular_conversion(msg->angular_velocity.z);
            std::cout << "Inside the call back";
            RCLCPP_INFO(this->get_logger(), "Linear Acceleration in g : x: '%f', y: '%f', z: '%f' \n Angular Acceleration in rad/s: x: '%f', y: '%f', z: '%f'", 
            linear_x, linear_y, linear_z, angular_x, angular_y, angular_z);  
            
        }

        float linear_conversion(float acc){ 

            return acc / 9.8;

        }

        float anngular_conversion(float deg){

            return (deg*3.1415926) / 180; 
        }

        rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscriber_ ;
    };
     
    int main(int argc, char **argv)
    {
        rclcpp::init(argc, argv);
        auto node = std::make_shared<ConversionNode>(); 
        rclcpp::spin(node);
        rclcpp::shutdown();
        return 0;
    }