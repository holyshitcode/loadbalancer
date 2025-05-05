#include "processor.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int process_counter = 0;

/*
 * create processor
 */
struct Processor *create_processor() {
    struct Processor *processor = malloc(sizeof(struct Processor));
    if (processor == NULL) {
        return NULL;
    }
    processor->processor_id = ++process_counter;
    processor->task_list = NULL;
    processor->task_count = 0;
    processor->next = NULL;
    return processor;
}

/*
 * create processor and insert into list
 */
int insert_processor_to_list(struct Processor **processor_list) {
    struct Processor *new_processor = create_processor();
    if (new_processor == NULL) {
        return -1;
    }
    if(*processor_list == NULL) {
        *processor_list = new_processor;
    }else {
        new_processor->next = (*processor_list)->next;
        (*processor_list)->next = new_processor;
    }
    return 0;
}


/*
 *  insert task into processor's task_list
 */
int insert_task_to_processor(struct Processor *proc, struct Task *task_list) {
    if(proc == NULL || task_list == NULL) {
        return -1;
    }
    struct Task **target_list = &proc->task_list;
    insert_task(target_list);
    proc->task_count++;
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
    proc->task_count--;
    sleep(remove_task->running_time);
    free(remove_task);
    return 0;
}
