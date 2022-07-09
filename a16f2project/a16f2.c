#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define StackLimit 50

typedef struct{
    int price;
    char size;
} StackElementType;

typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

void TraverseStack(StackType Stack);

int main(){
    int amount, i;
    StackType stack;
    StackType temp_stack;
    StackElementType item;
    char size;
    int found;

    CreateStack(&stack);
    CreateStack(&temp_stack);

    printf("Give number of items ");
    scanf("%d", &amount);
    printf("Give the items to store\n");

    for(i=0; i<amount; i++){

        printf("Give price ");
        scanf("%d", &item.price);
        printf("Give size ");
        scanf("%s", &item.size);
        getchar();

        Push(&stack, item);

    }

    printf("Items in the box");
    TraverseStack(stack);

    printf("What size do you want? ");
    scanf("%c", &size);
    getchar();

    found = 0;
    while(!EmptyStack(stack) && found == FALSE){
        item = stack.Element[stack.Top];
        Pop(&stack, &item);
        if(item.size == size){
            found = 1;
        }else{
            Push(&temp_stack, item);
        }
    }

    if(found == 1){
        printf("Found the size %c\n", size);
    }
    else{
        printf("Not Found the size %c\n", size);
    }

    printf("Items in the box");
    TraverseStack(stack);

    printf("Items out of the box");
    TraverseStack(temp_stack); /*number 5*/

    while(!EmptyStack(temp_stack)){
        item = stack.Element[stack.Top];
        Pop(&temp_stack, &item);
        Push(&stack, item);
    }

    printf("Items in the box"); /*number 7*/
    TraverseStack(stack);

    printf("Items out of the box");
    TraverseStack(temp_stack);

    return 0;
}


void CreateStack(StackType *Stack)
/* Λειτουργία: Δημιουργεί μια κενή στοίβα.
   Επιστρέφει: Κενή Στοίβα.*
*/
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι κενή.
   Επιστρέφει: True αν η Stack είναι κενή, False διαφορετικά
*/
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι γεμάτη.
   Επιστρέφει: True αν η Stack είναι γεμάτη, False διαφορετικά
*/
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
/* Δέχεται: Μια στοίβα Stack και ένα στοιχείο Item.
   Λειτουργία: Εισάγει το στοιχείο Item στην στοίβα Stack αν η Stack δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη Stack.
   Έξοδος: Μήνυμα γεμάτης στοίβας, αν η στοίβα Stack είναι γεμάτη
*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Διαγράφει το στοιχείο Item από την κορυφή της Στοίβας αν η Στοίβα δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη Stack.
   Έξοδος:  Μήνυμα κενής στοίβας αν η Stack είναι κενή
*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

void TraverseStack(StackType Stack){
    int i;


    printf("\nplithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {

        printf("%c, %d \n",Stack.Element[i].size, Stack.Element[i].price);
    }
    printf("\n");
}
