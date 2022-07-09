#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    FALSE, TRUE
} boolean;

typedef struct{
    int code;
    int prot;
} QueueElementType;

typedef struct QueueNode *QueuePointer;

typedef struct QueueNode{
	QueueElementType Data;
    QueuePointer Next;
} QueueNode;

typedef struct{
    QueuePointer Front;
    QueuePointer Rear;
} QueueType;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
void TraverseQ(QueueType Queue);

void insert_prot(QueueType *Queue, QueueElementType Item);


int main(){
    QueueType queue;
    int i, amount;
    QueueElementType item;

    printf("DWSE TO PLITHOS: ");
    scanf("%d", &amount);

    CreateQ(&queue);
    for(i = 0; i<amount; i++){
        printf("DWSE TON KODIKO TOU %dou KOMVOU: ", i+1);
        scanf("%d", &item.code);
        printf("DWSE TO VATHMO PROTERAIOTITAS TOU %dou KOMVOU: ", i+1);
        scanf("%d", &item.prot);
        insert_prot(&queue, item);
    }

    printf("----------Priority Queue-------------\n");
    TraverseQ(queue);

    return 0;
}

void insert_prot(QueueType *Queue, QueueElementType Item){
    QueuePointer TempPtr;
    QueuePointer CurrPtr;
    QueuePointer PredPtr;
    boolean flag;

    TempPtr= (QueuePointer)malloc(sizeof(struct QueueNode));
    TempPtr->Data = Item;
    TempPtr->Next = NULL;

    if(EmptyQ(*Queue)){
        Queue->Front = TempPtr;
        Queue->Rear = TempPtr;
    }
    else{
        PredPtr = Queue->Front;
        CurrPtr = Queue->Front;
        flag = FALSE;

        if(CurrPtr->Data.prot > TempPtr->Data.prot){
            Queue->Front = TempPtr;
            TempPtr->Next = CurrPtr;

        }
        else{
            while(CurrPtr != NULL && !flag){
                if(CurrPtr->Data.prot > TempPtr->Data.prot){
                    PredPtr->Next = TempPtr;
                    TempPtr->Next = CurrPtr;
                    flag = TRUE;
                }
                PredPtr = CurrPtr;
                CurrPtr = CurrPtr->Next;
            }
            if(!flag){
                PredPtr->Next = TempPtr;
                Queue->Rear = TempPtr;
            }
        }
    }
}

void CreateQ(QueueType *Queue)
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη ουρά.
   Επιστρέφει: Μια κενή συνδεδεμένη ουρά
*/
{
	Queue->Front = NULL;
	Queue->Rear = NULL;
}

boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια συνδεδεμένη ουρά.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, false  διαφορετικά
*/
{
	return (Queue.Front==NULL);
}

void TraverseQ(QueueType Queue){
    QueuePointer CurrPtr;

    if (EmptyQ(Queue)){
   	    printf("EMPTY Queue\n");
    }
    else{
   	    CurrPtr = Queue.Front;
        while ( CurrPtr != NULL ){
      	     printf("%d %d\n", CurrPtr->Data.prot, CurrPtr->Data.code);
             CurrPtr = CurrPtr->Next;
        }
    }
    printf("\n");
}
