#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647

/**
 * Implementacni test IB002 2015 - uloha 2 (max 10 bodu)
 *
 * Vyplnte nasledujici udaje:
 * Jmeno: Jan Hudecek
 * UCO: 433779
 *
 * Pozn: pro ucely testovani musite mit ve slozce s programem i soubor
 * graphs.dat. Je v zipu se zadanim.
 *
 * Zadani:
 *
 * Naprogramujte funkci isTwocolourable, ktera pro zadany jednoduchy
 * souvisly neorientovany graf urci zda, je obarvitelny dvema barvami.
 *
 * Pripomente si, ze obarveni grafu definujeme jako prirazeni barev k vrcholum
 * tak, ze zadne dva vrcholy, ktere maji spolecnou hranu, nemaji stejnou barvu.
 *
 * Vstup: Graf reprezentovany matici sousednosti 'graph' rozmeru 'n' x 'n'
 * Vystup: 1 pro graf obarvitelny dvema barvami, 0 jinak
 *
 * Pr. cyklus delky 4:
 *
 * [[0,1,0,1],
 *  [1,0,1,0],
 *  [0,1,0,1],
 *  [1,0,1,0]]
 *
 * Pr. hvezda S3 se stredem ve vrcholu 0:
 *
 * [[0,1,1,1],
 *  [1,0,0,0],
 *  [1,0,0,0],
 *  [1,0,0,0]]
 */

int isTwoColorableRec(int n, int graph[n][n], int* black, int* red, int vertex) {
    //if(black[vertex] == 1)

    int result = 1;
    for(int i = 0; i< n; i++) {
        if(graph[vertex][i] == 1) {
            if(black[vertex]) {
                if(black[i])
                    return 0;
                if(red[i] == 0) {
                    red[i] = 1;
                    result*=isTwoColorableRec(n, graph, black, red, i);
                }
            } else {
                if(red[i])
                    return 0;
                if(black[i] == 0) {
                    black[i] = 1;
                    result *= isTwoColorableRec(n, graph, black, red, i);
                }
            }
        }
    }
    return result;
}

int isTwocolourable(int n, int graph[n][n])
{
    int visited[n];
    memset(visited, 0, n*sizeof(int));
    int black[n];
    memset(black, 0, n*sizeof(int));
    int red[n];
    memset(red, 0, n*sizeof(int));
    black[0] = 1;
    return isTwoColorableRec(n, graph, black, red, 0);
}

/**
 * Program generuje soubor ve formatu dot, ktery obsahuje testovany graf.
 *
 * Vygenerovane soubory nahrajte do online nastroje pro zobrazeni graphvizu:
 * http://sandbox.kidstrythisathome.com/erdos/
 * nebo http://graphviz-dev.appspot.com/ - zvlada i vetsi grafy
 **/


/***********************************************************************
 ***                Nasleduje kod testu, neupravujte                 ***
 **********************************************************************/

#define BIAS6 63
#define SMALLN 62
#define TOPBIT6 32

/**
 * Get the size of graph out of graph6 or sparse6 string.
 */
static int graphsize(char *s)
{
    char *p;
    int n;

    if (s[0] == ':') p = s+1;
    else             p = s;
    n = *p++ - BIAS6;

    if (n > SMALLN) {
        n = *p++ - BIAS6;
        n = (n << 6) | (*p++ - BIAS6);
        n = (n << 6) | (*p++ - BIAS6);
    }
    return n;
}

/**
 * Convert string in graph6 format to graph.
 */
static void stringtograph(char *s, int n, int graph[n][n])
{
    int x = 0;

    char *p = s + 1;
    if (n > SMALLN) p += 3;

    int k = 1;
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < j; ++i) {
            if (--k == 0) {
                k = 6;
                x = *(p++) - BIAS6;
            }

            if (x & TOPBIT6) {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
            x <<= 1;
        }
    }
}


void matrix2dot(int n, int graph[n][n])
{
    FILE* outputFile;
    outputFile = fopen("graph.dot" , "w");
    fprintf(outputFile, "graph G {\n");
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (graph[u][v]) {
                fprintf(outputFile, "\t %d -- %d\n", u, v);
            }
        }
    }
    fprintf(outputFile, "}\n");
    fclose(outputFile);
}

void test()
{
    FILE* f = fopen("graphs.dat", "r");
    if (f == NULL) {
        fprintf(stderr, "Error: Ve slozce se souborem chybi testovaci data: graphs.dat\n");
        return;
    }

    int success = 1;
    int solution;
    // This is generally a bad technique, but OK if we know the input
    for(char b[512]; fscanf(f, "%s %d\n", b, &solution) != EOF;) {
        int n = graphsize(b);
        int graph[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                graph[i][j] = 0;

        stringtograph(b, n, graph);
        int result = isTwocolourable(n, graph);

        if (result != solution) {
            printf("Test neprosel.\n");
            printf("Vas vysledek: %d\n", result);
            printf("Ocekavany vysledek: %d\n", solution);
            printf("Vykresleny graf najdete v souboru graph.dot\n");
            matrix2dot(n, graph);
            success = 0;
            break;
        }
    }

    if (success) {
        printf("Vsechny testy prosly :)\n");
    }

    fclose(f);
}

int main()
{
    test();
    return 0;
}
