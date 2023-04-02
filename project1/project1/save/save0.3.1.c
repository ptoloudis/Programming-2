#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
   int tax; //gia na do ean einai taxinomimenos o pinakas
} book;

int linear_search (const book *ptr,const long unsigned int AEM,int search);
int binary_search (const book *ptr,const long unsigned int AEM,int search);
int find0 (const book *ptr);//gia na bro pou einai o teleuteos  mathitis
int insertionSort(const book *ptr, int n);

void clear (book *ptr);
int  add (book *ptr,const long unsigned int AEM,const char name[],const short unsigned int mathima,const int K,int mega);
int find (const book *ptr,const long unsigned int AEM,int search);
int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima);
void print (const book *ptr);
int rmv (book *ptr,const long unsigned int AEM,const int K,int mega);
void sort (book *ptr,int search);

int main(int argc ,char *argv[]){
    int M=0,K=0,i,epistofi,MEGETHOS;
    book *books;
    long unsigned int AEM;
    char NAME[64];
    char menu;
    short unsigned int MATHIMA;



    M=atoi(argv[1]);
    K=atoi(argv[2]);

//desmesi kai arxikopoisi tou pinaka
   books->students = (student *) malloc(M*sizeof(student));
    for(i=0;i<M;i++){
        books->students[i].aem=0; 
    }
    books->size=M;
    books->tax=0;

// programma
    while (1)
    {
        epistofi =0;
        MEGETHOS =0;

        scanf("%c",&menu);
        switch (menu)
        {
            case 'a':
                scanf("%lu %s %u",&AEM,NAME,&MATHIMA);
                epistofi = add(books,AEM,NAME,MATHIMA,K,MEGETHOS);
                if (epistofi == 1)
                {
                    printf("A-OK %lu, %d %d",AEM,MEGETHOS,books->size);
                }
                else
                {
                    printf("A-NOK %lu, %d %d",AEM,MEGETHOS,books->size);    
                }            
                break;
            
            case 'r':
                scanf("%lu",&AEM);
                epistofi = rmv(books,AEM,K,MEGETHOS);
                if (epistofi == 1)
                {
                    printf("R-OK %lu, %d %d\n",AEM,MEGETHOS,books->size);
                }
                else
                {
                    printf("R-NOK %lu %d %d\n",AEM,MEGETHOS,books->size);
                }
                break;

            case 'm':
                scanf("%lu %u",&AEM,&MATHIMA);
                epistofi = mod (books,AEM,MATHIMA);
                if (epistofi == 1)
                {
                    printf("M-OK %lu\n",AEM );
                }
                else
                {
                    printf("M-NOK %lu\n",AEM );
                }
                break;
                
            case 's':
                sort(books,epistofi);
                fprintf(stderr,"$%d\n",epistofi );
                break;

            case 'f':
                scanf("%lu",&AEM);
                epistofi =find(books,AEM,MEGETHOS);
                if (i>=0 && i<books->size) 
                {
                    printf("#\n F-OK %s %u",books->students[epistofi].name, books->students[epistofi].mathima);
                    fprintf(stderr,"$%d\n",MEGETHOS );
                }
                else
                {
                    printf("# F-NOK %lu",AEM );
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

int  add (book *ptr,const long unsigned int AEM, const char name[],const short unsigned int mathima, int K,int mega){
    int keno=0,i;
    student *tptr;// gia na min xaso ta idei apothikeymena

    keno = find0(ptr);

    if(ptr->size==keno)
    {//auxisi pinaka kai elenxos ean petixe
        tptr =(student*) realloc (ptr->students,(ptr->size+K)*sizeof(student) );
        if (tptr == NULL)
        {
            mega = keno;
            return 0;
        }
        else
        {   for ( i =ptr->size ; i < (ptr->size + K); i++)
            {// fia midenismo ton neon
                tptr[i].aem =0;
            }

            ptr->size = ptr->size + K;
            ptr->students = tptr;
            ptr->students[keno].aem = AEM;
            strcpy(ptr->students[keno].name,name);
            ptr->students[keno].mathima = mathima;
            ptr->tax = 0;
            mega = keno+1;
            return 1;
            
        }
        
    }
    
    if (ptr->students[keno].aem == 0)
    {  // PROTHIKI
        ptr->students[keno].aem = AEM;
        strcpy(ptr->students[keno].name,name);
        ptr->students[keno].mathima = mathima;
        ptr->tax = 0;
        mega = keno+1;
        return 1;
    }
    else
    {
        mega = keno;
        return 0;
    }
        
}

int find (const book *ptr,const long unsigned int AEM,int search){
    int i;

    search=0;
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

int linear_search (const book *ptr,const long unsigned int AEM,int search)
{
    int i;

    for ( i = 0; (i <ptr->size) && (ptr->students[i].aem==0) && (AEM != ptr->students[i].aem ); i++)
    {
        search++;
    }
    return i;
}

int binary_search (const book *ptr,const long unsigned int AEM,int search){
    int  low=0,high,mid;
    
    high=find0(ptr);
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
        search++;
    }          
    return (-1);
}

int find0 (const book *ptr){
    int i;
    for ( i = 0; (i < ptr->size) && (ptr->students[i].aem==0); i++);
    return i--;
}

int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima){
    int i;

    i=find(ptr,AEM,0);
    if (i>=0 && i<ptr->size )
    {
        ptr->students[i].mathima = mathima;
        return 1;
    }
    return 0;
}

void print (const book *ptr){
    int i,max;

    printf("\n#\n");
    max=find0(ptr);

    for (i = 0; i < max; i++)
    {
       printf("%lu %s %u",ptr->students[i].aem,ptr->students[i].name,ptr->students[i].mathima); 
    }
}

int rmv (book *ptr,const long unsigned int AEM,const int K,int mega){
    int i,j;
    student *tptr;

    i=find(ptr,AEM,0);
    if ( i>=0 && i<ptr->size  )
    {
        j=find0(ptr);
        ptr->students[i].aem = ptr->students[j].aem;
        strcpy(ptr->students[i].name,ptr->students[j].name);
        ptr->students[i].mathima = ptr->students[j].mathima;
        ptr->students[j].aem = 0;

        if ((ptr->size-j)>K)
        {
            tptr=(student *) realloc(ptr->students,(ptr->size - K)*sizeof(student));
            if (tptr != NULL)
            {
                ptr->students = tptr;
            }
        }
        mega=i-1;  
        return 1;
    }
    mega=i;
    return 0;
}

void sort (book *ptr,int search){
    int i,j;

    i = find0(ptr);
    j = insertionSort(ptr, i);
    search = j;
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
