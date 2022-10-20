#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    VIEWER_EVENT_PROCESS_IN_MESSAGE = 0,
    VIEWER_EVENT_LAST
} viewer_event_type_t;

typedef struct {
    viewer_event_type_t ev;
    uint8_t *msg;
    size_t msg_len;
} viewer_event_t;

int viewer_event_handler(viewer_event_t event);

