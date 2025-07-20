#include <errno.h>
#include "../include/libasm.h"
ssize_t ft_write_wrapper(int fd, const void *buf, size_t count) {
    ssize_t ret = ft_write(fd, buf, count);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}
