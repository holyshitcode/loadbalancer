#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "task.h"
#define for_each(pos, head) for(pos = (head)->next; pos != (head); pos = pos->next)

extern int processor_counter;

struct Processor {
    int processor_id;
    int task_count;
    struct Task *task_list;
    struct Processor *next;
};

int insert_task_to_processor(struct Processor *proc, struct Task *task_list);
int consume_task_from_processor(struct Processor *proc);
struct Processor *create_processor();
int insert_processor_to_list(struct Processor **processor_list);
#endif