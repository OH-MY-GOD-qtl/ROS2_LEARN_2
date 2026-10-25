cmake_minimum_required(VERSION 3.20)
project(cpp02_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(base_interfaces_demo REQUIRED)

add_executable(demo01_server src/demo01_server.cpp)
add_executable(demo02_client src/demo02_client.cpp)

target_link_libraries(demo01_server PUBLIC
  rclcpp::rclcpp
  ${base_interfaces_demo_TARGETS}
)
target_link_libraries(demo02_client PUBLIC
  rclcpp::rclcpp
  ${base_interfaces_demo_TARGETS}
)

target_compile_features(demo01_server PUBLIC cxx_std_17)
target_compile_features(demo02_client PUBLIC cxx_std_17)

install(TARGETS
  demo01_server demo02_client
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
