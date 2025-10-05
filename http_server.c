// http_server.c
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0) {
        const char *page = "<html><body><form method='POST' enctype='multipart/form-data'>"
                           "<input type='file' name='media'><input type='submit'></form></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, response);
    }

    if (strcmp(method, "POST") == 0) {
        // Handle upload (simplified placeholder)
        system("cp /tmp/uploaded_file /tmp/media/latest");
        FILE *trigger = fopen("/tmp/media/trigger.txt", "w");
        if (trigger) { fprintf(trigger, "update"); fclose(trigger); }
        const char *msg = "Upload received!";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(msg), (void*) msg, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, response);
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &handle_request, NULL, MHD_OPTION_END);
    if (!daemon) return 1;
    getchar(); // Keep running
    MHD_stop_daemon(daemon);
    return 0;
}
