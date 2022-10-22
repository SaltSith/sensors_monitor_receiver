#include "viewer_events.h"

#include "pb_helper/pb_helper.h"

#include "zmq_plugin/zmq_plugin_task.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

static int viewer_event_handler_process_in_message(void *arg);

typedef int(*viewer_event_handler_type)(void *arg);

static viewer_event_handler_type viewer_event_handlers[VIEWER_EVENT_LAST] = {
        viewer_event_handler_process_in_message,
};

static int
viewer_event_handler_process_in_message(void *arg)
{
    monitor_MonitorMsg *in_msg = (monitor_MonitorMsg *)arg;

    if (in_msg->has_timestamp) {
        struct tm  ts;
        char buf[80];
        ts = *localtime(&in_msg->timestamp);
        strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
        printf("Datetime: %s ", buf);
    }

    if (in_msg->has_uid) {
        printf("UID: %u \r\n", in_msg->uid);
    }
    switch (in_msg->which_msg) {
        case monitor_MonitorMsg_temperature_async_tag:
            for (uint8_t i = 0; i < in_msg->msg.temperature_async.temperatures_count; i++) {
                if (in_msg->msg.temperature_async.temperatures[i].has_element && in_msg->msg.temperature_async.temperatures[i].has_temp) {
                    printf("Element %s temperature %f C\r\n",
                            in_msg->msg.temperature_async.temperatures[i].element == monitor_Temperature_Element_CPU ? "CPU":"GPU",
                            in_msg->msg.temperature_async.temperatures[i].temp);
                }
            }

            break;

        case monitor_MonitorMsg_temperature_get_res_tag:
            break;

        case monitor_MonitorMsg_version_get_res_tag:
            break;

        default:
            printf("Unknown message\r\n");
            break;
    }
    printf("\r\n");
    free(in_msg);

    return 0;
}

int
viewer_event_handler(viewer_event_t event)
{
    return viewer_event_handlers[event.ev](event.arg);
}

