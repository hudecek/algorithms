#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Implementacny test IB002 - uloha 2. (8 bodov)
 *
 * Vyplnte nasledujuce udaje:
 * Meno:
 * UCO:
 * Skupina (v ktorej ste zapisany):
 *
 * Vasou ulohou je v tomto zadani naimplementovat modifikovany zasobnik.
 * Implementujete modifikovane metody push a pop. Pre blizsi popis citajte
 * komentare v kode.
 *
 * Po ukonceni prace nahrajte vas kod do odovzdavarne:
 * IS -> Student -> IB002 -> Odevzdavarny -> PraktickyTest_skupina
 * Odovzdavajte len zdrojovy kod, NEODOVZDAVAJTE subory s nastaveniami pre IDE.
 *
 * @author Henrich Lauko
 */

/**
 * Struktura Item sluzi pre reprezentaciu objektu v zasobniku
 * obsahuje atribut value reprezrezentujuci hodnotu v zasobniku
 * a atribut prev reprezentujuci ukazatel na predchadzajuci prvok Item
 * v zasobniku.
 */
typedef struct Item{
    int value; //hodnota v zasobniku
    struct Item* prev; //predchadzajuci  prvok v zasobniku
}Item;

/**
 * Struktura BrokenStack obsahuje ukazatel na vrchol zasobniku
 */
typedef struct BrokenStack{
    Item* top;
}BrokenStack;

/**
 * Vytvorenie prazdneho BrokenStack zasobniku
 */
BrokenStack* createStack(){
    BrokenStack* s = (BrokenStack*) malloc(sizeof(BrokenStack));
    s->top = NULL;
    return s;
}

   /**
    * Push vklada na vrchol zasobniku tak, ze pokial vkladana hodnota je
    * vacsia alebo rovna ako vrchol zasobniku(top), vklada normalne,
    * tj. prida ju nad vrchol a zmeni(top). Ak je vkladana hodnota mensia,
    * vlozi ju na prvu poziciu pod vrchol.  V pripade prazdneho zasobniku (na
    * vrchole je NULL) vkladame normalne.  Ukazku mozete vidiet na
    * nasledujucom priklade:
    *
    * Stav zasobniku:      10| 5|       (10 je na vrchu zasobniku)
    * Volame Push(11):     11|10| 5|    (11 bola vacsia ako 10)
    * Volame Push(6):      11| 6|10| 5| (6 bola mensia ako 11)
    *
    * Pri implementacii treba z argumentu value naalokovat objekt Item a spravne
    * nastavit vsetky ukazatele "prev".
    *
    * Dajte si pozor na pristupovanie ku objektom, ktore mozu byt NULL. Vzdy
    * kontrolujte, k akym objektom pristupujete.
    *
    * Dno zasobniku kontrolujete podla toho ci je ukazatiel (top alebo prev) == NULL
    */
    void push(BrokenStack* s, int value){
        if(s == NULL)
            return;
        Item* toAdd = malloc(sizeof(Item));
        toAdd->prev = NULL;
        toAdd->value = value;
        if(s->top == NULL) {
            s->top = toAdd;
        } else {
            if(value < s->top->value) {
                toAdd->prev = s->top->prev;
                s->top->prev = toAdd;
            } else {
                toAdd->prev = s->top;
                s->top = toAdd;
            }
        }
    }

    /**
    * Metoda Pop() funguje obdobne. Pokial hodnota na vrchu zasobniku je
    * vacsia alebo rovna ako hodnota hned pod vrcholom, pop funguje
    * normalne, tj. odobere hornu polozku. V pripade, ze hodnota na vrchu je
    * mensia ako hodnota pod vrcholom, odstrani sa zo zasobniku polozka pod
    * vrcholom. Tj. odstrani sa vzdy vacsia z hodnot na vrchole a pod nim.
    * Ak je v zasobniku len jedna polozka, odstani sa tato.
    *
    * Pop() vracia hodnotu polozky, ktora je odstranena zo zasobniku.
    *
    * V pripade zavolania pop() na prazdny zasobnik vrati sa -1;
    *
    * Vid priklad:
    *
    * Stav zasobniku:      11| 6|10| 5|
    * Volame Pop():         6|10| 5|    (11 bola vacsia ako 6) Pop() vrati hodnotu 11
    * Volame Pop():         6| 5|       (10 bola vacsia ako 6) Pop() vrati hodnotu 10
    * Volame Pop():         5|          Pop() vrati hodnotu 5
    * Volame Pop():        Empty stack! Pop() vrati -1
    *
    * Opat kontrolujte spravne ukazate a davajte si pozor na pracu s NULL.
    * Nezabudnite udrziavat korektny top. O spravne dealokovanie sa nemusite starat.
    */
    int pop(BrokenStack* s){
        int value = 0;
        Item* toFree;
        if(s == NULL || s->top == NULL)
            return -1;
        if(s->top->prev == NULL) {
            value = s->top->value;
            free(s->top);
            s->top = NULL;
            return value;
        }

        if(s->top->value >= s->top->prev->value) {
            value = s->top->value;
            toFree = s->top;
            s->top = s->top->prev;
            free(toFree);
            return value;
        } else {
            value = s->top->prev->value;
            toFree = s->top->prev;
            s->top->prev = s->top->prev->prev;
            free(toFree);
            return value;
        }

        return 0;
    }

    /**
     * Vypise obsah zasobniku v podobe: top|hodnota|hodnota|...|
     * Nevypisuje na standardny vystup, ale vracja v textovej premennej.
     */
    char* print(BrokenStack* s){
        char* str = (char*)malloc(256);
        strcpy(str, "");
        Item* i = s->top;
        if(i == NULL){
            strcat(str,"Empty stack!");
        }
        while(i != NULL){
            char buffer[10];
            sprintf(buffer, "%d", i->value);
            strcat(str,buffer);
            strcat(str,"|");
            i = i->prev;
        }
        return str;
    }

    /**
     * @param s
     * @return pocet prvkov v zasobniku s
     */
    int countItems(BrokenStack* s){
        int count = 0;
        Item* item = s->top;
        while(item != NULL){
            count++;
            item = item->prev;
        }
        return count;
    }

    int main(void)
    {
        /* svoj kod mozete testovat tu: */

        /* nasledujuci kod nemente*/
        BrokenStack* s = createStack();

        //Test 1.
        push(s,12);
        printf("Test 1.:");
        if(!strcmp("12|", print(s))){
             push(s,9);
            if(!strcmp("12|9|", print(s))){
                push(s,11);
                push(s,1);
                if(!strcmp("12|1|11|9|",print(s))){
                    puts("OK");
                }else{
                    printf("Chyba, vas stav zasobniku: %s != 12|1|11|9|\n", print(s));
                }
            }else{
                printf("Chyba, vas stav zasobniku: %s != 12|9|\n", print(s));
            }
        }else{
            printf("Chyba, vas stav zasobniku: %s != 12|\n", print(s));
        }

        //Test 2.
        BrokenStack* s2 = createStack();
        Item* h = (Item*) malloc(sizeof(Item));
        h->prev = NULL;
        h->value = 10;
        s2->top = h;
        push(s2,15);
        printf("Test 2.:");
        if(!strcmp("15|10|", print(s2))){
            puts("OK");
        }else{
            printf("Chyba, vas stav zasobniku: %s != 15|10|\n", print(s2));
        }

        //Test 3.
        int value = pop(s);
        printf("Test 3.:");
        if(!strcmp("1|11|9|",print(s))){
            if(value == 12){
                value = pop(s);
                if(!strcmp("1|9|",print(s))){
                    if(value == 11){
                        puts("OK");
                    }else{
                        printf("Pop vraci jinou hodnotu %d != 11\n",value);
                    }
                }else{
                    printf("Chyba, vas stav zasobniku: %s != 1|9|\n", print(s));
                }
            }else{
                printf("Pop vraci jinou hodnotu %d != 12\n",value);
            }
        }else{
            printf("Chyba, vas stav zasobniku: %s != 1|11|9|\n", print(s));
        }

        //Test 4.
        pop(s);
        value = pop(s);
        printf("Test 4.:");
        if(!strcmp("Empty stack!", print(s))){
            if(value == 1){
                value = pop(s);
                printf("Test 8.:");
                if(!strcmp("Empty stack!", print(s))){
                    if(value == -1){
                        puts("OK");
                    }else{
                        printf("Pop vraci jinou hodnotu %d != -1\n",value);
                    }
                }else{
                    printf("Chyba, vas stav zasobniku: %s != Empty stack!\n", print(s));
                }
            }else{
                printf("Pop vraci jinou hodnotu %d != 1\n",value);
            }
        }else{
            printf("Chyba, vas stav zasobniku: %s != Empty stack!\n", print(s));
        }

        //Test 5.
        printf("Test 5.:");
        BrokenStack* s3 = createStack();
        for(int i = 0; i < 100; i++){
            push(s3,i);
        }
        int count =  countItems(s3);
        if(count != 100){
            printf("Chyba, pocet prvkov v zasobniku: %d != 100\n", count);
        }else{
            puts("OK");
        }

        //Test 6.
        printf("Test 6.:");
        for(int i = 0; i < 50; i++){
            pop(s3);
        }
        count = countItems(s3);
        if(count != 50){
            printf("Chyba, pocet prvkov v zasobniku: %d != 50\n", count);
        }else{
            for(int i = 0; i < 50; i++){
                pop(s3);
            }
            count = countItems(s3);
            if(count != 0){
                printf("Chyba, pocet prvkov v zasobniku: %d != 0\n", count);
            }else{
                puts("OK");
            }
        }

        return 0;
    }
