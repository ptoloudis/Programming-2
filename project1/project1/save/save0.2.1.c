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

int clear (book *ptr);
int  add (book *ptr,const long unsigned int AEM,const char name[],const short unsigned int mathima,int K);
int find (const book *ptr,const long unsigned int AEM,int search);
int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima);
void print (const book *ptr);
int rmv (book *ptr,const long unsigned int AEM);

int main(int argc ,char *argv[]){}

int clear (book *ptr){
    free( ptr->students );
    ptr->size = 0;
    ptr->tax=0;
    return 0;
}

int  add (book *ptr,const long unsigned int AEM, const char name[],const short unsigned int mathima, int K){
    int upar=0,i;
    book *tptr;// gia na min xaso ta idei apothikeymena

    upar=find(ptr, AEM,0);

    if(ptr->size==upar)
    {//auxisi pinaka kai elenxos ean petixe
        tptr =(book*) realloc (ptr,(ptr->size+K)*sizeof(book) );
        if (tptr == NULL)
        {
            return 0;
        }
        else
        {   for ( i =ptr->size ; i < (ptr->size + K); i++)
            {// fia midenismo ton neon
                tptr->students[i].aem =0;
            }

            tptr->size = ptr->size + K;
            ptr = tptr;
            upar = upar+1;
            
        }
        
    }
    
    if (ptr->students[upar].aem == 0)
    {  // PROTHIKI
        ptr->students[upar].aem = AEM;
        strcpy(ptr->students[upar].name,name);
        ptr->students[upar].mathima = mathima;
        ptr->tax = 0;
        return 1;
    }
    else
    {
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
    int i,max;

    max=find0(ptr);
    for ( i = 0; i < ptr->size; i++)
    {
        if (AEM == ptr->students[i].aem )
        {
            return i;
        }
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
    return (-1)
}

int find0 (const book *ptr){
   int i;
   for ( i = 0; i < ptr->size; i++)
   {
       if (ptr->students[i].aem==0)
       {
          break;
       } 
   }
    return i--;
}

int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima){
    int i;

    i=find(ptr,AEM,0);
    if (i!=-1 && i<ptr->size )
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
       printf("%d %s %d",ptr->students[i].aem,ptr->students[i].name,ptr->students[i].mathima); 
    }
}

int rmv (book *ptr,const long unsigned int AEM){
    int i,j;

    i=find(ptr,AEM);
    if (i!=-1 && i<ptr->size )
    {
        j=find0(ptr);
        ptr->students[i].aem = ptr->students[j].aem;
        strcpy(ptr->students[i].name,ptr->students[j].name);
        ptr->students[i].mathima = ptr->students[j].mathima;
        ptr->students[j].aem = 0;
        
        return 1;
    }
    return 0;
}