cmake_minimum_required(VERSION 3.5)
project(gpio_rewrite)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

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

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
)


add_executable(LED src/LED.cpp)
ament_target_dependencies(LED rclcpp)

add_executable(test_ src/test_.cpp include/${PROJECT_NAME}/gpio_40pin.cpp)
ament_target_dependencies(test_ rclcpp)

add_executable(time_test src/time_test.cpp include/${PROJECT_NAME}/gpio_40pin.cpp)
ament_target_dependencies(time_test rclcpp)

install(DIRECTORY include/
  DESTINATION include/
)

install(TARGETS
  LED
  test_
  time_test
  DESTINATION lib/${PROJECT_NAME})
  

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
