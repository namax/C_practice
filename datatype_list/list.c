//
// Created by namax on 7/16/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/**
 * Initialize the list
 * @param list
 * @param destroy
 * @param print
 */
void list_init(List *list, void(*destroy)(void *data), void(*print)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->print = print;
    list->head = NULL;
    list->tail = NULL;
    return;
}

/**
 *
 * @param list
 */
void list_destroy(List *list) {
    void *data;

    while (list_size(list) > 0) {
        if (list_rem_next(list, NULL, (void **) &data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }

    memset(list, 0, sizeof (List));
    return;
}

/**
 *
 * @param list
 */
void list_print(List *list) {
    ListElmt * cur_element;
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    cur_element = list->head;

    do {
        printf("%d\n", *((int *) cur_element->data));
        cur_element = cur_element->next;
    } while (cur_element != NULL);

    printf("\n --- End of the List ---\n");
    return;
}

/**
 *
 * @param list
 * @param element
 * @param data
 * @return
 */
int list_ins_next(List *list, ListElmt *element, const void *data) {
    ListElmt * new_element;

    if ((new_element = (ListElmt *) malloc(sizeof (ListElmt))) == NULL)
        return;

    new_element->data = (void *) data;
    if (element == NULL) {
        //ins at the head of the list
        if (list_size(list) == 0) {
            list->tail = new_element;
        }

        new_element->next = list->head;
        list->head = new_element;

    } else {
        if (element->next == NULL) {
            list->tail = new_element;
        }

        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    return 0;
}


/**
 *
 * @param list
 * @param element
 * @param data
 * @return
 */
int list_rem_next(List *list, ListElmt *element, void **data) {
    ListElmt *old_element;

    //not allow remove from empty list
    if (list_size(list) == 0)
        return -1;

    if (element == NULL) {
        //from the head

        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1) {
            list->tail = NULL;
        }
    } else {
        //from any place
        if (element->next == NULL) {
            return -1;
        }

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (element->next == NULL) {
            list->tail = element;
        }

    }

    free(old_element);
    list->size--;
    return 0;
}


