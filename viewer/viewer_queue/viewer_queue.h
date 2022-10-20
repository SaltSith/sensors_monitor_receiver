#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

int viewer_queue_init(void);
void viewer_queue_unlink(void);
void viewer_queue_pop(void);
int viewer_queue_get(void);

bool viewer_queue_push_event_process_in_message(uint8_t *msg_buff, size_t msg_len);
