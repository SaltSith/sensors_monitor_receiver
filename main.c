#include <stdio.h>

#include "zmq_plugin/zmq_plugin_task.h"
#include "viewer/viewer.h"

int 
main(void)
{
    if (viewer_init()) {
        return -1;
    }

    if (zmq_plugin_task_init()) {
        return -1;
    }

    pthread_join(viewer_task_handle_get(), NULL);

    pthread_join(zmq_plugin_task_handle_get(), NULL);

    return 0;
}
