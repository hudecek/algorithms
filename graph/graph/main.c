#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/**
 * Implementacny test IB002 - uloha 1. (12 bodov)
 *
 * Vyplnte nasledujuce udaje:
 * Meno:
 * UCO:
 * Skupina (v ktorej ste zapisany):
 *
 * Vasou ulohou je v tomto zadani naimplementovat metodu, ktora bude v grafe
 * pocitat pocet vyskytov hviezdiciek.
 *
 * Hviezdicku v grafe definujeme ako uzol, ktory ma prave 5 susedov.
 * Uzol U je susedom uzlu V, ak existuje hrana z U do V alebo z V do U.
 * Uzol nie je sam sebe susedom, aj ked ma slucku (cz: smycku, en: loop).
 *
 * Graf je reprezentovany maticou, kde matrix[i][j] vyjadruje hranu
 * z vrcholu i a vrcholu j. Hodnota v matici vyjadruje vahu hrany, ak hrana
 * medzi vrcholmi neexistuje, hodnota je INT_MAX.
 *
 * Mame specialne grafy, kde kazdy uzol ma slucku (cz: smycku, en: loop)
 * s ohodnotenim nula. Tak si na to davajte pozor, pretoze uzol nie je sam sebe
 * susedom. Vseobecne hrana dlzky nula moze byt aj medzi roznymi uzlami a
 * robi z nich susedov.
 *
 * Po ukonceni prace nahrajte vas kod do odovzdavarne:
 * IS -> Student -> IB002 -> Odevzdavarny -> PraktickyTest_skupina
 * Odovzdavajte len zdrojovy kod, NEODOVZDAVAJTE subory s nastaveniami pre IDE.
 *
 * @author Henrich Lauko
 */

#define MAX_V 256

/**
 * Definicia grafu
 */
typedef struct Graph {
    int matrix[MAX_V][MAX_V];//matica reprezentujuca graf az do rozmerov 256 x 256
    int V;//pocet platnych vrcholov
}Graph;


/**
 * Vytvori graf s v vrcholmi, bez hran, s nulami na diagonale
 * @param v vrcholov grafu
 * @return ukazatel na vytvoreny graf, tj. strukturu Graph.
 */
Graph* createGraph(int v){
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = v;

    for(int i = 0; i < v; i++){
        for(int  j = 0; j < v; j++){
            if(i == j){
                graph->matrix[i][j] = 0;
            }else{
                graph->matrix[i][j] = INT_MAX;
            }
        }
    }
    return graph;
}


/**
 * Prida orientovanu hranu z u do v
 * @param g graf ktory sa modifikuje
 * @param u pociatok hrany
 * @param v koniec hrany
 * @param weight vaha hrany
 * Nespravi nic, ak indexy vrcholov su mimo matice
 */
void addEdge(Graph* g, int u, int v, int weight){
    if((u < 0 || u >= g->V) || (v < 0 || v >= g->V)) return;
    g->matrix[u][v] = weight;
}

/**
  * Implementujte metodu, ktora vrati pocet hviezdiciek v grafe g.
  * Hviezdicku v grafe definujeme ako vrchol, ktory ma prave 5 susedov.
  * Uzol U je susedom uzlu V, ak existuje hrana z U do V alebo z V do U.
  * @param g graf, v ktorom funkcia spocita hviezdicky
  */
 int computeStars(Graph* g) {
     int stars = 0;
     int n = 0;
     for(int i=0; i<g->V; i++) {
         n = 0;
         for(int j=0; j<g->V; j++) {
             if(i!=j) {
                 if(g->matrix[i][j] != INT_MAX)
                     n++;
                 if(g->matrix[j][i] != INT_MAX)
                     n++;
             }
         }
         if(n == 5)
             stars++;
     }
    return stars;
 }


int main(void)
{
    /* svoj kod mozete testovat tu: */

    /* nasledujuci kod nemente*/
    Graph* g = createGraph(20);
    //test 1
    printf("Test 1.:");
    int value = computeStars(g);
    if(value == 0) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 0\n",value);
    }

    //test 2
    addEdge(g, 1, 2, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 4, 1);
    addEdge(g, 4, 5, 1);
    addEdge(g, 5, 6, 1);
    printf("Test 2.:");
    value = computeStars(g);
    if(value == 0) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 0\n",value);
    }

    //test 3
    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 3, 1);
    addEdge(g, 1, 4, 1);
    addEdge(g, 1, 5, 1);
    addEdge(g, 1, 6, 1);
    printf("Test 3.:");
    value = computeStars(g);
    if(value == 1) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 1\n",value);
    }

    //test 4
    addEdge(g, 10, 12, 1);
    addEdge(g, 10, 13, 1);
    addEdge(g, 10, 14, 1);
    addEdge(g, 10, 15, 1);
    addEdge(g, 10, 16, 1);
    printf("Test 4.:");
    value = computeStars(g);
    if(value == 2) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 2\n",value);
    }

    //test 5
    addEdge(g, 1, 6, 5);
    addEdge(g, 1, 7, 1);
    addEdge(g, 1, 8, 0);
    addEdge(g, 1, 9, -1);
    printf("Test 5.:");
    value = computeStars(g);
    if(value ==  1) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 1\n",value);
    }

    //test 6
    addEdge(g, 11, 1, 0);
    addEdge(g, 11, 2, 0);
    addEdge(g, 11, 3, 0);
    addEdge(g, 11, 4, 0);
    addEdge(g, 11, 5, 0);
    addEdge(g, 17, 6, 1);
    addEdge(g, 17, 7, 1);
    addEdge(g, 17, 8, 1);
    addEdge(g, 17, 9, 1);
    addEdge(g, 17, 19, 1);
    printf("Test 6.:");
    value = computeStars(g);
    if(value == 3) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 3\n",value);
    }//

    Graph* g2 = createGraph(20);
    //test 7
    addEdge(g2,2,1,1);
    addEdge(g2,3,1,1);
    addEdge(g2,4,1,1);
    addEdge(g2,5,1,1);
    addEdge(g2,6,1,1);
    value = computeStars(g2);
    printf("Test 7.:");
    if(value == 1) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 1\n",value);
    }

    //test 8
    addEdge(g2,7,1,1);
    value = computeStars(g2);
    printf("Test 8.:");
    if(value == 0) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 0\n",value);
    }

    //test 9
    addEdge(g2,2,10,1);
    addEdge(g2,3,10,1);
    addEdge(g2,4,10,1);
    addEdge(g2,5,10,1);
    addEdge(g2,6,10,1);
    addEdge(g2,2,11,1);
    addEdge(g2,3,11,1);
    addEdge(g2,4,11,1);
    addEdge(g2,5,11,1);
    addEdge(g2,6,11,1);
    value = computeStars(g2);
    printf("Test 9.:");
    if(value == 2) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 2\n",value);
    }

    //test 10
    addEdge(g2,12,2,1);
    addEdge(g2,13,2,1);
    addEdge(g2,14,15,1);
    addEdge(g2,16,17,1);
    addEdge(g2,16,3,1);
    addEdge(g2,17,3,1);
    value = computeStars(g2);
    printf("Test 10.:");
    if(value == 4) {
        puts("OK");
    }else{
        printf("Chyba, vas vysledok: %i != 4\n",value);
    }
    return 0;
}

