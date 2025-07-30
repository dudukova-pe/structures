#include <stdio.h>
#include <stdlib.h>
#include "./queue.h"

Elem* get_head(Queue* queue) {
        if (queue == NULL) {
                return NULL;
        }
        return queue->head;
}

void* get_elem(Queue* queue) {
        if (queue == NULL) {
                return NULL;
        }
        if (get_head(queue) == NULL) {
                return NULL;
        }
        return queue->head->comp;
}

void* get_comp(Elem* elem) {
        if (elem == NULL) {
                return NULL;
        }
        return elem->comp;
}

Elem* get_next(Elem* elem) {
        if (elem == NULL) {
                return NULL;
        }
        return elem->next;
}

Elem* get_tail(Queue* queue) {
        if (queue == NULL) {
                return NULL;
        }
        return queue->tail;
}

void set_comp(Elem* elem, void* comp) {
        if (elem != NULL) {
                elem->comp = comp;
        }
}

void set_next(Elem* elem, Elem* next) {
        if (elem != NULL) {
                elem->next = next;
        }
}

void set_head(Queue* queue, Elem* head) {
        if (queue != NULL) {
                queue->head = head;
        }
}

void set_tail(Queue* queue, Elem* tail) {
        if (queue != NULL) {
                queue->tail = tail;
        }
}

Elem* create_Elem(void* comp) {
        Elem* elem = (Elem*)calloc(1, sizeof(Elem));
        set_comp(elem, comp);
        set_next(elem, NULL);
        return elem;
}

Queue* create_Queue() {
        Queue* queue = (Queue*)calloc(1, sizeof(Queue));
        set_head(queue, NULL);
        set_tail(queue, NULL);
        return queue;
}

int check_empty(Queue* queue) {
        if (get_head(queue) == NULL) {
                return 1;
        }
        return 0;
}

int check_comp(Queue* queue, void* comp) {
        Elem* ptr = get_head(queue);
        while (ptr != NULL) {
                if (get_comp(ptr) == comp) {
                        return 1;
                }
                ptr = get_next(ptr);
        }
        return 0;
}

void push(Queue* queue, void* comp) {
        Elem* elem = create_Elem(comp);
        Elem* tail = get_tail(queue);
        set_next(tail, elem);
        set_tail(queue, elem);
        if (get_head(queue) == NULL) {
                set_head(queue, elem);
        }
}

void pop(Queue* queue, void** result) {
        Elem* head = get_head(queue);
        Elem* new = get_next(head);
        if (result != NULL) {
                *result = get_comp(head);
        }
        free(head);
        set_head(queue, new);
        if (get_head(queue) == NULL) {
                set_tail(queue, NULL);
        }
}

void delete_Queue(Queue* queue) {
        Elem* ptr = get_head(queue);
        while (ptr != NULL) {
                Elem* next = get_next(ptr);
                free(ptr);
                ptr = next;
        }
        free(queue);
}