/**
 * Implementacni test IB002 - uloha 2. (8 bodu)
 *
 * Vyplnte nasledujici udaje:
 * Jmeno:
 * UCO:
 * Skupina (v ktere jste zapsani):
 *
 * V tomto prikladu budete pracovat se stromem, reprezentujici hierarchii mnozin.
 * Kazdy uzel obsahuje klic, jenz je prvkem mnoziny. Uzly obsahuji seznam potomku,
 * jejichz klice jsou podmnozinou klice rodice. Konkretneji je datova
 * struktura uzlu popsana nize u tridy Node.
 *
 * ======
 *  UKOL
 * ======
 * Vasi ulohou bude v tomto zadani implementovat metodu findMinimalRootOfNodes.
 * Ta jako vstup bere 2 uzly stromu, a vraci uzel, z nehoz se lze dostat do obou
 * vstupnich uzlu (dostat je mysleno jen pohybem smerem dolu, tedy prechodem na potomky)
 * a zaroven je tento uzel na nejnizsi mozne urovni (nejblize obeda zadanym uzlum).
 *
 * Okrajove pripady: v pripadech, ze je nejaky vstupni uzel null, nebo uzly nejsou
 * stejneho stromu, vracejte null. Tyto pripady vsak nejsou testovany.
 *
 * Priklad:
 * mejme nasledujici strom
 *              a (= TreeSet.root)
 *            /   \
 *           b     c
 *         /   \    \
 *        d     e    f
 *             / \    \
 *            g   h    i
 *
 * findMinimalRootOfNodes(g,h) = e
 * findMinimalRootOfNodes(d,h) = b
 * findMinimalRootOfNodes(a,i) = a
 * findMinimalRootOfNodes(h,i) = a
 * findMinimalRootOfNodes(i,i) = i
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximalni delka klice v uzlu, jenz je datovym typem retezec
#define MAX_LEN 100

// maximalni pocet potomku v uzlu (jedna se o n-arni stromy)
#define MAX_COUNT 20

/**
 * Struktura uzlu:
 * Uzel obsahuje klic (char[]) key, ktery je unikatni mezi svymy sourozenci,
 * ale neni unikatni v cele strukture stromu, stejny klic mohou mit treba
 * rodic-potomek, bratranci, nebo libovolne vzdalenejsi uzly.
 *
 * Uzel obsahuje ukazatele na rodice parent, koren stromu ma parent = null
 * potomci jsou ulozeni v poli children, list ma delku tohoto seznamu 0.
 */
typedef struct Node Node;

struct Node
{
     char key[MAX_LEN];

     Node* parent;

     Node* children[MAX_COUNT];
     unsigned numOfChildren;
};

//---------------------------------------------------------------------------------------
// funkce pro vytvoreni noveho uzlu a zaceseni pod rodice
Node *CreateNewNode(char *key, Node* parent)
{
     Node *newNode = (Node*) malloc (sizeof(Node));

     newNode->numOfChildren = 0;
     newNode->parent = parent;
     strcpy(newNode->key, key);

     // jestli nezakladame koren stromu
     if (parent != NULL)
     {
          parent->children[parent->numOfChildren] = newNode;
          parent->numOfChildren++;
     }

     return newNode;
}

//---------------------------------------------------------------------------------------
// funkce zrusi strom
void DestroyTree(Node *root)
{
     if (root == NULL)
          return;

     int i;

     for (i=0; i<root->numOfChildren; i++)
     {
          DestroyTree(root->children[i]);
          free(root->children[i]);
     }

}

//---------------------------------------------------------------------------------------
// funkce vytvori inicialni stromovou strukturu, ktera se pouzije pro
// otestovani Vami napsaneho kodu
Node* InitTree()
{
     Node 	*root = CreateNewNode("IB002 Algorithms and data structures I", NULL),
                *algorithms = CreateNewNode("algorithms", root),
                *iterativeAlgorithms = CreateNewNode("Iterative algorithms", algorithms),
                *searchingIt = CreateNewNode("searching algorithms", iterativeAlgorithms),
                *recursiveAlgorithms = CreateNewNode("recursive algorithms", algorithms),
                *divideAndConquer = CreateNewNode("divide and conquer algorithms", recursiveAlgorithms),
                *searchingRe = CreateNewNode("searching algorithms", divideAndConquer),
                *randomizedAlgorithms = CreateNewNode("randomized algorithms", algorithms),
                *dataStructures = CreateNewNode("data structures", root),
                *dynamicDataStructures = CreateNewNode("dynamic data structures", dataStructures),
                *graphs = CreateNewNode("graphs", dynamicDataStructures),
                *trees = CreateNewNode("trees", dynamicDataStructures),
                *lists = CreateNewNode("linear data structures", dynamicDataStructures),
                *staticDataStructures = CreateNewNode("static data structures", dataStructures);

     CreateNewNode("select sort", searchingIt);
     CreateNewNode("insert sort", searchingIt);
     CreateNewNode("bubble sort", searchingIt);
     CreateNewNode("heap sort", searchingIt);

     CreateNewNode("fibonacci", iterativeAlgorithms);
     CreateNewNode("power", iterativeAlgorithms);

     CreateNewNode("merge sort", searchingRe);
     CreateNewNode("quick sort", searchingRe);

     CreateNewNode("monte carlo pi", randomizedAlgorithms);

     CreateNewNode("weighted graph", graphs);
     CreateNewNode("unweighted graph", graphs);
     CreateNewNode("directed graph", graphs);
     CreateNewNode("undirected graph", graphs);
     CreateNewNode("bipartited graph", graphs);

     CreateNewNode("binary search tree", trees);
     CreateNewNode("red black tree", trees);
     CreateNewNode("B tree", trees);
     CreateNewNode("B+ tree", trees);

     CreateNewNode("list", lists);
     CreateNewNode("queue", lists);
     CreateNewNode("stack", lists);

     CreateNewNode("n-tuple", staticDataStructures);
     CreateNewNode("array of static length", staticDataStructures);
     CreateNewNode("primitive data types", staticDataStructures);

     return root;
}

int findNode(Node** array, Node* toFind, int size) {
    for(int i=0; i<size; i++) {
        if(array[i] == toFind)
            return 1;
    }
    return 0;
}

//-----------------------------------------------------------------------
// first -- prvni zadany uzel stromu
// second -- druhy zadany uzel stromu
// return value -- koren minimalniho stromu obsahujiciho oba uzlu
Node *findMinimalRootOfNodes(Node *first, Node *second)
{
     // TODO: telo teto funkce je treba naprogramovat
     //
     // Poznamka:
     // K reseni ulohy muzete (ale nemusite) pouzit prilozenou implementaci
     // zasobniku. Neberte prosim prilozenou implementaci zasobniku jako
     // doporuceni, kterym smerem se pri reseni vydat. Existuje i pekne funkcni
     // reseni bez vyuziti zasobniku.
     //
     // Zakladni strukturu "Node" je povoleno modifikovat dle potreb.

    if(first == NULL || second == NULL)
        return NULL;

    Node* walker = first;
    int size = 1;

    Node** doneFirst = NULL;
    while(walker!= NULL) {
        doneFirst = realloc(doneFirst, size*(sizeof(Node*)));
        doneFirst[size-1] = walker;
        walker = walker->parent;
        size++;
    }

    walker = second;
    Node* result = NULL;
    while(walker!=NULL) {
        for(int i=0; i<size-1; i++) {
            if(doneFirst[i] == walker)
                result = walker;
        }
        if(result != NULL)
            walker = NULL;
        if(walker != NULL)
            walker= walker->parent;
    }
    if(doneFirst!= NULL)
        free(doneFirst);
    return result;
}


//---------------------------------------------------------------------------------------

void simplePrintAll(Node *node, int level)
{
     unsigned i;

     for (i=0; i<level; i++)
          printf("\t");

     printf("%s \n", node->key);

     for (i=0; i<node->numOfChildren; i++)
     {
          simplePrintAll(node->children[i], level+1);
     }
}

//---------------------------------------------------------------------------------------

Node *findNodeByKey(Node *from, char *key)
{
     if (key == NULL)
          return NULL;

     if (!strcmp(key, from->key))
          return from;

     unsigned i;
     for (i=0; i<from->numOfChildren; i++)
     {
          Node *res = findNodeByKey(from->children[i], key);

          if (res != NULL)
                return res;
     }

     return NULL;
}

//---------------------------------------------------------------------------------------
// hlavni funkce se spoustou testu na overeni funkcnosti
//---------------------------------------------------------------------------------------
int main(void)
{
     Node *treeSet = InitTree();
     simplePrintAll(treeSet, 0);

     // test 1
     printf("Test 1.:");
     Node *r = findNodeByKey(treeSet, "IB002 Algorithms and data structures I");
     Node *algoritmy = findNodeByKey(treeSet, "algorithms");
     Node *found = findMinimalRootOfNodes(r, algoritmy);

     if (found == r)
     {
          printf("OK \n");
     }
     else
     {
          printf("Chyba: nalezeny uzel mel byt (%s), ale vas uzel byl (%s) \n",
                    r->key, found->key);
     }

     // test 2
    printf("Test 2.:");

    found = findMinimalRootOfNodes(algoritmy, algoritmy);
    if(found == algoritmy)
     {
        printf("OK \n");
     }
     else
     {
          printf("Chyba: nalezeny uzel mel byt (%s), ale vas uzel byl (%s) \n",
                    algoritmy->key, found->key);
     }

    // test 3
    printf("Test 3.:");

     Node *heapSort = findNodeByKey(r, "heap sort");
     Node *selectSort = findNodeByKey(r, "select sort");

     found = findMinimalRootOfNodes(heapSort, selectSort);
    if (found == findNodeByKey(r, "searching algorithms"))
     {
          printf("OK \n");
     }
     else
     {
          printf("Chyba, nalezeny uzel mel byt (%s), ale vas uzel byl (%s) \n",
                    findNodeByKey(r, "searching algorithms")->key, found->key);
     }

    // test 4
     printf("Test 4.:");

     Node *graphs = findNodeByKey(r, "graphs");
    Node *directedGraph = findNodeByKey(r, "directed graph");

    found = findMinimalRootOfNodes(graphs, directedGraph);

    if (found == graphs)
     {
          printf("OK \n");
     }
     else
     {
          printf("Chyba, nalezeny uzel mel byt (%s), ale vas uzel byl (%s) \n", graphs->key, found->key);
     }

    // test 5
     printf("Test 5.:");

    Node *BPlusTree = findNodeByKey(r, "B+ tree");
    Node *power = findNodeByKey(r, "power");

    found = findMinimalRootOfNodes(BPlusTree, power);

     if (found == r)
     {
          printf("OK \n");
     }
     else
     {
          printf("Chyba, nalezeny uzel mel byt (%s), ale vas uzel byl (%s) \n", r->key, found->key);
     }

    // test 6
     printf("Test 6.:");
     Node *dataStructures = findNodeByKey(r, "data structures");
     Node *mergeSort = findNodeByKey(r, "merge sort");

    found = findMinimalRootOfNodes(dataStructures, mergeSort);

    if (found == r)
     {
          printf("OK \n");
     }
     else
     {
          printf("Chyba, nalezeny uzel mel byt (%s), ale vas uzel byl (%s) \n", r->key, found->key);
     }

     DestroyTree(treeSet);

     return 0;
}

//---------------------------------------------------------------------------------------
