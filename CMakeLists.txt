cmake_minimum_required(VERSION 3.23)

set(QT6_INSTALL_PATH D:/pkg/Qt/6.3.1/mingw_64)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.297.tar.gz"
        SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
)

project(Dota_2_Layout_Handler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

hunter_add_package(jsoncpp)

set(CMAKE_PREFIX_PATH ${QT6_INSTALL_PATH})

find_package(jsoncpp CONFIG REQUIRED)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Dota_2_Layout_Handler main.cpp main_widget.cpp d2_layout_handler.cpp d2_layout.cpp)
target_link_libraries(Dota_2_Layout_Handler
        Qt::Core
        Qt::Gui
        Qt::Widgets
        jsoncpp_lib_static)

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    if (NOT EXISTS "${QT6_INSTALL_PATH}/bin")
        set(QT6_INSTALL_PATH "${QT6_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT6_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT6_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT6_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT6_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT6_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()