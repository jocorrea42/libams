#include <errno.h>
#include "../include/libasm.h"
ssize_t ft_read_wrapper(int fd, void *buf, size_t count) {
    ssize_t ret = ft_read(fd, buf, count);
    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return ret;
}
