// screenhat_server.c
#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define PORT 8080
#define MEDIA_DIR "/tmp/media/"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0) {
        char page[8192] = "<html><body><h1>piHAT Portal</h1>"
                          "<form method='POST' enctype='multipart/form-data'>"
                          "<input type='file' name='media'><input type='submit' value='Upload'></form><br>";

        strcat(page, "<h2>Uploaded Media</h2>");
        DIR *dir = opendir(MEDIA_DIR);
        struct dirent *entry;
        if (dir) {
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_type == DT_REG) {
                    char line[512];
                    snprintf(line, sizeof(line),
                             "<form method='POST' action='/delete?file=%s'>"
                             "%s <input type='submit' value='Delete'></form><br>",
                             entry->d_name, entry->d_name);
                    strcat(page, line);
                }
            }
            closedir(dir);
        }
        strcat(page, "</body></html>");
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, response);
    }

    if (strcmp(method, "POST") == 0 && strncmp(url, "/delete?file=", 13) == 0) {
        const char *filename = url + 13;
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s%s", MEDIA_DIR, filename);
        remove(filepath);
        const char *msg = "File deleted!";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(msg), (void*) msg, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, response);
    }

    return MHD_NO;
}

int main() {
    mkdir(MEDIA_DIR, 0777); // Ensure media directory exists
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &handle_request, NULL, MHD_OPTION_END);
    if (!daemon) return 1;
    getchar(); // Keep running
    MHD_stop_daemon(daemon);
    return 0;
}
