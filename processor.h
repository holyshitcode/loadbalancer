#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "task.h"

struct Processor {
    int processor_id;
    int task_count;
    struct Task *task_list;
};

#endif