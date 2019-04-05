#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct numop{
    char type;
    double num;
    char op;
}numop;

typedef struct node{
    numop* record;
    struct node* next;
}node;

node* CreateStack(){
    node* HEAD=NULL;
    return HEAD;
}

int IsEmpty(node* S){
    if(S==NULL){
        return 1;
    }
    return 0;
}

numop* Top(node* S){
    if(S!=NULL){
        return S->record;
    }
    return NULL;
}

numop* CreateRecord(){
    numop* new=malloc(sizeof(numop));
    return new;
}

void Push(node** S, float si){
    numop* a1=CreateRecord();
    a1->type='n';
    a1->num=si;
    node* new=malloc(sizeof(node));
    new->record=a1;
    new->next=*S;
    *S=new;
    return;
}

numop* Pop(node** S){
    numop* new;
    new=(*S)->record;   
    *S=(*S)->next;
    return new;
}

int main()
{
    node* ST=CreateStack();
    
    char s[1000];
    
    int i=0;
    while((s[i]=getchar())!=EOF){
        if(s[i]!=' ')
            i++;
    }
    
    int len=i-1;
    numop* b1,*b2;
    for(i=len;i>=0;i--){
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'){
            b1=Pop(&ST);
            b2=Pop(&ST);
            if(s[i]=='+'){
                Push(&ST,b1->num+b2->num);
            }
            else if(s[i]=='-'){
                Push(&ST,(b1->num)-(b2->num));
            }
            else if(s[i]=='*'){
                Push(&ST,(b1->num)*(b2->num));
            }
            else if(s[i]=='/'){
                Push(&ST,(b1->num)/(b2->num));
            }
        }
        else{
            Push(&ST,(int)s[i]-48);
        }
        
    }
    printf("%f\n",(Top(ST))->num);
    return 0;
}
