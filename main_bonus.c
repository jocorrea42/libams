#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libasm.h"

void test_atoi_base(void)
{
    printf("=========== ft_atoi_base_bonus ===========\n");

    struct {
        const char *str;
        const char *base;
        int expected;
    } tests[] = {
        {"1010", "01", 10},
        {"-1A", "0123456789ABCDEF", -26},
        {"zzz", "abcdefghijklmnopqrstuvwxyz", 17575},
        {"123", "0123456789", 123},
        {"  \t\n+42", "0123456789", 42},
        {"--10", "01", 0},        // invalid double sign
        {"123", "0", 0},          // invalid base length
        {"123", NULL, 0},         // null base
        {NULL, "01", 0},          // null string
        {"", "01", 0},            // empty string
        {"  +--10", "0123456789", 0}, // invalid mixed signs
        {"  +++10", "0123456789", 0}, // invalid multiple signs
        {"0", "0", 0},            // base with one character
        {NULL, NULL, 0}
    };

    for (int i = 0; tests[i].str; i++)
    {
        int result = ft_atoi_base(tests[i].str, tests[i].base);
        printf("[%d] str: \"%s\" base: \"%s\" -> result: %d (expected: %d)\n",
            i, tests[i].str ? tests[i].str : "NULL",
            tests[i].base ? tests[i].base : "NULL",
            result, tests[i].expected);
    }
}

int cmp_int(void *a, void *b)
{
    if (!a || !b) return 0;
    int ia = *(int *)a;
    int ib = *(int *)b;

    if (ia < ib)
        return -1;
    else if (ia > ib)
        return 1;
    else
        return 0;
}

void print_list(t_list *list)
{
    printf("List: ");
    while (list)
    {
        if (list->data)
            printf("%d -> ", *(int *)list->data);
        else
            printf("(null) -> ");
        list = list->next;
    }
    printf("NULL\n");
}

void free_data(void *data)
{
    free(data);
}

void test_list_push_front_and_size(void)
{
    printf("\n=========== ft_list_push_front_bonus & ft_list_size_bonus ===========\n");

    t_list *list = NULL;

    // test empty list size
    printf("Initial list size (empty): %d\n", ft_list_size(list));

    // push NULL data
    ft_list_push_front(&list, NULL);
    printf("After adding NULL data, size: %d\n", ft_list_size(list));
    print_list(list);

    // cleanup
    while (list)
    {
        t_list *tmp = list->next;
        if (list->data)
            free(list->data);
        free(list);
        list = tmp;
    }

    // normal test
    list = NULL;
    int values[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        int *val = malloc(sizeof(int));
        *val = values[i];
        ft_list_push_front(&list, val);
        printf("Added %d, list size now: %d\n", *val, ft_list_size(list));
    }
    print_list(list);

    // cleanup
    while (list)
    {
        t_list *tmp = list->next;
        free(list->data);
        free(list);
        list = tmp;
    }
}

void test_list_sort(void)
{
    printf("\n=========== ft_list_sort_bonus ===========\n");

    // test sorting empty list
    t_list *list = NULL;
    ft_list_sort(&list, cmp_int);
    printf("Sorting empty list passed (no crash)\n");

    // test sorting NULL comparator
    int val = 42;
    ft_list_push_front(&list, &val);
    ft_list_sort(&list, NULL);
    printf("Sorting with NULL comparator (should do nothing):\n");
    print_list(list);

    // cleanup
    while (list)
    {
        t_list *tmp = list->next;
        // no allocated data, so no free here
        free(list);
        list = tmp;
    }

    // test sorting normal list
    int vals[] = {4, 2, 5, 1, 3};
    list = NULL;
    for (int i = 0; i < 5; i++)
    {
        int *valp = malloc(sizeof(int));
        *valp = vals[i];
        ft_list_push_front(&list, valp);
    }
    printf("Before sort:\n");
    print_list(list);

    ft_list_sort(&list, cmp_int);

    printf("After sort:\n");
    print_list(list);

    // cleanup
    while (list)
    {
        t_list *tmp = list->next;
        free(list->data);
        free(list);
        list = tmp;
    }
}

void test_list_remove_if(void)
{
    printf("\n=========== ft_list_remove_if_bonus ===========\n");

    // test remove_if on empty list
    t_list *list = NULL;
    int ref = 1;
    ft_list_remove_if(&list, &ref, cmp_int, free_data);
    printf("Remove_if on empty list (no crash)\n");

    // test remove_if with NULL cmp or free function
    int val1 = 1;
    ft_list_push_front(&list, &val1);
    ft_list_remove_if(&list, &ref, NULL, free_data);
    printf("Remove_if with NULL cmp (should do nothing):\n");
    print_list(list);

    ft_list_remove_if(&list, &ref, cmp_int, NULL);
    printf("Remove_if with NULL free function (should remove without free):\n");
    print_list(list);

    // cleanup
    while (list)
    {
        t_list *tmp = list->next;
        free(list);
        list = tmp;
    }

    // test normal remove_if
    int vals[] = {1, 2, 3, 2, 4};
    list = NULL;
    for (int i = 0; i < 5; i++)
    {
        int *valp = malloc(sizeof(int));
        *valp = vals[i];
        ft_list_push_front(&list, valp);
    }
    printf("Before remove_if (removing 2):\n");
    print_list(list);

    int ref2 = 2;
    ft_list_remove_if(&list, &ref2, cmp_int, free_data);

    printf("After remove_if:\n");
    print_list(list);

    // cleanup
    while (list)
    {
        t_list *tmp = list->next;
        free(list->data);
        free(list);
        list = tmp;
    }
}

int main(void)
{
    test_atoi_base();
    test_list_push_front_and_size();
    test_list_sort();
    test_list_remove_if();
    return 0;
}
