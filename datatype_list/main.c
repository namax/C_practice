/* 
 * File:   main.c
 * Author: namax
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void destroy_list_element(void *data) {
    if (data)
        free(data);
}

void print_list_element(void *data) {
    printf("%d\n", *((int *) data));
}

int main(int argc, char **argv) {

    List list;
    int *pInt;
    int k = 5;
    list_init(&list, destroy_list_element, print_list_element);
    pInt = (int *) malloc(sizeof(int));
    *pInt = k;
    list_ins_next(&list, NULL, pInt);
    list_ins_next(&list, NULL, pInt);
    list_print(&list);
    list_destroy(&list);
    return (EXIT_SUCCESS);
}
