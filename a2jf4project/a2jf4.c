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

void insert_list_m_elements(ListPointer *List, int n);

int main(){
    ListPointer list;
    int n, amount, i;
    ListElementType number;

    CreateList(&list);
    printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS:");
    scanf("%d", &amount);
    for(i=0; i<amount; i++){
        printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS:");
        scanf("%d", &number);
        LinkedInsert(&list, number, NULL);
    }

    printf("*********Arxiki lista************\n");
    LinkedTraverse(list);

    printf("DWSE TI THESI, META APO TIN OPOIA THA EISAXTHOUN TA STOIXEIA:");
    scanf("%d", &n);

    insert_list_m_elements(&list, n);

    printf("*********Teliki lista************\n");
    LinkedTraverse(list);

    return 0;
}

void insert_list_m_elements(ListPointer *List, int n){
    ListPointer TempPtr;
    int i, j, m;
    ListElementType number;

    if(EmptyList(*List)){
        printf("EMPTY LIST");
    }
    else{
        TempPtr = *List;
        i = 1;
        while(TempPtr->Next != NULL && i<n){
            TempPtr = TempPtr->Next;
            i += 1;
        }
        if(n>i || n<1){ //temporarily
            printf("ERROR\n");
        }
        else{
            printf("DWSE TO PLITHOS TWN STOIXEIWN POU THA EISAXTHOUN:");
            scanf("%d", &m);
            for(j=0; j<m; j++){
                printf("DWSE TON ARI8MO GIA EISAGWGH STH LISTA: ");
                scanf("%d", &number);
                LinkedInsert(&List, number, TempPtr);
                TempPtr = TempPtr->Next;
            }
        }
    }

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
