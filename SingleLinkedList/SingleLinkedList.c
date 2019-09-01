#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int data; 
    struct node_t *next;
} node_t;

node_t *head = NULL;

void add_at(int pos, int data) {
    node_t *node = malloc(sizeof(node_t) * 1);
    node->data = data;
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
        return;
    }


    if (cur == NULL) {
        prev->next = node;
        return;
    }


    prev->next = node;
    node->next = cur;
}

void add_beg(int data) {
    add_at(0, data);
}

void add_end(int data) {
    add_at(-1, data);
}

void remov(int data) {
    node_t *prev = NULL;
    node_t *cur = head;

    while (cur != NULL && cur->data != data) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        return;
    }

    if (prev == NULL) {
        if (cur->next == NULL) {

            head = NULL;
        } else {

            head = cur->next;
        }

        free(cur);
        return;
    }


    if (cur->next == NULL) {
        prev->next = NULL;

        free(cur);
        return;
    }

    if (prev != NULL && cur->next != NULL) {
        prev->next = cur->next;

        free(cur);
        return;
    }
}

void listAll() {
    node_t *temp = head;

    while (temp != NULL) {
        printf("data: %d\n", temp->data);
        temp = temp->next;
    }
}

int main(int argc, char **argv) {
    add_end(2);
    add_end(3);
    add_end(5);
    add_beg(1);
    add_at(3, 4);

    printf("first item:\n");
    listAll();

    remov(1);
    remov(3);
    remov(5);

    printf("second item:\n");
    listAll();

    return 0;
}
