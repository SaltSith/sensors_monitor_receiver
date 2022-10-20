#include "viewer_queue.h"
#include "viewer_events/viewer_events.h"

#include <mqueue.h>
#include <stdlib.h>
#include <stdbool.h>

#define VIEWER_QUEUE_NAME "/viewer_queue"

static int viewer_queue = -1;

int
viewer_queue_init(void)
{
    struct mq_attr attr;

    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = sizeof(viewer_event_t);
    attr.mq_curmsgs = 0;

    viewer_queue = mq_open(VIEWER_QUEUE_NAME,
                            O_CREAT | O_NONBLOCK | O_RDWR,
                            0777,
                            &attr);

    return viewer_queue;
}

void
viewer_queue_unlink(void)
{

    mq_unlink(VIEWER_QUEUE_NAME);
}

void
viewer_queue_pop(void)
{
    int result;
    unsigned int msg_prio;

    viewer_event_t event;
    int msg_len = sizeof(viewer_event_t);

    result = mq_receive(viewer_queue,
                        (char *)&event,
                        msg_len,
                        &msg_prio);

    if (result > 0) {
        viewer_event_handler(event);
    }
}

int
viewer_queue_get(void)
{
    return viewer_queue;
}

bool
viewer_queue_push_event_process_in_message(uint8_t *msg_buff, size_t msg_len)
{
    viewer_event_t event = {.ev = VIEWER_EVENT_PROCESS_IN_MESSAGE, .msg = msg_buff, .msg_len = msg_len};

    int result = mq_send(viewer_queue,
                         (char *)&event,
                         sizeof(viewer_event_t),
                         0);

    return result == 0 ? true : false;
}
