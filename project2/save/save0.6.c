#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>

struct list {
    unsigned short int code_math ;
    struct list *next;
};

typedef struct {
    long unsigned int aem;
    char name[64];
    short unsigned int mathima;// ta xrostoymena mathimata
    struct list *cource;
    struct student *prev;
    struct student *next;
} student;

typedef struct 
{
   student *students;
   int size;
   int full;
   int tax; //gia na do ean einai taxinomimenos o pinakas
   int ply;
   int max_hash;
   int min_hash;
} book;

// my function project 2
int dlt_lst (book *ptr,const int i);
int add_list_2(student *pr,student *ne);
int rmv_list_2(student *dell); // not used free 
int find_list_2(student *frst, char name[],int metritis);
void print_list_2(student *ptr);
unsigned long hash(char *str);
int add_hash(book *ptr,student *hasht,student *ne);
int rmv_hash(book *ptr,student *hasht,student *del);

// my function project 1
int linear_search (const book *ptr,const long unsigned int AEM,int *search);
int binary_search (const book *ptr,const long unsigned int AEM,int *search);
int insertionSort(const book *ptr);
int find0 (const book *ptr,const long unsigned int AEM,int *search);

// function project 2
int reg (book *ptr, const long unsigned int AEM , unsigned short code);
int unreg (book *ptr, const long unsigned int AEM , unsigned short code);
int isreg (book *ptr, const long unsigned int AEM , unsigned short code);
int list_cource (book *ptr, const long unsigned int AEM );
int find_by_name (book *ptr ,student *hash, char name[]);

// function project 1
void clear (book *ptr,student *hasht);
int  add (book *ptr,student *hasht,const long unsigned int AEM,const char name[],const short unsigned int mathima,const int K);
int find (const book *ptr,const long unsigned int AEM);
int mod (book *ptr,const long unsigned int AEM,const short unsigned int mathima);
void print (const book *ptr);
int rmv (book *ptr,student *hasht,const long unsigned int AEM,const int K);
void sort (book *ptr);
void quit (book *ptr,student *hasht);

int main(int argc ,char *argv[]){
    int M=0,K=0,H=0,i=0,maxs;
    book univer,*books;
    student *ptr,*hasht;
    long unsigned int AEM;
    char NAME[64];
    char menu;
    short unsigned int MATHIMA,cources;

    M=atoi(argv[1]);
    K=atoi(argv[2]);
    H=atoi(argv[3]);

//desmesi kai arxikopoisi tou pinaka
    if (M>0)
    {
        ptr = (student *) malloc(M*sizeof(student));
        univer.students = ptr;
        books = &univer;
        for(i=0;i<M;i++){
            books->students[i].aem = 0; 
            books->students[i].cource = NULL;
        }
        books->size = M;
        books->full = 0;
        books->tax = 0;
        books->ply = 0;
        books->max_hash = H;
        books->min_hash = H;
    }
    else
    {
        ptr = NULL;
        univer.students = ptr;
        books = &univer;
        books->size=M;
        books->full = 0;
        books->tax=-1;
        books->ply = 0;
        books->max_hash = H;
        books->min_hash = H;
    }
    hasht = (student *) malloc(H*sizeof(student));
        

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
                add(books,hasht,AEM,NAME,MATHIMA,K);
                break;
            
            case 'r':
                scanf("%lu",&AEM);
                rmv(books,hasht,AEM,K);
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
                clear(books,hasht);
                break;
                
            case 'g':
                scanf("%lu %hu",&AEM,&cources);
                reg(books,AEM,cources);
                break;

            case 'u':
                scanf("%lu %hu",&AEM,&cources);
                unreg(books,AEM,cources);
                break;

            case 'i':
                scanf("%lu %hu",&AEM,&cources);
                isreg(books,AEM,cources);
                break;
            
            case 'l':
                scanf("%lu ",&AEM);
                list_cource(books,AEM);
                break;
                
            case 'n':
                scanf("%s",NAME);
                find_by_name(books,hasht,NAME);
                break;
            
            case 'q':
                quit(books,hasht);
                return 0;
        }
    }
}

void clear (book *ptr,student *hasht){
    int i;
    for (i = 0; i < ptr->full; i++)
    {
        dlt_lst(ptr,i);
    }
    free(hasht);
    free( ptr->students );
    ptr->size = 0;
    ptr->full = 0;
    ptr->tax=-1;
    printf("\nC-OK\n");
}

int  add (book *ptr,student *hasht,const long unsigned int AEM, const char name[],const short unsigned int mathima,const int K){
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
            ptr->students[i].cource = NULL; 
        }
        ptr->size=K;
        ptr->full = 0;
        ptr->tax=0;
        ptr->ply=0;
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
                tptr[i].cource = NULL;
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
        tptr = &ptr->students[ptr->full];
        add_hash(ptr,hasht, tptr);
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

    for ( i = 0; i < ptr->full; i++)
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
    if (i!=-1){
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

int rmv (book *ptr,student *hasht,const long unsigned int AEM,const int K){
    int i,j,k,*p,max;
    student *tptr;

    p=&i;
    k=ptr->size;
    i=find0(ptr,AEM,p);
    if (i!= -1){
        tptr = &ptr->students[ptr->full];
        rmv_hash(ptr,hasht,tptr);
        dlt_lst(ptr,i);
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

void quit (book *ptr,student *hasht){
    free( ptr->students );
    free(hasht);
}

// function project 2
int reg (book *ptr, const long unsigned int AEM , unsigned short code){
    int i=0,*j;
    struct list *lis,*nxt,*pr;

    j = &i;
    i = find0(ptr,AEM,j);
    if (ptr->students[i].aem == AEM){
        if (ptr->students[i].cource == NULL){
            lis = (struct list *) malloc(sizeof(struct list));
            ptr->students[i].cource = lis;
            printf("\nG-OK %lu %hu\n",AEM,code);
            return 0;
        }

        lis = ptr->students[i].cource;
        while (1){
            if ( lis->code_math == code){
                printf("\nG-NOK %hu\n",code);
                return 0;
            }
            if ((lis->code_math - code) < 0){
                pr = lis;
                lis = lis->next;
                continue;
            }
            nxt = lis;
            lis = (struct list *) malloc(sizeof(struct list));
            lis->code_math = code;
            lis->next = nxt; 
            pr->next = lis; 
            printf("\nG-OK %lu %hu\n",AEM,code);
        }    
    }
    printf("\nG-NOK %lu\n",AEM);
    return 0;
}

int unreg (book *ptr, const long unsigned int AEM , unsigned short code){
    int i=0,*j;
    struct list *lis,*nxt,*pr;

    j = &i;
    i = find0(ptr,AEM,j);
    if (ptr->students[i].aem == AEM){
        while (1){
            if ( lis->next == NULL){
                printf("\nU-NOK %hu\n",code);
                return 0;
            }
            if ( lis->code_math == code){
                nxt = lis->next;
                pr->next = nxt;
                free(lis);
                printf("\nU-OK %lu %hu\n",AEM,code);
                return 0;
            }
            pr = lis;
            lis = lis->next;
        }     
    }
    printf("\nU-NOK %lu\n",AEM);
    return 0;
}

int isreg (book *ptr, const long unsigned int AEM , unsigned short code){
    int i=0,*j;
    struct list *lst;

    j=&i;
    i=find0(ptr,AEM,j);
    if (ptr->students[i].aem == AEM)
    {
        lst = ptr->students[i].cource;
        while (1)
        {      
            if (lst == NULL)
            {
                printf("NO");   
                return 0;
            }
            if (lst->code_math == code)
            {
                printf("YES");
                return 0;
            }
            lst = lst->next;
        }
    }
    printf("\nI-NOK %lu \n",AEM);
    return 0;
}

int list_cource (book *ptr, const long unsigned int AEM ){
    int i=0,*j;
    struct list *lst;

    j=&i;
    i=find0(ptr,AEM,j);
    if (ptr->students[i].aem == AEM)
    {
        printf("L-OK %s",ptr->students[i].name);
        lst = ptr->students[i].cource;
        for (; lst!=NULL ; lst = lst->next)
        {
            printf("%hu",lst->code_math);
        }
        return 0;
    }
    printf("L-NOK %lu",AEM);
    return 0;
}

int dlt_lst( book *ptr,const int i){
    struct list *lis,*nxt;

    lis = ptr->students[i].cource;
    while (1){
        if ( lis == NULL){
            return 0;
        }
        nxt = lis->next;
        free(lis);
        lis = nxt;     
    }
}

int add_list_2(student *pr,student *ne){
    struct student *nxt,*prt,*neo;

    prt = (struct student *) pr;
    neo = (struct student *) ne;
    
    nxt = prt->next;

    prt->next = neo;
    neo->next = nxt;
    neo->prev = prt;
    nxt->prev = neo;

    return 0;
}

int rmv_list_2(student *dell){
    struct student *nxt,*prv,*del;

    del = (struct student *) dell;
    prv= del->prev;
    nxt = del->next;
    prv->next = nxt;
    
    return 0;
}

int find_list_2(student *frst, char name[],int metritis){
    struct student *lst, *head;


    lst = (struct student *)frst;
    head = lst;
    while (1)
    {   
        metritis++;
        if (!strcmp(lst->name,name))
        {
            frst = (student *)lst;
            return 1;
        }

        metritis++;
        if (strcmp(lst->name,name)>0)
        {
            return 0;
        }

        lst = lst->next;
        metritis++;
        if (lst == head)
        {
        return 0;
        }
    }
}

void  print_list_2(student *ptr){
    printf("\n%lu %hu\n",ptr->aem,ptr->mathima);
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int add_hash(book *ptr ,student *hasht,student *ne){
    unsigned long int k;
    int i,new, LF;
    char *name;
    struct student *next,*neo,*new_hash, *head ;
    
    name = ne->name;
    k = hash(name)/ptr->max_hash;
    next = (struct student *) hasht;
    neo = (struct student *) ne;
    *next = *next + k;
    head = next;
    
    while(1)
    {
        if (next == head)
        {
            break;
        }
        if (!strcmp(next->name,ne->name))
        {//idio onoma
            while(1){
                if (next->aem<ne->aem)
                {
                    next = next->next;
                    continue ;
                }
                if (next->aem>ne->aem){
                    break;
                }
            }
            break;
        }
        if (strcmp(next->name,ne->name)>0)
        {
            next=next->next;
            continue ;
        }
        else{
            break;   
        }
    }  
    
    LF = (ptr->ply + 1)/ptr->max_hash;
    if (LF < 4)
    {
        add_list_2((student *)next,ne);
        ptr->ply++;
        return 1;
    }
    else
    {//gia ayjisi toy pinaka
        new_hash = (struct student *) malloc((ptr->max_hash * 2)*sizeof(student));
        if(new_hash == NULL){
            printf("NO space");
            return 0;
        }
        new=ptr->max_hash;
        ptr->max_hash=ptr->max_hash*2;

        for ( i = 0; i < new; i++)
        {   
            neo = (struct student *) hasht;
            neo = *neo + 1;
            head = neo;
            
            while(1)
            {
                if(neo == head){
                    break;
                }
                next = neo->next;
                neo->next = NULL;
                neo->prev = NULL;
                add_hash(ptr,(student *)new_hash,(student *)neo);
                neo = next;
            }
        }
        
        free(hash);
        hasht = (student *) new_hash;
        add_hash(ptr,hasht,ne);
        ptr->ply++;

        return 1;
    }
}

int rmv_hash(book *ptr,student *hash,student *del){
    int i,j,max,pply , LF;
    struct student *next,*neo,*new_hash,*head;
    
    rmv_list_2(del);
    ptr->ply = ptr->ply -1;
    LF = ptr->ply/ptr->max_hash;

    if(LF == 1){
        if(ptr->min_hash == ptr->max_hash){
            return 0;
        }
        
        new_hash = (struct student *) malloc((ptr->max_hash / 2)*sizeof(student));
        if(new_hash == NULL){
            printf("NO space");
            return 0;
        }
        max=ptr->max_hash;
        ptr->max_hash=ptr->max_hash*2;
        pply=ptr->ply;
        neo = (struct student *)hash;

        for ( i = 0; i < max; i++)
        {   
            neo = *neo + 1;
            head = neo;
            for (j = 0; j < pply; j++)
            {
                if(neo == head){
                    break;
                }
                next = neo->next;
                neo->next = NULL;
                neo->prev = NULL;
                add_hash(ptr,(student *)new_hash,(student *)neo);
                neo = next;
            }
        }

        free(hash);
        hash = (student *)new_hash;
    }
    return 0;
}

int find_by_name(book *ptr,student *hasht, char name[]){
    unsigned long int k;
    int i ,metritis=0;
    struct student *head,*next;

    k = hash(name)/ptr->max_hash;
    head = (struct student *) hasht;
    head = *head + k; 
    i = find_list_2((student *)head,name,metritis++);
    if(i==0){
        printf("N-NOK %s",name);
        return 0;
    }   

    printf("N-OK %s",name);
    while (1)
    {
        printf("%lu %hu",head->aem,head->mathima);
        next = (struct student *)head->next;
        if(strcmp(next->name,name)){
            return 0;
        }
    }
    return 1;
}

/*      struct timespec start, end;
        unsigned long elapsed_time;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        // κώδικας που θέλουμε να χρονομετρήσουμε
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000
                + (end.tv_nsec - start.tv_nsec) / 1000;
        fprintf(stderr, "%lu microseconds\n", elapsed_time);
        */