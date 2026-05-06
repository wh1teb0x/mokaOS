#include <errno.h>
#include <sys/types.h>

caddr_t sbrk(int incr) {
  errno = ENOMEM;  // Error: NO MEMory
  return (caddr_t)-1;
}

void _exit(void) {
  while (1) {
    __asm__("hlt");
  }
}

int getpid() { return 1; }

int kill(int pid, int sig) {
  errno = EINVAL;
  return -1;
}
