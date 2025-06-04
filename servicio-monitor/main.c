#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("estado.txt", "r");
    if (fp == NULL) {
        printf("Estado: PENDIENTE\n");
    } else {
        char buffer[256];
        fgets(buffer, sizeof(buffer), fp);
        printf("Estado: %s\n", buffer);
        fclose(fp);
    }
    return 0;
}
