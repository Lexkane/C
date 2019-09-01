#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int data; 
    struct node_t *prev;
    struct node_t *next;
} node_t;

node_t *head = NULL;

void add_at(int pos, int data) {
    node_t *node = malloc(sizeof(node_t) * 1);
    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    if (head == NULL) {
        head = node;
        return;
    }

    int idx = 0;

    node_t *prev = NULL;
    node_t *cur = head;
    while (cur != NULL && idx != pos) {
        ++idx;
        prev = cur;
        cur = cur->next;
    }


    if (idx == 0) {
        head = node;
        node->next = cur;
        cur->prev = node;
        return;
    }


    if (cur == NULL) {
        prev->next = node;
        node->prev = prev;
        return;
    }

    prev->next = node;
    node->prev = prev;
    node->next = cur;
    cur->prev = node;
}

void add_beg(int data) {
    add_at(0, data);
}

void add_end(int data) {
    add_at(-1, data);
}

void remov(int data) {
    node_t *cur = head;

    while (cur != NULL && cur->data != data) {
        cur = cur->next;
    }


    if (cur == NULL) {
        return;
    }

    if (cur->prev == NULL) {
        if (cur->next == NULL) {

            head = NULL;
        } else {
  
            head = cur->next;
            head->prev = NULL;
        }

        free(cur);
        return;
    }

    if (cur->next == NULL) {
        cur->prev->next = NULL;

        free(cur);
        return;
    }

 
    if (cur->prev != NULL && cur->next != NULL) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        free(cur);
        return;
    }
}

void listAll_fwd() {
    node_t *temp = head;

    while (temp != NULL) {
        printf("data: %d\n", temp->data);
        temp = temp->next;
    }
}

void listAll_rev() {
    node_t *temp = head;


    while (temp->next != NULL) {
        temp = temp->next;
    }

    while (temp != NULL) {
        printf("data: %d\n", temp->data);
        temp = temp->prev;
    }
}

int main(int argc, char **argv) {
    add_end(2);
    add_end(3);
    add_end(5);
    add_beg(1);
    add_at(2, 4);

    printf("forward:\n");
    listAll_fwd();

    remov(1);
    remov(3);
    remov(5);

    printf("reverse:\n");
    listAll_rev();

    return 0;
}
