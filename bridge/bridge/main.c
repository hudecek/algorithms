// Implementační test IB002 - úloha 1. (lehčí, 12 bodů)

// Vyplňte následující údaje:
// Jméno:
// UČO:
// Skupina:

#include <stdio.h>
#include <stdlib.h>

//
// Vytvoří prázdnou matici sousednosti pro graf o n vrcholech.
//
int** createGraph(int n){
  int** k = (int**) malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++)
    k[i] = (int*) calloc(n, sizeof(int));
  return k;
}

//
// Přidá hranu (u,v) do grafu. Graf je neorientovaný, tj. hrany jsou obousměrné.
//
void add_edge(int** matrix, int u, int v) {
  matrix[u][v] = 1;
  matrix[v][u] = 1;
}

//
// ÚKOL:
// Naprogramujte funkci, která ověří, že je daná hrana mostem. Hrana v grafu
// se nazývá most, pokud neleží na žádném cyklu (a jejím odebráním by se tedy
// graf rozpadnul na více komponent).
//
// Funkce dostane graf zadaný počtem vrcholů a maticí sousednosti,
// a dva vrcholy u, v (resp. jejich čísla). Funkce vrací 1 nebo 0.
// Pokud hrana (u,v) v grafu není, vraťte 0.
// Pokud hrana (u,v) v grafu je, vraťte 1 pokud je mostem, 0 pokud ne.
//
// Příklad:
//       2           4
//     /   \       /   \
//    0  -  1  -  3  -  5     6
//
// is_bridge(7, graph, 0, 4) = 0, neboť tato hrana v grafu není
// is_bridge(7, graph, 1, 3) = 1, odebráním se graf rozpadne na dvě komponenty
// is_bridge(7, graph, 2, 1) = 0, hrana se nachází na cyklu 0 - 1 - 2
//

int isNotThere(int* array, int size, int vertex) {
    for(int i=0; i<size; i++) {
        if(array[i] == vertex)
            return 0;
    }
    return 1;
}

int isReachable(int** matrix, int u, int v, int* toSearch, int* size, int n) {
    int result = 0;
    for(int i=0; i<n; i++) {
        if(matrix[u][i] == 1) {
            if(i == v)
                return 1;
            if(isNotThere(toSearch,*size, i)) {
                toSearch[*size] = i;
                (*size)++;
                result+=isReachable(matrix, i, v, toSearch, size, n);
            }
        }
    }
    return result;
}



int is_bridge(int n, int** matrix, int u, int v) {
    if(matrix[u][v] == 0)
        return 0;
    matrix[u][v] = 0;
    matrix[v][u] = 0;
    int toSearch[n];
    int size = 0;
    int result = 0;
    if(!isReachable(matrix, u, v, toSearch, &size, n)) {
        result = 1;
    }
    matrix[u][v] = 1;
    matrix[v][u] = 1;
    return result;
}

//
// Následící kod testuje funkcionalitu. Neupravujte.
// Každý test obsahuje několik volání vaší funkce. Test je úspěšný jen pokud
// všechny volání vrátí správnou odpověď.
//

void test(int n, int** graph, int u, int v, int expectation) {
  if (is_bridge(n, graph, u, v) == expectation)
    printf("Ok.\n");
  else
    printf("Chyba, pro hranu (%i, %i) je správná odpověď %i\n", u, v, expectation);
}

int main() {
  // Graf z obrázku výše
  int n = 7;
  int ** graph = createGraph(n);
  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 0);
  add_edge(graph, 1, 3);
  add_edge(graph, 3, 4);
  add_edge(graph, 4, 5);
  add_edge(graph, 5, 3);

  printf("Test 1.:\n");
  test(n, graph, 0, 4, 0);  // neexistujici hrana v jedné komponenta
  test(n, graph, 5, 6, 0);  // neexistujici hrana mezi komponentami

  printf("Test 2.:\n");
  test(n, graph, 0, 2, 0);  // není mostem
  test(n, graph, 1, 3, 1);  // je mostem

  printf("Test 3.:\n");
  test(n, graph, 2, 1, 0);  // otestovaní všech hran na levém cyklu
  test(n, graph, 1, 0, 0);
  test(n, graph, 2, 0, 0);
  test(n, graph, 1, 2, 0);
  test(n, graph, 0, 1, 0);
  test(n, graph, 3, 1, 1);  // test mostu druhým směrem

  // Složitější graf
  n = 10;
  graph = createGraph(n);
  add_edge(graph, 0, 1);
  add_edge(graph, 1, 2);
  add_edge(graph, 2, 3);
  add_edge(graph, 3, 4);
  add_edge(graph, 4, 0);

  add_edge(graph, 5, 6);
  add_edge(graph, 6, 7);
  add_edge(graph, 7, 5);

  add_edge(graph, 3, 6);
  add_edge(graph, 8, 9);

  printf("Test 4.:\n");
  test(n, graph, 8, 9, 1);
  test(n, graph, 0, 1, 0);  // hrana velkého cyklu
  test(n, graph, 5, 6, 0);  // hrana malého cyklu

  printf("Test 5.:\n");
  test(n, graph, 3, 6, 1);  // propojka mezi cykly
  test(n, graph, 6, 5, 0);
  test(n, graph, 6, 7, 0);
  test(n, graph, 2, 3, 0);
  test(n, graph, 4, 3, 0);

  printf("Test 6.:\n");     // test 5 symetricky
  test(n, graph, 6, 3, 1);  // propojka mezi cykly
  test(n, graph, 5, 6, 0);
  test(n, graph, 7, 6, 0);
  test(n, graph, 3, 2, 0);
  test(n, graph, 3, 4, 0);
  return 0;
}
