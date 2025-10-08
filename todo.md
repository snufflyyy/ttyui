# todo list for ttyui

 - finish notifcations and notifcation manager
 - create more genaric widgets
 - make widget manager shrink if widgets are removed during runtime
 - account for terminal resizing
 - change everything to keep track of its state and not recalculate the position and sizes of the widgets every "frame"

# refactor code list

 - refactor the shitty ttyui_box_render function in rendering/box.c
 - remove stupid .settings struct idea
 - use the nice way of creating struct variables using the .variable_name thingy (besides vector2 because that would be annoying)
