add_library(viewer_events
            viewer_events.h viewer_events.c)

include_directories ("${PROJECT_SOURCE_DIR}/viewer")
include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos")
include_directories ("${PROJECT_SOURCE_DIR}/monitor_protos/nanopb")
include_directories ("${PROJECT_SOURCE_DIR}/")

target_link_libraries(viewer_events pb_helper)
