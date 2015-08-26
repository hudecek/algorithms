#include<stdio.h>
#include<stdlib.h>

/**
 * Implementacni test IB002 - uloha 2. (12 bodu)
 *
 * Vyplnte nasledujice udaje:
 * Jmeno:
 * UCO:
 * Skupina (ve ktere jste zapsan):
 *
 * Vasi ulohou v tomto prikladu je modifikovat jiz existujici strukturu
 * oboustranne zretezeneho linearniho seznamu (budu psat List).
 *
 * List s uzly a, b, c, d, e, f, g, h, i, j vypada bezne takto:
 * null <- a <-> b <-> c <-> d <-> e <-> f <-> g <-> h <-> i <-> j -> null
 * kde <-> znaci ukazatele tam i zpet
 *
 * Nas modifikovany StrangeList pouziva pro reprezentaci stejne promenne, jen
 * ukazatele ukazuji jinam.
 * Ukazatele dopredu budou ukazovat ob jeden uzel, ukazatele zpet zustanou zachovany.
 * Po rozepsani do dvou pater vzniknou takto hezke 2 seznamy:
 * null  <-  a  ->  c  ->  e  ->  null
 *             \   /  \   /  \
 *               b  ->  d  -> f  -> null
 * kde zpetna lomitka \ znaci sipku nahoru a normalni / znaci sipku dolu
 * (tedy cesta f -> e -> d -> c -> b -> a zustava zachovana).
 * predposledni a posledni ukazatel ukazuji na null
 *
 * Vasim ukolem je naprogramovat funkci listToStrangeList, ktera z Listu vytvori
 * nas StrangeList.
 * @author Karel Kubicek
 */

struct Element
{
  int value;
  struct Element *next;
  struct Element *prev;
};

/**
 * vlozi prvok na koniec zoznamu
 * @param beginning  zaciatok zoznamu
 * @param end  koniec zoznamu
 * @param value  vkladana hodnota
 * @return  zaciatok zoznamu
 */
void insert(struct Element **beginning, struct Element **end, int value);

/**
 * zmaze zvoleny prvok
 * @param beginning  zaciatok zoznamu
 * @param end koniec zoznamu
 * @param elem  zvoleny prvok
 */
void delete(struct Element **beginning, struct Element **end, struct Element *elem);

/**
 * zmaze vsetky prvky v zozname
 * @param beginning  zaciatok zoznamu
 * @param end  koniec zoznamu
 */
void delete_all(struct Element **beginning, struct Element **end);

/**
 * vypisy slouzici ke kontrole
 * @param beginning  pocatek vypisu
 * @return
 */
void print_list(struct Element *beginning);

/**
 * TODO: naimplementujte metodu listToStrangeList
 * pracujte s listem, na ktery mate ukazatele listBegining a listEnd
 * metoda ma za ukol prevest list z pocatecni podoby do modifikovane podoby,
 * ktera je popsana v komentari na zacatku
 * metoda vraci ukazatele na zacatek druheho listu (v ukazce vyse je to prvek b)
 * v pripade prazdneho listu vratte null
 *
 * @return ukazatel na druhy "dopredny" list
 */
struct Element* listToStrangeList(struct Element *beginning, struct Element *end)
{
    if(beginning == NULL || end == NULL)
        return NULL;
    if(beginning == end)
        return NULL;
    struct Element* walker = beginning;
    struct Element* save;
    while(walker->next != end) {
        save = walker->next;
        walker->next = walker->next->next;
        walker = save;
    }
    return beginning->next->prev;
}

int main()
{
  struct Element* beginning = NULL;
  struct Element* end = NULL;

  printf("Test 1.:");
  if(beginning == NULL &&
     end == NULL &&
     listToStrangeList(beginning, end) == NULL)
       printf("OK\n");
  else
     printf("Chyba pri praci s prazdnym listem");

  printf("Test 2.:");
  delete_all(&beginning, &end);

  struct Element *first_part, *second_part;

  first_part = beginning;
  second_part = listToStrangeList(beginning, end);

  if(second_part == NULL && beginning == end)
    printf("OK\n");
  else
    printf("Chyba pri praci s listem s jednim prvkem\n");

  for (int i = 3; i <= 10; i++)
  {
    delete_all(&beginning, &end);
    beginning = NULL;
    end = NULL;
    first_part = NULL;
    second_part = NULL;

    for (int j = 1; j < i; j++)
      insert(&beginning, &end, j);

    printf("Test %d.:", i);

    first_part = beginning;
    second_part = listToStrangeList(beginning, end);

    for(int j = 1; j < i; j += 2)
    {
      if(first_part->value != j)
      {
        printf("Chyba, spatne poradi - licha cisla\n");
        return i;
      }

      if(first_part != NULL)
        first_part = first_part->next;

      if(second_part == NULL) break;
      if(second_part->value != j+1)
      {
        printf("Chyba, spatne poradi - suda cisla\n");
        return i;
      }
      second_part = second_part->next;
    }

    printf("OK\n");
    delete_all(&beginning, &end);
  }
}

void insert(struct Element **beginning, struct Element **end, int value)
{
  struct Element* new = (struct Element*) malloc(sizeof(struct Element));
  new->value = value;
  new->next = NULL;
  new->prev = NULL;

  if(*end == NULL)
  {
    *beginning = new;
    *end = new;
  }
  else
  {
    (*end)->next = new;
    *end = new;
  }
}

void delete(struct Element **beginning, struct Element **end, struct Element *elem)
{
  if(elem == NULL)
    return ;

  if(*beginning == elem)
    *beginning = (*beginning)->next;

  if(*end == elem)
    *end = (*end)->prev;

  if(elem->prev != NULL)
    elem->prev->next = elem->next;

  free(elem);
}

void delete_all(struct Element **beginning, struct Element **end)
{
  struct Element *tmp = *beginning;

  if(*beginning != NULL &&
     (*beginning)->next != NULL &&
     *beginning != (*beginning)->next->prev)
  {
    struct Element *tmp2;
    struct Element *tmp_second_line = (*beginning)->next->prev;
    while(tmp_second_line != NULL)
    {
      tmp2 = tmp_second_line->next;
      delete(beginning, end, tmp_second_line);
      tmp_second_line = tmp2;
    }
  }
  while(*beginning != NULL)
  {
    tmp = (*beginning)->next;
    delete(beginning, end, *beginning);
    *beginning = tmp;
  }
}

void print_list(struct Element *beginning)
{
  printf("List: ");

  while(beginning != NULL)
  {
    printf("%d ", beginning->value);
    beginning = beginning->next;
  }

  printf("\n");
}
