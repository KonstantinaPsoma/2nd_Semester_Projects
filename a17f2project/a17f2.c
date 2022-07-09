#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define StackLimit 50


typedef int StackElementType;

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

StackType CopyStack(StackType *s1);
void TraverseStack(StackType Stack);

int main(){
    StackType stack1, stack2;
    int i;

    CreateStack(&stack1);
    for(i=0; i<20; i++){
        Push(&stack1, i);
    }

    printf("Stack s1\n");
    TraverseStack(stack1);

    stack2 = CopyStack(&stack1);

    printf("After copying s1 to s2\n");

    printf("Stack s1\n");
    TraverseStack(stack1);
    printf("Stack s2\n");
    TraverseStack(stack2);

    return 0;
}

StackType CopyStack(StackType *s1){
    StackElementType x;
    StackType s2, temp;


    CreateStack(&s2);
    CreateStack(&temp);

    while(!EmptyStack(*s1)){
        x = s1->Element[s1->Top];

        Pop(&(*s1), &x);
        Push(&temp, x);
    }

    while(!EmptyStack(temp)){
        Pop(&temp, &x);
        Push(&s2, x);
        Push(&(*s1), x);
    }

    return s2;
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

void TraverseStack(StackType Stack)
{
    int i;
    printf("plithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}





