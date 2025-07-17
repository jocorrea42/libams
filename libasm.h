#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>
#include <unistd.h>

/* ------------------ BASE FUNCTIONS ------------------ */

size_t  ft_strlen(const char *s);
char    *ft_strcpy(char *dst, const char *src);
int     ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char    *ft_strdup(const char *s);

/* ------------------ BONUS FUNCTIONS ------------------ */

/* Linked list structure for bonus */
typedef struct s_list
{
    void            *data;
    struct s_list   *next;
}               t_list;

/* Bonus functions */
int     ft_atoi_base(const char *str, const char *base);
void ft_list_push_front(t_list **begin_list, void *data);
int ft_list_size(t_list *begin_list);
void ft_list_sort(t_list **begin_list, int (*cmp)());
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

#endif
