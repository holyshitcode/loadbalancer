#include "balance.h"

#include <stdbool.h>
#include <stddef.h>

/*
 * judge can balance
 * depend on its task_count
 */
static bool can_balance(int amount) {
    if(amount == 0 || amount < CAN_BALANCE) {
        return true;
    }
    return false;
}

/*
 * find busiest processor and return
 */
static struct Processor *get_busiest_processor(struct Processor **proc_list, struct Processor *self){
    struct Processor *pos;
    int highest = 0;
    for_each(pos,*proc_list) {
        if(pos->task_count > highest) {
            highest = pos->task_count;
        }
    }
    for_each(pos,*proc_list) {
        if(!can_balance(pos->task_count)) {
            if(pos != self && pos->task_count >=  highest) {
                return pos;
            }
        }
    }
    return NULL;
}

/*
 * balance processors
 */
int balance(struct Processor **proc_list) {
        struct Processor *pos;
        for_each(pos,*proc_list) {
            if(!can_balance(pos->task_count)) {
                continue;
            }
            struct Processor *balance_target_processor = get_busiest_processor(proc_list,pos);
            if(balance_target_processor ==NULL) {
                return -1;
            }
            struct Task *from_processor_task = get_task(&balance_target_processor->task_list);
            if(from_processor_task == NULL) {
                return -1;
            }

            for(register int i = 0; i < balance_target_processor->task_count/2; i++ ) {
                insert_task_to_processor(pos,from_processor_task);
                balance_target_processor->task_count--;
            }
            return 0;
        }
    return -1;
}
