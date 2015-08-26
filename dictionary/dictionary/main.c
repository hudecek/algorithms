#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDS 26
#define MAX_WORDS 100


typedef struct _node {
    char key;
    struct _node* childs[MAX_CHILDS];
    int childCount;
} Node;

typedef struct {
    Node* childs[MAX_CHILDS];
    int childCount;
} Dictionary;

typedef struct {
    char* words[MAX_WORDS];
    int wordsCount;
} Words;

//vraci podstrom obsahujici jen slova zacinajici na dany prefix
Node* dictSearch(Dictionary *dict, char *prefix);

void listWordsWithPrefixRecursive(Dictionary* dict, Node* node, Words* words, char* prefix);
//prida znak na konec nejakeho slova
char* addCharToWord(char* string, char character);
//prida slovo do seznamu slov, rada: pouzivejte strukturu Words jako write only,
//    pokud se vam k tomu nehodi, napiste si vlastni, ale zbytecne si praci komplikujete
void wordsInsert(Words* wordsArray, char* word);


/**
 * TODO: Vrati zoznam slov v abecednom poradi zacinajucich na prefix
 * za slovo sa povazuju tie postupnosti uzlov ktore koncia uzlom bez deti
 * v pripade ze slova s prefixom neexistuju vrati null
 * V pripade ze cely prefix je jedno slovo vrati zoznam obsahujuci prave toto slovo.
 * @param prefix vypisovanych slov
 * @return zoznam slov s danym prefixom
 */
Words* listWordsWithPrefix(Dictionary* dict, char* prefix) {
    if (dict == NULL || prefix == NULL || dictSearch(dict,prefix) == NULL){
        return NULL;
    }

    Node * node = dictSearch(dict,prefix);
    Words* foundedWords = malloc(sizeof(Words));
    foundedWords->wordsCount = 0;
    listWordsWithPrefixRecursive(dict,node,foundedWords,prefix);
    return foundedWords;
}

void listWordsWithPrefixRecursive(Dictionary * dict, Node* node, Words* words, char* prefix){
    char * word = malloc(sizeof(prefix));
    node = dictSearch(dict,prefix);
    strcpy(word,prefix);

    Node * temp = node;
    while (temp->childs[0] != NULL) {
        if (temp->childCount > 1){
            listWordsWithPrefixRecursive(dict,node,words,addCharToWord(word, temp->childs[1]->key));
        }
        word = addCharToWord(word, temp->childs[0]->key);
        temp = temp->childs[0];
    }
    wordsInsert(words,word);
}

/**
 * Vlozi slovo do slovniku
 * @param dict slovnik, do ktereho vkladame
 * @param word vkladani slovo
 */
void dictInsert(Dictionary* dict, char* word) {
    if(word == NULL || strlen(word) == 0) return;

    Node* chosen = NULL;
    for (int i = 0; i < dict->childCount; ++i) {
        if(dict->childs[i]->key == word[0]) {
            chosen = dict->childs[i];
            break;
        }
    }
    //key is not in dictionary
    if(chosen == NULL) {
        chosen = malloc(sizeof(Node));
        chosen->key = word[0];
        chosen->childCount = 0;
        dict->childs[dict->childCount] = chosen;
        dict->childCount++;
    }

    Node* tmp;
    for (unsigned int i = 1; i < strlen(word); ++i) {
        tmp = chosen;
        for (int j = 0; j < chosen->childCount; ++j) {
            if(chosen->childs[j]->key == word[i]) {
                chosen = chosen->childs[j];
                break;
            }
        }
        if(chosen == tmp) {
            chosen = malloc(sizeof(Node));
            chosen->key = word[i];
            chosen->childCount = 0;
            tmp->childs[tmp->childCount] = chosen;
            tmp->childCount++;
        }
    }
}

/**
 * Vyhlada podstrom so slovami zacinajucimi na prefix
 * @param dict slovnik, do ktereho vkladame
 * @param prefix hladanych slov
 * @return uzol s nasledujucimi slovami
 */
Node* dictSearch(Dictionary* dict, char* prefix) {
    if(prefix == NULL || strlen(prefix) == 0) return NULL;

    Node* chosen = NULL;
    for (int i = 0; i < dict->childCount; ++i) {
        if(dict->childs[i]->key == prefix[0]) {
            chosen = dict->childs[i];
            break;
        }
    }
    //prefix is not in dictionary
    if(chosen == NULL) {
        return NULL;
    }

    Node* tmp;
    for (unsigned int i = 1; i < strlen(prefix); ++i) {
        tmp = chosen;
        for (int j = 0; j < chosen->childCount; ++j) {
            if(chosen->childs[j]->key == prefix[i]) {
                chosen = chosen->childs[j];
                break;
            }
        }
        if(chosen == tmp) {
            return NULL;
        }
    }
    return chosen;
}

void wordsInsert(Words* wordsArray, char* word) {
    wordsArray->words[wordsArray->wordsCount] = word;
    wordsArray->wordsCount++;
}

void wordsPrint(Words* wordsArray) {
    if(wordsArray == NULL) {
        puts("null");
        return;
    }
    printf("[");
    for (int i = 0; i < wordsArray->wordsCount - 1; ++i) {
        printf("%s, ", wordsArray->words[i]);
    }
    printf("%s]\n", wordsArray->words[wordsArray->wordsCount - 1]);
}

char* addCharToWord(char* string, char character) {
    char* newWord = malloc(strlen(string)+2);
    strcpy(newWord, string);
    newWord[strlen(string)] = character;
    newWord[strlen(string) + 1] = '\0';
    return newWord;
}


int main(void)
{
    // nasledujuci kod sluzi pre otestovanie vasej funkcnosti
    // mozete si ho modifikovat podla vlastnych potrieb
    Dictionary dic;
    dic.childCount = 0;
    //naplnenie slovniku
    dictInsert(&dic, "algoritmus");
    dictInsert(&dic, "algoritmizacia");
    dictInsert(&dic, "algologia");
    dictInsert(&dic, "funkcionalny");
    dictInsert(&dic, "funkcionalizmus");
    dictInsert(&dic, "funktiv");
    dictInsert(&dic, "futurizmus");
    dictInsert(&dic, "fuzia");

    Words* words;
    //listWordsWithPrefix("a") vrati slova v slovniku zacinajuce na "a"
    puts("Test 1.:");
    puts("Pozadovany vystup:\t[algologia, algoritmizacia, algoritmus]");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "a");
    wordsPrint(words);

    //listWordsWithPrefix("b") vrati slova v slovniku zacinajuce na "b"
    puts("\nTest 2.:");
    puts("Pozadovany vystup:\tnull");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "b");
    wordsPrint(words);

    //listWordsWithPrefix("funkc") vrati slova v slovniku zacinajuce na "funkc"
    puts("\nTest 3.:");
    puts("Pozadovany vystup:\t[funkcionalizmus, funkcionalny]");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "funkc");
    wordsPrint(words);

    //listWordsWithPrefix("fuz") vrati slova v slovniku zacinajuce na "fuz"
    puts("\nTest 4.:");
    puts("Pozadovany vystup:\t[fuzia]");
    printf("Vas vystup:\t\t");
    words = listWordsWithPrefix(&dic, "fuz");
    wordsPrint(words);
    return 0;
}
