#ifndef TASK_H
#define TASK_H

#define for_each(pos, head) for(pos = (head)->next; pos != (head); pos = pos->next)

struct Task{
    int running_time;
    struct Task *next;
};

struct Task * create_task();
int insert_task(struct Task **task_list);
struct Task *get_task(struct Task **task_list);

#endif