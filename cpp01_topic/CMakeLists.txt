cmake_minimum_required(VERSION 3.20)
project(cpp01_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(base_interfaces_demo REQUIRED)

add_executable(demo01_talker_str src/demo01_talker_str.cpp)
add_executable(demo02_listener_str src/demo02_listener_str.cpp)
add_executable(demo03_talker_stu src/demo03_talker_stu.cpp)
add_executable(demo04_listener_stu src/demo04_listener_stu.cpp)

target_link_libraries(demo01_talker_str PUBLIC
  rclcpp::rclcpp
  ${std_msgs_TARGETS}
  ${base_interfaces_demo_TARGETS}
)

target_link_libraries(demo02_listener_str PUBLIC
  rclcpp::rclcpp
  ${std_msgs_TARGETS}
  ${base_interfaces_demo_TARGETS}
)

target_link_libraries(demo03_talker_stu PUBLIC
  rclcpp::rclcpp
  ${std_msgs_TARGETS}
  ${base_interfaces_demo_TARGETS}
)

target_link_libraries(demo04_listener_stu PUBLIC
  rclcpp::rclcpp
  ${std_msgs_TARGETS}
  ${base_interfaces_demo_TARGETS}
)

target_compile_features(demo01_talker_str PUBLIC cxx_std_17)
target_compile_features(demo02_listener_str PUBLIC cxx_std_17)
target_compile_features(demo03_talker_stu PUBLIC cxx_std_17)
target_compile_features(demo04_listener_stu PUBLIC cxx_std_17)

install(TARGETS
  demo01_talker_str
  demo02_listener_str
  demo03_talker_stu
  demo04_listener_stu
  DESTINATION lib/${PROJECT_NAME}
)

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
