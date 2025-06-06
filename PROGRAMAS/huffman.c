//Reyes Caballero Jesus Emmanuel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct Nodo {
    char simbolo;
    int frecuencia;
    struct Nodo *izq, *der;
} Nodo;

typedef struct {
    Nodo *nodos[MAX];
    int tam;
} MinHeap;

Nodo* crear_nodo(char simbolo, int frecuencia) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->simbolo = simbolo;
    nuevo->frecuencia = frecuencia;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

void intercambiar(Nodo** a, Nodo** b) {
    Nodo* temp = *a;
    *a = *b;
    *b = temp;
}

void insertar_heap(MinHeap *heap, Nodo *nodo) {
    int i = heap->tam++;
    heap->nodos[i] = nodo;
    while (i && nodo->frecuencia < heap->nodos[(i - 1) / 2]->frecuencia) {
        intercambiar(&heap->nodos[i], &heap->nodos[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Nodo* extraer_min(MinHeap *heap) {
    Nodo* raiz = heap->nodos[0];
    heap->nodos[0] = heap->nodos[--heap->tam];
    int i = 0;
    while (1) {
        int menor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;
        if (izq < heap->tam && heap->nodos[izq]->frecuencia < heap->nodos[menor]->frecuencia) menor = izq;
        if (der < heap->tam && heap->nodos[der]->frecuencia < heap->nodos[menor]->frecuencia) menor = der;
        if (menor == i) break;
        intercambiar(&heap->nodos[i], &heap->nodos[menor]);
        i = menor;
    }
    return raiz;
}

void generar_codigos(Nodo* raiz, char* buffer, int profundidad, char* codigos[MAX]) {
    if (raiz->izq == NULL && raiz->der == NULL) {
        buffer[profundidad] = '\0';
        codigos[(unsigned char)raiz->simbolo] = strdup(buffer);
        return;
    }
    if (raiz->izq) {
        buffer[profundidad] = '0';
        generar_codigos(raiz->izq, buffer, profundidad + 1, codigos);
    }
    if (raiz->der) {
        buffer[profundidad] = '1';
        generar_codigos(raiz->der, buffer, profundidad + 1, codigos);
    }
}

void decodificar_archivo(const char *cadena, Nodo *raiz) {
    Nodo *actual = raiz;
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == '0') actual = actual->izq;
        else actual = actual->der;
        if (actual->izq == NULL && actual->der == NULL) {
            printf("%c", actual->simbolo);
            actual = raiz;
        }
    }
}

int main() {
    char nombreArchivo[100];
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);

    FILE *in = fopen(nombreArchivo, "r");
    if (!in) {
        printf("No se pudo abrir %s\n", nombreArchivo);
        return 1;
    }

    int frecuencias[MAX] = {0};
    int total = 0;
    char c;
    while ((c = fgetc(in)) != EOF) {
        frecuencias[(unsigned char)c]++;
        total++;
    }
    fclose(in);

    MinHeap heap = {.tam = 0};
    for (int i = 0; i < MAX; i++) {
        if (frecuencias[i] > 0) {
            insertar_heap(&heap, crear_nodo((char)i, frecuencias[i]));
        }
    }

    while (heap.tam > 1) {
        Nodo* izq = extraer_min(&heap);
        Nodo* der = extraer_min(&heap);
        Nodo* nuevo = crear_nodo('\0', izq->frecuencia + der->frecuencia);
        nuevo->izq = izq;
        nuevo->der = der;
        insertar_heap(&heap, nuevo);
    }

    Nodo* raiz = extraer_min(&heap);
    char* codigos[MAX] = {NULL};
    char buffer[100];
    generar_codigos(raiz, buffer, 0, codigos);

    in = fopen(nombreArchivo, "r");
    FILE *out = fopen("codificado.txt", "w");
    int bits_codificados = 0;
    while ((c = fgetc(in)) != EOF) {
        fputs(codigos[(unsigned char)c], out);
        bits_codificados += strlen(codigos[(unsigned char)c]);
    }
    fclose(in);
    fclose(out);

    printf("\nTamano original: %d bits\n", total * 8);
    printf("Tamano comprimido: %d bits\n", bits_codificados);
    printf("Tasa de compresion: %.2f%%\n", 100.0 * bits_codificados / (total * 8));

    out = fopen("codificado.txt", "r");
    fseek(out, 0, SEEK_END);
    long len = ftell(out);
    rewind(out);
    char *cadena = malloc(len + 1);
    fread(cadena, 1, len, out);
    cadena[len] = '\0';
    fclose(out);

    printf("\nTexto decodificado:\n");
    decodificar_archivo(cadena, raiz);
    printf("\n");

    for (int i = 0; i < MAX; i++) {
        if (codigos[i]) free(codigos[i]);
    }
    free(cadena);

    return 0;
}
