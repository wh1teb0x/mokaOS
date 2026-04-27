#include <errno.h>
#include <sys/types.h>

caddr_t sbrk(int incr) {
    errno = ENOMEM; // Error: NO MEMory
    return (caddr_t)-1;
}
