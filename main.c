#include "processor.h"
#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define PROCESSOR_NUM 8
#define TASK_NUM 500

struct Worker {
    struct Processor *self;
    struct Processor *whole_proc_list;
    struct Task *task_list;
};


void* thread_func(void* arg) {
    struct Worker* worker = (struct Worker*)arg;
    if (worker == NULL || worker->self == NULL) {
        fprintf(stderr, "Invalid worker or worker->self is NULL. Exiting thread.\n");
        pthread_exit(NULL);
    }
    printf("Thread %d started!\n", worker->self->processor_id);
    struct Processor *whole_proc_list = worker->whole_proc_list;
    struct Task *task_list = worker->task_list;
    struct Processor *self = worker->self;

    for(int i = 0; i < TASK_NUM / PROCESSOR_NUM; i++) {
        struct Processor *proc = worker->self;
        if(proc->processor_id < 5) {
            insert_task_to_processor(proc, task_list);
        }else {
            if(i > 40) {
                insert_task_to_processor(proc, task_list);
            }
        }
    }
    int counter = 0;
    // int insert_counting = 3;
    while( self->task_count > 0 ) {
        consume_task_from_processor(self);
        counter++;
        if(counter == 3) {
            balance(&whole_proc_list);
            counter = 0;
        }
        // if(self->processor_id > 4 && insert_counting > 0) {
        //     for(int i = 0; i < 20; i++) {
        //         insert_task_to_processor(self, task_list);
        //         insert_counting--;
        //     }
        // }
        usleep(100000);
        }



    return NULL;
}

void *thread_func2(void *arg) {
    struct Processor *whole_proc_list = (struct Processor*)arg;
    struct Processor *pos;
    while(1) {
        for_each(pos,whole_proc_list) {
            printf("%d's amount=%d ",pos->processor_id,pos->task_count);
        }
        printf("\n");
        fflush(stdout);
        sleep(3);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t cpu[PROCESSOR_NUM];
    pthread_t alarm;
    struct Processor *whole_proc_list = NULL;
    struct Processor *pos;

    for (int i = 0; i < PROCESSOR_NUM; ++i) {
        insert_processor_to_list(&whole_proc_list);
    }

    struct Task *task_list = NULL;
    for (int i = 0; i < TASK_NUM; ++i) {
        insert_task(&task_list);
    }
    struct Worker worker_list[PROCESSOR_NUM];
    int i = 0;

    for_each(pos, whole_proc_list) {
        if (i >= PROCESSOR_NUM) break;
        worker_list[i].self = pos;
        worker_list[i].whole_proc_list = whole_proc_list;
        worker_list[i].task_list = task_list;
        i++;
    }

    pthread_create(&alarm, NULL, thread_func2, whole_proc_list);
    // pthread_detach(alarm);

    for (int i = 0; i < PROCESSOR_NUM; ++i) {
        pthread_create(&cpu[i], NULL, thread_func, &worker_list[i]);
    }
    for (int i = 0; i < PROCESSOR_NUM; ++i) {
        pthread_join(cpu[i], NULL);
    }








    return 0;
}