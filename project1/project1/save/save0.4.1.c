#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
    long unsigned int aem;
    char name[64];
    short unsigned int mathima;
} student;

typedef struct 
{
   student *students;
   int size;
   int full;
   int tax; //gia na do ean einai taxinomimenos o pinakas
} book;

int linear_search (const book *ptr,const long unsigned int AEM,int *search);
int binary_search (const book *ptr,const long unsigned int AEM,int *search);
int insertionSort(const book *ptr, int n);

void clear (book *ptr);
int  add (book *ptr,const long unsigned int AEM,const char name[],const short unsigned int mathima,const int K);
int find (const book *ptr,const long unsigned int AEM,int *search);
int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima);
void print (const book *ptr);
int rmv (book *ptr,const long unsigned int AEM,const int K);
void sort (book *ptr,int *search);

int main(int argc ,char *argv[]){
    int M=0,K=0,i=0,epistofi,maxs,*j;
    book univer,*books;
    student *ptr;
    long unsigned int AEM;
    char NAME[64];
    char menu;
    short unsigned int MATHIMA;
    j=&i;


    M=atoi(argv[1]);
    K=atoi(argv[2]);

//desmesi kai arxikopoisi tou pinaka
    ptr = (student *) malloc(M*sizeof(student));
    univer.students = ptr;
    books = &univer;
    for(i=0;i<M;i++){
        books->students[i].aem=0; 
    }
    books->size=M;
    books->full = 0;
    books->tax=0;

// programma
    while (1)
    {
        epistofi =0;

        scanf("%c",&menu);
        switch (menu)
        {
            case 'a':
                scanf("%lu %s %hu",&AEM,NAME,&MATHIMA);
                maxs=strlen (NAME);
                for(i=0; i<maxs;i++){
                    NAME[i]=toupper(NAME[i]);
                }

                epistofi = add(books,AEM,NAME,MATHIMA,K);
                if (epistofi == 1)
                {
                    printf("\nA-OK %lu, %d %d\n",AEM,books->full,books->size);
                }
                else
                {
                    printf("\nA-NOK %lu, %d %d\n",AEM,books->full,books->size);    
                }            
                break;
            
            case 'r':
                scanf("%lu",&AEM);
                epistofi = rmv(books,AEM,K);
                if (epistofi == 1)
                {
                    printf("\nR-OK %lu, %d %d\n",AEM,books->full,books->size);
                }
                else
                {
                    printf("\nR-NOK %lu, %d %d\n",AEM,books->full,books->size);
                }
                break;

            case 'm':
                scanf("%lu %hu",&AEM,&MATHIMA);
                epistofi = mod(books,AEM,MATHIMA);
                if (epistofi == 1)
                {
                    printf("\nM-OK %lu\n",AEM );
                }
                else
                {
                    printf("\nM-NOK %lu\n",AEM );
                }
                break;
                
            case 's':
                sort(books,j);
                fprintf(stderr,"$%d\n",*j);
                break;

            case 'f':
                scanf("%lu",&AEM);
                epistofi =find(books,AEM,j);
                if (books->students[epistofi].aem == AEM) 
                {
                    printf("\nF-OK %s %u\n",books->students[epistofi].name, books->students[epistofi].mathima);
                    fprintf(stderr,"$%d\n",*j );
                }
                else
                {
                    printf("\nF-NOK %lu\n",AEM );
                }
                break;

            case 'p':
                print(books);
                break;

            case 'c':
                clear(books);
                break;
                
            case 'q':
                clear(books);
                return 0;
        }
    }


}

void clear (book *ptr){
    free( ptr->students );
    ptr->size = 0;
    ptr->tax=0;
}

int  add (book *ptr,const long unsigned int AEM, const char name[],const short unsigned int mathima,const int K){
    int i=0,j,*p,k;
    student *tptr;// gia na min xaso ta idei apothikeymena

    p=&i;

    j=find(ptr,AEM,p);

    if(j==-1 || j<=ptr->full ){
        if(ptr->students[j].aem!=AEM){ 
               
            if(ptr->size==ptr->full )
            {//auxisi pinaka kai elenxos ean petixe
                k=ptr->size;
                tptr =(student*) realloc (ptr->students,(ptr->size+K)*sizeof(student) );
                if (tptr == NULL)
                {
                    return 0;
                }
                else
                {   for ( i =ptr->size ; i < (ptr->size + K); i++)
                    {// fia midenismo ton neon
                        tptr[i].aem =0;
                    }

                    ptr->size = k + K;
                    ptr->students = tptr;
                    ptr->students[ptr->full].aem = AEM;
                    strcpy(ptr->students[ptr->full].name,name);
                    ptr->students[ptr->full].mathima = mathima;
                    ptr->tax = 0;
                    ptr->full=ptr->full+1;
                    return 1;
                    
                }
                
            }
            if (ptr->full == 0)
            {
                ptr->students[0].aem = AEM;
                strcpy(ptr->students[0].name,name);
                ptr->students[0].mathima = mathima;
                ptr->tax = 1;
                ptr->full= 1;
                return 1;
            }
            if (ptr->students[ptr->full].aem == 0)
            {  // PROTHIKI
                ptr->students[ptr->full].aem = AEM;
                strcpy(ptr->students[ptr->full].name,name);
                ptr->students[ptr->full].mathima = mathima;
                ptr->tax = 0;
                ptr->full=ptr->full+1;
                return 1;
            }
        }
    }
    return 0;
}

int find (const book *ptr,const long unsigned int AEM,int *search){
    int i;

    if (ptr->tax == 0)
    {
        i=linear_search(ptr,AEM,search);
    }
    else
    {
        i=binary_search(ptr,AEM,search);
    }
    return i;
}

int linear_search (const book *ptr,const long unsigned int AEM,int *search)
{
    int i;

    for ( i = 0; i <ptr->full; i++)
    {
        if (ptr->students[i].aem != AEM)
        {
           *search=*search+1;
        }  
        if (ptr->students[i].aem == AEM)
        {
           *search=*search+1;
           break;
        }      
    }
    return i;
}

int binary_search (const book *ptr,const long unsigned int AEM,int *search){
    int  low=0,high,mid;
    
    high=ptr->full;
    while(low<=high)
    {
        mid=(low + high)/2;
        if (ptr->students[mid].aem<AEM)
        {
            low=mid+1;
        }
        if (ptr->students[mid].aem>AEM)
        {
           high=mid-1;
        }
        if (ptr->students[mid].aem==AEM)
        {
            return mid;
        }
        *search=*search+1;
    }          
    return (-1);
}

int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima){
    int i,*p;
    p=&i;

    i=find(ptr,AEM,p);
    if ( ptr->students[i].aem==AEM)
    {
        ptr->students[i].mathima = mathima;
        return 1;
    }
    return 0;
}

void print (const book *ptr){
    int i,max;

    printf("\n#\n");
    max=ptr->full;

    for (i = 0; i < max; i++)
    {
       printf("%lu %s %hu\n",ptr->students[i].aem,ptr->students[i].name,ptr->students[i].mathima); 
    }
}

int rmv (book *ptr,const long unsigned int AEM,const int K){
    int i,j,k,*p,max;
    student *tptr;

    p=&i;
    k=ptr->size;
    i=find(ptr,AEM,p);
    if (ptr->students[i].aem==AEM  )
    {
        j=ptr->full;
        ptr->students[i].aem = ptr->students[j].aem;
        strcpy(ptr->students[i].name,ptr->students[j].name);
        ptr->students[i].mathima = ptr->students[j].mathima;
        ptr->students[j].aem = 0;

        max=ptr->size - ptr->full;
        if (max == K)
        {
            tptr=(student *) realloc(ptr->students,(k - K)*sizeof(student));
            if (tptr == NULL)
            {
                return 0;
            }
            ptr->size=k-K;
            ptr->students = tptr;
        }
        ptr->full=ptr->full-1;  
        return 1;
    }
    return 0;
}

void sort (book *ptr,int *search){
    int j;
    j = insertionSort(ptr, ptr->full);
    *search = j;
}

int insertionSort(const book *ptr, int n){
    int i, key, j, search = 0; 
    for (i = 1; i < n; i++) { 
        key = ptr->students[i].aem; 
        j = i - 1; 
  
        while (j >= 0 && ptr->students[j].aem > key) { 
            ptr->students[j+1].aem  =  ptr->students[j].aem; 
            strcpy(ptr->students[j+1].name, ptr->students[j].name);
            ptr->students[j+1].mathima = ptr->students[j].mathima;
            j = j - 1;
            search++; 
        } 
        ptr->students[j+1].aem = key; 
    } 
    return search;
} 
