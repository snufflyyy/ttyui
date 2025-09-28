cmake_minimum_required(VERSION 3.15)
project(ttyui C)

# needed for the zed code editor
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME}
    src/ttyui.c

    src/types/vector2.c

    src/display-buffer.c
    src/cursor.c
    src/box.c

    src/widgets/widget-manager.c
    src/widgets/widget-box.c

    #src/notifications/notification.c
    #src/notifications/notification-queue.c
    #src/notifications/notification-manager.c
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

# examples
add_subdirectory(examples/ttyui-weather)
