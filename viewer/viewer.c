#include "viewer.h"
#include "viewer_queue/viewer_queue.h"

#include <stdlib.h>
#include <stdio.h>

static pthread_t viewer_task_handle = -1;

static void *viewer_task(void *args);


static void
*viewer_task(void *args)
{
    fd_set rfds;
    FD_ZERO(&rfds);

    int viewer_queue = viewer_queue_get();
    FD_SET(viewer_queue, &rfds);

    pthread_cleanup_push(viewer_cleanup_handler, NULL);

    while (1) {
        int result = select(viewer_queue + 1, &rfds, NULL, NULL, NULL);

        if (result == -1) {
            printf("Error on select.\r\n");
        } else if (result) {
            printf("Data is available on viewer task queue.\r\n");
            viewer_queue_pop();
        } else {
            printf("No data within given timeout.\r\n");
        }
    }

    pthread_cleanup_pop(NULL);

    return NULL;
}

int
viewer_init(void)
{
    int result = viewer_queue_init();
    if (result < 0) {
        return -1;
    }

    result = pthread_create(&viewer_task_handle,
                            NULL,
                            viewer_task,
                            VIEWER_TASK_NAME);

    return result;
}

pthread_t
viewer_task_handle_get(void)
{
    return viewer_task_handle;
}

void
viewer_cleanup_handler(void *arg)
{
    viewer_queue_unlink();
}
