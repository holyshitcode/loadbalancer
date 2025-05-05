#include "processor.h"
#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROCESSOR_NUM 10
#define TASK_NUM 10

int main() {
    srand(time(NULL));

    struct Processor *proc_list = NULL;

    for (int i = 0; i < PROCESSOR_NUM; ++i) {
        insert_processor_to_list(&proc_list);
    }

    struct Task *task_list = NULL;
    for (int i = 0; i < TASK_NUM; ++i) {
        insert_task(&task_list);
    }

    struct Processor *pos;
    for (int i = 0; i < 6; ++i) {
        for_each(pos,proc_list) {
            if(pos->processor_id < 5) {
                insert_task_to_processor(pos, task_list);
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for_each(pos,proc_list) {
            if(pos->task_count < 4) {
                insert_task_to_processor(pos, task_list);
            }
        }
    }

    printf("Before balancing:\n");
    struct Processor *p;
    for_each(p, proc_list) {
        printf("Processor %d has %d tasks.\n", p->processor_id, p->task_count);
    }

    balance(&proc_list);
    balance(&proc_list);


    printf("\nAfter balancing1:\n");
    for_each(p, proc_list) {
        printf("Processor %d has %d tasks.\n", p->processor_id, p->task_count);
    }

    balance(&proc_list);
    balance(&proc_list);


    printf("\nAfter balancing2:\n");
    for_each(p, proc_list) {
        printf("Processor %d has %d tasks.\n", p->processor_id, p->task_count);
    }

    balance(&proc_list);
    balance(&proc_list);


    printf("\nAfter balancing3:\n");
    for_each(p, proc_list) {
        printf("Processor %d has %d tasks.\n", p->processor_id, p->task_count);
    }

    return 0;
}