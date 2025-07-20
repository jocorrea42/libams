#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "libasm.h"

void test_strlen(void) {
    printf("\n=== ft_strlen ===\n");
    const char *tests[] = {
        "", "a", "abc", "0123456789", "Lorem ipsum dolor sit amet.",
        "Con\nSaltos\nde\nLinea", "Espacios    ", "¡¿!@#$%^&*()_+", NULL
    };
    for (int i = 0; tests[i]; i++) {
        size_t std = strlen(tests[i]);
        size_t ft = ft_strlen_wrapper(tests[i]);
        printf("[%d] \"%s\"\n  strlen: %zu | ft_strlen: %zu\n", i, tests[i], std, ft);
    }
    // NULL test (should crash)
    // printf("strlen(NULL): %zu | ft_strlen(NULL): %zu\n", strlen(NULL), ft_strlen_wrapper(NULL));
}

void test_strcpy(void) {
    printf("\n=== ft_strcpy ===\n");
    char dest1[100], dest2[100];
    const char *tests[] = {
        "", "a", "abc", "0123456789", "Lorem ipsum dolor sit amet.",
        "Con\nSaltos\nde\nLinea", "Espacios    ", "¡¿!@#$%^&*()_+", NULL
    };
    for (int i = 0; tests[i]; i++) {
        strcpy(dest1, "XXXXXXXXXX");
        ft_strcpy_wrapper(dest2, "XXXXXXXXXX");
        char *std = strcpy(dest1, tests[i]);
        char *ft = ft_strcpy_wrapper(dest2, tests[i]);
        printf("[%d] \"%s\"\n  strcpy: \"%s\" | ft_strcpy: \"%s\"\n", i, tests[i], std, ft);
    }
    // NULL test (should crash)
    // ft_strcpy_wrapper(NULL, "test");
}

void test_strcmp(void) {
    printf("\n=== ft_strcmp ===\n");
    const char *a[] = {"", "a", "abc", "abc", "abc", "abc", "abc", "abc", NULL};
    const char *b[] = {"", "a", "abc", "abd", "ab", "abcd", "", "ABC", NULL};
    for (int i = 0; a[i]; i++) {
        int std = strcmp(a[i], b[i]);
        int ft = ft_strcmp_wrapper(a[i], b[i]);
        printf("[%d] \"%s\" vs \"%s\"\n  strcmp: %d | ft_strcmp: %d\n", i, a[i], b[i], std, ft);
    }
    // NULL test (should crash)
    // ft_strcmp_wrapper(NULL, "abc");
}

void test_write(void) {
    printf("\n=== ft_write ===\n");
    ssize_t ret_std, ret_ft;
    errno = 0;
    ret_std = write(1, "write: Hola mundo\n", 18);
    printf("write returned: %zd, errno: %d\n", ret_std, errno);
    errno = 0;
    ret_ft = ft_write_wrapper(1, "ft_write: Hola mundo\n", 21);
    printf("ft_write returned: %zd, errno: %d\n", ret_ft, errno);

    // Error cases
    errno = 0;
    ret_std = write(-1, "error", 5);
    printf("write(-1) returned: %zd, errno: %d\n", ret_std, errno);
    errno = 0;
    ret_ft = ft_write_wrapper(-1, "error", 5);
    printf("ft_write(-1) returned: %zd, errno: %d\n", ret_ft, errno);
}

void test_read(void) {
    printf("\n=== ft_read ===\n");
    char buf1[100], buf2[100];
    ssize_t ret_std, ret_ft;
    int fd = open("tester/main.c", O_RDONLY);
    if (fd < 0) { perror("open"); return; }
    errno = 0;
    ret_std = read(fd, buf1, 50);
    printf("read returned: %zd, errno: %d\n", ret_std, errno);
    if (ret_std > 0) printf("read buffer: %.*s\n", (int)ret_std, buf1);
    lseek(fd, 0, SEEK_SET);
    errno = 0;
    ret_ft = ft_read_wrapper(fd, buf2, 50);
    printf("ft_read returned: %zd, errno: %d\n", ret_ft, errno);
    if (ret_ft > 0) printf("ft_read buffer: %.*s\n", (int)ret_ft, buf2);
    close(fd);

    // Error case
    errno = 0;
    ret_std = read(-1, buf1, 10);
    printf("read(-1) returned: %zd, errno: %d\n", ret_std, errno);
    errno = 0;
    ret_ft = ft_read_wrapper(-1, buf2, 10);
    printf("ft_read(-1) returned: %zd, errno: %d\n", ret_ft, errno);
}

void test_strdup(void) {
    printf("\n=== ft_strdup ===\n");
    const char *tests[] = {
        "", "a", "abc", "0123456789", "Lorem ipsum dolor sit amet.",
        "Con\nSaltos\nde\nLinea", "Espacios    ", "¡¿!@#$%^&*()_+", NULL
    };
    for (int i = 0; tests[i]; i++) {
        char *std = strdup(tests[i]);
        char *ft = ft_strdup_wrapper(tests[i]);
        printf("[%d] \"%s\"\n  strdup: \"%s\" | ft_strdup: \"%s\"\n", i, tests[i], std, ft);
        if (std && ft) printf("  strcmp: %d\n", strcmp(std, ft));
        free(std);
        free(ft);
    }
    // NULL test (should crash)
    // ft_strdup_wrapper(NULL);
}

int main(void) {
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    return 0;
}