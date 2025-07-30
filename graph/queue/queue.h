#ifndef QUEUE_H
#define QUEUE_H

typedef struct Elem {
        void* comp;
        struct Elem* next;
} Elem;

typedef struct Queue {
        Elem* head;
        Elem* tail;
} Queue;

void* get_elem(Queue* queue);
Queue* create_Queue();
int check_empty(Queue* queue);
int check_comp(Queue* queue, void* comp);
void push(Queue* queue, void* comp);
void pop(Queue* queue, void** result);
void delete_Queue(Queue* queue);

#endif /*QUEUE_H*/