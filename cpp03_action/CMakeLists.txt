cmake_minimum_required(VERSION 3.20)
project(cpp03_action)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(base_interfaces_demo REQUIRED)

add_executable(demo01_action_server src/demo01_action_server.cpp)
add_executable(demo02_action_client src/demo02_action_client.cpp)

target_link_libraries(demo01_action_server PUBLIC
  rclcpp::rclcpp
  rclcpp_action::rclcpp_action
  ${base_interfaces_demo_TARGETS}
)
target_link_libraries(demo02_action_client PUBLIC
  rclcpp::rclcpp
  rclcpp_action::rclcpp_action
  ${base_interfaces_demo_TARGETS}
)

target_compile_features(demo01_action_server PUBLIC cxx_std_17)
target_compile_features(demo02_action_client PUBLIC cxx_std_17)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
