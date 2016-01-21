cmake_minimum_required(VERSION 2.6)

project(crcl_app)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  )

find_package(xml_parser_generator REQUIRED)
find_package(crcl_cpp REQUIRED)

# 
# This makes the local project's include and lib directories available to
# other local projects, without requiring installation in /opt/ros/
# 
catkin_package(
  CATKIN_DEPENDS roscpp
  INCLUDE_DIRS include
)

include_directories(
  include
  ${xml_parser_generator_INCLUDE_DIRS}
  ${crcl_cpp_INCLUDE_DIRS}
)

add_library(crcl_program_instance_handler
  src/crcl_program_instance_handler.cpp
  )

add_executable(crcl_program_instance_printer
  src/crcl_program_instance_printer.cpp
  )

target_link_libraries(crcl_program_instance_printer
  crcl_program_instance_handler
  crcl_program_instance_parser
  crcl_cpp
  xml_instance
)

install(TARGETS crcl_program_instance_handler
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  )

install(TARGETS crcl_program_instance_printer
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  )
