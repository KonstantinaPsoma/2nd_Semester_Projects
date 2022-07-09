#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define StackLimit 50


typedef char StackElementType;

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
    StackElementType ch;
    StackType stack;
    boolean found, flag;
    int counter;

    CreateStack(&stack);

    printf("Enter string: \n");

    found = FALSE;
    flag = FALSE;
    counter = 0;

    do{
        scanf("%c", &ch);
        getchar();
        Push(&stack, ch);
        counter += 1;

        if(ch == 'C'){
            flag = TRUE;
            counter -= 1;
            Pop(&stack, &stack.Element[stack.Top]);
            do{
               scanf("%c", &ch);
               getchar();
               if(ch == stack.Element[stack.Top]){
                    Pop(&stack, &stack.Element[stack.Top]);
                    counter -= 1;
               }
               else
                  found = TRUE;
            }while(found == FALSE && counter>=0);
        }

    }while(ch != '#' && found == FALSE);

    if(ch == '#' && counter == 1)
            return 0;

    if(ch == '#'&& flag == TRUE){
        printf("TRUE");
    }
    else
        printf("FALSE");


    return 0;
}


void CreateStack(StackType *Stack){
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack){
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack){
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item){
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item){
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

