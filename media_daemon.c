// media_daemon.c
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str), lensuffix = strlen(suffix);
    return lenstr >= lensuffix && strcmp(str + lenstr - lensuffix, suffix) == 0;
}

int main() {
    while (1) {
        if (access("/tmp/media/trigger.txt", F_OK) == 0) {
            if (ends_with("/tmp/media/latest", ".gif")) {
                system("sudo fbi -T 1 --noverbose -a /tmp/media/latest"); // GIF playback
            } else if (ends_with("/tmp/media/latest", ".mp4")) {
                system("omxplayer /tmp/media/latest"); // Video playback
            } else {
                system("sudo fbi -T 1 --noverbose -a /tmp/media/latest"); // Static image
            }
            remove("/tmp/media/trigger.txt");
        }
        sleep(1);
    }
}
