#include "postman.h"

#include <assert.h>

#include "viewer_queue/viewer_queue.h"

void
postman_send_message(uint8_t *msg, size_t msg_len)
{
    assert(msg != NULL);

    viewer_queue_push_event_process_in_message(msg, msg_len);
}