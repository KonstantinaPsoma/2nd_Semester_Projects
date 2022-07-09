#include <stdlib.h>
#include <stdio.h>

/* Queue */
#define QueueLimit 10

typedef int QueueElementType;


typedef struct {
	int Front, Rear;
	QueueElementType Element[QueueLimit];
	int count;
} QueueType;

typedef enum {FALSE, TRUE} boolean;

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);

void TraverseQ(QueueType Queue);

int main(){
    QueueType queue;
    QueueElementType i, x;

    CreateQ(&queue);

    printf("---a---");
    queue.count = 0;
    for(i=0; i<10; i++){
        AddQ(&queue, i);
        queue.count += 1;
    }

    printf("\nQueue: ");
    TraverseQ(queue);
    printf("Front=%d Rear=%d Count=%d\n", queue.Front, queue.Rear, queue.count);

    printf("---b---\n");
    AddQ(&queue, 10);

    printf("\nQueue: ");
    TraverseQ(queue);
    printf("Front=%d Rear=%d Count=%d\n", queue.Front, queue.Rear, queue.count);

    printf("---c---");
    RemoveQ(&queue, &x);
    queue.count -= 1;

    printf("\nQueue: ");
    TraverseQ(queue);
    printf("Removed item=%d Front=%d Rear=%d Count=%d\n", x, queue.Front, queue.Rear, queue.count);

    printf("---d---");
    AddQ(&queue, 25);
    queue.count += 1;

    printf("\nQueue: ");
    TraverseQ(queue);
    printf("Front=%d Rear=%d Count=%d\n", queue.Front, queue.Rear, queue.count);

    printf("---e---\n");
    AddQ(&queue, 10);

    printf("\nQueue: ");
    TraverseQ(queue);
    printf("Front=%d Rear=%d Count=%d\n", queue.Front, queue.Rear, queue.count);

    printf("---f---\n");
    while(!EmptyQ(queue)){
        RemoveQ(&queue, &x);
        queue.count -= 1;
        printf("Queue: ");
        TraverseQ(queue);
        printf("Removed item=%d Front=%d Rear=%d Count=%d\n", x, queue.Front, queue.Rear, queue.count);
    }

    return 0;
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
	return (Queue.count==0);
}

boolean FullQ(QueueType Queue)
/* Δέχεται:    Μια ουρά.
   Λειτουργία: Ελέγχει αν η ουρά είναι γεμάτη.
   Επιστρέφει: True αν η ουρά είναι γεμάτη, False διαφορετικά
*/
{
	return Queue.count==QueueLimit;
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

void TraverseQ(QueueType Queue) {
	int current;
	int i;

	if(EmptyQ(Queue))
        printf("Empty Queue");
    else{
        current = Queue.Front;
        for(i=0; i<Queue.count; i++){
            printf("%d ", Queue.Element[current]);
            current = (current + 1) % QueueLimit;
        }
    }

	printf("\n");
}
