#include "keyboard.h"
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <stropts.h>
#include <sys/stat.h>
#include <unistd.h>

#define DIR "/dev/input/"
#define LEN_FILENAME 256

static int is_char_device(const struct dirent *f) {
  struct stat statfile;
  char filename[LEN_FILENAME];
  snprintf(filename, LEN_FILENAME, "%s%s", DIR, f->d_name);

  if (stat(filename, &statfile)) {
    return 0;
  }
  return S_ISCHR(statfile.st_mode);
}

char *get_keyboard() {
  int num;
  struct dirent **event_file;
  char *filename = malloc(sizeof(char) * LEN_FILENAME);
  int fd = -1;
  unsigned int evbit = 0;
  const unsigned int kbdbit = KEY_A | KEY_B | KEY_C | KEY_Z;

  num = scandir(DIR, &event_file, is_char_device, alphasort);

  for (int i = 0; i < num; i++) {

    snprintf(filename, LEN_FILENAME, "%s%s", DIR, event_file[i]->d_name);

    fd = open(filename, O_RDONLY);

    ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);

    if ((evbit & EV_KEY) == EV_KEY) {

      ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(evbit)), &evbit);

      if ((evbit & kbdbit) == kbdbit) {
        close(fd);
        break;
      }
    }

    close(fd);
  }

  return filename;
}