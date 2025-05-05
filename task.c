#include "task.h"
#include <stdio.h>
#include <stdlib.h>

#define RUNNING_TIME rand() % 10 + 1
/*
 *  create new Task
 *  and set running time randomly
 *
 */
struct Task * create_task() {
    struct Task *new_task = malloc(sizeof(struct Task));
    if (!new_task) {
        return NULL;
    }
    new_task->running_time = RUNNING_TIME;
    new_task->next = NULL;
    return new_task;
}

/*
 *  create and insert task to global task_list
 */
int insert_task(struct Task **task_list) {
    struct Task *new_task = create_task();
    if(!new_task) {
        return -1;
    }
    if(*task_list == NULL) {
        *task_list = new_task;
        (*task_list)->next = new_task;
    }else {
        new_task->next = (*task_list)->next;
        (*task_list)->next = new_task;
    }
    return 0;
}

struct Task *get_task(struct Task **task_list) {
    if(*task_list == NULL) {
        return NULL;
    }
    struct Task *return_task = (*task_list)->next;

    if(return_task->next == return_task) {
        *task_list = NULL;
        return return_task;
    }
    (*task_list)->next = return_task->next;
    return return_task;
}

