/***************************************************************************
 Implementacny test IB002 - uloha 1. (12 bodov)

 Vyplnte nasledujuce udaje:
 Meno:
 UCO:
 Skupina (v ktorej ste zapisany):

 Zadanie:
 Ruzovo-modry strom je binarny strom obsahujuci celociselne kluce, v ktorom
 kazdy uzol ma bud modru alebo ruzovu farbu a navyse su splnene podmienky:
 1. koren stromu je ruzovy
 2. vsetky listy su modre (list je uzol, ktory nema ziadneho potomka)
 3. ziaden uzol nema rovnaku farbu ako niektory z jeho synov
 4. ak ma uzol prave jedneho syna, potom obsahuje cislo delitelne 2

 Vasou ulohou je napisat funkciu isPinkBlue, ktora skontroluje, ci je strom
 ruzovo-modry. Mozete samozrejme doplnit aj dalsie pomocne funkcie podla
 vlastneho uvazenia. Pre vase pohodlie mate k dispozicii obrazky stromov,
 ktore sa testuju v prilozenom maine.

 Po ukonceni prace nahrajte vas kod do odovzdavarne:
 IS -> Student -> IB002 -> Odevzdavarny -> PraktickyTest_skupina
 Odovzdavajte len zdrojovy kod, NEODOVZDAVAJTE subory s nastaveniami pre IDE.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {PINK, BLUE} Color; //enum na reprezentaciu farieb uzlov

/* Kazdy uzol si pamata svoj kluc, farbu, ukazatel na rodica a synov.
   Koren stromu ma ukazatel na rodica nastaveny na NULL, rovnako su na NULL
   nastavene ukazatele left a right ak prislusny syn neexistuje */
typedef struct Node {
    int key;
    Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;


int isPBtreeRec(Node* node) {
    if(node->left == NULL && node->right == NULL) {
        if(node->color != BLUE)
            return 0;
        else return 1;
    }

    if(node->left == NULL || node->right == NULL) {
        if(node->key % 2 != 0)
            return 0;
        if(node->left == NULL) {
            if(node->right->color == node->color)
                return 0;
            else return isPBtreeRec(node->right);
        } else {
            if(node->left->color == node->color)
                return 0;
            else return isPBtreeRec(node->left);
        }
    }
    if(node->left->color == node->color || node->right->color == node->color)
        return 0;
    return isPBtreeRec(node->left)*isPBtreeRec(node->right);

    return 1;
}

/**
 * Funkcia overi, ci strom je ruzovo-modry podla vyssie uvedenej definicie
 * @param root ukazatel na koren stromu
 * @return 0 ak strom nie je ruzovo-modry, 1 inak
 */
int isPinkBlue (Node* root) {
    if(root == NULL)
        return 0;
    if(root->color != PINK)
        return 0;
    return isPBtreeRec(root);
}


/**
 * pomocna funkcia pouzita v buildTreeFromArrays - mozete ignorovat
 */
Node* insertNode(Node* root, int key, Color color);


/**
 * Funkcia, ktora vybuduje testovaci strom:
 * jednotlive prvky sa postupne vlozia do stromu na poziciu, ktora je urcena
 * rovnako ako u (nevyvazeneho) binarneho vyhladavacieho stromu.
 *
 * Funkciu mozete pouzit na vybudovanie vlastneho testovacieho stromu.
 * (ak vlastne testovacie stromy vytvarat nechcete, funkciu mozete ignorovat)
 * !!! Funkciu pouzivaju aj testy, takze ju NEMENTE !!!
 *
 * Napr. pre vybudovanie strom3.png zavolajte:
 * int keys[]={5,4,6,2,8,1,3,7,9}; Node* t = buildTreeFromArrays(keys,"PBBPPBBBB")
 *
 * @param keys pole klucov jednotlivych uzlov
 * @param colors retazec farieb jednotlivych uzlov. P pre ruzovu, B pre modru
 * @return ukazatel na koren vybudovaneho stromu
 */
Node* buildTreeFromArrays(const int keys[], const char* colors) {
    Node* root = NULL;
    for(unsigned i=0; i<strlen(colors); i++) {
        root = insertNode(root,keys[i],(colors[i]=='B' || colors[i]=='M')?BLUE:PINK);
    }
    return root;
}

/***************************************************************************
 *Nasledujuci kod sluzi len pre ucely testov. Nemusite mu venovat pozornost.
 **************************************************************************/
void freeTree(Node* root);
#define TEST_COUNT 10
extern const char testNames[TEST_COUNT][100];
extern const int expectedResults[TEST_COUNT];
extern const char failHints[TEST_COUNT][100];
extern const int treeKeys[TEST_COUNT][100];
extern const char treeColors[TEST_COUNT][100];
/**************************************************************************/


/**
 * testovaci main - NEMENIT
 * ak chcete vas program otestovat na inych stromoch,
 * tento main NEMENTE ale zakomentuje a pouzite vlastny
 */
int main(void)
{
    Node* testTree = NULL;
    int success = 0;
    puts("Testy:");
    puts("-------------------");

    for (int i=0; i<TEST_COUNT; i++) {
        testTree = buildTreeFromArrays(treeKeys[i],treeColors[i]);
        printf("Test %2d/%-2d - %s: ",i+1,TEST_COUNT,testNames[i]);
        fflush(stdout);
        int res = isPinkBlue(testTree);
        printf("%s\n",(res!=expectedResults[i]?"FAIL":"OK"));
        if (res!=expectedResults[i]) puts(failHints[i]);
        else success++;
        freeTree(testTree);
    }
    puts("-------------------");
    printf("SPRAVNE: %d/%d %s\n",success,TEST_COUNT,(success==TEST_COUNT)?":-)":":-(");

    return 0;
}


/***************************************************************************
 * Nasledujuci kod (az do konca suboru) sluzi len pre ucely testov.
 * Nemusite mu venovat pozornost. NEMODIFIKOVAT.
 **************************************************************************/
const char testNames[TEST_COUNT][100] = {
    "prazdny strom (root==NULL)",
    "strom 1",
    "strom 2",
    "strom 3",
    "strom 4",
    "strom 5",
    "strom 6",
    "strom 7",
    "strom 8",
    "strom 9"
};

const int expectedResults[TEST_COUNT] = {0,0,0,1,0,1,0,1,1,0};

const char failHints[TEST_COUNT][100] = {
    "Prazdny strom nema ruzovy koren",
    "1-uzlovy ruzovy strom nema modre listy",
    "1-uzlovy modry strom nema ruzovy koren",
    "Vas program oznacil korektny strom za nekorektny",
    "Uzol s 1 synom musi obsahovat parne (sude) cislo",
    "Vas program oznacil korektny strom za nekorektny",
    "List stromu nesmie byt ruzovy",
    "Vas program oznacil korektny strom za nekorektny",
    "Vas program oznacil korektny strom za nekorektny",
    "Uzol nesmie mat rovnaku farbu ako jeho syn"
};

const char treeColors[TEST_COUNT][100] = {
    "",
    "P",
    "B",
    "PBBPPBBBB",
    "PB",
    "PB",
    "PBBPP",
    "PBBPPBB",
    "PBBPPBBBBPPPBBBBBB",
    "PBBPPBBBBPPBBBBBBB"
};
const int treeKeys[TEST_COUNT][100] = {
    {0}, //v skutocnosti prazdny, 0 len aby gcc nevypisalo warning
    {7},
    {3},
    {5,4,6,2,8,1,3,7,9},
    {5,4},
    {2,4},
    {2,1,4,3,5},
    {2,1,5,4,6,3,7},
    {10,8,20,2,18,1,6,14,19,4,12,16,3,5,11,13,15,17},
    {10,8,20,2,18,1,6,14,19,4,12,16,3,5,11,13,15,17}
};


void freeTree(Node* root) {
    if (!root) return;
    if (root->left) freeTree(root->left);
    if (root->right) freeTree(root->right);
    free(root);
}

Node* insertNode(Node* root, int key, Color color){
    Node* newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = color;
    newNode->left = NULL;
    newNode->right = NULL;

    Node* tmp = NULL; //remembers parent
    Node* subRoot = root;
    while(subRoot != NULL) {
        tmp = subRoot;
        if(key < subRoot->key) {
            subRoot = subRoot->left;
        }
        else {
            subRoot = subRoot->right;
        }
    }
    newNode->parent = tmp;
    if(tmp != NULL) {
        if(newNode->key < tmp->key) {
            tmp->left = newNode;
        }
        else {
            tmp->right = newNode;
        }
    }
    else root = newNode;
    return root;
}

