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
int insertionSort(const book *ptr);
int find0 (const book *ptr,const long unsigned int AEM,int *search);

void clear (book *ptr);
int  add (book *ptr,const long unsigned int AEM,const char name[],const short unsigned int mathima,const int K);
int find (const book *ptr,const long unsigned int AEM);
int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima);
void print (const book *ptr);
int rmv (book *ptr,const long unsigned int AEM,const int K);
void sort (book *ptr);
void quit (book *ptr);

int main(int argc ,char *argv[]){
    int M=0,K=0,i=0,maxs;
    book univer,*books;
    student *ptr;
    long unsigned int AEM;
    char NAME[64];
    char menu;
    short unsigned int MATHIMA;

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
    while (1){
    
        scanf("%c",&menu);
        switch (menu)
        {
            case 'a':
                scanf("%lu %s %hu",&AEM,NAME,&MATHIMA);
                maxs=strlen (NAME);
                for(i=0; i<maxs;i++){
                    NAME[i]=toupper(NAME[i]);
                }
                add(books,AEM,NAME,MATHIMA,K);
                break;
            
            case 'r':
                scanf("%lu",&AEM);
                rmv(books,AEM,K);
                break;

            case 'm':
                scanf("%lu %hu",&AEM,&MATHIMA);
                mod(books,AEM,MATHIMA);
                break;
                
            case 's':
                sort(books);
                break;

            case 'f':
                scanf("%lu",&AEM);
                find(books,AEM);
                break;

            case 'p':
                print(books);
                break;

            case 'c':
                clear(books);
                break;
                
            case 'q':
                quit(books);
                return 0;
        }
    }
}

void clear (book *ptr){
    free( ptr->students );
    ptr->size = 0;
    ptr->full = 0;
    ptr->tax=-1;
    printf("\nC-OK\n");
}

int  add (book *ptr,const long unsigned int AEM, const char name[],const short unsigned int mathima,const int K){
    int i=0,j,*p,k;
    student *nptr,*tptr;// gia na min xaso ta idei apothikeymena

    p=&i;
    if(ptr->tax == -1){
        nptr = (student *) malloc(K*sizeof(student));
        if(nptr == NULL){
            printf("\nA-NOK %lu, %d %d\n",AEM,ptr->full,ptr->size);
            return 0;
        }
        ptr->students = nptr;
        for(i=0;i<K;i++){
            ptr->students[i].aem=0; 
        }
        ptr->size=K;
        ptr->full = 0;
        ptr->tax=0;

    }

    j=find0(ptr,AEM,p);

    if(j!=-1 ){
        printf("\nA-NOK %lu, %d %d\n",AEM,ptr->full,ptr->size);
        return 0;
    }
                 
    if(ptr->size==ptr->full )
    {//auxisi pinaka kai elenxos ean petixe
        k=ptr->size;
        tptr =(student*) realloc (ptr->students,(ptr->size+K)*sizeof(student) );
        if (tptr == NULL){
            printf("\nA-NOK %lu, %d %d\n",AEM,ptr->full,ptr->size);
            return 0;
        }
        else{
           for ( i =ptr->size ; i < (ptr->size + K); i++)
            {// fia midenismo ton neon
                tptr[i].aem =0;
            }
                ptr->size = k + K;
                ptr->students = tptr;                  
        }
    }      
      
    if (ptr->students[ptr->full].aem == 0)
    {  // PROTHIKI
        ptr->students[ptr->full].aem = AEM;
        strcpy(ptr->students[ptr->full].name,name);
        ptr->students[ptr->full].mathima = mathima;
        ptr->tax = 0;
        ptr->full=ptr->full+1;
        printf("\nA-OK %lu, %d %d\n",AEM,ptr->full,ptr->size);
        return 1;
    }
        
    printf("\nA-NOK %lu, %d %d\n",AEM,ptr->full,ptr->size);
    return 0;
}

int find0 (const book *ptr,const long unsigned int AEM,int *search){
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

int linear_search (const book *ptr,const long unsigned int AEM,int *search){
    int i;

    for ( i = 0; i <= ptr->full; i++)
    {
        *search=*search+1;
        if (ptr->students[i].aem == AEM){
           return i;
        }      
    }
    return -1;
}

int binary_search (const book *ptr,const long unsigned int AEM,int *search){
    int  low=0,high,mid;
    
    high=ptr->full-1;
    while(low<=high)
    {
        mid=(low + high)/2;
        *search=*search+1;
        if (ptr->students[mid].aem==AEM)
        {
            return mid;
        }
        *search=*search+1;
        if (ptr->students[mid].aem<AEM)
        {
            low=mid+1;
        }
        
        else {
           high=mid-1;
        }
        
    }          
    return (-1);
}

int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima){
    int i,*p;
    p=&i;

    i=find0(ptr,AEM,p);
    if ( ptr->students[i].aem==AEM){
        ptr->students[i].mathima = mathima;
        printf("\nM-OK %lu\n",AEM );
        return 0;
    }
    printf("\nM-NOK %lu\n",AEM );
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
    i=find0(ptr,AEM,p);
    if (i!= -1){
        j=ptr->full-1;
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
                printf("\nR-NOK %lu, %d %d\n",AEM,ptr->full,ptr->size);
                return 0;
            }
            ptr->size=k-K;
            ptr->students = tptr;
        }
        ptr->tax=0;
        ptr->full=ptr->full-1;  
        printf("\nR-OK %lu, %d %d\n",AEM,ptr->full,ptr->size);
        return 0;
    }
    printf("\nR-NOK %lu, %d %d\n",AEM,ptr->full,ptr->size);
    return 0;
}

void sort (book *ptr){
    int j;
    j = insertionSort(ptr);
    fprintf(stderr,"\n$%d\n",j);
    printf("\nS-OK\n");
    ptr->tax= 1;
}

int insertionSort(const book *ptr){
    int i, j,k=0,search = 0;
    student key ;
     
    for (i = 1; i < ptr->full; i++) { 
        key.aem = ptr->students[i].aem;
        strcpy(key.name,ptr->students[i].name);
        key.mathima=ptr->students[i].mathima; 
  
        k=0;
        for(j = i - 1;(j >= 0) && (ptr->students[j].aem > key.aem);j--) { 
            ptr->students[j+1].aem  =  ptr->students[j].aem; 
            strcpy(ptr->students[j+1].name, ptr->students[j].name);
            ptr->students[j+1].mathima = ptr->students[j].mathima;
            k=1;      
        } 
       
        search=search+i-j-k;
        ptr->students[j+1].aem = key.aem; 
        strcpy(ptr->students[j+1].name,key.name);
        ptr->students[j+1].mathima=key.mathima; 
    } 
    return search;
} 

int find (const book *ptr,const long unsigned int AEM){
    int i,j=0,*p;
    p=&j;
    i=find0(ptr,AEM,p);
    if (i!=-1) {
        printf("\nF-OK %s %u\n",ptr->students[i].name, ptr->students[i].mathima);
        fprintf(stderr,"\n$%d\n",*p );
    }
    else{
        printf("\nF-NOK %lu\n",AEM );
        fprintf(stderr,"\n$%d\n",*p );
    }
    return 0;
}
void quit (book *ptr){
    free( ptr->students );
}