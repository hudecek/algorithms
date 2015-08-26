#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 256

/**
 * Implementacni test IB002 - uloha 2. (8 bodu)
 *
 * Vyplnte nasledujice udaje:
 * Jmeno:
 * UCO:
 * Skupina (v ktere jste zapsan):
 *
 * V tomto prikladu budete pracovat se stromem, reprezentujici hierarchii unixoveho
 * souboroveho systemu. Uzel stromu Directory reprezentuje jednu slozku. Klic uzlu obsahuje
 * String se jmenem slozky (tento klic musi byt unikatni mezi sourozenci), list nasledniku
 * a ukazatele na rodice (nebudeme ulohu komplikovat simulaci .. a .). Presnejsi popis
 * struktury Directory najdete dole.
 * Vasi ulohou bude v tomto zadani implementovat metodu mkdirp. Ta bude simulovat
 * prikaz mkdir s prepinacem -p. Prikaz mkdir ma za ukol vytvorit adresar v zadane
 * ceste (pro zjednoduseni vzdy budeme adresovat absolutne, tedy celou cestou).
 * Prepinac -p slouzi k tomu, aby v pripade neexistence slozek v ceste k nove vytvarene
 * slozky, byly vytvoreny vsechny chybejici slozky.
 * Vstupem funkce bude String path, coz je retezec, ktery popisuje vetev stromu,
 * kde jednotlive klice jsou rozdeleny znakem "/". Prvni existujici slozka je
 * korenovy adresar, ktery ma jako klic prazdny retezec, jen po nem nasleduje "/".
 *
 * Priklad:
 * mejme cestu: /home/user/Documents
 * ta znaci 4 uzly ve stromu: uzel korenoveho adresare "", uzel "home", uzel "user"
 * a uzel "Documents".
 * Posloupnost prikazu:
 * f.mkdirP("/home/user");
 * f.mkdirP("/tmp/tmp/tmp");
 * f.mkdirP("/tmp/tmp2/tmp");
 * f.mkdirP("/tmp/tmp2/tmp2");
 * f.mkdirP("/tmp/tmp2/tmp2"); //toto nic neprovede
 * f.mkdirP("/home/user/Documents");
 * vytvori tento strom (klice budu nadale obalovat ""):
 *
 *                         "" (= Files.root)
 *                       /                  \
 *                    "home"               "tmp"
 *                      |                /       \
 *                 "Documents"        "tmp"     "tmp2"
 *                                      |       /    \
 *                                    "tmp"  "tmp"  "tmp2"
 *
 * @author Karel Kubicek, Matus Madzin
 */


/**
 * Struktura Directory predstavuje jeden adresar stromu.
 * String directory_name je klicem, ktery unikatni v dane slozce (tedy nemohou 2
 * slozky se stejnym jmenem mit stejneho rodice).
 * Klic muze byt prazdny retezec jen v pripade korenoveho adresare.
 * parent je ukazatel na rodice, v pripade korenoveho adresare je null
 * List sub_directory je seznam ukazatelu na potomky. Pokud je prazdny,
 * je slozka listem stromu.
 */
typedef struct _directory {
    char* directoryName;
    struct _directory* parent;
    struct _directory* subDirectory[MAX_SIZE];
    int subDirectoryCount;
} Directory;

/*
 * Globalni promenna pro ulozeni vysledku funkce pathSplit pro rozdeleni
 * cesty na jednotlive jmena slozek
 * Za platnymi jmeny slozek se nachazi retezec "", muzete tedy iterovat jen po nej
 * nebo muzete zjistit pocet klicu z navratove hodnoty pathSplit
 */
char pathNames[MAX_SIZE][MAX_SIZE];

/*
 * Tato funkce rozdeli retazec path podle '/'. Ziskane retezce ulozi v globalni
 * promenne pathNames.
 * @param  retazec ktery chceme rozdelit
 * @return pocet klicu, na ktere byl retezec rozdelen
 */
int pathSplit(char* path);

/**
 * vypise pracovni adresar = prevedeni slozky zpet na retezec
 * @param from
 * @param totalPath stores result of the function
 */
int pwd(Directory* from, char *totalPath);

/**
 * vlozi do slozky to novou slozku na posledni pozici
 * nekontroluje, zdali slozka se stejnym klicem ve slozce neni, to musite
 * kontrolovat sami
 * @param to ukazatel na Directory, ve ktere chcete novou slozku vytvorit
 * @param name klic nove slozky, neni kontrolovan na jedinecnost
 * @return ukazatel na nove vlozenou slozku
 */
Directory* dirInsert(Directory* to, char* name);

/**
 * TODO: naimplementujte funkci mkdirP
 * V pripade, ze vstupni retezec path je NULL, pak nic neprovadite
 * Korenovy adresar jiz existuje, to je jedina slozka, kterou nevytvarite
 * Pro prazdny retezec nevytvarejte slozku, prazdny retezec je jmenem jen
 * korenoveho adresare, ktery nevytvarite vy
 * Tato funkce nebude volana s nesmyslnym vstupem typu nesmysl/home/user,
 * ale vzdy bude volana s / na zacatku
 * V pripade existence cesty nic neprovadite
 *
 * pro rozdeleni cesty pouzijte pathSplit, ktera je okomentovana vyse
 * jestli se retezce rovnaji zjistite pomoci strcmp(prvni, druhy) == 0
 *
 * po volani malloc(sizeof(Directory))
 * nezapomente nastavit vsechny parametry nove slozky, jinak je v nich smeti
 *
 * @param path cesta, kterou mate v pripade neexistence vytvorit
 */
void mkdirP(Directory* root, char* path) {
    int no = pathSplit(path);
    Directory* togo = NULL;
    Directory* walker = root;
    for(int i=0; i<no; i++) {
        togo = NULL;
        for(int j=0; j<walker->subDirectoryCount; j++) {
            if(strcmp(walker->subDirectory[j]->directoryName, pathNames[i])==0) {
                togo = walker->subDirectory[j];
            }
        }
        if(togo == NULL) {
            togo = dirInsert(walker, pathNames[i]);
        }
        walker = togo;
    }
}

int main()
{
    /* svuj kod mozete testovat tu: */

    /* nasledujuci kod nemente*/
    Directory d;
    d.directoryName = "";
    d.parent = NULL;
    d.subDirectoryCount = 0;
    int ret;

    //test 1
    puts("Test 1.:");
    mkdirP(&d, "/home/user");

    char homePath[MAX_SIZE];
    Directory* home = d.subDirectory[0];
    pwd(home, homePath);
    if(strcmp(homePath, "/home/") == 0) {
        puts("OK, ");
    }
    else {
        printf("Chyba, cesta mela byt /home/, vase cesta byla %s\n", homePath);
    }

    //test 2
    puts("Test 2.:");
    char userPath[MAX_SIZE];
    Directory* user = home->subDirectory[0];
    pwd(user, userPath);
    if(strcmp(userPath, "/home/user/") == 0) {
        puts("OK");
    }
    else {
        printf("Chyba, cesta mela byt /home/user/, vase cesta byla %s\n", userPath);
    }

    //test 3
    puts("Test 3.:");
    mkdirP(&d, "/home/user");
    if(d.subDirectoryCount > 1) {
        puts("Chyba, vytvarite 2 slozky stejneho jmena");
    }
    else {
        puts("OK");
    }

    //test 4
    puts("Test 4.:");
    mkdirP(&d, "/home/user/Documents");
    Directory* doc = user->subDirectory[0];

    char docPath[MAX_SIZE];
    pwd(doc, docPath);
    if(strcmp(docPath, "/home/user/Documents/") == 0) {
        puts("OK");
    }
    else {
        printf("Chyba, cesta mela byt /home/user/Documents/, vase cesta byla %s\n",
               docPath);
    }

    //test 5
    puts("Test 5.:");
    mkdirP(&d, "/home/user/tmp");
    mkdirP(&d, "/tmp/tmp/tmp");
    mkdirP(&d, "/tmp/tmp2/tmp");
    mkdirP(&d, "/tmp/tmp2/tmp2");

    if(d.subDirectoryCount == 2) {
        puts("OK");
    }
    else {
        printf("Chyba, korenovy adresar mel obsahovat 2 slozky, vas obsahuje %i\n",
               d.subDirectoryCount);
    }

    //test 6
    puts("Test 6.:");

    if(d.subDirectory[1]->subDirectoryCount == 2 &&
            d.subDirectory[1]->subDirectory[1]->subDirectoryCount == 2) {
        puts("OK");
    }
    else {
        printf("Chyba, adresar /tmp ma obsahovat 2 slozky, vas obsahuje %i\n",
               d.subDirectory[1]->subDirectoryCount);
        printf("nebo, adresar /tmp/tmp2 ma obsahovat 2 slozky, vas obsahuje %i\n",
               d.subDirectory[1]->subDirectory[1]->subDirectoryCount);
    }
  return 0;
}

int pathSplit(char* path) {
    char tmp[MAX_SIZE];
    strcpy(tmp, path);

    int j = 0;

    char *name = strtok(tmp, "/");

    while(name != NULL) {
        strcpy(pathNames[j], name);
        name = strtok(NULL, "/");
        j++;
    }

    strcpy(pathNames[j], "");
    return j;
}

Directory* dirInsert(Directory* to, char* name) {
    Directory* newDir = malloc(sizeof(Directory));
    char* newName = malloc(MAX_SIZE*sizeof(char));
    strcpy(newName, name);
    newDir->directoryName = newName;
    newDir->parent = to;
    newDir->subDirectoryCount = 0;
    to->subDirectory[to->subDirectoryCount] = newDir;
    to->subDirectoryCount++;
    return newDir;
}

int pwd(Directory* from, char* totalPath) {
    if(from == NULL) {
        return 0;
    }

    char path[MAX_SIZE];
    int i = 0;

    while(from != NULL) {
        if(i == 0) {
            strcpy(totalPath, from->directoryName);
            strcat(totalPath, "/");
        }
        else {
            strcpy(path, totalPath);
            strcpy(totalPath, from->directoryName);
            strcat(totalPath, "/");
            strcat(totalPath, path);
        }

        from = from->parent;
        i++;
    }
    return 1;
}
