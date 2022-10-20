add_library(postman
            postman.h postman.c)

include_directories ("${PROJECT_SOURCE_DIR}/viewer")
target_link_libraries(postman viewer)
