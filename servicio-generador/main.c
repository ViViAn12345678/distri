#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <microhttpd.h>

#define PORT 80

long primo_generado = 0;
int listo = 0;

int es_primo(long num) {
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (long i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

long generar_primo(int digitos) {
    long inicio = pow(10, digitos - 1);
    long fin = pow(10, digitos) - 1;
    long primo;
    srand(time(NULL));
    do {
        primo = inicio + rand() % (fin - inicio + 1);
    } while (!es_primo(primo));
    return primo;
}

int responder(void *cls, struct MHD_Connection *connection, const char *url,
              const char *method, const char *version,
              const char *upload_data, size_t *upload_data_size, void **con_cls) {

    const char *respuesta;
    char buffer[256];

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/estatus") == 0) {
        if (listo)
            snprintf(buffer, sizeof(buffer), "PRIMO: %ld\n", primo_generado);
        else
            snprintf(buffer, sizeof(buffer), "Estado: PENDIENTE\n");

        respuesta = buffer;
    } else {
        respuesta = "Ruta no válida\n";
    }

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(respuesta), (void*)respuesta, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
    return ret;
}

int main() {
    int digitos = 5;
    primo_generado = generar_primo(digitos);
    listo = 1;

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL, &responder, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    printf("Servidor iniciado en puerto %d\n", PORT);
    getchar();  // espera indefinidamente
    MHD_stop_daemon(daemon);
    return 0;
}
