#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>
#include <unistd.h>

/* ------------------ WRAPPERS ------------------ */
ssize_t ft_read_wrapper(int fd, void *buf, size_t count);
ssize_t ft_write_wrapper(int fd, const void *buf, size_t count);
size_t  ft_strlen_wrapper(const char *s);
char   *ft_strcpy_wrapper(char *dst, const char *src);
int     ft_strcmp_wrapper(const char *s1, const char *s2);
char   *ft_strdup_wrapper(const char *s);

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

#endif
