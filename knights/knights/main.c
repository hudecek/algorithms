/*
Implementační test IB002 - úloha 1. (12 bodů)

Vyplňte následující údaje:
Jméno:
UČO:
Skupina (do které jste zapsáni):
*/

/*
Vaším úkolem je zkontrolovat, zda zadaný graf je "jezdcův graf", tedy
reprezentuje množinu všech legálních tahů figury jezdec (knight) na
šachovnici zadané velikosti. Šachovnice je reprezentována grafem, kde každý
vrchol odpovídá jednomu poli šachovnice. Pole jsou očíslována sekvenčně,
počínaje levým horním rohem. Tedy například šachovnice velikosti 3x3 má pole
očíslována následovně:

0 1 2
3 4 5
6 7 8

Graf reprezentuje množinu všech tahů jezdce, pokud hrana mezi políčky u a v
existuje právě tehdy, když jezdec může udělat tah u->v. Ve výše uvedeném
případě 3x3 tedy například jsou hranami (0,7) a (0,5), naopak (0,3) a (0,4)
hranami nejsou. Příklad jezdcova grafu pro šachovnici 8x8 je v souboru
knights8x8.png.

V přiloženém kódu je graf reprezentován seznamem sousedů, kde navíc můžete
předpokládat, že se sousedé každého vrcholu jsou setříděni podle velikosti
(tj. v příkladě výše má vrchol 0 sousedy [5,7] a vrchol 6 sousedy
[1,5]). Pokud raději pracujete s maticí sousednosti, můžete si pomocí funkce
getNeighbourhoodMatrix převést reprezentaci grafu seznamem sousedů na
reprezentaci maticí sousednosti.

Může se hodit:
1) Pokud chcete setřídit seznam sousedů vrcholu i v poli seznamu board, pak
   můžete použít následující kód:

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

qsort (board[i]+sizeof(int), board[i][0], sizeof(int), compare);

2) vrchol s číslem i je na řádku i/size a sloupci i%size
   vrchol na řádku y a sloupci x má číslo y*size+x
   (řádky se počítají odshora, řádky i sloupce se číslují od nuly)


Po ukončení práce nahrajte váš kod do odevzdávárny:
IS -> Student -> IB002 -> Odevzdávárny -> PraktickyTest_skupina
Odevzdávejte jen zdrojový kod, NEODEVZDAVAJTE soubory s nastavením pro IDE.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 300
#define TEST_COUNT 10

int** getNeighbourhoodMatrix(int, int**);
void cleanup(int, int**);


/*
Tato funkce provádí vlastní test.

Vstup:
@param size: délka strany šachovnice
@param board: graf šachovnice reprezentovaný seznamem sousedů
             (tedy board[i] je pole obsahujici seznam sousedu vrcholu i:
          board[i][0] - stupen vrcholu i
              board[i][j] - j-ty naslednik vrcholu i)

Výstup:
@return: 1 pokud je graf jezdcův graf, 0 pokud ne
*/
int isKnights(int size, int** board) {
  // TODO: implementujte funkci
    int n = 0;
  for(int i=0; i<size; i++) {
      for(int j=0; j<size; j++) {
          /*
          printf("Pole: %d\n", i*size+j);
          for(int k = 0; k<size; k++) {
              printf("%d\n", board[size*i+j][k]);
          }*/
          n = 0;
          if(i-2 >= 0) {
              if(j-1 >= 0) {
                  if(board[i*size+j][n+1]!=(i-2)*size+j-1)
                      return 0;
                  n++;
              }
              if(j+1<size) {
                  if(board[i*size+j][n+1]!=(i-2)*size+j+1)
                      return 0;
                  n++;
              }

          }
          if(i -1 >=0) {
              if(j-2 >=0) {
                  if(board[i*size+j][n+1]!=(i-1)*size+j-2)
                      return 0;
                  n++;
              }
              if(j+2 < size) {
                  if(board[i*size+j][n+1]!=(i-1)*size+j+2)
                      return 0;
                  n++;
              }
          }
          if(i+1 < size) {
              if(j-2 >= 0) {
                  if(board[i*size+j][n+1]!=(i+1)*size+j-2)
                      return 0;
                  n++;
              }
              if(j+2 < size) {
                  if(board[i*size+j][n+1]!= (i+1)*size+j+2)
                      return 0;
                  n++;
              }
          }
          if(i+2 < size) {
              if(j-1 >=0) {
                  if(board[i*size+j][n+1]!=(i+2)*size+j-1)
                      return 0;
                  n++;
              }
              if(j+1 < size) {
                  if(board[i*size+j][n+1]!=(i+2)*size+j+1)
                      return 0;
                  n++;
              }
          }
          if(n!=board[i*size+j][0])
              return 0;
      }
  }
  return 1;
}

/*
Načte graf tahu ze souboru

formát souboru:
   size
   sousedi vrcholu "0", odděleni mezerou
   ...
   sousedi vrcholu "size*size-1", odděleni mezerou
*/
int** readBoard(int* size, const char* fileName) {
    printf("Input board: %s\n", fileName);
    FILE* inputFile;
    inputFile = fopen(fileName , "r");
    if (inputFile == NULL) {
        printf("Critical error: input file ''%s'' not opened.\n", fileName);
        exit(EXIT_FAILURE);
        }

    char line[MAX_LINE_LENGTH];
    char *str;

    fgets(line, 100, inputFile);
    str = strtok(line,"");
    *size = atoi(str);

    int i,j;
    int temp_array[MAX_LINE_LENGTH];
    int degree;
    int** array;

    array = malloc((*size)*(*size)*sizeof(int*));

    for (i = 0; i < (*size)*(*size); i++) {
        fgets(line, MAX_LINE_LENGTH, inputFile);
        degree = 0;
        str = strtok(line," \n");
        while (str != NULL) {
            temp_array[degree] = atoi(str);
            degree++;
            str = strtok(NULL," \n");
            }

        array[i] = malloc((degree+1)*sizeof(int));
        array[i][0] = degree;

        for(j=0; j < degree; j++)
            array[i][j+1] = temp_array[j];

        }
    fclose(inputFile);
    return array;
}

/*
Vrátí matici sousednosti pro graf reprezentovaný seznamem sousedů.
V matici je hrana reprezentovaná 1, ne-hrana pak 0.

Jestlize pouzijete funkci array=getNeighbourhoodMatrix(size,board), nezapomente uvolnit alokovanou pamet volanim cleanup(size, array).

Vstup:
@param graph: vstupní graf reprezentovaný seznamem sousedů, vrcholy jsou číslované 0..len(graph)

Výstup:
@ret: matice sousednosti o rozměrech len(graph)xlen(graph)
*/
int** getNeighbourhoodMatrix(int size, int** board) {
    int** matrix;
    matrix = malloc(size*size*sizeof(int*));
    int i,j;
    int neighbour;
    for (i=0; i < size*size; i++) {
        matrix[i] = calloc(size*size,sizeof(int));
        }
    for (i=0; i < size*size; i++) {
        for (j=1; j <= board[i][0]; j++) {
            neighbour = board[i][j];
            matrix[i][neighbour] = 1;
            matrix[neighbour][i] = 1;
            }
        }

    return matrix;

}


/**
 * Pomocna funkcia pre uvolnenie pamate pouzitej pre sachovnicu/maticu susednosti.
 * Vstup:
 * @param size:	 	pocet riadkov matice
 * @param array: 	pole, ktore sa ma uvolnit
 */
void cleanup(int size, int** array) {
    int i;
    for (i = 0; i <size*size; i++)
        free(array[i]);
}



int main() {
    int size = 0;
    int** board;
    //int i,j;

    const char testFile[TEST_COUNT][80] = {
      "board1x1.txt", "board2x2.txt", "board2x2invalid.txt", "board3x3.txt", "board3x3oneextra.txt", "board3x3onemissing.txt", "board3x3emptyline.txt", "board8x8.txt", "board8x8invalid.txt", "board100x100.txt"};
    const int testResult[TEST_COUNT] = {1,1,0,1,0,0,0,1,0,1};
    const char testReason[TEST_COUNT][80] = {"I 1x1 bez hran je korektní graf",
              "Korektní graf",
              "Nekorektní graf",
              "Korektní graf",
              "Nekorektní graf: jedna hrana navíc",
              "Nekorektní graf: jedna hrana chybí",
              "Nekorektní graf: u jednoho vrcholu chybí sousedi",
              "Korektní, dostatečně velký graf",
              "Chybný, dostatečně velký graf",
                "Korektní, hodně velký graf"};

        for(int i=0; i<10; i++){
      printf("Test %d\n", i+1);
      board = readBoard(&size, testFile[i]);
      if (isKnights(size, board) == testResult[i]) {
        printf("PASSED\n");
      } else {
        printf("FAILED\n");
        printf("DUVOD: %s\n", testReason[i]);
      }
      cleanup(size, board);
    }

    return 0;
}
