// screenhat_daemon.c
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#define MEDIA_DIR "/tmp/media/"
#define REFRESH_INTERVAL 5

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str), lensuffix = strlen(suffix);
    return lenstr >= lensuffix && strcmp(str + lenstr - lensuffix, suffix) == 0;
}

void play_media(const char *filename) {
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s%s", MEDIA_DIR, filename);

    if (ends_with(filename, ".gif") || ends_with(filename, ".jpg") || ends_with(filename, ".png") || ends_with(filename, ".bmp")) {
        char cmd[600];
        snprintf(cmd, sizeof(cmd), "sudo fbi -T 1 --noverbose -a '%s'", filepath);
        system(cmd);
    } else if (ends_with(filename, ".mp4") || ends_with(filename, ".avi") || ends_with(filename, ".mov")) {
        char cmd[600];
        snprintf(cmd, sizeof(cmd), "omxplayer '%s'", filepath);
        system(cmd);
    }
}

int main() {
    while (1) {
        DIR *dir = opendir(MEDIA_DIR);
        struct dirent *entry;

        if (dir) {
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_type == DT_REG) {
                    play_media(entry->d_name);
                    sleep(REFRESH_INTERVAL);
                }
            }
            closedir(dir);
        } else {
            system("clear"); // Optional: blank screen if no media
        }

        sleep(REFRESH_INTERVAL);
    }
}
