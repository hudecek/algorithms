# -*- coding: utf-8 -*-
"""
Implementační test IB002 - úloha 1. (12 bodů)

Vyplňte následující údaje:
Jméno:
UČO:
Skupina (do které jste zapsáni): 
"""

"""
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
1) Pokud chcete setřídit seznam s, pak stačí zavolat s.sort()

2) vrchol s číslem i je na řádku i//size a sloupci i%size
   vrchol na řádku y a sloupci x má číslo y*size+x
   (řádky se počítají odshora, řádky i sloupce se číslují od nuly)

Po ukončení práce nahrajte váš kod do odevzdávárny:
IS -> Student -> IB002 -> Odevzdávárny -> PraktickyTest_skupina
Odevzdávejte jen zdrojový kod, NEODEVZDAVAJTE soubory s nastavením pro IDE.
"""

"""
Tato funkce provádí vlastní test.

Vstup:
@param size: délka strany šachovnice
@param board: graf šachovnice reprezentovaný seznamem sousedů
             (tedy board[i] je seznam sousedu vrcholu i)

Výstup:
@return: True pokud je graf jezdcův graf, False pokud ne
"""
def isKnights(size, board):
    print("Board size: %i x %i" % (size, size))
    # TODO: zde vložte svoje řešení
    return True
        
"""
Načte graf tahu ze souboru
formát souboru:
   size
   sousedi vrcholu "0", odděleni mezerou
   ...
   sousedi vrcholu "size*size-1", odděleni mezerou
"""
def readBoard(fileName):
    print("Input board: %s" % fileName)
    f = open(fileName, 'r')
    board = []
    size = int(f.readline())
    board = [map(int, line.split()) for line in f]
    f.close()
    return size, board

"""
Vrátí matici sousednosti pro graf reprezentovaný seznamem sousedů.
V matici je hrana reprezentovaná 1, ne-hrana pak 0.

Vstup:
@param graph: vstupní graf reprezentovaný seznamem sousedů, vrcholy jsou číslované 0..len(graph)

Výstup:
@ret: matice sousednosti o rozměrech len(graph)xlen(graph)
"""
def getNeighbourhoodMatrix(graph):
    n = len(graph)
    matrix = [[0]*n for i in range(n)]
    for i in range(n):
        for j in graph[i]:
            matrix[i][j] = 1
    return matrix


"""
Testovací data
"""
testFile = ["board1x1.txt", "board2x2.txt", "board2x2invalid.txt", "board3x3.txt", "board3x3oneextra.txt", "board3x3onemissing.txt", "board3x3emptyline.txt", "board8x8.txt", "board8x8invalid.txt", "board100x100.txt"]
testResult = [True, True, False, True, False, False, False, True, False, True]
testReason = ["I 1x1 bez hran je korektní graf",
              "Korektní graf",
              "Nekorektní graf",
              "Korektní graf",
              "Nekorektní graf: jedna hrana navíc",
              "Nekorektní graf: jedna hrana chybí",
              "Nekorektní graf: u jednoho vrcholu chybí sousedi",
              "Korektní, dostatečně velký graf",
              "Chybný, dostatečně velký graf",
              "Korektní, hodně velký graf"]

for i in range(len(testFile)):
    print("Test %i" % (i+1))
    size, board = readBoard(testFile[i])
    if isKnights(size, board) == testResult[i]:
        print("PASSED")
    else:
        print("FAILED!")
        print("DUVOD: %s" % testReason[i])

"""
Funkce pro generování grafů dané velikosti.
"""
def getGraph(size, fileName):
    print("Board size: %i x %i" % (size, size))
    f = open(fileName, 'w')
    f.write("%i\n" % size)
    for position in range(size*size):
        moves = getLegalMoves(position, size)
        for v in moves:
            f.write("%i " % v)
        f.write("\n")
    f.close()
    
