#include <stdio.h>
#include <stdlib.h>

#define StackLimit 15

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

void TraverseStack(StackType Stack);

int main(){
    StackElementType i;
    StackType stack, temp;
    StackElementType n, x;
    StackElementType limit;

    CreateStack(&stack);
    CreateStack(&temp);

    for(i=0; i<150; i+=10){
        Push(&stack, i);
    }
    TraverseStack(stack);

    limit = (stack.Top-1)/2;
    printf("Give nth element (n<=%d) ", limit);
    scanf("%d", &n);

    Pop(&stack, &stack.Element[stack.Top]); /*Qa*/
    x = stack.Element[stack.Top];
    Pop(&stack, &x);

    printf("\nQuestion a: x=%d\n", x);
    TraverseStack(stack);


    /*Qb*/
    Push(&temp, stack.Element[stack.Top]);
    Pop(&stack, &stack.Element[stack.Top]);
    x = stack.Element[stack.Top];
    Push(&stack, temp.Element[temp.Top]);
    Pop(&temp, &temp.Element[temp.Top]);

    printf("\nQuestion b: x=%d\n", x);
    TraverseStack(stack);


    for(i=0; i<n; i++){ /*Qc*/
        Pop(&stack, &x);
    }

    printf("\nQuestion c: x=%d\n", x);
    TraverseStack(stack);


    for(i=0; i<n; i++){ /*Qd*/
        Pop(&stack, &x);
        Push(&temp, x);
    }

    printf("\nQuestion d: x=%d\n", x);

    for(i=0; i<n; i++){
        Push(&stack, temp.Element[temp.Top]);
        Pop(&temp, &temp.Element[temp.Top]);
    }
    TraverseStack(stack);


    while(!EmptyStack(stack)){ /*Qe*/
        Pop(&stack, &x);
        Push(&temp, x);
    }
    printf("\nQuestion e: x=%d\n", x);

    while(!EmptyStack(temp)){
        Pop(&temp, &x);
        Push(&stack, x);
    }
    TraverseStack(stack);


    while(stack.Top != 1){ /*Qf*/
        Pop(&stack, &x);
        Push(&temp, x);
    }
    printf("\nQuestion f: x=%d\n", x);

    while(!EmptyStack(temp)){
        Pop(&temp, &x);
        Push(&stack, x);
    }
    TraverseStack(stack);


    while(!EmptyStack(stack)){ /*Qg*/
        Pop(&stack, &x);
    }
    printf("\nQuestion g: x=%d\n", x);
    TraverseStack(stack);

    return 0;

}


void CreateStack(StackType *Stack){
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

void TraverseStack(StackType Stack){
    int i;
    printf("plithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
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
