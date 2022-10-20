cmake_minimum_required(VERSION 3.0)

project(senosrs_monitor_receiver
        VERSION 1.0.0
        LANGUAGES C)

add_executable(${CMAKE_PROJECT_NAME} main.c)

target_link_libraries(${CMAKE_PROJECT_NAME} rt)
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)

add_subdirectory(viewer)
target_link_libraries(${CMAKE_PROJECT_NAME} viewer)

add_subdirectory(viewer/viewer_queue)
target_link_libraries(${CMAKE_PROJECT_NAME} viewer_queue)

add_subdirectory(viewer/viewer_events)
target_link_libraries(${CMAKE_PROJECT_NAME} viewer_events)

add_subdirectory(postman)
target_link_libraries(${CMAKE_PROJECT_NAME} postman)

add_subdirectory(monitor_protos/nanopb)
target_link_libraries(${CMAKE_PROJECT_NAME} nanopb)

add_subdirectory(monitor_protos/protos_src)
target_link_libraries(${CMAKE_PROJECT_NAME} monitor_protos)

add_subdirectory(monitor_protos/pb_helper)
target_link_libraries(${CMAKE_PROJECT_NAME} pb_helper)



# zmq plugin
add_subdirectory(zmq_plugin)
target_link_libraries(${CMAKE_PROJECT_NAME} zmq_plugin)

add_subdirectory(zmq_plugin/zmq_plugin_socket)
target_link_libraries(${CMAKE_PROJECT_NAME} zmq_plugin_socket)

target_link_libraries(${CMAKE_PROJECT_NAME} czmq)
target_link_libraries(${CMAKE_PROJECT_NAME} zmq)

# testing 
enable_testing()

#testing plugin_socket
add_executable(test_plugin_socket zmq_plugin/zmq_plugin_socket/test/test.c)
target_link_libraries(test_plugin_socket zmq_plugin_socket)
target_link_libraries(test_plugin_socket czmq)
target_link_libraries(test_plugin_socket zmq)
add_test(NAME test_plugin_socket COMMAND test_plugin_socket)

#testing plugin_task
add_executable(test_plugin_task zmq_plugin/test/test.c)
target_link_libraries(test_plugin_task zmq_plugin)
target_link_libraries(test_plugin_task zmq_plugin_socket)
target_link_libraries(test_plugin_task czmq)
target_link_libraries(test_plugin_task zmq)
add_test(NAME test_plugin_task COMMAND test_plugin_task)

#testing monitor
