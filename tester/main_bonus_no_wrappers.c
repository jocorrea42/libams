#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libasm_bonus.h"

// ---------- TEST FT_ATOI_BASE ----------
void test_atoi_base_exhaustive(void)
{
    printf("=========== ft_atoi_base_bonus EXHAUSTIVE ===========\n");

    struct
    {
        const char *str;
        const char *base;
        int expected;
        const char *desc;
    } tests[] = {
        {"123", "", 0, "base vacía"},
        {"123", "0", 0, "base de un solo carácter"},
        {"123", "01234567890", 0, "base con caracteres repetidos"},
        {"123", "01234+56789", 0, "base con signo '+'"},
        {"123", "01234-56789", 0, "base con signo '-'"},
        {"123", "01234 56789", 0, "base con espacio"},
        {"123", "01234\t56789", 0, "base con tab"},
        {"123", "01234\n56789", 0, "base con salto de línea"},
        {NULL, "0123456789", 0, "str NULL"},
        {"", "0123456789", 0, "str vacío"},
        {"42", "0123456789", 42, "decimal positivo"},
        {"-42", "0123456789", -42, "decimal negativo"},
        {"+42", "0123456789", 42, "decimal con signo +"},
        {"   42", "0123456789", 42, "decimal con espacios"},
        {"\t\n  42", "0123456789", 42, "decimal con tabs y saltos"},
        {"--42", "0123456789", 0, "doble signo negativo"},
        {"++42", "0123456789", 0, "doble signo positivo"},
        {"-+42", "0123456789", 0, "signos mezclados"},
        {"1010", "01", 10, "binario positivo"},
        {"-1010", "01", -10, "binario negativo"},
        {"7B", "0123456789ABCDEF", 123, "hexadecimal positivo"},
        {"-7B", "0123456789ABCDEF", -123, "hexadecimal negativo"},
        {"zzz", "abcdefghijklmnopqrstuvwxyz", 17575, "base 26 positivo"},
        {"-zzz", "abcdefghijklmnopqrstuvwxyz", -17575, "base 26 negativo"},
        {"42abc", "0123456789", 42, "decimal con letras al final"},
        {"abc42", "0123456789", 0, "letras antes de número"},
        {"  +--10", "0123456789", 0, "espacios y signos mezclados"},
        {"123", NULL, 0, "base NULL"},
        {NULL, NULL, 0, NULL}};

    for (int i = 0; tests[i].desc; i++)
    {
        int result = ft_atoi_base(tests[i].str, tests[i].base);
        printf("[%2d] %-30s | str: \"%s\" base: \"%s\" -> result: %d (expected: %d) %s\n",
               i,
               tests[i].desc,
               tests[i].str ? tests[i].str : "NULL",
               tests[i].base ? tests[i].base : "NULL",
               result, tests[i].expected,
               (result == tests[i].expected) ? "OK" : "FAIL");
    }
}

// ---------- TEST FT_LIST_PUSH_FRONT & FT_LIST_SIZE ----------
void test_list_push_front_and_size(void)
{
    printf("\n=========== ft_list_push_front_bonus & ft_list_size_bonus (EXHAUSTIVE) ===========\n");
    t_list *list = NULL;

    printf("Initial size (should be 0): %d\n", ft_list_size(list));

    ft_list_push_front(&list, NULL);
    printf("After NULL push, size: %d\n", ft_list_size(list));

    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        int *v = malloc(sizeof(int)); *v = vals[i];
        ft_list_push_front(&list, v);
        printf("Pushed %d, size: %d\n", *v, ft_list_size(list));
    }

    int *v = malloc(sizeof(int)); *v = 99;
    ft_list_push_front(&list, v);
    printf("Pushed %d at head, size: %d\n", *v, ft_list_size(list));

    ft_list_push_front(NULL, v); // debe no crashear
    printf("Push with NULL begin_list (should not crash)\n");

    printf("List: ");
    for (t_list *tmp = list; tmp; tmp = tmp->next) {
        if (tmp->data) printf("%d -> ", *(int*)tmp->data);
        else printf("(null) -> ");
    }
    printf("NULL\n");

    while (list) {
        t_list *n = list->next;
        free(list->data);
        free(list);
        list = n;
    }
}

// ---------- TEST FT_LIST_SORT ----------
int cmp_int(void *a, void *b)
{
    if (!a || !b)
        return 0;
    int ia = *(int *)a, ib = *(int *)b;
    return (ia > ib) - (ia < ib);
}

void test_list_sort(void)
{
    printf("\n=========== ft_list_sort_bonus (EXHAUSTIVE) ===========\n");
    t_list *list = NULL;

    ft_list_sort(&list, cmp_int);
    printf("Sort empty list: OK\n");

    int *v = malloc(sizeof(int)); *v = 42;
    ft_list_push_front(&list, v);
    ft_list_sort(&list, cmp_int);
    printf("Sort single element: %d\n", *(int*)list->data);
    free(list->data); free(list); list = NULL;

    int vals1[] = {1, 2, 3, 4, 5};
    for (int i = 4; i >= 0; i--) {
        int *v = malloc(sizeof(int)); *v = vals1[i];
        ft_list_push_front(&list, v);
    }
    ft_list_sort(&list, cmp_int);
    printf("Sorted: ");
    for (t_list *tmp = list; tmp; tmp = tmp->next)
        printf("%d ", *(int*)tmp->data);
    printf("\n");
    while (list) {
        t_list *n = list->next;
        free(list->data);
        free(list);
        list = n;
    }

    int vals2[] = {4, 2, 5, 1, 3};
    for (int i = 0; i < 5; i++) {
        int *v = malloc(sizeof(int)); *v = vals2[i];
        ft_list_push_front(&list, v);
    }
    printf("Before sort: ");
    for (t_list *tmp = list; tmp; tmp = tmp->next)
        printf("%d ", *(int*)tmp->data);
    printf("\n");
    ft_list_sort(&list, cmp_int);
    printf("After sort: ");
    for (t_list *tmp = list; tmp; tmp = tmp->next)
        printf("%d ", *(int*)tmp->data);
    printf("\n");
    while (list) {
        t_list *n = list->next;
        free(list->data);
        free(list);
        list = n;
    }

    int vals3[] = {2, 2, 1, 3, 3};
    for (int i = 0; i < 5; i++) {
        int *v = malloc(sizeof(int)); *v = vals3[i];
        ft_list_push_front(&list, v);
    }
    ft_list_sort(&list, cmp_int);
    printf("Sorted with duplicates: ");
    for (t_list *tmp = list; tmp; tmp = tmp->next)
        printf("%d ", *(int*)tmp->data);
    printf("\n");
    while (list) {
        t_list *n = list->next;
        free(list->data);
        free(list);
        list = n;
    }

    ft_list_sort(&list, NULL);
    printf("Sort with NULL comparator: OK (should do nothing)\n");
}

// ---------- TEST FT_LIST_REMOVE_IF ----------
void free_data(void *data) { free(data); }

void test_list_remove_if(void)
{
    printf("\n=========== ft_list_remove_if_bonus (EXHAUSTIVE) ===========\n");
    t_list *list = NULL;
    int ref = 1;

    ft_list_remove_if(&list, &ref, cmp_int, free_data);
    printf("Remove_if on empty list: OK\n");

    for (int i = 0; i < 3; i++) {
        int *v = malloc(sizeof(int)); *v = 7;
        ft_list_push_front(&list, v);
    }
    ref = 7;
    ft_list_remove_if(&list, &ref, cmp_int, free_data);
    printf("Remove all elements with value 7, size: %d\n", ft_list_size(list));

    int vals[] = {1, 2, 3, 2, 4};
    for (int i = 0; i < 5; i++) {
        int *v = malloc(sizeof(int)); *v = vals[i];
        ft_list_push_front(&list, v);
    }
    ref = 2;
    ft_list_remove_if(&list, &ref, cmp_int, free_data);
    printf("After remove_if 2, size: %d\n", ft_list_size(list));
    printf("List contents: ");
    for (t_list *tmp = list; tmp; tmp = tmp->next)
        printf("%d ", *(int*)tmp->data);
    printf("\n");

    ft_list_remove_if(&list, &ref, NULL, free_data);
    printf("Remove_if with NULL comparator (no change), size: %d\n", ft_list_size(list));

    ref = 3;
    ft_list_remove_if(&list, &ref, cmp_int, NULL);
    printf("Remove_if 3 with NULL free_fct, size: %d\n", ft_list_size(list));
    printf("List contents: ");
    for (t_list *tmp = list; tmp; tmp = tmp->next)
        printf("%d ", *(int*)tmp->data);
    printf("\n");

    while (list) {
        t_list *n = list->next;
        free(list->data);
        free(list);
        list = n;
    }
}

int main(void)
{
    test_atoi_base_exhaustive();
    test_list_push_front_and_size();
    test_list_sort();
    test_list_remove_if();
    return 0;
}
