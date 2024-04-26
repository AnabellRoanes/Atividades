#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pontos{
    float x;
    float y;
};

void lerPontos(FILE *arquivo, int ponto, struct pontos *vertices);
float areaTriangulo(struct pontos vertices[], int tamanho);

int main() {

    FILE *arquivo;
    int ponto;

    arquivo = fopen("vertices.txt", "r");
    system("cls");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado, ERRO !!!!\n");
        exit(1);
    }

    fscanf(arquivo, "%d", &ponto);
    struct pontos vertices[ponto];
    
    lerPontos(arquivo, ponto, vertices);
    
    float area = areaTriangulo(vertices, ponto);

    printf("A área do polígono é %.0f", area);
    fclose(arquivo);

    return 0;
}

void lerPontos(FILE *arquivo, int ponto, struct pontos *vertices) {
    for (int i = 0; i < ponto; i++) fscanf(arquivo, "%f %f", &vertices[i].x, &vertices[i].y);
}

float areaTriangulo(struct pontos vertices[], int tamanho) {
    float area = 0;

    for (int i = 0; i < tamanho - 2; i++) {
        float M[3][3] = {
            {vertices[0].x, vertices[0].y, 1},
            {vertices[i + 1].x, vertices[i + 1].y, 1},
            {vertices[i + 2].x, vertices[i + 2].y, 1},
        };

        float det = 0;

        det = det + (M[0][0] * M[1][1] * M[2][2]);
        det = det + (M[0][1] * M[1][2] * M[2][0]);
        det = det + (M[0][2] * M[1][0] * M[2][1]);
        det = det - (M[2][0] * M[1][1] * M[0][2]);
        det = det - (M[2][1] * M[1][2] * M[0][0]);
        det = det - (M[2][2] * M[1][0] * M[0][1]);

        area += det / 2;
    }

    if (area < 0) {
        area = -area;
    }

    return area;
}