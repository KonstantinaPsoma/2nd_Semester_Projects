#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define HMax 9              /*     το μέγεθος του πίνακα HashTable
                                ενδεικτικά ίσο με 5 */
#define VMax 30             /*το μέγεθος της λίστας,
                                ενδεικτικά ίσο με 30 */
#define EndOfList -1        /* σημαία που σηματοδοτεί το τέλος της λίστας
                                και της κάθε υπολίστας συνωνύμων */

typedef struct{
    char phone_number[11];
    int code;
} ListElementType;

typedef char KeyType[32];

typedef struct {
	KeyType RecKey;
	ListElementType Data;
	int Link;
} ListElm;

typedef struct  {
	int HashTable[HMax];   // πίνακας δεικτών προς τις υπολίστες συνωνύμων
    int Size;                // πλήθος εγγραφών της λίστας List
	int SubListPtr;          // Dδείκτης σε μια υπολίστα συνωνύμων
    int StackPtr;           // δείκτης προς την πρώτη ελεύθερη θέση της λίστας List
	ListElm List[VMax];
} HashListType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateHashList(HashListType *HList);
int HashKey(KeyType Key);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void AddRec(HashListType *HList,ListElm InRec);
void DeleteRec(HashListType *HList,KeyType DelKey);

void PrintPinakes(HashListType HList);

void BuildHashList(HashListType *HList);
void Search_HashList_By_Subject(HashListType HList, int code);
int findAverage(char s[]);

int main(){
    HashListType HList;
    ListElm Item;
    int Loc, Pred, code;
    char ch, surname[20];
    KeyType key;

    printf("1. Create HashList\n");

    BuildHashList(&HList);
    PrintPinakes(HList);

    printf("2. Insert new teacher\n");
    do{
        printf("Enter teacher's name: ");
        scanf("%s", Item.RecKey);
        printf("Enter teacher's surname: ");
        scanf("%s", surname);

        strcat(Item.RecKey, " ");
        strcat(Item.RecKey, surname);

        printf("Enter teacher's phone: ");
        scanf("%s", Item.Data.phone_number);
        printf("Enter teacher code: ");
        scanf("%d", &Item.Data.code);

        Item.Link=EndOfList;
        AddRec(&HList, Item);
        printf("\nContinue Y/N: ");
        do{
            scanf("%c", &ch);
        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
    } while (toupper(ch)!='N');
    PrintPinakes(HList);

    printf("3. Delete a teacher\n");

    printf("Enter teacher's name: ");
    scanf("%s", key);
    printf("Enter teacher's surname: ");
    scanf("%s", surname);

    strcat(key, " ");
    strcat(key, surname);

    SearchHashList(HList, key, &Loc, &Pred);
    if(Loc != -1){
        DeleteRec(&HList, key);
    }
    else
        printf("DEN YPARXEI EGGRAFH ME KLEIDI %s\n", key);
    PrintPinakes(HList);

    printf("4. Search for a teacher\n");

    printf("Enter teacher's name: ");
    scanf("%s", key);
    printf("Enter teacher's surname: ");
    scanf("%s", surname);

    strcat(key, " ");
    strcat(key, surname);

    SearchHashList(HList, key, &Loc, &Pred);
    if(Loc != -1){
        printf("[%s, %s, %d]\n", key, Item.Data.phone_number, Item.Data.code);
    }
    else
        printf("DEN YPARXEI EGGRAFH ME KLEIDI %s\n", key);

    printf("\n5. Search by subject\n");
    printf("Enter code: ");
    scanf("%d", &code);
    Search_HashList_By_Subject(HList, code);

    return 0;
}

void BuildHashList(HashListType *HList){
    FILE *fp;
    ListElm info;
    char surname[20];
    char termch;
    int nscan;

    fp = fopen("i4f6.txt", "r");
    CreateHashList(HList);

    if (fp == NULL)
        printf("Can't open %s\n", "i4f6.txt");
    else{
         while(TRUE){
            nscan = fscanf(fp, "%10[^,],%20[^,],%10[^,],%d%c", info.RecKey, surname, info.Data.phone_number, &info.Data.code, &termch);
            if(nscan == EOF)
                break;
            if(nscan!= 5 || termch != '\n')
                printf("Error\n");
            else{
                strcat(info.RecKey, " ");
                strcat(info.RecKey, surname);
                AddRec(HList, info);
            }
        }
        fclose(fp);
    }
}

void Search_HashList_By_Subject(HashListType HList, int code){
    int SubIndex, i;

    printf("List of teachers with subject code %d:\n", code);
    for (i=0; i<HMax;i++){
        SubIndex = HList.HashTable[i];
        while ( SubIndex != EndOfList ){
            if(HList.List[SubIndex].Data.code == code){
                printf("%d: [%s, %s, %d]\n", SubIndex,HList.List[SubIndex].RecKey,HList.List[SubIndex].Data.phone_number, HList.List[SubIndex].Data.code);
            }
            SubIndex = HList.List[SubIndex].Link;
        }
    }

}

int findAverage(char s[]){
    char first,last;

    first=s[0];
    last=s[strlen(s)-1];
    return ((first-64)+(last-64))/2;
}

int HashKey(KeyType Key)
/* Δέχεται:    Την τιμή Key ενός κλειδιού.
   Λειτουργία: Βρίσκει την τιμή κατακερματισμού HValue για το κλειδί Key.
   Επιστρέφει: Την τιμή κατακερματισμού HValue
*/
{
    int average;
	/*σε περίπτωση που το KeyType δεν είναι ακέραιος
	θα πρέπει να μετατρέπεται κατάλληλα το κλειδί σε αριθμό*/
	average = findAverage(Key);
	return average%HMax;
}

void CreateHashList(HashListType *HList)
/* Λειτουργία: Δημιουργεί μια δομή HList.
   Επιστρέφει: Την δομή HList
*/
{
	int index;

	HList->Size=0;           //ΔΗΜΙΟΥΡΓΕΙ ΜΙΑ ΚΕΝΗ ΛΙΣΤΑ
	HList->StackPtr=0;       //ΔΕΙΚΤΗς ΣΤΗ ΚΟΡΥΦΗ ΤΗΣ ΣΤΟΙΒΑΣ ΤΩΝ ΕΛΕΥΘΕΡΩΝ ΘΕΣΕΩΝ

    /*ΑΡΧΙΚΟΠΟΙΕΙ ΤΟΝ ΠΙΝΑΚΑ HashTable ΤΗΣ ΔΟΜΗΣ HList ΩΣΤΕ ΚΑΘΕ ΣΤΟΙΧΕΙΟΥ ΤΟΥ
        ΝΑ ΕΧΕΙ ΤΗ ΤΙΜΗ EndOfList (-1)*/
    index=0;
	while (index<HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }

     //Δημιουργία της στοίβας των ελεύθερων θέσεων στη λίστα HList
    index=0;
	while(index < VMax-1)
	{
		HList->List[index].Link=index+1;
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
}

boolean FullHashList(HashListType HList)
/* Δέχεται:    Μια δομή HList.
   Λειτουργία: Ελέγχει αν η λίστα List της δομής HList είναι γεμάτη.
   Επιστρέφει: TRUE αν η λίστα List είναι γεμάτη, FALSE διαφορετικά.
*/
{
	return(HList.Size==VMax);
}

void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στην υπολίστα συνωνύμων.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της προηγούμενης
                εγγραφής στην υπολίστα
*/
{
	int Next;

	Next=HList.SubListPtr;
	*Loc=-1;
	*Pred=-1;
	while(Next!=EndOfList){
		if (strcmp(HList.List[Next].RecKey, KeyArg) == 0){
			*Loc=Next;
			Next=EndOfList;
		}
		else{
			*Pred=Next;
			Next=HList.List[Next].Link;
		}
	}
}
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* Δέχεται:     Μια δομή HList και μια τιμή κλειδιού KeyArg.
    Λειτουργία: Αναζητά μια εγγραφή με κλειδί KeyArg στη δομή HList.
    Επιστρέφει: Τη θέση Loc της εγγραφής και τη θέση Pred της
                προηγούμενης εγγραφής της υπολίστας στην οποία ανήκει.
                Αν δεν υπάρχει εγγραφή με κλειδί KeyArg τότε Loc=Pred=-1
*/
{
	int HVal;
	HVal=HashKey(KeyArg);
    if (HList.HashTable[HVal]==EndOfList)
	{
		*Pred=-1;
		*Loc=-1;
	}
	else
	{
		HList.SubListPtr=HList.HashTable[HVal];
		SearchSynonymList(HList,KeyArg,Loc,Pred);
	}
}

void AddRec(HashListType *HList,ListElm InRec)
/* Δέχεται:    Μια δομή HList και μια εγγραφή InRec.
   Λειτουργία: Εισάγει την εγγραφή InRec στη λίστα List, αν δεν είναι γεμάτη,
                και ενημερώνει τη δομή HList.
   Επιστρέφει: Την τροποποιημένη δομή HList.
   Έξοδος:     Μήνυμα γεμάτης λίστας, αν η List είναι γεμάτη, διαφορετικά,
                αν υπάρχει ήδη εγγραφή με το ίδιο κλειδί,
                εμφάνιση αντίστοιχου μηνύματος
*/
{
	int Loc, Pred, New, HVal;

   // New=0;
	if(!(FullHashList(*HList)))
	{
		Loc=-1;
		Pred=-1;

		SearchHashList(*HList,InRec.RecKey,&Loc,&Pred);
		if(Loc==-1)
		{
            HList->Size=HList->Size +1;
			New=HList->StackPtr;
			HList->StackPtr=HList->List[New].Link;
			HList->List[New] = InRec;
			if (Pred==-1)
			{
			    HVal=HashKey(InRec.RecKey);
                HList->HashTable[HVal]=New;
				HList->List[New].Link=EndOfList;
			}
			else
			{
                HList->List[New].Link=HList->List[Pred].Link;
				HList->List[Pred].Link=New;
			}
		}

		else
		{
			printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
		}
	}
	else
	{
		printf("Full list...");
	}
}
void DeleteRec(HashListType *HList,KeyType DelKey)
/* DEXETAI:    TH DOMH (HList) KAI To KLEIDI (DelKey) THS EGGRAFHS
               POY PROKEITAI NA DIAGRAFEI
   LEITOYRGIA: DIAGRAFEI, THN EGGRAFH ME KLEIDI (DelKey) APO TH
               LISTA (List), AN YPARXEI ENHMERWNEI THN DOMH HList
   EPISTREFEI: THN TROPOPOIHMENH DOMH (HList)
   EJODOS:     "DEN YPARXEI EGGRAFH ME KLEIDI" MHNYMA
*/
{
	int Loc, Pred, HVal;

	SearchHashList(*HList,DelKey,&Loc,&Pred);
	if(Loc!=-1)
	{
		if(Pred!=-1)
		{
			HList->List[Pred].Link=HList->List[Loc].Link;
		}
		else
		{
			HVal=HashKey(DelKey);
		    HList->HashTable[HVal]=HList->List[Loc].Link;
		}
		HList->List[Loc].Link=HList->StackPtr;
		HList->StackPtr=Loc;
		HList->Size=HList->Size -1;
	}
	else
	{
		printf("DEN YPARXEI  EGGRAFH ME KLEIDI %s \n",DelKey);
	}
}

void PrintPinakes(HashListType HList)
{
    int i;
	printf("Hash table\n");
	for (i=0; i<HMax;i++)
              printf("%d,",HList.HashTable[i]);

	printf("\nHash List\n");
    for (i=0;i<HList.Size;i++)
	   printf("%d) %s, %d\n",i,HList.List[i].RecKey,HList.List[i].Link);
	printf("\n");
}

