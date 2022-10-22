#include "viewer_events.h"

#include "pb_helper/pb_helper.h"

#include "zmq_plugin/zmq_plugin_task.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

static int viewer_event_handler_process_in_message(void *arg);

typedef int(*viewer_event_handler_type)(void *arg);

static viewer_event_handler_type viewer_event_handlers[VIEWER_EVENT_LAST] = {
        viewer_event_handler_process_in_message,
};

static int
viewer_event_handler_process_in_message(void *arg)
{
    monitor_MonitorMsg *in_msg = (monitor_MonitorMsg *)arg;
    printf("ok\r\n");
    switch (in_msg->which_msg) {
        case monitor_MonitorMsg_temperature_async_tag:
            break;

        case monitor_MonitorMsg_temperature_get_res_tag:
            break;

        case monitor_MonitorMsg_version_get_res_tag:
            break;

        default:
            break;
    }

    free(in_msg);

    return 0;
}

int
viewer_event_handler(viewer_event_t event)
{
    return viewer_event_handlers[event.ev](event.arg);
}

