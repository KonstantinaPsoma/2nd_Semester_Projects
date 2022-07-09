#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef int ListElementType;           /* ο τύπος των στοιχείων της συνδεδεμένης λίστας
                                        ενδεικτικά τύπου int */
typedef struct ListNode *ListPointer;   //ο τύπος των δεικτών για τους κόμβους

typedef struct ListNode
{
	ListElementType Data;
    ListPointer Next;
} ListNode;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);

void concat_list(ListPointer List, ListPointer BList, ListPointer *FinalList);

int main(){
    ListPointer list1, list2, FinalList;
    ListElementType amount;
    ListElementType number;
    ListPointer PredPtr;
    int i;

    CreateList(&list1);
    CreateList(&list2);

    printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 1:");
    scanf("%d", &amount);

    for(i=0; i<amount; i++){
        printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 1:");
        scanf("%d", &number);
        PredPtr = NULL;
        LinkedInsert(&list1, number, PredPtr);
    }

    printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 2:");
    scanf("%d", &amount);

    for(i=0; i<amount; i++){
        printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 2:");
        scanf("%d", &number);
        LinkedInsert(&list2, number, NULL);
    }

    printf("LISTA 1:\n");
    LinkedTraverse(list1);
    printf("LISTA 2:\n");
    LinkedTraverse(list2);

    concat_list(list1, list2, &FinalList);

    printf("SYNENWMENH LISTA:\n");
    LinkedTraverse(FinalList);

    return 0;
}

void concat_list(ListPointer List, ListPointer BList, ListPointer *FinalList){
    ListPointer CurrPtr;

    CreateList(FinalList);

    CurrPtr = List;
    while(CurrPtr->Next != NULL){
        LinkedInsert(&(*FinalList), CurrPtr->Data, NULL);
        CurrPtr = CurrPtr->Next;
    }
    LinkedInsert(&(*FinalList), CurrPtr->Data, NULL);

    CurrPtr = BList;
    while(CurrPtr->Next != NULL){
        LinkedInsert(&(*FinalList), CurrPtr->Data, NULL);
        CurrPtr = CurrPtr->Next;
    }
    LinkedInsert(&(*FinalList), CurrPtr->Data, NULL);

}

void CreateList(ListPointer *List)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη λίστα.
  Επιστρέφει:  Τον μηδενικό δείκτη List
*/
{
	*List = NULL;
}

boolean EmptyList(ListPointer List)
/* Δέχεται:   Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
  Λειτουργία: Ελέγχει αν η συνδεδεμένη λίστα είναι κενή.
  Επιστρέφει: True αν η λίστα είναι κενή και false διαφορετικά
*/
{
	return (List==NULL);
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο,
                ένα στοιχείο δεδομένων Item και έναν δείκτη PredPtr.
   Λειτουργία: Εισάγει έναν κόμβο, που περιέχει το Item, στην συνδεδεμένη λίστα
                μετά από τον κόμβο που δεικτοδοτείται από τον PredPtr
                ή στην αρχή  της συνδεδεμένης λίστας,
                αν ο PredPtr είναι μηδενικός(NULL).
  Επιστρέφει:  Την τροποποιημένη συνδεδεμένη λίστα με τον πρώτο κόμβο της
                να δεικτοδοτείται από τον List.
*/
{
	ListPointer TempPtr;

   TempPtr= (ListPointer)malloc(sizeof(struct ListNode));
 /*  printf("Insert &List %p, List %p,  &(*List) %p, (*List) %p, TempPtr %p\n",
   &List, List,  &(*List), (*List), TempPtr); */
   TempPtr->Data = Item;
	if (PredPtr==NULL) {
        TempPtr->Next = *List;
        *List = TempPtr;
    }
    else {
        TempPtr->Next = PredPtr->Next;
        PredPtr->Next = TempPtr;
    }
}


void LinkedTraverse(ListPointer List)
/* Δέχεται:    Μια συνδεδεμένη λίστα με τον List να δείχνει στον πρώτο κόμβο.
   Λειτουργία: Διασχίζει τη συνδεδεμένη λίστα και
                επεξεργάζεται κάθε δεδομένο ακριβώς μια φορά.
   Επιστρέφει: Εξαρτάται από το είδος της επεξεργασίας.
*/
{
	ListPointer CurrPtr;

   if (EmptyList(List))
   	    printf("EMPTY LIST\n");
   else
   {
   	     CurrPtr = List;
         while ( CurrPtr!=NULL )
        {
             printf("%d ", (*CurrPtr).Data);
             CurrPtr = CurrPtr->Next;
        }
        printf("\n");
   }
}
