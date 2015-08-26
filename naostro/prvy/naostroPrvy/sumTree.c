#include <stdio.h>
#include <stdlib.h>

#include <string.h> //pouzito v testech
#include <limits.h> //pouzito v testech

/**
 * @author Marek Klucar
 */

/**
 * Implementacni test IB002 2015 - uloha 1 (max 10 bodu)
 *
 * Vyplnte nasledujici udaje:
 * Jmeno: Jan Hudecek
 * UCO: 433779
 *
 * Zadani:
 *
 * Vasi ulohou je implementovat dve funkce pro praci s datovou strukturou "Souctovy strom".
 * Muzete si samozrejme pridat vlastni pomocne funkce.
 *
 * Souctovy strom je binarny strom, kde kazdy uzel ma nasledujici vlastnost:
 * Pokud ma uzel alespon jednoho syna, potom je klic uzlu roven souctu klicu vsech jeho synu.
 * Vsimnete si, ze uvedena veta je implikace. Listy stromu teda mohou obsahovat libovolne hodnoty.
 * Z definice je strom, ktery neobsahuje zadne uzly, a strom, ktery obsahuje prave jeden uzel,
 * povazovan za souctovy.
 *
 * Priklad:
 * souctove stromy      nesouctove stromy
 *  53       47            53       47
 *  /\        \            /\       /
 * 21 32       47         21 21    23
 *
 *
 * Vasi prvni ulohou je napsat funkci isSumTree, ktera overi, zda je strom souctovy.
 *
 * Vasi druhou ulohou je napsat funkci, ktera vybuduje souctovy strom
 * co nejmensi vysky ze zadaneho pole.
 * Listy stromu budu prave prvky pole v poradi zleva doprava.
 * Pro jednoduchost predpokladame, ze delka pole bude mocninou dvojky (toto je
 * bez ujmy na obecnosti - pokud by to neplatilo, mohli bychom pridat na konec pole nuly).
 *
 * Napriklad:
 * Z pole [1,2,3,4] vznikne strom:
 *      10
 *    /    \
 *   3      7
 *  / \    / \
 * 1   2  3   4
 *
 */

/**
  * Struktura pro reprezentaci uzlu v souctovem strome.
  * Na jeji vytvoreni muzete pouzit createNode.
  */

typedef struct Node {
    int key; //hodnota uzlu, ktora ma byt rovna souctu hodnot vsech synu (pokud alespon jeden existuje).
    struct Node* parent; //ukazatel na rodice, pokud neexistuje tak NULL
    struct Node* left; //ukazatel na leveho syna, pokud neexistuje tak NULL
    struct Node* right; //ukazatel na praveho syna, pokud neexistuje tak NULL
} Node;

/**
 * @brief createNode vytvori novy uzel s hodnotou 0, vsechny ukazatele budou NULL.
 * @return ukazatel na vytvoreny uzol.
 */
Node* createNode() {
    Node* ret = malloc(sizeof(Node));
    ret->parent = ret->left = ret->right = NULL;
    ret->key = 0;
    return ret;
}

/**
  * Struktura pro reprezentaci souctoveho stromu, 'root' je koren stromu a je NULL, pokud je strom prazdny.
  * Na jeji vytvoreni muzete pouzit createSumTree.
  */
typedef struct SumTree {
    Node* root;
} SumTree;

/**
 * @brief createSumTree vytvori prazdny strom (koren je NULL)
 * @return ukazatel na vytvoreny strom
 */
SumTree* createSumTree() {
    SumTree* ret = malloc(sizeof(SumTree));
    ret->root = NULL;
    return ret;

}


int isSumTreeRec(Node* n) {
    if(n->left == NULL && n->right == NULL)
        return 1;
    if(n->left == NULL) {
        if(n->right->key == n->key)
            return isSumTreeRec(n->right);
        else return 0;
    }
    if(n->right == NULL) {
        if(n->left->key == n->key)
            return isSumTreeRec(n->left);
        else return 0;
    }
    if(n->left->key + n->right->key == n->key)
        return isSumTreeRec(n->left)*isSumTreeRec(n->right);
    else return 0;
}

/**
 * @brief isSumTree rozhodne, zda je strom souctovy.
 * @param 't' je ukazatel na strom (muzete predpokladat, ze 't' neni NULL).
 * @return 1 pokud strom je souctovy, jinak 0
 */
int isSumTree(const SumTree* t) {
    if(t == NULL)
        return 0;
    if(t->root == NULL)
        return 1;
    Node* n = t->root;

    return isSumTreeRec(n);
}



/**
 * @brief buildSumTree vybuduje souctovy strom co nejmensi vysky z pole array
 * @param 'array' pole cisel
 * @param 'len' delka pole, bude vzdy mocnina 2
 * @return ukazatel na strom vybudovany nad polom array
 */
SumTree* buildSumTree(const int* array, int len) {
    SumTree* tree = createSumTree();
    Node* Narray[2*len -1];
    for(int i=0; i<2*len-1; i++) {
        Narray[i] = createNode();
    }
    int j = 0;
    for(int i = len -1; i <= 2*len -2; i++) {
        Narray[i]->key = array[j];
        j++;
    }


    for(int i =len-2; i>=0; i--) {
        Narray[i]->key = Narray[2*i+1]->key + Narray[2*i+2]->key;
        Narray[i]->left = Narray[2*i+1];
        Narray[i]->right = Narray[2*i+2];
        Narray[2*i+2]->parent = Narray[i];
        Narray[2*i+1]->parent = Narray[i];
    }
    tree->root = Narray[0];
    return tree;
}


void allTests(); //jen deklarace testovaci funkce, muzete ignorovat
/**
 * @brief run je hlavni funkce volana z mainu
 * Pokud chcete krome dodanych testu spustit vlastni testovaci kod, dopiste ho sem.
 */
void run() {
    allTests();
}


/***********************************************************************
 ***             Nasleduje kod testu, NEMODIFIKUJTE JEJ              ***
 **********************************************************************/

// Nize uvedene funkce jsou zamerne napsane zvlastnim zpusobem,
// aby z nich nebylo mozne ziskat napovedu pro riesenie ulohy :-)

const int None = INT_MAX;

int getNodeValueByCode(const SumTree* t,int code,int depth) {
    Node* node = t->root;
    for (int i=depth-1; i>-1; i--) {
        if (node == NULL) continue;
        node = (code&(1<<i))?node->right:node->left;
    }
    if (node==NULL) return None;
    return node->key;
}


void treeToList(const SumTree* t, int* result) {
    int codes[63] = {0,
                   0,1,
                   0,1,2,3,
                   0,1,2,3,4,5,6,7,
                   0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
                   0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    int depths[63] = {0,
                    1,1,
                    2,2,2,2,
                    3,3,3,3,3,3,3,3,
                    4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
                    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};

    for (int i=0; i<63; i++) {
        result[i]=getNodeValueByCode(t,codes[i],depths[i]);
    }
}

SumTree* listToTree(const int* L) {
    SumTree* t = createSumTree();
    Node* nodes[64] = {NULL};
    for (int i=1; i<32; i++) {
        nodes[i] = (L[i-1]!=None)?createNode():NULL;
    }

    for (int i=1; i<32; i++) {
        if (nodes[i] != NULL) {
            nodes[i]->key = L[i-1];
            nodes[i]->left = nodes[2*i];
            nodes[i]->right = nodes[2*i+1];
            nodes[i]->parent = nodes[i/2];
        }
    }
    t->root = nodes[1];
    return t;
}

void printTree(const SumTree* tree) {
    const char treeTemplate[] = "                               %4s\n" \
                                "              %4s                            %4s\n" \
                                "      %4s            %4s            %4s            %4s\n" \
                                "  %4s    %4s    %4s    %4s    %4s    %4s    %4s    %4s\n" \
                                "%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s%4s\n";
    int treeList[63];
    treeToList(tree,treeList);
    char nodeStrings[31][5];
    for (int i=0; i<31; i++) {
        sprintf(nodeStrings[i],"%d",treeList[i]);
        if (treeList[i]==None) nodeStrings[i][0]=0;
    }

    puts("------------------------- Nacrt stromu -------------------------");
    printf(treeTemplate, nodeStrings[0], nodeStrings[1], nodeStrings[2],
           nodeStrings[3], nodeStrings[4], nodeStrings[5], nodeStrings[6],
           nodeStrings[7], nodeStrings[8], nodeStrings[9], nodeStrings[10],
           nodeStrings[11], nodeStrings[12], nodeStrings[13], nodeStrings[14],
           nodeStrings[15], nodeStrings[16], nodeStrings[17], nodeStrings[18],
           nodeStrings[19], nodeStrings[20], nodeStrings[21], nodeStrings[22],
           nodeStrings[23], nodeStrings[24], nodeStrings[25], nodeStrings[26],
           nodeStrings[27], nodeStrings[28], nodeStrings[29], nodeStrings[30]);
    puts("------------------------ Koniec  nacrtu ------------------------");
}

int checkParentsRecursive(const Node* node, const Node* parentShouldBe) {
    if (node == NULL) return 1;
    if (node->parent != parentShouldBe) return 0;
    return checkParentsRecursive(node->left, node) && checkParentsRecursive(node->right,node);
}

int checkParents(const SumTree* tree) {
    return checkParentsRecursive(tree->root,NULL);
}

void freeTreeRecursive(Node* node) {
    if (!node) return;
    freeTreeRecursive(node->left);
    freeTreeRecursive(node->right);
    free(node);
}

void freeTree(SumTree* tree) {
    freeTreeRecursive(tree->root);
    free(tree);
}

void testIsSumTree(int* success_global, int* total) {
    const int TEST_COUNT = 10;
    char testNames[][250] = {
        "prazdny strom (root==None)",
        "strom s jednim uzlem",
        "maly korektni strom 1",
        "maly korektni strom 2",
        "maly nekorektni strom 1",
        "maly nekorektni strom 2",
        "velky korektni strom 1",
        "velky korektni strom 2",
        "velky nekorektni strom 1",
        "velky nekorektni strom 2",
    };

    int expectedResults[] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 0};

    char failHints[][250] = {
        "Vas program oznacil prazdny strom za nesouctovy, podle definice je takovy strom souctovy.",
        "Vas program oznacil strom s jedinym uzlem za nesuctovy, podla definice je takovy strom souctovy.",
        "Vas program oznacil nize nacrtnuty strom za nesouctovy: ",
        "Vas program oznacil nize nacrtnuty strom za nesouctovy: ",
        "Vas program oznacil nize nacrtnuty strom za souctovy: ",
        "Vas program oznacil nize nacrtnuty strom za souctovy: ",
        "Vas program oznacil nize nacrtnuty strom za nesouctovy: ",
        "Vas program oznacil nize nacrtnuty strom za nesouctovy: ",
        "Vas program oznacil nize nacrtnuty strom za souctovy: ",
        "Vas program oznacil nize nacrtnuty strom za souctovy: "
    };

    int printTrees[] = {0,0,1,1,1,1,1,1,1,1};

    int treeCodes[][31] = {
        {},
        {47},
        {47, None, 47},
        {53, 21, 32},
        {28, 7},
        {53, 21, 21},
        {120, 28, 92, 6, 22, 38, 54, 1, 5, 9, 13, 17, 21, 25, 29, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        {6, 3, 3, None, 3, 3, None, None, None, 1, 2, None, 3},
        {120, 28, 92, 6, 22, 38, 54, 1, 5, None, 13, 17, 21, 25, 29, 0, 1, 2, 3, None, None, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16},
        {121, 28, 92, 6, 22, 38, 54, 1, 5, 9, 13, 17, 21, 25, 29, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}
    };

    int treeCodeLengths[] = {0,1,3,3,2,3,31,13,31,31};
    for (int i=0; i<TEST_COUNT; i++) {
        for (int j=treeCodeLengths[i]; j<31; j++) {
            treeCodes[i][j] = None;
        }
    }

    puts("Testy isSumTree:");
    puts("-------------------");

    int success = 0;

    for (int i=0; i<TEST_COUNT; i++) {
        SumTree* testTree = listToTree(treeCodes[i]);
        printf("XXXXXXXXXXXXXXXXXXXXXXXX  TEST %2d/%-2d  XXXXXXXXXXXXXXXXXXXXXXXX\n",i+1,TEST_COUNT);
        printf("%s: ",testNames[i]);
        int res = isSumTree(testTree);
        if (res == -1) {
                    puts("FAIL, funkcia isSumTree vratila -1");
                    continue;
        }
        puts(res!=expectedResults[i]?"FAIL":"OK");

        if (res!=expectedResults[i]) {
            puts(failHints[i]);
            if (printTrees[i]) printTree(testTree);
        }
        else success++;
        puts("");
        freeTree(testTree);
    }
    printf("SPRAVNE: %d/%d %s\n",success,TEST_COUNT,(success==TEST_COUNT)?":-)":":-(");
    puts("-------------------");

    *total += TEST_COUNT;
    *success_global += success;
}

void testBuildSumTree(int* success_global, int* total) {
    const int TEST_COUNT = 5;
    const int None = INT_MAX;

    char testNames[][250] = {
        "jednoprvkove pole",
        "dvouprvkove pole",
        "ctyrprvkove pole",
        "osmiprvkove pole",
        "sestnactiprvkove pole"
    };

    //Dale sa predpoklada, ze i-te (0 based) pole bude mit 2^i prvku
    int lists[][16] = {
        {47},
        {28,7},
        {8,12,19,91},
        {2,3,5,7,11,13,17,19},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}
    };

    int expectedLists[][63] = {
        {47},
        {35,28,7},
        {130,20,110,8,12,19,91},
        {77,17,60,5,12,24,36,2,3,5,7,11,13,17,19},
        {120,28,92,6,22,38,54,1,5,9,13,17,21,25,29,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}
    };

    for (int i=0; i<TEST_COUNT; i++) {
        for (int j=(1<<(i+1))-1; j<63; j++) {
            expectedLists[i][j] = None;
        }
    }

    puts("Testy buildSumTree:");
    puts("-------------------");

    int success=0;

    for (int i=0; i<TEST_COUNT; i++) {
        printf("XXXXXXXXXXXXXXXXXXXXXXXX  TEST %2d/%-2d  XXXXXXXXXXXXXXXXXXXXXXXX\n",i+1,TEST_COUNT);
        printf("%s: ",(testNames[i]));

        int ok=1;

        SumTree* tree = buildSumTree(lists[i],1<<i);
        if (tree == NULL) {
                    puts("FAIL, funkce builSumTree vratila NULL");
                    continue;
        }

        if (!checkParents(tree)) {
            puts("Nektery z uzlu nema spravne nastaveneho rodice.");
            ok = 0;
        }

        int res[63];
        treeToList(tree,res);


        for (int j=0; j<63; j++) {
            if (res[j]!=expectedLists[i][j]) {
                ok = 0;
                break;
            }
        }

        printf("%s",ok?"OK\n":"FAIL\n");
        if (!ok) {
            printf("Zadane pole bylo: [");
            for (int j=0; j<(1<<i); j++) {
                if (j) printf(", ");
                printf("%d",lists[i][j]);
            }
            puts("]");
            puts("Vas program vybudoval nize uvedeny strom (zobrazuje se max. 5 urovni stromu)");
            printTree(tree);
        }
        else success++;
        puts("");
        freeTree(tree);
    }
    printf("SPRAVNE: %d/%d %s\n",success,TEST_COUNT,(success==TEST_COUNT)?":-)":":-(");
    puts("-------------------");

    *total += TEST_COUNT;
    *success_global += success;
}

void allTests() {
    int success=0, total=0;
    testIsSumTree(&success, &total);
    testBuildSumTree(&success, &total);

    puts("-------------------");
    printf("CELKEM SPRAVNE: %d/%d %s\n",success,total,(success==total)?":-)":":-(");
}

int main() {
    run();
    return 0;
}

