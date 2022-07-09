#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 1001

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);

boolean isFibonacci(stoixeio_synolou n, typos_synolou set_fib);
void createFibonacciSet(stoixeio_synolou threshold, typos_synolou set_fib);
void displaySet(stoixeio_synolou threshold, typos_synolou set);


int main(){
    stoixeio_synolou max, n;
    typos_synolou set_fib;


    do{
        printf("Dwse to megistoarithmo. ");
        scanf("%d", &max);
    }while(max<2 || max>1000);

    createFibonacciSet(max, set_fib);
    displaySet(max, set_fib);

    do{
       printf("Enter number to check: ");
       scanf("%d", &n);

       if(n>=0 && n<=1000){
            if(isFibonacci(n, set_fib)){
                printf("Fibonacci!\n");
            }
            else{
                printf("Not Fibonacci...\n");
            }
       }
    }while(n >= 0);

    return 0;
}


boolean isFibonacci(stoixeio_synolou n, typos_synolou set_fib){

    if(Melos(n, set_fib)==TRUE){
        return TRUE;
    }
    else
        return FALSE;
}


void createFibonacciSet(stoixeio_synolou threshold, typos_synolou set_fib){
    int i, f;

    Dimiourgia(set_fib);

    Eisagogi(0, set_fib);
    Eisagogi(1, set_fib);

    f = 2;
    i = 1;

    while(f<=threshold){
        Eisagogi(f, set_fib);
        f=f+i;
        i=f-i;
    }

}


void displaySet(stoixeio_synolou threshold, typos_synolou set){
	stoixeio_synolou i;

	for (i=0; i<=threshold; i++){
		if(Melos(i,set))
			printf(" %d",i);
	}
	printf("\n");
}


void Dimiourgia(typos_synolou synolo){
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = FALSE;
}


void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo){
    synolo[stoixeio] = TRUE;
}


boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo){
    return synolo[stoixeio];
}



