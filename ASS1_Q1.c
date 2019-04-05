#include<stdio.h>
#include<stdlib.h>

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

void Push(node** S, numop* key){
    node* new=malloc(sizeof(node));
    new->record=key;
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
    int Q,instruct,numb,i;
    char ope;
    scanf("%d",&Q);
    for(i=0;i<Q;i++){
        scanf("%d",&instruct);
        if(instruct==1){
            scanf("%d",&numb);
            numop* new1=CreateRecord();
            new1->type='n';
            new1->num=numb;
            Push(&ST,new1);
            printf("$\n");
        }
        else if(instruct==2){
            scanf(" %c",&ope);
            numop* new2=CreateRecord();
            new2->type='o';
            new2->op=ope;
            Push(&ST,new2);
            printf("$\n");
        }
        else if(instruct==3){
            if(IsEmpty(ST)){
                printf("error\n");
            }
            else{
                if(Top(ST)->type=='n'){
                    printf("%f\n",Top(ST)->num);
                }
                else if(Top(ST)->type=='o'){
                    printf("%c\n",Top(ST)->op);
                }
            }
        }
        else if(instruct==4){
            IsEmpty(ST)?printf("True\n"):printf("False\n");
        }
        else if(instruct==5){
            if(IsEmpty(ST)){
                printf("error\n");
            }
            
            else{
                if(Top(ST)->type=='n'){
                    printf("%f\n",Top(ST)->num);
                }
                else if(Top(ST)->type=='o'){
                    printf("%c\n",Top(ST)->op);
                }
                Pop(&ST);
            }
            }
        
    }
    return 0;
}
