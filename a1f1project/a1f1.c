#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define megisto_plithos 201

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);

boolean isPrime(stoixeio_synolou n);
void createPrimeSet(stoixeio_synolou first, stoixeio_synolou last, typos_synolou S);
void displaySet(stoixeio_synolou first, stoixeio_synolou last, typos_synolou S);

int main(){
    stoixeio_synolou first, last;
    typos_synolou S;


    do{
        printf("Enter the first number (2-200): ");
        scanf("%d", &first);
    }while(first<2 || first>=200);


    do{
        printf("Enter the last number (2-200): ");
        scanf("%d", &last);
    }while(last<2 || last>200 || last <= first);

    createPrimeSet(first, last, S);
    displaySet(first, last, S);

    return 0;
}


boolean isPrime(stoixeio_synolou n){
    int ans;
    int j;

    ans = 1;
    j = 1;
    do{
        j += 1;
    }while(n % j != 0);

    if(j>=2 && j<n){
        ans = 0;
    }

    if(ans == 1){
        return TRUE;
    }
    else{
        return FALSE;
    }

}


void createPrimeSet(stoixeio_synolou first, stoixeio_synolou last, typos_synolou S){
    stoixeio_synolou i;

    Dimiourgia(S);
    for(i=first; i<=last; i++){
        if(isPrime(i) == TRUE){
            Eisagogi(i, S);
        }
    }

}

void displaySet(stoixeio_synolou first, stoixeio_synolou last, typos_synolou S){
    stoixeio_synolou i;

	for (i=first; i<=last; i++){
		if(Melos(i,S))
			printf(" %d",i);
	}
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
