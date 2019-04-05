#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int element;
    int set;
    struct node* next;
}record;

int Find(int a, record* E){
    return (E+a)->set;
}

int Union(int a, int b, record* E, record** Set, int* size){
    int j=(E+a)->set;
    int k=(E+b)->set;
    int i,temp;
    if(j==k){
        return 0;
    }
    if(j>k){
        temp=j;
        j=k;
        k=temp;
    }

    record* node=*(Set+j);
    for(i=0;i<*(size+j);i++){
        node->set=k;
        node=node->next;
    }
    (*(Set+i-1))->next=*(Set+k);
    *(Set+k)=*(Set+j);
    *(Set+j)=NULL;
    *(size+j)=0;
    *(size+k)=j+k;

    return 1;
}

int Same(int a, int b, record* E){
    if((E+a)->set==(E+b)->set){
        return 1;
    }
    return 0;
}

int main(){
    int m,n,i,operation;
    int a,b;
    scanf("%d %d",&n,&m);
    record* E=malloc(n*sizeof(record));
    record* Set[n];
    int size[n];
    for(i=0;i<n;i++){
        (E+i)->element=i;
        (E+i)->set=i;
        (E+i)->next=NULL;
        Set[i]=(E+i);
        size[i]=1;
    }

    for(i=0;i<m;i++){
        scanf("%d ",&operation);
        switch(operation){
            case 1:
                scanf("%d %d",&a,&b);
                printf("%d\n",Union(a,b,E,Set,size));
                break;
            case 2:
                scanf("%d",&a);
                printf("%d\n",Find(a,E));
                break;
            case 3:
                scanf("%d %d",&a,&b);
                printf("%d\n",Same(a,b,E));
                break;        
        }
    }

    return 0;
}