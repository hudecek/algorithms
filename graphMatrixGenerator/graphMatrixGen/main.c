

/*
 * Implementacny test IB002 - uloha 2. (8 bodov)
 *
 * Vyplnte nasledujuce udaje:
 * Meno:
 * UCO:
 * Skupina(v ktorej ste zapisany):
 */

// Zadani:
//
// Naimplementujte metodu 'Generate', ktora vygeneruje maticu sousednosti grafu splnajuceho podmienky:
//     - obsahuje presne dany pocet vrcholov N (N je zadane ako parameter konstruktora Graph, N>=6)
//     - graf je neorientovany
//     - graf neobsahuje slucky
//     - graf neobsahuje cykly
//     - graf obsahuje hrany 3 roznych dlzok: 4, 5, 6
//     - z kazdeho vrcholu grafu vychadzaju maximalne 3 hrany (stupen kazdeho vrcholu je mensi nez 4)
//     - graf obsahuje najmenej N/2 hran (zaokruhlene nadol)
//     Pocet uzlov grafu bude splnat N >= 6 (nemusite kontrolovat)
//     Neexistujuce hrany v matici reprezentujte hodnotou -1.
//     Snazte sa o co najefektivnejsiu implementaciu.
// [8 bodov]

#include <stdio.h>
#include <stdlib.h>
#define COORS(x,y,size) ((x)*(size)+(y))

void Generate(int *matrix, int pocetVrcholov);

int pocetVrcholov = 6;
int main()
{
int i,j;

int matrix1[pocetVrcholov*pocetVrcholov];
for( i = 0; i < pocetVrcholov; i++) {
    for( j = 0; j < pocetVrcholov; j++) {
        matrix1[COORS(i,j,pocetVrcholov)] = -1;
    }
}
Generate(matrix1, pocetVrcholov);
int result = Validate(matrix1, pocetVrcholov);
printf("Validacia: %d\n", result); //malo by byt 1

pocetVrcholov = 9;
int matrix2[pocetVrcholov*pocetVrcholov];
for( i = 0; i < pocetVrcholov; i++) {
    for( j = 0; j < pocetVrcholov; j++) {
        matrix2[COORS(i,j,pocetVrcholov)] = -1;
    }
}
Generate(matrix2, pocetVrcholov);
result = Validate(matrix2, pocetVrcholov);
printf("Validacia: %d\n", result); //malo by byt 1

return 0;
}

void Generate(int *matrix, int pocetVrcholov) {
    int a, b;
    for(int i=0; i<pocetVrcholov/2-1;i++) {
        switch(i % 3) {
        case 0:
            a = 4;
            b = 5;
            break;
        case 1:
            a = 5;
            b = 6;
            break;
        case 2:
            a = 4;
            b = 6;
            break;
        }


        matrix[COORS(i, 2*i+1, pocetVrcholov)]= a;
        matrix[COORS(i, 2*i+2, pocetVrcholov)] = b;
        matrix[COORS(2*i+1, i, pocetVrcholov)]= a;
        matrix[COORS(2*i+2, i, pocetVrcholov)] = b;
    }
}

int Validate(int *matrix, int pocetVrcholov)
{
int numberOfEdges = 0;
int i, j ;
for( i = 0; i < pocetVrcholov; i++) {
    for( j = 0; j < pocetVrcholov; j++) {
        if (matrix[COORS(i,j,pocetVrcholov)] != matrix[COORS(j,i,pocetVrcholov)]) {
            printf("CHYBA: graf je orientovany!");
            return 0;
        }

        if (matrix[COORS(i,j,pocetVrcholov)] != -1)
                {
                    if (i <= j)
                    {
                        numberOfEdges++;
                    }

                    if (matrix[COORS(i,j,pocetVrcholov)] < 4 || matrix[COORS(i,j,pocetVrcholov)] > 6)
                    {
                        printf("CHYBA: nespravna vaha hrany %d %d ", i, j );
                        return 0;
                    }
                }
    }
}

if ( numberOfEdges < (pocetVrcholov / 2) )
        {
            printf("CHYBA: nizky pocet hran! %d %d",numberOfEdges,(pocetVrcholov/2));
            return 0;
        }

for ( i = 0; i < pocetVrcholov; i++)
        {
            if (matrix[COORS(i,i,pocetVrcholov)] != -1)
            {
                printf("CHYBA: graf obsahuje smycku %d", i);
                return 0;
            }
        }
for ( i = 0; i < pocetVrcholov; i++)
        {
            int degree = 0;
            for ( j = 0; j < pocetVrcholov; j++)
            {
                if (matrix[COORS(i,j,pocetVrcholov)] != -1)
                {
                    degree++;
                }
            }
            if (degree > 3)
            {
                printf("CHYBA: vrchol ma stupen viac, nez 3");
                return 0;
            }
        }

return 1;
}
