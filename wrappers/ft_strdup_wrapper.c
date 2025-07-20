#include <stdlib.h>
#include <stddef.h>
#include "../include/libasm.h"

// Solo copia la cadena usando ASM, pero malloc lo hace C
char *ft_strdup_wrapper(const char *s) {
    size_t len = ft_strlen(s) + 1;
    char *dst = (char *)malloc(len);
    if (!dst)
        return NULL;
    ft_strcpy(dst, s);
    return dst;
}
