#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "libasm.h"

void	test_strlen(void)
{
	printf("\n=========== ft_strlen ===========\n");

	const char *tests[] = {
		"",
		"Hola",
		"42 Madrid",
		"¡Caracteres especiales!@#$%^&*()",
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
		NULL
	};

	for (int i = 0; tests[i]; i++)
	{
		size_t std = strlen(tests[i]);
		size_t ft = ft_strlen(tests[i]);
		printf("[%d] \"%s\"\n-> strlen = %zu | ft_strlen = %zu\n",
			i, tests[i], std, ft);
	}

	// ⚠️ Uncomment to test crash on NULL (expected behavior)
	// printf("\nNULL test (expected crash):\n");
	// printf("strlen(NULL): %zu\n", strlen(NULL));
	// printf("ft_strlen(NULL): %zu\n", ft_strlen(NULL));
}

void	test_strcpy(void)
{
	printf("\n=========== ft_strcpy ===========\n");

	char buffer[100];
	const char *tests[] = {
		"",
		"Hola mundo",
		"1234567890",
		"Lorem ipsum dolor sit amet",
		NULL
	};

	for (int i = 0; tests[i]; i++)
	{
		char *std = strcpy(buffer, tests[i]);
		char *ft = ft_strcpy(buffer, tests[i]);
		printf("[%d] \"%s\"\n-> strcpy = \"%s\" | ft_strcpy = \"%s\"\n",
			i, tests[i], std, ft);
	}

	// ⚠️ NULL test (uncomment with care)
	// printf("\nstrcpy(NULL, \"test\") => crash esperado\n");
	// ft_strcpy(NULL, "test");
}

void	test_strcmp(void)
{
	printf("\n=========== ft_strcmp ===========\n");

	const char *a[] = {"hola", "hola", "Hola", "", "abc", "abc", "", "z", NULL};
	const char *b[] = {"hola", "holA", "hola", "", "", "abc", "abc", "z", NULL};

	for (int i = 0; a[i]; i++)
	{
		int std = strcmp(a[i], b[i]);
		int ft = ft_strcmp(a[i], b[i]);
		printf("[%d] \"%s\" vs \"%s\"\n-> strcmp = %d | ft_strcmp = %d\n",
			i, a[i], b[i], std, ft);
	}

	// ⚠️ NULL test (uncomment with care)
	// ft_strcmp(NULL, "abc");
}

void	test_write(void)
{
	ssize_t ret_std, ret_ft;
	errno = 0;
	const char *msg1 = "Mensaje original write\n";
	const char *msg2 = "Mensaje ft_write asm\n";

	printf("\n=========== ft_write ===========\n");

	ret_std = write(1, msg1, strlen(msg1));
	printf("write returned: %zd, errno: %d\n", ret_std, errno);
	errno = 0;
	ret_ft = ft_write(1, msg1, strlen(msg1));
	printf("ft_write returned: %zd, errno: %d\n", ret_ft, errno);
	errno = 0;
	ret_std = write(1, msg2, strlen(msg2));
	printf("write returned: %zd, errno: %d\n", ret_std, errno);
	errno = 0;
	ret_ft = ft_write(1, msg2, strlen(msg2));
	printf("ft_write returned: %zd, errno: %d\n", ret_ft, errno);
	// Test error: fd inválido
	errno = 0;
	ret_std = write(-1, "Error test\n", 11);
	printf("write error returned: %zd, errno: %d\n", ret_std, errno);
	errno = 0;
	ret_ft = ft_write(-1, "Error test\n", 11);
	printf("ft_write error returned: %zd, errno: %d\n", ret_ft, errno);
}

void test_read(void)
{
    char buf_std[100] = {0};
    char buf_ft[100] = {0};
    ssize_t ret_std, ret_ft;
    int fd;

    printf("\n=========== ft_read ===========\n");

    fd = open("main.c", O_RDONLY);
    if (fd < 0)
    {
        perror("open testfile.txt");
        return;
    }

    errno = 0;
    ret_std = read(fd, buf_std, 50);
    printf("read returned: %zd, errno: %d\n", ret_std, errno);
    if (ret_std > 0)
        printf("read buffer: %.*s\n", (int)ret_std, buf_std);

    lseek(fd, 0, SEEK_SET); // Reset file pointer

    errno = 0;
    ret_ft = ft_read(fd, buf_ft, 50);
    printf("ft_read returned: %zd, errno: %d\n", ret_ft, errno);
    if (ret_ft > 0)
        printf("ft_read buffer: %.*s\n", (int)ret_ft, buf_ft);

    close(fd);

    // Error test: invalid fd
    errno = 0;
    ret_std = read(-1, buf_std, 10);
    printf("read error returned: %zd, errno: %d\n", ret_std, errno);

    errno = 0;
    ret_ft = ft_read(-1, buf_ft, 10);
    printf("ft_read error returned: %zd, errno: %d\n", ret_ft, errno);
}

void test_strdup(void)
{
    printf("\n=========== ft_strdup ===========\n");

    const char *tests[] = {
        "",
        "Hola mundo",
        "1234567890",
        "¡Caracteres especiales!@#$%^&*()",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
        NULL
    };
    for (int i = 0; tests[i]; i++)
    {
        char *std = strdup(tests[i]);
        char *ft = ft_strdup(tests[i]);
        if (std == NULL || ft == NULL)
        {
            printf("[%d] \"%s\" -> malloc failed\n", i, tests[i]);
            if(ft_strlen(std) > 0)
                free(std);
            if(ft_strlen(ft) > 0)
                free(ft);
            continue;
        }
		printf("std: %s, ft: %s\n", std, ft);
        int cmp = strcmp(std, ft);
        printf("[%d] \"%s\"\n-> strdup vs ft_strdup: strcmp = %d\n", i, tests[i], cmp);
        free(std);
        free(ft);
    }

    // ⚠️ NULL test (uncomment with care - expected crash)
    // printf("\nNULL test (expected crash):\n");
    // char *null_std = strdup(NULL);
    // char *null_ft = ft_strdup(NULL);
}

int	main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
    test_read();
    test_strdup();
	return (0);
}
