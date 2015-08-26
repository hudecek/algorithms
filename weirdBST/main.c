/********************
Implementační test IB002 - úloha 2. (8 bodů)

Vyplňte následující údaje:
Jméno:
UČO:
Skupina (do které jste zapsáni):
********************/

/********************
Vasou ulohou je implementovat specificku variantu binarneho vyhladavacieho stromu nazvanu Weird Binary Search Tree, podporujucu operacie insert, search a deactivate (zodpoveda operacii delete). Tato datova struktura sa okrem specifikacie jednotlivych operacii lisi premennou 'active', ktora sa pouziva namiesto mazania uzlov. V kazdom okamihu je v takomto strome najviac jeden uzol s akymkolvek danym klucom. Vasou ulohou je implementovat operacie search a deactivate.

Operacia insert funguje podobne ako u bezneho binarneho vyhladavacieho stromu (BST) a mate k dispozicii jej uplnu a spravnu implementaciu. Mozete predpokladat, ze vysledkom akejkolvek postupnosti operacii insert je korektny BST, t.j. ak 'node' je uzol s klucom 'key', tak vsetky kluce v podstrome s korenom node->left maju kluce ostro mensie ako 'key' a obdobne pre pravy podstrom.

Operacia search ma vratit uzol s danym klucom 'key', ak sa taky uzol nachadza v strome, rovnako ako u bezneho BST. Pritom nezalezi na tom, ci je dany uzol aktivny, alebo nie. Ak vsak uzol s danym klucom 'key' neexistuje, search vrati uzol s klucom 'k', kde 'k' je najvacsi kluc ostro mensi ako 'key' nachadzajuci sa v strome, taktiez bez ohladu na to ci je uzol s klucom 'k' aktivny, alebo nie.

Operacia deactivate ma najst uzol s danym klucom 'key'. Ak taky uzol existuje, treba nastavit jeho premennu 'active' na hodnotu false bez ohladu na to, ci bola jej predchadzajuca hodnota true alebo false. Ak uzol s klucom 'key' neexistuje, treba najst uzol s klucom 'k', kde 'k' je najmensi kluc ostro vacsi ako 'key' nachadzajuci sa v strome a nastavit premennu 'active' tohto uzla na false bez ohladu na to, ci predtym bola true alebo false.

Poznamka 1: Takato specifikacia operacie deactivate znamena, ze nemusite presuvat casti stromu pod 'zmazanym' uzlom.

Poznamka 2: Pozor, operacie search a deactivate za urcitych okolnosti mozu vratit NULL.

Poznamka 3: Vase riesenie musi byt zalozene na prechadzani stromu a nemoze skusat hladat vacsie, resp. mensie prvky ako dany kluc.


Po ukonceni prace nahrajte vas kod do odovzdavarne:
IS -> Student -> IB002 -> Odevzdavarny -> PraktickyTest_skupina
Odovzdavajte len zdrojovy kod, NEODOVZDAVAJTE subory s nastaveniami pre IDE.********************/


#include <stdio.h>
#include <stdlib.h>


enum {FALSE, TRUE};

/* Kazdy uzol si pamata svoj kluc, farbu, ukazatel na rodica a synov.
   Koren stromu ma ukazatel na rodica nastaveny na NULL, rovnako su na NULL
   nastavene ukazatele left a right ak prislusny syn neexistuje */
typedef struct Node {
    int key;
    int active; //Set to false by deleting the Node
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct WeirdBST {
    Node* root;
} WeirdBST;


/**
 * Funkcia vklada kluc do WeirdBST podla specifikacie; funkcia je korektna a nesmiete ju menit.
 * Vstup:
 * @param tree ukazatel na WeirdBST
 * @param key kluc ktory sa ma do stromu vlozit
 */
void insertNode(WeirdBST* tree, int key){
    printf("InsertNode %d\n.",key);
    Node* tmp = NULL;
    Node* subRoot = tree->root;
    while(subRoot != NULL) {
        if (key == subRoot->key) {
            subRoot->active = TRUE;
            return ;
            }
        tmp = subRoot;
        if(key < subRoot->key) {
            subRoot = subRoot->left;
        }
        else {
            subRoot = subRoot->right;
        }
    }

    Node* insertedNode = malloc(sizeof(Node));
    insertedNode->key = key;
    insertedNode->active = TRUE;
    insertedNode->left = NULL;
    insertedNode->right = NULL;

    insertedNode->parent = tmp;
    if(tmp == NULL) {
        tree->root = insertedNode;
    }
    else {
        if(insertedNode->key < tmp->key) {
            tmp->left = insertedNode;
        }
        else {
            tmp->right = insertedNode;
        }
    }
}
/*
Node* pred(Node* node) {
    Node* saved = node;
    Node* walker;
    if(node  == NULL)
        return NULL;
    if(node->parent == NULL && node->left == NULL)
        return NULL;
    if(node->left) {
        walker = node->left;
        while(walker->right!=NULL)
            walker= walker->right;
        return walker;
    }
    while(node->parent != NULL && node->parent->left == node) {
        node = node->parent;
    }
    if(node->parent == NULL)
        return NULL;
    if(node->parent->left == NULL)
        return node->parent;
    return node->parent;
}
*/

Node* searchRec(Node* node, int key) {
    if(node == NULL)
        return NULL;
    if(node->key == key)
        return node;
    if(node->key > key) {
        if(node->left != NULL)
            return searchRec(node->left, key);
        else return NULL;
    }
    if(node->key < key) {
        if(node->right != NULL)
            return searchRec(node->right, key);
        else return NULL;
    }
    return NULL;
}


/**
 * Funkcia vyhlada uzol s danym klucom. Ak sa taky kluc v strome nevyskytuje, vyhlada uzol s klucom 'k', kde 'k' je najvacsi z klucov mensich nez 'key' nachadzajucich sa v strome.
 * Vstup:
 * @param tree ukazatel na WeirdBST strom, v ktorom ma prebehnut vyhladavanie
 * @param key kluc ktory sa ma vyhladat
 *
 * Vystup:
 * @return ukazatel na najdeny uzol zodpovedajuci specifikacii WeirdBST
 */
Node* searchNode(WeirdBST* tree, int key){
    if(tree == NULL || tree->root == NULL)
        return NULL;
    Node* node;
    while(key > 0) {
        node = searchRec(tree->root, key);
        if(node == NULL)
            key--;
        else key = -1;
    }
    return node;
}

/**
 * Pomocna funkcia 'vymaze' uzol tym, ze ho nastavi na active=FALSE
 *
 * Vstup:
 * @param node ukazatel na uzol, ktory sa ma deaktivovat
 */
inline void deactivateGivenNode(Node* node){
    if (node == NULL) {
        puts("Critical error; attempt to deactivate NULL node.");
        exit(EXIT_FAILURE);
    }
    node->active = FALSE;
}
/*
Node* findSucc(Node* node, int key) {
    Node* walker = node;
    int over = 0;
    while(!over) {
        if(key >= walker->key) {
            if(walker->right!=NULL)
                walker = walker->right;
            else over = 1;
        } else {
            if(walker->left!=NULL) {
                walker = walker->left;
            } else
                return walker;
        }
    }
    return NULL;
}
*/

int max(WeirdBST* tree) {
    Node* n = tree->root;
    while(n->right != NULL) {
        n = n->right;
    }
    return n->key;
}

/**
 * Funkcia vyhlada uzol s danym klucom a deaktivuje ho. Ak sa taky kluc v strome nevyskytuje, vyhlada uzol s klucom 'k', kde 'k' je najmensi z klucov vacsich nez 'key' nachadzajucich sa v strome a deaktivuje tento uzol.
 *
 * Vstup:
 * @param tree ukazatel na WeirdBST v ktorom ma prebehnut deaktivacia
 * @param key kluc ktory sa ma deaktivovat
 *
 * Vystup:
 * @return ukazatel na deaktivovany uzol zodpovedajuci specifikacii WeirdBST
 */
Node* deactivateNode(WeirdBST* tree, int key){
    Node* node = NULL;
    if(tree == NULL || tree->root == NULL)
        return NULL;
    int maxim = max(tree);
    while(key <= maxim) {
        node = searchRec(tree->root, key);
        if(node == NULL)
            key++;
        else key = maxim+1;
    }
    if(node)
        deactivateGivenNode(node);
    return node;
}

/*
note on pointers:
t*	(data type of pointer to a value with type t)
&v	(the address of a variable v)
*a	(the object at the address a - "derefferencing")

if you have a Node* node
you can access for example key by node->key (which is same as (*node).key)
if you have just Node node
you can access key by node.key
*/


/**********************************************************************
* Auxiliary cleanup functions
**********************************************************************/

/**
 * Pomocna cleanup funkcia; uvolni pamat pouzitu danym podstromom.
 *
 * Vstup:
 * @param node ukazatel uzol ktoreho podstrom sa ma zmazat.
 */
void freeNode(Node* node) {
    if (node == NULL)
        return;
    freeNode(node->left);
    freeNode(node->right);

    free(node);
}

/**
 * Pomocna cleanup funkcia; uvolni pamat pouzitu danym podstromom.
 *
 * Vstup:
 * @param tree ukazatel WeirdBST ktory sa ma zmazat.
 */
void freeTree(WeirdBST* tree) {
    freeNode(tree->root);
}


/**
 * Testovanie prebieha v main a ma tri fazy: najprv su Vase funkcie testovane na prazdnom strome, potom na strome obsahujucom prave jeden uzol, a nakoniec na uplnom strome vyobrazenom  v 'graph.jpg' (pozor na to, ze sa jedna o BST a teda kazdy potomok je bud vlavo, alebo vpravo od rodica v zavislosti od kluca).
 */
int main(void){
    WeirdBST wbst;
    wbst.root = NULL;

    puts("Testing wierd binary search tree.");

    puts("");
    puts("Testing search and deactivate on an empty tree.");
    Node* result = searchNode(&wbst,4);
    if (result == NULL)
        puts("Correct search of 4.");
    else
        puts("Search of 4 failed.");

    result = deactivateNode(&wbst, 14);
    if (result == NULL)
        puts("Correct deactivation of 4");
    else
        puts("Deactivation of 4 failed.");

    puts("");
    puts("Testing search and deactivate on a tree with only one node; the key of the root is 12.");
    insertNode(&wbst, 12);

    result = searchNode(&wbst,12);
    if (result != NULL && result->key == 12)
        puts("Correct search of 12.");
    else
        puts("Search of 12 failed.");

    result = searchNode(&wbst,11);
    if (result == NULL)
        puts("Correct search of 11.");
    else
        puts("Search of 11 failed.");

    result = searchNode(&wbst,13);
    if (result != NULL && result->key == 12)
        puts("Correct search of 13.");
    else
        puts("Search of 13 failed.");

    result = deactivateNode(&wbst, 12);
    if (result != NULL && result->key == 12 && result->active == FALSE)
        puts("Correct deactivation of 12");
    else
        puts("Deactivation of 12 failed.");

    result = deactivateNode(&wbst, 11);
    if (result != NULL && result->key == 12 && result->active == FALSE)
        puts("Correct deactivation of 11");
    else
        puts("Deactivation of 11 failed.");

    result = deactivateNode(&wbst, 13);
    if (result == NULL)
        puts("Correct deactivation of 13");
    else
        puts("Deactivation of 13 failed.");

    puts("");
    puts("Testing search and deactivate on the full tree.");

    insertNode(&wbst, 8);
    insertNode(&wbst, 19);
    insertNode(&wbst, 5);
    insertNode(&wbst, 10);
    insertNode(&wbst, 14);
    insertNode(&wbst, 20);
    insertNode(&wbst, 16);
    insertNode(&wbst, 9);
    insertNode(&wbst, 11);



    if( 12 == searchNode(&wbst, 12)->key){
        puts("Correct search of 12.");
    }else{
        puts("Search of 12 failed.");
    }

    if( 14 == searchNode(&wbst, 14)->key){
        puts("Correct search of 14.");
    }else{
        puts("Search of 14 failed.");
    }

    if( 16 == searchNode(&wbst, 16)->key){
        puts("Correct search of 16.");
    }else{
        puts("Search of 16 failed.");
    }

    if( 14 == searchNode(&wbst, 15)->key){
        puts("Correct search of 15.");
    }else{
        puts("Search of 15 failed.");
    }

    if( 12 == searchNode(&wbst, 13)->key){
        puts("Correct search of 13.");
    }else{
        puts("Search of 13 failed.");
    }

    result = searchNode(&wbst,4);
    if (NULL == result)
        puts("Correct search of 4.");
    else
        puts("Search of 4 failed.");

    result = searchNode(&wbst,7);
    if (result == NULL)
        puts("Incorrect search of 7.");
    if( 5 == searchNode(&wbst, 7)->key){
        puts("Correct search of 7.");
    }else{
        puts("Search of 7 failed.");
    }

    result = deactivateNode(&wbst, 12);
    if (result != NULL && result->key == 12 && result->active == FALSE)
        puts("Correct deactivation of 12");
    else
        puts("Deactivation of 12 failed.");

    result = deactivateNode(&wbst, 19);
    if (result != NULL && result->key == 19 && result->active == FALSE)
        puts("Correct deactivation of 19.");
    else
        puts("Deactivation of 19 failed.");

    result = deactivateNode(&wbst, 20);
    if (result != NULL && result->key == 20 && result->active == FALSE)
        puts("Correct deactivation of 20.");
    else
        puts("Deactivation of 20 failed.");

    result = deactivateNode(&wbst, 13);
    if (result != NULL && result->key == 14 && result->active == FALSE)
        puts("Correct deactivation of 13");
    else
        puts("Deactivation of 13 failed.");

    result = deactivateNode(&wbst, 15);
    if (result != NULL && result->key == 16 && result->active == FALSE)
        puts("Correct deactivation of 15");
    else
        puts("Deactivation of 15 failed.");

    result = deactivateNode(&wbst, 17);
    if (result != NULL && result->key == 19 && result->active == FALSE)
        puts("Correct deactivation of 17");
    else
        puts("Deactivation of 17 failed.");

    result = deactivateNode(&wbst, 21);
    if (result == NULL)
        puts("Correct deactivation of 21");
    else
        puts("Deactivation of 21 failed.");


    //cleanup
    freeTree(&wbst);

    return 0;
}
