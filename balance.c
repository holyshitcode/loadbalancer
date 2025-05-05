#include "balance.h"

#include <stdbool.h>
#include <stddef.h>

/*
 * judge can balance
 * depend on its task_count
 */
bool can_balance(int amount) {
    if(amount == 0 || amount < CAN_BALANCE) {
        return true;
    }
    return false;
}

/*
 * find busiest processor and return
 */
struct Processor *get_busiest_processor(struct Processor **proc_list){
    struct Processor *pos;
    for_each(pos,*proc_list) {
        if(!can_balance(pos->task_count)) {
            return pos;
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
            struct Processor *balance_target_processor = get_busiest_processor(proc_list);
            if(balance_target_processor ==NULL) {
                return -1;
            }
            // struct Task *to_processor_task = pos->task_list;
            struct Task *from_processor_task = balance_target_processor->task_list;
            if(from_processor_task == NULL) {
                return -1;
            }

            int limit = balance_target_processor->task_count - CAN_BALANCE;
            for(register int i = 0; i < limit; i++ ) {
                insert_task_to_processor(pos,from_processor_task);
            }
            return 0;
        }
    return -1;
}
