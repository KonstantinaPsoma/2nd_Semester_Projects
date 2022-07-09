#include <stdlib.h>
#include <stdio.h>

/* Queue */
#define QueueLimit 4

typedef struct{
    int arrival;
    int stay;
    int start;
    int end;
} QueueElementType;

typedef struct {
	int Front, Rear;
	QueueElementType Element[QueueLimit];;
} QueueType;

typedef enum {FALSE, TRUE} boolean;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);

void ReadCustomer(QueueType *Queue);
QueueType TimesInQueue(QueueType *Queue);
void TraverseQ(char phrase[], QueueType Queue);

int main(){
    QueueType WaitingQueue;
    QueueType ServiceQueue;
    int i;

    CreateQ(&WaitingQueue);
    for(i=0; i<3; i++){
        printf("Give: arrival time,stay time for client %d: ", i+1);
        ReadCustomer(&WaitingQueue);
    }
    TraverseQ("Waiting Queue", WaitingQueue);

    ServiceQueue = TimesInQueue(&WaitingQueue);

    TraverseQ("Waiting Queue", WaitingQueue);
    TraverseQ("Service Queue", ServiceQueue);

    return 0;
}

void ReadCustomer(QueueType *Queue){
    QueueElementType tmpCustomer;

    scanf("%d,%d", &tmpCustomer.arrival, &tmpCustomer.stay);
    tmpCustomer.start = -1;
    tmpCustomer.end = -1;
    AddQ(&(*Queue), tmpCustomer);
}

QueueType TimesInQueue(QueueType *Queue){
    int earliestStart = 0;
    int currentStart = 0;
    int currentEnd = 0;

    QueueType QueueServiced;
    QueueElementType CurrentCust;

    CreateQ(&QueueServiced);

    while(!EmptyQ(*Queue)){
        RemoveQ(&(*Queue), &CurrentCust);
        if(CurrentCust.arrival > earliestStart){
            currentStart = CurrentCust.arrival;
        }
        else
            currentStart = earliestStart;

        currentEnd = currentStart + CurrentCust.stay;
        earliestStart = currentEnd;

        CurrentCust.start = currentStart;
        CurrentCust.end = currentEnd;
        AddQ(&QueueServiced, CurrentCust);
    }
    return QueueServiced;
}

void CreateQ(QueueType *Queue)
/*  Λειτουργία:  Δημιουργεί μια κενή ουρά.
    Επιστρέφει:  Κενή ουρά
*/
{
	Queue->Front = 0;
	Queue->Rear = 0;
}

boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, False διαφορετικά
*/
{
	return (Queue.Front == Queue.Rear);
}

boolean FullQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι γεμάτη.
   Επιστρέφει: True αν η ουρά είναι γεμάτη, False διαφορετικά
*/
{
	return ((Queue.Front) == ((Queue.Rear +1) % QueueLimit));
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Αφαιρεί το στοιχείο Item από την εμπρός άκρη της ουράς
                αν η ουρά δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα κενής ουρά αν η ουρά είναι κενή
*/
{
	if(!EmptyQ(*Queue))
	{
		*Item = Queue ->Element[Queue -> Front];
		Queue ->Front  = (Queue ->Front + 1) % QueueLimit;
	}
	else
		printf("Empty Queue");
}

void AddQ(QueueType *Queue, QueueElementType Item)
/* Δέχεται:    Μια ουρά Queue και ένα στοιχείο Item.
   Λειτουργία: Προσθέτει το στοιχείο Item στην ουρά Queue
                αν η ουρά δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη ουρά.
   Έξοδος:     Μήνυμα γεμάτης ουράς αν η ουρά είναι γεμάτη
*/
{
	if(!FullQ(*Queue))
	{
		Queue ->Element[Queue ->Rear] = Item;
		Queue ->Rear = (Queue ->Rear + 1) % QueueLimit; ;
	}
	else
		printf("Full Queue");
}

void TraverseQ(char phrase[], QueueType Queue) {
	int current;
	int i=1;

    if(!EmptyQ(Queue)){
        printf("%s\n", phrase);
        current = Queue.Front;
        printf("Client \t\tStart\tEnd\tArrival\tStay\n");

        while (current != Queue.Rear) {
            printf("Client %d\t%d\t%d\t%d\t%d\n", i, Queue.Element[current].start, Queue.Element[current].end, Queue.Element[current].arrival, Queue.Element[current].stay);
            current = (current + 1) % QueueLimit;
            i += 1;
        }
    }
    else{
        printf("%s is Empty", phrase);
    }

	printf("\n");
}

