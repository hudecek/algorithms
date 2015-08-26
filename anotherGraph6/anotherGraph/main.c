/**
 * Implementacny test IB002 - uloha 1. (12 bodov)
 *
 * Vyplnte nasledujuce udaje:
 * Meno:
 * UCO:
 * Skupina (v ktorej ste zapisany):
 *
 * Vasou ulohou bude v tomto zadani spocitat dlzku cesty cez nejake konkretne body z apouzitia algoritmu BellmanFord.
 * Pre blizsie inform=acie citajte nizsie v komentaroch.
 *
 * Po ukonceni prace nahrajte vas kod do odovzdavarne:
 * IS -> Student -> IB002 -> Odevzdavarny -> PraktickyTest_skupina
 * Odovzdavajte len zdrojovy kod, NEODOVZDAVAJTE subory s nastaveniami pre IDE.
 *
 * @author Henrich Lauko, do C prelozil Karel Kubicek
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define INT_MAX 2147483647

//struktura path je linearne jednosmerne zretezeny seznam
typedef struct _path {
    struct _path* next; //ukazatel na dalsi polozku, posledni ukazuje na NULL
    int vertex; //cislo vrcholu
} Path;

typedef struct Graph {
    int matrix[SIZE][SIZE]; //matice reprezentujici obsah
    int size; //aktivni velikost matice = pocet vrcholu
} Graph;

/**
 * vrati delku nejkratsi cesty v g z from do to
 *
 * v pripade ze najkratsia cesta neexistuje - ma zaporny cyklus, alebo vrcholi niesu spojene - vrati INT_MAX
 *
 * @param g prahladavany graf
 * @param from pociatok pocitania vzdialenosti
 * @param to koniec hladanej cesty
 * @return dlzku najkracsej cesty medzi from a to
 *
 * Ak cesta neexistuje pole obsahuje INT_MAX
 */
int BellmanFord(Graph* g, int from, int to);

/**
 * Vasou ulohou bude v tomto zadani spravne aplikovat prilozeny algoritmus BellmanFord,
 * ktory spocita najkratsiu vzdialenost 2 vrcholov v grafe.
 *
 * Metoda pathLength dostava na vstupe pole vrcholov vasou ulohou bude spocitat dlzku najkratsej
 * cesty ktora postupne prechadza vsetkymi vrcholmi.
 *
 * Ak path = {1,2,3} tak vysledna cesta bude dlzka cesty medzi vrcholom 1 a vrcholom 3 cez vrchol 2.
 *
 * V pripade ze cesta obsahuje zaporny cyklus alebo neexistuje vratte INT_MAX.
 * Ak je cesta prazdna algoritmus vrati INT_MAX.
 * Ak Cesta obsahuje jeden vrchol algoritmus vrati 0.
 *
 * V ostatnych pripadoch vrati najkratsiu cestu ktora prejde v poradi vsetky vrcholi zo zoznamu. Nie je vylucene ze
 * sa cesta bude vracat cez niektore vrcholi.
 */
int pathLength(Graph* g, Path* path){
    if(path == NULL)
        return INT_MAX;
    if(path->next == NULL)
        return 0;
    int length = 0;
    int total = 0;
    while (path->next!= NULL) {
        length = BellmanFord(g, path->vertex, path->next->vertex);
        if(length == INT_MAX)
            return INT_MAX;
        total+=length;
        path = path->next;
    }
    return total;
}

Path* createPath(int* vertices, int count);

void test(Graph* g, Path* p, int expected);

/**
 * Vytvori graf bez hran, uzel sousedi sam se sebou smyckou delky 0
 * @param g graf na inicializaci
 * @param size velikost grafu
 */
void initGraph(Graph* g, int size);

/**
 * prida do grafu hranu u v delky weight
 */
void addEdge(Graph* g, int u, int v, int weight);

int main(void)
{
    Graph g;
    initGraph(&g, 6);
    addEdge(&g, 0, 1, 1);
    addEdge(&g,1, 2, 2);
    addEdge(&g,0, 2, 1);
    addEdge(&g,2, 3, 3);
    addEdge(&g,3, 4, 1);
    addEdge(&g,4, 0, 1);

    //Test 1.
    puts("Test 1.: ");
    test(&g, NULL, INT_MAX);//prazdna cesta
    Path tmp;
    tmp.next = NULL;
    tmp.vertex = 1;//cesta dlzky 0
    test(&g, &tmp, 0);

    //Test 2.
    puts("Test 2.: ");
    Path* p;
    int arr1[] = {1,2,3,4};
    p = createPath(arr1, 4); //cesta 1 -> 2 -> 3 -> 4
    test(&g, p, 6);
    int arr2[] = {0,2,3};
    p = createPath(arr2, 3);
    test(&g, p, 4);
    int arr3[] = {0,1,5};
    p = createPath(arr3, 3); //nedosiahnutelny vrchol
    test(&g, p, INT_MAX);

    //Test 3
    puts("Test 3.: ");
    int arr4[] = {0,1,2,1,0};
    p = createPath(arr4, 5);
    test(&g, p, 16);

    //Test 4.
    puts("Test 4.: ");
    int arr5[] = {0,3,1,4,2};
    p = createPath(arr5, 5);
    test(&g, p, 15);

    //Test 5.
    puts("Test 5.: ");
    Graph g2;
    initGraph(&g2, 2);
    addEdge(&g2, 0, 1, -1);
    addEdge(&g2, 1, 0, -1);
    int arr6[] = {0,1};
    p = createPath(arr6, 2);
    test(&g2, p, INT_MAX);//zaporny cyklus v grafe
    int arr7[] = {0,1,0};
    p = createPath(arr7, 3);
    test(&g2, p, INT_MAX);//zaporny cyklus v grafe

    //Test 6.
    puts("Test 6.: ");
    Graph g3;
    initGraph(&g3, 4);
    addEdge(&g3, 0, 1, 1);
    addEdge(&g3, 1, 2, 1);
    addEdge(&g3, 2, 3, 1);
    addEdge(&g3, 3, 0, 1);
    int arr8[] = {1,1,2};
    p = createPath(arr8, 3); //prechod cez jeden vrchol dvakrat
    test(&g3, p, 1);

    //Test 7.
    puts("Test 7.: ");
    int arr9[] = {3,2,1,0};
    p = createPath(arr9, 4);
    test(&g3, p, 9);

    //Test 8.
    puts("Test 8.: ");
    int arr10[] = {3,3,2,2,1,1,0,0};
    p = createPath(arr10, 8);
    test(&g3, p, 9);

    //Test 9.
    puts("Test 9.: ");
    Graph g4;
    initGraph(&g4, 5);
    addEdge(&g4, 0, 1, 1);
    addEdge(&g4, 2, 3, 1);
    addEdge(&g4, 3, 4, 1);
    int arr11[] = {0,1};
    p = createPath(arr11, 2);
    test(&g4, p, 1);
    int arr12[] = {1,0};
    p = createPath(arr12, 2);
    test(&g4, p, INT_MAX); //cesta neexistuje
    int arr13[] = {2,4};
    p = createPath(arr13, 2);
    test(&g4, p, 2);
    int arr14[] = {4,2};
    p = createPath(arr14, 2);
    test(&g4, p, INT_MAX); //cesta neexistuje
    int arr15[] = {0,4};
    p = createPath(arr15, 2);
    test(&g4, p, INT_MAX); //cesta neexistuje

    //Test 10.
    puts("Test 10.: ");
    addEdge(&g4, 0, 1, -1);
    addEdge(&g4, 1, 2, -3);
    int arr17[] = {0,1};
    p = createPath(arr17, 2);
    test(&g4, p, -1);
    int arr18[] = {0,4};
    p = createPath(arr18, 2);
    test(&g4, p, -2);
    return 0;
}

int BellmanFord(Graph* g, int from, int to){
    int distance[g->size];
    for(int i = 0; i < g->size; i++){
        distance[i] = INT_MAX;
    }

    distance[from] = 0;

    for(int i = 0; i < g->size; i++){
        for(int u = 0; u < g->size; u++){
            for(int v = 0; v < g->size; v++){
                if(g->matrix[u][v] == INT_MAX) continue;
                if(distance[u] + g->matrix[u][v] < distance[v]){
                    if(distance[u] == INT_MAX) continue;
                    distance[v] = distance[u] + g->matrix[u][v];
                }
            }
        }
    }

    for(int u = 0; u < g->size; u++){
        for(int v = 0; v < g->size; v++){
            if(g->matrix[u][v] == INT_MAX) continue;
            if(distance[u] + g->matrix[u][v] < distance[v]){
                if(distance[u] == INT_MAX) continue;
                return INT_MAX;
            }
        }
    }

    return distance[to];
}
Path* createPath(int* vertices, int count) {
    Path* p = NULL;
    for (int i = count-1; i >= 0; --i) {
        Path* newP = malloc(sizeof(Path));
        newP->vertex = vertices[i];
        newP->next = p;
        p = newP;
    }
    return p;
}
void test(Graph* g, Path* p, int expected){
    int value = pathLength(g, p);
    if(value == expected){
        puts("OK!");
    }else{
        printf("Chyba vasa dlzka cesty je: %i != %i", value, expected);
    }
}
void initGraph(Graph* g, int size) {
    g->size = size;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(i == j) {
                g->matrix[i][j] = 0;
            }
            else {
                g->matrix[i][j] = INT_MAX;
            }
        }
    }
}
void addEdge(Graph* g, int u, int v, int weight){
    if(u < 0 || u >= g->size) return;
    if(v < 0 || v >= g->size) return;
    g->matrix[u][v] = weight;
}
