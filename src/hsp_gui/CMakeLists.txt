
cmake_minimum_required(VERSION 2.8.12)

project(hsp_gui)

find_package(Qt5Widgets REQUIRED)
find_package(catkin REQUIRED COMPONENTS
                        roscpp
                        geometry_msgs 
                        image_transport
                        sensor_msgs
                        husky_msgs
                        ugv_control
                        )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(hsp_gui_INCLUDE_DIRECTORIES
        src
        include
        resources )

include_directories(${hsp_gui_INCLUDE_DIRECTORIES}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${catkin_INCLUDE_DIRS} )

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS roscpp geometry_msgs husky_msgs ugv_control
    DEPENDS Qt5Widgets )

file(GLOB hsp_gui_SRCS src/*.cpp)
list(REMOVE_ITEM hsp_gui_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )
list(REMOVE_ITEM hsp_gui_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/UGVControl.cpp )

file(GLOB hsp_gui_HDRS include/*.h)
list(REMOVE_ITEM hsp_gui_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/include/UGVControl.h )

file(GLOB hsp_gui_UIS resources/*.ui)
file(GLOB hsp_gui_QRSCS resources/qrc/*.qrc)

qt5_add_resources(hsp_gui_VFS ${hsp_gui_QRSCS}) #VFS = Virtual File System
qt5_wrap_cpp(hsp_gui_MOCS ${hsp_gui_HDRS})
qt5_wrap_ui(hsp_gui_UI_HDRS ${hsp_gui_UIS} )

add_definitions(${Qt5Widgets_DEFINITIONS}
                ${catkin_DEFINITIONS}
                -std=c++11 )

add_library(_hsp_gui
            ${hsp_gui_SRCS}
            ${hsp_gui_MOCS}
            ${hsp_gui_UI_HDRS}
            ${hsp_gui_VFS} )


## Declare a C++ library
# add_library(UGVControl
#   src/UGVControl.cpp
# )

#add_dependencies(
#    UGVControl ${catkin_EXPORTED_TARGETS}
#)
#
#target_link_libraries(UGVControl ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME} src/main.cpp)


add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
add_dependencies(_hsp_gui ${catkin_EXPORTED_TARGETS})

target_link_libraries(_hsp_gui
                        Qt5::Widgets
                        ${catkin_LIBRARIES} 
#			UGVControl
)

target_link_libraries(${PROJECT_NAME}
                        _hsp_gui
#                        Qt5::Widgets
#                        ${catkin_LIBRARIES} 
#			UGVControl
)


