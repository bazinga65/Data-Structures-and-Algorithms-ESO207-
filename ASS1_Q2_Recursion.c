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

void Push(node** S, char si){
    numop* a1=CreateRecord();
    if(si=='+'||si=='-'||si=='*'||si=='/'){
        a1->type='o';
        a1->op=si;
    }
    else{
        a1->type='n';
        a1->num=si;
    }
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

float Answer(node** S){
    char ope;
    float c1,c2;
    if(Top(*S)->type=='o'){
        char ope=(Top(*S)->op);
        Pop(S);
        c1=Answer(S);
        c2=Answer(S);
        if(ope=='+'){
            return c1+c2;
        }
        else if(ope=='-'){
            return c1-c2;
        }
        else if(ope=='*'){
            return c1*c2;
        }
        else if(ope=='/'){
            return c1/c2;
        }
    }
    
        return Pop(S)->num-48;
    
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
        Push(&ST,s[i]);
    }
    printf("%f\n",Answer(&ST));
    return 0;
}
