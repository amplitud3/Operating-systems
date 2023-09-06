#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void die(const char* fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);


  if(fmt[0] && fmt[strlen(fmt) - 1] == ':') {
    fputc(' ', stderr);
    perror(NULL);
  } else {
    fputc('\n', stderr);
  }

  exit(0);
}

int main(int argc, char** argv) {

  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANONYMOUS;

  char* buffer = mmap(NULL, 4096, protection, visibility, -1, 0);
  if(buffer == MAP_FAILED) die("could not map memory:");
  pid_t pid = fork();

  if(pid == -1) die("could not fork:");


  if(pid == 0) 
  {
    fgets(buffer, 4096, stdin);
  } 
  else 
  {

    wait(NULL);

    printf("%s\n", buffer);
  }

  return 0;
}