#include <stdio.h>
#include <string.h>

typedef struct {
    char estado[50];
    int codigo;
    char cidade[50];
    int populacao;
    float area;
    double pib;
    int pontos_turisticos;
} Carta;

// Lê os dados de uma carta do terminal
void lerCarta(Carta *c) {
    printf("Digite o estado: ");
    scanf(" %49[^\n]", c->estado);
    printf("Digite o código da carta: ");
    scanf("%d", &c->codigo);
    printf("Digite o nome da cidade: ");
    scanf(" %49[^\n]", c->cidade);
    printf("Digite a população: ");
    scanf("%d", &c->populacao);
    printf("Digite a área (km²): ");
    scanf("%f", &c->area);
    printf("Digite o PIB (em bilhões): ");
    scanf("%lf", &c->pib);
    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &c->pontos_turisticos);
    printf("\n");
}

// Exibe uma carta formatada, incluindo densidade populacional
void mostrarCarta(const Carta *c) {
    double densidade = c->populacao / c->area;
    printf("Carta %d - %s, %s\n", c->codigo, c->cidade, c->estado);
    printf("  População: %d\n", c->populacao);
    printf("  Área: %.2f km²\n", c->area);
    printf("  PIB: %.2f bilhões\n", c->pib);
    printf("  Pontos turísticos: %d\n", c->pontos_turisticos);
    printf("  Densidade: %.2f hab/km²\n\n", densidade);
}

/*
 Retorna:
  +1 se a vence,
  -1 se b vence,
   0 se empate.
 'op' varia de 1 a 5:
   1 = população (maior vence)
   2 = área       (maior vence)
   3 = PIB        (maior vence)
   4 = pontos turísticos (maior vence)
   5 = densidade  (menor vence)
*/
int compara(const Carta *a, const Carta *b, int op) {
    double va = 0, vb = 0;
    int inverso = 0;

    switch (op) {
        case 1:
            va = a->populacao;
            vb = b->populacao;
            break;
        case 2:
            va = a->area;
            vb = b->area;
            break;
        case 3:
            va = a->pib;
            vb = b->pib;
            break;
        case 4:
            va = a->pontos_turisticos;
            vb = b->pontos_turisticos;
            break;
        case 5:
            va = a->populacao / a->area;
            vb = b->populacao / b->area;
            inverso = 1;  // densidade: menor valor vence
            break;
        default:
            return 0;
    }

    if (va == vb) return 0;
    // se inverso==0, maior vence; se inverso==1, menor vence
    if ((va > vb && !inverso) || (va < vb && inverso))
        return +1;
    else
        return -1;
}

int main() {
    Carta c1, c2;
    int escolha, op1, op2, r1, r2, res;

    printf("=== Super Trunfo - Países ===\n\n");

    // Cadastro
    printf("--- Cadastro da Carta 1 ---\n");
    lerCarta(&c1);
    printf("--- Cadastro da Carta 2 ---\n");
    lerCarta(&c2);

    // Exibição
    printf("--- Cartas Cadastradas ---\n");
    mostrarCarta(&c1);
    mostrarCarta(&c2);

    // Menu de comparação
    printf("Escolha o tipo de comparação:\n");
    printf(" 1 - Um atributo\n");
    printf(" 2 - Dois atributos\n");
    printf("Opção: ");
    scanf("%d", &escolha);
    printf("\n");

    // comparações disponíveis
    printf("Atributos:\n");
    printf(" 1 - População (maior vence)\n");
    printf(" 2 - Área (maior vence)\n");
    printf(" 3 - PIB (maior vence)\n");
    printf(" 4 - Pontos turísticos (maior vence)\n");
    printf(" 5 - Densidade (menor vence)\n\n");

    if (escolha == 1) {
        // um atributo
        printf("Escolha o atributo para comparação: ");
        scanf("%d", &op1);
        res = compara(&c1, &c2, op1);
        if (res ==  1) printf("Carta %d (%s) VENCE!\n", c1.codigo, c1.cidade);
        else if (res == -1) printf("Carta %d (%s) VENCE!\n", c2.codigo, c2.cidade);
        else            printf("EMPATE!\n");
    }
    else if (escolha == 2) {
        // dois atributos
        printf("Primeiro atributo: ");
        scanf("%d", &op1);
        printf("Segundo atributo: ");
        scanf("%d", &op2);

        r1 = compara(&c1, &c2, op1);
        r2 = compara(&c1, &c2, op2);

        // se ambos resultados iguais (1 ou -1), aquele vence
        if (r1 == r2) {
            if (r1 ==  1) printf("Carta %d (%s) VENCE nos dois critérios!\n", c1.codigo, c1.cidade);
            else if (r1 == -1) printf("Carta %d (%s) VENCE nos dois critérios!\n", c2.codigo, c2.cidade);
            else printf("EMPATE nos dois critérios!\n");
        } else {
            // desempate: usa primeiro atributo, se empate no primeiro, usa segundo
            int decisao = (r1 != 0) ? r1 : r2;
            if (decisao ==  1) printf("Carta %d (%s) VENCE no critério de desempate!\n", c1.codigo, c1.cidade);
            else if (decisao == -1) printf("Carta %d (%s) VENCE no critério de desempate!\n", c2.codigo, c2.cidade);
            else printf("EMPATE GERAL!\n");
        }
    }
    else {
        printf("Opção inválida.\n");
    }

    return 0;
}
