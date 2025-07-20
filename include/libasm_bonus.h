#ifndef LIBASM_BONUS_H
#define LIBASM_BONUS_H

#include <stddef.h>
#include <unistd.h>
/* ------------------ BONUS FUNCTIONS ------------------ */

/* Linked list structure for bonus */
typedef struct s_list
{
    void            *data;
    struct s_list   *next;
}               t_list;

/* Bonus functions (ASM) */
int     ft_atoi_base(const char *str, const char *base);
void ft_list_push_front(t_list **begin_list, void *data);
int ft_list_size(t_list *begin_list);
void ft_list_sort(t_list **begin_list, int (*cmp)());
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

/* Wrappers for bonus functions */
int ft_atoi_base_bonus_wrapper(const char *str, const char *base);
void ft_list_push_front_bonus_wrapper(t_list **begin_list, void *data);
int ft_list_size_bonus_wrapper(t_list *begin_list);
void ft_list_sort_bonus_wrapper(t_list **begin_list, int (*cmp)());
void ft_list_remove_if_bonus_wrapper(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

#endif