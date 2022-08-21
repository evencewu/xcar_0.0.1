cmake_minimum_required(VERSION 3.5)
project(ctrl_main)

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
find_package(geometry_msgs REQUIRED)
find_package(ai_msgs REQUIRED) 

include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
)


add_executable(master src/master.cpp)
ament_target_dependencies(master rclcpp geometry_msgs ai_msgs)

install(DIRECTORY include/
  DESTINATION include/
)

install(TARGETS
  master
  DESTINATION lib/${PROJECT_NAME})
  

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
