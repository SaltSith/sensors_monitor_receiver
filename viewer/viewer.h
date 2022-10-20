
#pragma once

#include <pthread.h>

#define VIEWER_TASK_NAME "viewer_task"

int viewer_init(void);
pthread_t viewer_task_handle_get(void);
void viewer_cleanup_handler(void *arg);