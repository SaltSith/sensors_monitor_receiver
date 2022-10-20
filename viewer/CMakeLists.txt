add_library(viewer
            viewer.h viewer.c)

target_link_libraries(viewer viewer_queue viewer_events)
