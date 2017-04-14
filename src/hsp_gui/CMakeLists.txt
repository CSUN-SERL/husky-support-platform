
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
                                ${CMAKE_CURRENT_SOURCE_DIR}
                                ${catkin_INCLUDE_DIRS} )

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES _hsp_gui
    CATKIN_DEPENDS roscpp geometry_msgs husky_msgs ugv_control
    DEPENDS Qt5Widgets )

file(GLOB hsp_gui_SRCS src/*.cpp)
list(REMOVE_ITEM hsp_gui_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )

file(GLOB hsp_gui_HDRS include/*.h)

file(GLOB hsp_gui_UIS resources/*.ui)
file(GLOB hsp_gui_QRSCS resources/qrc/*.qrc)

qt5_wrap_cpp(hsp_gui_MOCS ${hsp_gui_HDRS})
qt5_wrap_ui(hsp_gui_UI_HDRS ${hsp_gui_UIS} )

add_definitions(${Qt5Widgets_DEFINITIONS}
                            ${catkin_DEFINITIONS}
                            -std=c++11 )


##### start UIAdapter

include_directories(lcar_msgs)

qt5_wrap_cpp(uiadapter_MOCS lcar_msgs/ui_adapter.h)

add_library(UiAdapter
            lcar_msgs/ui_adapter.h
            lcar_msgs/ui_adapter.cpp 
            ${uiadapter_MOCS})

add_dependencies(UiAdapter
                    ${catkin_EXPORTED_TARGETS} )

target_link_libraries(UiAdapter
                        ${catkin_LIBRARIES}
                        Qt5::Widgets )

##### end UiAdapter


###### start vr

include_directories(
                                voice_recognition
                                /usr/lib/jvm/java-6-openjdk-amd64/include
                                /usr/lib/jvm/java-6-openjdk-amd64/include/linux
 )

file(GLOB voice_recognition_SRCS voice_recognition/*.cpp)
file(GLOB voice_recognition_HDRS voice_recognition/*.h)

qt5_wrap_cpp(voice_recognition_MOCS ${voice_recognition_HDRS}) #makes meta objects compile file

add_library(vr
            ${voice_recognition_SRCS}
            ${voice_recognition_MOCS}
            ${voice_recognition_HDRS}
            )

add_dependencies(vr 
                    UiAdapter
                    ${catkin_EXPORTED_TARGETS})

target_link_libraries(vr 
                        UiAdapter
                        Qt5::Widgets
                        ${catkin_LIBRARIES}
/usr/lib/jvm/java-6-openjdk-amd64/jre/lib/amd64/server/libjvm.so )

##### end vr



add_library(_hsp_gui
            ${hsp_gui_SRCS}
            ${hsp_gui_MOCS}
            ${hsp_gui_UI_HDRS} )

add_dependencies(_hsp_gui ${catkin_EXPORTED_TARGETS})


add_executable(${PROJECT_NAME} src/main.cpp)

add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})


target_link_libraries(_hsp_gui
                        UiAdapter
                        vr
                        Qt5::Widgets
                        ${catkin_LIBRARIES} )

target_link_libraries(${PROJECT_NAME}
                                 _hsp_gui 
                                Qt5::Widgets
                                ${catkin_LIBRARIES})



