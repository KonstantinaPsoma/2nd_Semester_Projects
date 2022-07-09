#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
    int AM;
    int RecNo;
} BinTreeElementType;

typedef struct{
    int AM;
    char surname[20];
    char name[20];
    char gender;
    int year;
    float grade;
}StudentT;

typedef struct BinTreeNode *BinTreePointer;
 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTInorder(BinTreePointer Root);

int BuildBST(BinTreePointer *Root);
void writeNewStudents(BinTreePointer *Root, int *size);
void printStudentsWithGrade(float theGrade);
void PrintStudent(int RecNum);

int main(){
    BinTreePointer Root, LocPtr;
    BinTreeElementType Item;
    int size;
    float given_grade;
    boolean found;

    printf("Q1. Build BST from a file\n");
    size = BuildBST(&Root);

    printf("Q2. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(Root);

    printf("Q3. Write new students, update file and BST\n");
    writeNewStudents(&Root, &size);

    printf("Q4. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(Root);

    printf("Q5. Search for a student\n");
    printf("Give student's code? ");
    scanf("%d", &Item.AM);
    RecBSTSearch(Root, Item, &found, &LocPtr);
    if(found)
        PrintStudent(Item.RecNo);
    else
        printf("The student with code:%d has not been found\n", Item.AM);

    printf("Q6. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(Root);

    printf("Q7. Print students with grades >= given grade\n");
    printf("Give the grade: ");
    scanf("%f", &given_grade);
    printStudentsWithGrade(given_grade);

    return 0;
}

int BuildBST(BinTreePointer *Root){
    FILE *fp;
    int nscan;
    char termch;
    StudentT info;
    BinTreeElementType indexRec;
    int size;

    CreateBST(&Root);
    fp = fopen("foitites.dat", "r");
    size = 0;

    if (fp != NULL){
        while(TRUE){
            nscan = fscanf(fp, "%d,%20[^,],%20[^,],%c,%d,%f,%c", &info.AM, info.name,info.surname, &info.gender, &info.year, &info.grade, &termch);
            if(nscan == EOF)
                break;
            if(nscan!= 7 || termch != '\n')
                printf("Error 1\n");
            else{
                indexRec.AM = info.AM;
                indexRec.RecNo = size;
                RecBSTInsert(Root, indexRec);
                size += 1;
            }
        }
        fclose(fp);
        return size;

    }
}

void writeNewStudents(BinTreePointer *Root, int *size){
    StudentT info;
    char ch;
    BinTreeElementType indexRec;
    BinTreeElementType x;
    BinTreePointer LocPtr;
    boolean found;
    FILE *fp;

    fp = fopen("foitites.dat", "a");
    *size = 0;

    if (fp == NULL)
        printf("Can't open %s\n", "foitites.dat");
    else{
        do{
            printf("Give student's AM? ");
            scanf("%d", &x.AM);
            RecBSTSearch(*Root, x, &found, &LocPtr);
            if(!found){
                info.AM = x.AM;
                indexRec.AM = info.AM;
                printf("Give student surname? ");
                scanf("%s", info.surname);
                getchar();

                printf("Give student name? ");
                scanf("%s", info.name);
                getchar();

                printf("Give student sex F/M? ");
                scanf("%c", &info.gender);

                printf("Give student's registration year? ");
                scanf("%d", &info.year);

                printf("Give student's grade? ");
                scanf("%f", &info.grade);

                indexRec.RecNo = *size;
                RecBSTInsert(Root, indexRec);
                fprintf(fp, "%d,%s,%s,%c,%d,%f", info.AM, info.name,info.surname, info.gender, info.year, info.grade);
                *size += 1;
            }
            else
                printf("%d is already in the file\n", x.AM);

            printf("\nContinue Y/N: ");
            do{
                scanf("%c", &ch);
            } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
        } while (toupper(ch)!='N');
        fclose(fp);
    }
}

void printStudentsWithGrade(float theGrade){
    FILE *fp;
    int nscan;
    char termch;
    StudentT info;

    fp = fopen("foitites.dat", "r");

    if (fp == NULL)
        printf("Can't open %s\n", "foitites.dat");
    else{
        while(TRUE){
            nscan = fscanf(fp, "%d,%20[^,],%20[^,],%c,%d,%f,%c", &info.AM, info.name,
                           info.surname, &info.gender, &info.year, &info.grade, &termch);
            if(nscan == EOF)
                break;
            if(nscan!= 7 || termch != '\n')
                printf("Error\n");
            else{
                if(info.grade >= theGrade)
                    printf("%d,%s,%s,%c,%d,%f", info.AM, info.name,
                           info.surname, info.gender, info.year, info.grade);
            }
        }
        fclose(fp);
    }
}

void PrintStudent(int RecNum){
    FILE *fp;
    int nscan;
    char termch;
    StudentT info;
    int lines;

    fp = fopen("foitites.dat", "r");

    lines =0;
    if (fp == NULL)
        printf("Can't open %s\n", "foitites.dat");
    else{
        while(lines != RecNum){
            nscan = fscanf(fp, "%d,%20[^,],%20[^,],%c,%d,%f,%c", &info.AM, info.name,
                           info.surname, &info.gender, &info.year, &info.grade, &termch);
            if(nscan == EOF)
                break;
            if(nscan!= 7 || termch != '\n')
                printf("Error\n");
            lines += 1;
        }
        if(lines == RecNum + 1)
            printf("%d,%s,%s,%c,%d,%lf", info.AM, info.name, info.surname, info.gender,
                   info.year, info.grade);
    }
    fclose(fp);
}


void CreateBST(BinTreePointer *Root)
/* Λειτουργία: Δημιουργεί ένα κενό ΔΔΑ.
   Επιστρέφει:  Τον μηδενικό δείκτη(NULL) Root
*/
{
    *Root = NULL;
}

boolean BSTEmpty(BinTreePointer Root)
/* Δέχεται:   Ενα ΔΔα με το Root να δείχνει στη ρίζα του.
  Λειτουργία: Ελέγχει αν το ΔΔΑ είναι κενό.
  Επιστρέφει: TRUE αν το ΔΔΑ είναι κενό και FALSE διαφορετικά
*/
{
    return (Root==NULL);
}

void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item)
/* Δέχεται:     Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και ένα στοιχείο Item.
   Λειτουργία:  Εισάγει το στοιχείο Item στο ΔΔΑ.
   Επιστρέφει: Το τροποποιημένο ΔΔΑ με τον δείκτη Root να δείχνει στη ρίζα του
*/
{
    if (BSTEmpty(*Root)) {
        (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        (*Root) ->Data.AM = Item.AM;
        (*Root) ->Data.RecNo = Item.RecNo;
        (*Root) ->LChild = NULL;
        (*Root) ->RChild = NULL;
    }
    else
        if (Item.AM < (*Root) ->Data.AM)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item.AM > (*Root) ->Data.AM)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("TO STOIXEIO EINAI HDH STO DDA\n");
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue,
                    boolean *Found, BinTreePointer *LocPtr)
/* Δέχεται:    Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
   Λειτουργία: Αναζητά στο ΔΔΑ έναν κόμβο με τιμή KeyValue στο πεδίο κλειδί του.
   Επιστρέφει: Η Found έχει τιμή TRUE και ο δείκτης LocPtr δείχνει στον κόμβο που
                περιέχει την τιμή KeyValue, αν η αναζήτηση είναι επιτυχής.
                Διαφορετικά η Found έχει τιμή FALSE
*/
{
    if (BSTEmpty(Root))
        *Found=FALSE;
    else
        if (KeyValue.AM < Root->Data.AM)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue.AM > Root->Data.AM)
                RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
            else
                {
                    *Found = TRUE;
                    *LocPtr=Root;
                }
}


void RecBSTInorder(BinTreePointer Root)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί ενδοδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
    if (Root!=NULL) {
    //    printf("L");
        RecBSTInorder(Root->LChild);
        printf("(%d, %d), ",Root->Data.AM, Root->Data.RecNo);
    //    printf("R");
        RecBSTInorder(Root->RChild);
    }
   // printf("U");
}

