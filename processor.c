#include "processor.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/*
 *  insert task into processor's task_list
 */
int insert_task_to_processor(struct Processor *proc, struct Task *task_list) {
    if(proc == NULL || task_list == NULL) {
        return -1;
    }
    struct Task **target_list = &proc->task_list;
    insert_task(target_list);
    return 0;
}

/*
 * remove and running for running time
 * and remove task
 */
int consume_task_from_processor(struct Processor *proc) {
    struct Task **target_list = &proc->task_list;
    struct Task *remove_task = get_task(target_list);
    if(remove_task == NULL) {
        return -1;
    }
    sleep(remove_task->running_time);
    free(remove_task);
    return 0;
}
