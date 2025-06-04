#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

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

int main() {
    int digitos;
    printf("Introduce el número de dígitos del primo: ");
    scanf("%d", &digitos);

    printf("Generando número primo de %d dígitos...\n", digitos);
    sleep(5);

    long primo = generar_primo(digitos);
    FILE *fp = fopen("estado.txt", "w");
    fprintf(fp, "PRIMO: %ld\n", primo);
    fclose(fp);

    printf("Primo generado: %ld\n", primo);
    return 0;
}
