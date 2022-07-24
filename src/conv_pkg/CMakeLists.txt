cmake_minimum_required(VERSION 3.5)
project(conv_pkg)


# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)


add_executable(cpp_conv_node src/conversion_node.cpp)
ament_target_dependencies(cpp_conv_node rclcpp sensor_msgs)

install(TARGETS
  cpp_conv_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
