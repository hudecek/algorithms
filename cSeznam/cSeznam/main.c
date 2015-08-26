/*******************************************************************************
Implementacni test IB002

Vyplnte nasledujici udaje:
Jmeno:
UCO:
Skupina (do ktere jste zapsani):
*******************************************************************************/

/*******************************************************************************
Jednostranne spojovany seznam znate z prednasky - jde o zretezeny seznam
uzlu (Node), kde kazdy uzel ukazuje na sveho naslednika.

Tato uloha pracuje se dvema typy jednostranne spojovanych seznamu:
Linearni seznam - kde posledni prvek seznamu ukazuje na NULL.
Kruhovy seznam - kde posledni prvek seznamu ukazuje zpet na prvni prvek seznamu.

Vasim ukolem je naprogramovat nasledujici funkce:

1) getLength: zjisti delku (tj. pocet ruznych uzlu) seznamu

2) isCircular: otestuje, zda je seznam kruhovy

3) calculateOpposites: pro kruhove seznamy delky 2n naplni u kazdeho uzlu
polozku opposite uzlem, ktery je o n kroku dale (tedy v kruhu je to uzel
"naproti"). Napriklad v kruhovem seznamu 1 -> 2 -> 3 -> 4 (-> 1) je opposite
uzlu 1 uzel 3, uzlu 2 uzel 4, uzlu 3 uzel 1 a uzlu 4 uzel 2.

Pro vsechny funkce muzete predpokladat, ze seznam na vstupu obsahuje
vzajemne ruzne klice a ze je linearni nebo kruhovy, tj. nemusite napriklad
osetrovat situaci, kdy naslednikem "posledniho" v seznamu je "druhy".

Chovani funkce calculateOpposites neni definovano na kruhovem seznamu liche
(neparne) delky. Tento pripad nebude testovan, nemusite jej tedy overovat.
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

/**
 * Trida Node reprezentujici prvek v spojovanem seznamu
 */
typedef struct Node{
    int key; //klic
    struct Node* next; //ukazatel na nasledujici Node
    struct Node* opposite; //ukazatel na opposite Node
}Node;

/***************************************************************************
 * Doprogramujte nasledujici funkce
 ***************************************************************************/

/**
 * Otestuje, zda je zadany zretezeny seznam kruhovy.
 *
 * Prazdny seznam neni kruhovy.
 *
 * @param node - prvni prvek seznamu
 * @return 1 pokud je seznam kruhovy, 0 jinak
 */
int isCircular(Node* node){
    if(node == NULL)
        return 0;
    Node* walker = node->next;
    while(walker != NULL && walker != node)
        walker = walker->next;
    if(walker == node)
        return 1;
    return 0;
}

/**
 * Vrati delku (linearniho nebo kruhoveho) zretezeneho seznamu zacinajiciho
 * v zadanem uzlu.
 *
 * Pokud je seznam prazdny, vrati 0.
 *
 * @param node - prvni prvek seznamu
 * @return delka (pocet prvku) seznamu,  0 pokud je prazdny (NULL)
 */
int getLength(Node* node){
    if(node == NULL)
        return 0;
    int length = 1;
    Node* walker = node->next;
    while(walker != NULL && walker != node) {
        walker = walker->next;
        length++;
    }
    return length;
}

/**
 * Korektne naplni polozky "opposite" v uzlech kruhoveho seznamu sude
 * delky.
 *
 * Pokud vstupni seznam neni kruhovy nebo nema sudou delku (neni testovano,
 * nemusite osetrovat), nedela nic, tj. seznam neupravuje.
 *
 * @param node - prvni prvek seznamu
 */
void calculateOpposites(Node* node){
    Node* walker = node;
    int length = getLength(node);
    if(isCircular(node) && length % 2 == 0) {
        for(int i = 0; i<length/2; i++) {
            walker = walker->next;
        }
        for(int i=0; i<length/2; i++) {
            walker->opposite = node;
            node->opposite = walker;
            walker = walker->next;
            node = node->next;
        }
    }
}

/***************************************************************************
 * Nasledujuce funkce slouzi na testovani, nemente je.
 ***************************************************************************/

/**
 * Testuje, zda protejsi prvky seznamu zacinajiciho danym uzlem maji dane klice
 *
 * @param node - prvni prvek seznamu
 * @param oList seznam klicu
 * @param n - delka oList
 * @return 1 pokud maji protejsi prvky klice z daneho seznamu, 0 jinak
 */
int testOpposites(Node* node, int* oList, int n){
    Node* tmp = node;
    for(int i = 0; i < n; i++){
        if(tmp->opposite == NULL){
            return 0;
        }
        if(oList[i] != tmp->opposite->key){
            return 0;
        }
        else{
            tmp = tmp->next;
        }
    }
    return 1;
}

/**
 * Vytvori jednosmerne spojovany seznam z danych hodnot
 * @param list vstupni hodnoty (obycejne pole)
 * @param n pocet prvku seznamu
 * @return prvni uzel vytvoreneho seznamu
 */
Node* makeLinkedList(int* list, int n) {
    Node* fakeStart = (Node*) malloc(sizeof(Node));
    Node* tmp = fakeStart;
    for(int i = 0; i < n; i++){
        Node* node = (Node*) malloc(sizeof(Node));
        node->key = list[i];
        node->next = NULL;
        node->opposite = NULL;
        tmp->next = node;
        tmp = node;
    }
    return fakeStart->next;
}

/**
 * Vytvori kruhovy jednosmerne spojovany seznam z danych hodnot
 * @param list vstupni hodnoty (obycejne pole)
 * @param n pocet prvku seznamu
 * @return prvni uzel vytvoreneho seznamu
 */
Node* makeCircularList(int* list, int n) {
    Node* fakeStart = (Node*) malloc(sizeof(Node));
    Node* tmp = fakeStart;
    for(int i = 0; i < n; i++){
        Node* node = (Node*) malloc(sizeof(Node));
        node->key = list[i];
        node->next = NULL;
        node->opposite = NULL;
        tmp->next = node;
        tmp = node;
    }
    tmp->next = fakeStart->next;
    return fakeStart->next;
}

int main(void)
{
    //test 1.
    printf("Test 1: delka prazdneho seznamu: \n");
    Node* list = NULL;
    if (getLength(list) == 0){
        printf("PASSED\n");
    }else{
        printf("FAILED!, melo byt 0, vase delka je: %d\n", getLength(list));
    }

    //test 2.
    printf("\nTest 2a: seznam delky 2, nekruhovy - delka: \n");
    int data1[2] = {4,8};
    list = makeLinkedList(data1, 2);
    if (getLength(list) == 2){
        printf("PASSED\n");
    }else{
        printf("FAILED!, melo byt 2, vase delka je: %d\n", getLength(list));
    }

    printf("Test 2b: seznam delky 2, nekruhovy - kruhovost: \n");
    if (!isCircular(list)){
        printf("PASSED\n");
    }else{
        printf("FAILED!, oznacili jste nekruhovy seznam za kruhovy\n");
    }

    printf("Test 2c: seznam delky 2, nekruhovy - protejsky: \n");
    calculateOpposites(list);
    if (list->opposite == NULL){
        printf("PASSED\n");
    }else{
        printf("FAILED!, nekruhovy seznam nema protejsky\n");
    }

    //test 3.
    printf("\nTest 3a: seznam delky 2, kruhovy - delka: \n");
    list = makeCircularList(data1, 2);
    if (getLength(list) == 2){
        printf("PASSED\n");
    }else{
        printf("FAILED!, melo byt 2, vase delka je: %d\n", getLength(list));
    }

    printf("Test 3b: seznam delky 2, kruhovy - kruhovost: \n");
    if (isCircular(list)){
        printf("PASSED\n");
    }else{
       printf("FAILED!, oznacili jste kruhovy seznam za nekruhovy\n");
    }

    printf("Test 3c: seznam delky 2, kruhovy - protejsky: \n");
    calculateOpposites(list);
    int testData1[2] = {8,4};
    if (testOpposites(list, testData1, 2)){
        printf("PASSED\n");
    }else{
        printf("FAILED!, kruhovemu seznamu jste nastavili spatne protejsky:\n");
        printf("nasledujici vypis by mel vypadat takto 4->8, 8->4,\n");
        Node* tmp = list;
        for(int i = 0; i < 2; i++){
            if(tmp != NULL){
                if(tmp->opposite != NULL){
                    printf("%d->%d,", tmp->key, tmp->opposite->key);
                }else{
                    printf("%d->NULL, ", tmp->key);
                }
                tmp = tmp->next;
            }
        }
        printf("\n");
    }

    //test 4.
    printf("\nTest 4a: seznam delky 6, nekruhovy - delka: \n");
    int data2[6] = {3, 5, 6, 7, 9, 10};
    list = makeLinkedList(data2, 6);
    if (getLength(list) == 6){
        printf("PASSED\n");
    }else{
        printf("FAILED!, melo byt 6, vase delka je: %d\n", getLength(list));
    }

    printf("Test 4b: seznam delky 6, nekruhovy - kruhovost: \n");
    if (!isCircular(list)){
        printf("PASSED\n");
    }else{
        printf("FAILED!, oznacili jste nekruhovy seznam za kruhovy\n");
    }

    printf("Test 4c: seznam delky 6, nekruhovy - protejsky: \n");
    calculateOpposites(list);
    if (list->opposite == NULL){
        printf("PASSED\n");
    }else{
        printf("FAILED!, nekruhovy seznam nema protejsky\n");
    }

    //test 5.
    printf("\nTest 5a: seznam delky 6, kruhovy - delka: \n");
    list = makeCircularList(data2, 6);
    if (getLength(list) == 6){
        printf("PASSED\n");
    }else{
        printf("FAILED!, melo byt 6, vase delka je: %d\n", getLength(list));
    }

    printf("Test 5b: seznam delky 6, kruhovy - kruhovost: \n");
    if (isCircular(list)){
        printf("PASSED\n");
    }else{
       printf("FAILED!, oznacili jste kruhovy seznam za nekruhovy\n");
    }

    printf("Test 5c: seznam delky 6, kruhovy - protejsky: \n");
    calculateOpposites(list);
    int testData[6] = {7,9,10,3,5,6};
    if (testOpposites(list, testData, 6)){
        printf("PASSED\n");
    }else{
        printf("FAILED!, kruhovemu seznamu jste nastavili spatne protejsky:\n");
        printf("nasledujici vypis by mel vypadat takto 3->7, 5->9, 6->10, 7->3, 9->5, 10->6,\n");
        Node* tmp = list;
        for(int i = 0; i < 6; i++){
            if(tmp != NULL){
                if(tmp->opposite != NULL){
                    printf("%d->%d,", tmp->key, tmp->opposite->key);
                }else{
                    printf("%d->NULL, ", tmp->key);
                }
                tmp = tmp->next;
            }
        }
        printf("\n");
    }
    return 0;
}

