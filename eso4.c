#include<stdio.h>
#include<stdlib.h>

typedef struct node{
char color;
int value;
struct node* parent;
struct node* lchild;
struct node* rchild;
}node;

int black_height(node* root){
int height=0;
while(root!=NULL){
    if(root->color=='b'){
        height++;
    }
    root=root->rchild;
}
return height;
}

int search(node* root,int key){
int found=0;
while((root!=NULL)&&(!found)){
    if(root->value==key){
        found=1;
    }
    else if(root->value>key){
        root=root->lchild;
    }
    else if(root->value<key){
        root=root->rchild;
    }
}
return found;
}

void search_by(node* root,int key){
int found=0;
while((root!=NULL)&&(!found)){
    if(root->value==key){
        found=1;
    }
    else if(root->value>key){
        root=root->lchild;
    }
    else if(root->value<key){
        root=root->rchild;
    }
}
if(found){
    printf("%c,%d ",root->color,black_height(root));
}
else{
    printf("-1,-1 ");
}
}

void left_rotate(node** root, node* x){
node* y=x->rchild;
x->rchild=y->lchild;
if(y->lchild!=NULL){
    (y->lchild)->parent=x;
}
y->parent=x->parent;
if(x->parent==NULL){
    (*root)=y;
}
else if(x->parent->lchild==NULL){
    (x->parent)->rchild=y;
}
else if(x->parent->lchild==NULL){
    (x->parent)->lchild=y;
}
else if(x==(x->parent)->lchild){
    (x->parent)->lchild=y;
}
else{
    (x->parent)->rchild=y;
}
y->lchild=x;
x->parent=y;
}

void right_rotate(node** root, node* x){
node* y=x->lchild;
x->lchild=y->rchild;
if(y->rchild!=NULL){
    (y->rchild)->parent=x;
}
y->parent=x->parent;
if(x->parent==NULL){
    (*root)=y;
}
else if(x->parent->lchild==NULL){
    (x->parent)->rchild=y;
}
else if(x->parent->rchild==NULL){
    (x->parent)->lchild=y;
}
else if(x==(x->parent)->lchild){
    (x->parent)->lchild=y;
}
else{
    (x->parent)->rchild=y;
}
y->rchild=x;
x->parent=y;
}

node* create_node(){
node* new=malloc(sizeof(node));
return new;
}

void insert(node** root,int val){
if(search(*root,val)){
    return;
}
if(*root==NULL){
    (*root)=create_node();
    (*root)->color='b';
    (*root)->value=val;
    (*root)->parent=NULL;
    (*root)->lchild=NULL;
    (*root)->rchild=NULL;
    return;
}
int found=0;
node* curr=(*root);
node* par;
while(!found){
    if(curr->value==val){
        found=1;
    }
    else if((curr->value)>val){
        par=curr;
        curr=curr->lchild;
        if(curr==NULL){
            (par->lchild)=create_node();
            (par->lchild)->color='r';
            (par->lchild)->value=val;
            (par->lchild)->parent=par;
            (par->lchild)->lchild=NULL;
            (par->lchild)->rchild=NULL;
            curr=par->lchild;
            break;
        }
    }
    else if((curr->value)<val){
        par=curr;
        curr=curr->rchild;
        if(curr==NULL){
            (par->rchild)=create_node();
            (par->rchild)->color='r';
            (par->rchild)->value=val;
            (par->rchild)->parent=par;
            (par->rchild)->lchild=NULL;
            (par->rchild)->rchild=NULL;
            curr=par->rchild;
            break;
        }
    }
}
if(par->color=='b'){
    return;
}

node* unc;
char temp_col;
while(curr!=(*root)&&(par->color=='r')){

    if((par->parent)->lchild==NULL){
        if(par->lchild==NULL){
            temp_col=par->color;
            par->color=(par->parent)->color;
            (par->parent)->color=temp_col;
            left_rotate(root,(par->parent));
            break;
        }
        else if(par->rchild==NULL){
            right_rotate(root,par);
            par=(par->parent);
            curr=par;
        }
        else if(curr==par->lchild){
            right_rotate(root,par);
            par=(par->parent);
            curr=par;
        }
        else{
            temp_col=par->color;
            par->color=(par->parent)->color;
            (par->parent)->color=temp_col;
            left_rotate(root,(par->parent));
            break;
        }
    }
    else if((par->parent)->rchild==NULL){
        if(par->rchild==NULL){
            temp_col=par->color;
            par->color=(par->parent)->color;
            (par->parent)->color=temp_col;
            right_rotate(root,(par->parent));
            break;
        }
        else if(par->lchild==NULL){
            left_rotate(root,par);
            par=(par->parent);
            curr=par;
        }
        else if(curr==par->rchild){
            left_rotate(root,par);
            par=(par->parent);
            curr=par;
        }
        else{
            temp_col=par->color;
            par->color=(par->parent)->color;
            (par->parent)->color=temp_col;
            right_rotate(root,(par->parent));
            break;
        }
    }
    else if(par==(par->parent)->lchild){
        unc=(par->parent)->rchild;
        if(unc->color=='b'){
            if(curr==par->rchild){
                left_rotate(root,par);
                par=(par->parent);
                curr=par;
            }
            else{
                temp_col=par->color;
                par->color=(par->parent)->color;
                (par->parent)->color=temp_col;
                right_rotate(root,(par->parent));
                break;
            }
        }
        else{
            (par->parent)->color='r';
            unc->color='b';
            par->color='b';
            curr=(par->parent);
            par=curr->parent;
        }
    }
    else{
        unc=(par->parent)->lchild;
        if(unc->color=='b'){
            if(curr==par->lchild){
                right_rotate(root,par);
                par=(par->parent);
                curr=par;
            }
            else{
                temp_col=par->color;
                par->color=(par->parent)->color;
                (par->parent)->color=temp_col;
                left_rotate(root,(par->parent));
                break;
            }
        }
        else{
            (par->parent)->color='r';
            unc->color='b';
            par->color='b';
            curr=(par->parent);
            par=curr->parent;
        }
    }
}
(*root)->color='b';
}

void delete_fixup(node** root, node* splice, node* para){
node* uncle;
if(splice==NULL){
    if(para->lchild==NULL){
        //it is splice itself
        uncle=para->rchild;
        if(uncle->color=='r'){
            uncle->color='b';
            para->color='r';
            left_rotate(root,para);
            uncle=para->rchild;
        }
        if(uncle->lchild==NULL){
            if(uncle->rchild==NULL){
                uncle->color='r';
                splice=para;
            }
            else{
                uncle->color=para->color;
                para->color='b';
                uncle->rchild->color='b';
                left_rotate(root,para);
                // splice=*root;
                (*root)->color='b'; return;
            }
        }
        else if(uncle->rchild==NULL){
            if(uncle->lchild==NULL){
                uncle->color='r';
                splice=para;
            }
            else{
                uncle->color='r';
                uncle->lchild->color='b';
                right_rotate(root,uncle);
                uncle=para->rchild;
                uncle->color=para->color;
                para->color='b';
                uncle->rchild->color='b';
                left_rotate(root,para);
            }   (*root)->color='b'; return;
        }
        else if((uncle->lchild->color=='b')&&(uncle->rchild->color=='b')){
            uncle->color='r';
            splice=para;
        }
        else{
            if(uncle->rchild->color=='b'){
                uncle->color='r';
                uncle->lchild->color='b';
                right_rotate(root,uncle);
                uncle=para->rchild;
            }
            uncle->color=para->color;
            para->color='b';
            uncle->rchild->color='b';
            left_rotate(root,para);
            // splice=*root;
            (*root)->color='b'; return;
        }
    }
    else{
        uncle=para->lchild;
        if(uncle->color=='r'){
            uncle->color='b';
            para->color='r';
            right_rotate(root,para);
            uncle=para->lchild;
        }
        if(uncle->rchild==NULL){
            if(uncle->lchild==NULL){
                uncle->color='r';
                splice=para;
            }
            else{
                uncle->color=para->color;
                para->color='b';
                uncle->lchild->color='b';
                right_rotate(root,para);
                // splice=*root;
                (*root)->color='b'; return;
            }
        }
        else if(uncle->lchild==NULL){
            if(uncle->rchild==NULL){
                uncle->color='r';
                splice=para;
            }
            else{
                uncle->color='r';
                uncle->rchild->color='b';
                left_rotate(root,uncle);
                uncle=para->lchild;
                uncle->color=para->color;
            para->color='b';
            uncle->lchild->color='b';
            right_rotate(root,para);
            // splice=*root;
            (*root)->color='b'; return;
            }
        }
        else if((uncle->rchild->color=='b')&&(uncle->lchild->color=='b')){
            uncle->color='r';
            splice=para;
        }
        else{
            if(uncle->lchild->color=='b'){
                uncle->color='r';
                uncle->rchild->color='b';
                left_rotate(root,uncle);
                uncle=para->lchild;
            }
            uncle->color=para->color;
            para->color='b';
            uncle->lchild->color='b';
            right_rotate(root,para);
            // splice=*root;
            (*root)->color='b'; return;
        }
    }
}
while((splice!=*root)&&(splice->color=='b')){
    if(splice==splice->parent->lchild){
        uncle=splice->parent->rchild;
        if(uncle->color=='r'){
            uncle->color='b';
            splice->parent->color='r';
            left_rotate(root,splice->parent);
            uncle=splice->parent->rchild;
        }
        if(uncle->lchild==NULL){
            if(uncle->rchild==NULL){
                uncle->color='r';
                splice=splice->parent;
            }
            else{
                uncle->color=splice->parent->color;
                splice->parent->color='b';
                uncle->rchild->color='b';
                left_rotate(root,splice->parent);
                splice=*root;
            }
        }
        else if(uncle->rchild==NULL){
            if(uncle->lchild==NULL){
                uncle->color='r';
                splice=splice->parent;
            }
            else{
                uncle->color='r';
                uncle->lchild->color='b';
                right_rotate(root,uncle);
                uncle=splice->parent->rchild;
            uncle->color=splice->parent->color;
            splice->parent->color='b';
            uncle->rchild->color='b';
            left_rotate(root,splice->parent);
            splice=*root;
            }
        }
        else if((uncle->lchild->color=='b')&&(uncle->rchild->color=='b')){
            uncle->color='r';
            splice=splice->parent;
        }
        else{
            if(uncle->rchild->color=='b'){
                uncle->color='r';
                uncle->lchild->color='b';
                right_rotate(root,uncle);
                uncle=splice->parent->rchild;
            }
            uncle->color=splice->parent->color;
            splice->parent->color='b';
            uncle->rchild->color='b';
            left_rotate(root,splice->parent);
            splice=*root;
        }
    }
    else{
        uncle=splice->parent->lchild;
        if(uncle->color=='r'){
            uncle->color='b';
            splice->parent->color='r';
            right_rotate(root,splice->parent);
            uncle=splice->parent->lchild;
        }
        if(uncle->rchild==NULL){
            if(uncle->lchild==NULL){
                uncle->color='r';
                splice=splice->parent;
            }
            else{
                uncle->color=splice->parent->color;
                splice->parent->color='b';
                uncle->lchild->color='b';
                right_rotate(root,splice->parent);
                splice=*root;
            }
        }
        else if(uncle->lchild==NULL){
            if(uncle->rchild==NULL){
                uncle->color='r';
                splice=splice->parent;
            }
            else{
                uncle->color='r';
                uncle->rchild->color='b';
                left_rotate(root,uncle);
                uncle=splice->parent->lchild;
            uncle->color=splice->parent->color;
            splice->parent->color='b';
            uncle->lchild->color='b';
            right_rotate(root,splice->parent);
            splice=*root;
            }
        }
        else if((uncle->rchild->color=='b')&&(uncle->lchild->color=='b')){
            uncle->color='r';
            splice=splice->parent;
        }
        else{
            if(uncle->lchild->color=='b'){
                uncle->color='r';
                uncle->rchild->color='b';
                left_rotate(root,uncle);
                uncle=splice->parent->lchild;
            }
            uncle->color=splice->parent->color;
            splice->parent->color='b';
            uncle->lchild->color='b';
            right_rotate(root,splice->parent);
            splice=*root;
        }
    }
}
splice->color='b';
(*root)->color='b';
}

void delete(node** RT,int val){
if(!search(*RT,val)){
    printf("-1 ");
    return;
}
int found=0;
node* root=*RT;
while((root!=NULL)&&(!found)){
    if(root->value==val){
        found=1;
    }
    else if(root->value>val){
        root=root->lchild;
    }
    else if(root->value<val){
        root=root->rchild;
    }
}
node* leaf;
node* splice;
node* para;
if(root->rchild!=NULL){
    leaf=root->rchild;
    while(leaf->lchild!=NULL){
        leaf=leaf->lchild;
    }
    root->value=leaf->value;
    if(leaf->parent->lchild==NULL){
        leaf->parent->rchild=leaf->rchild;
    }
    else if(leaf->parent->rchild==NULL){
        leaf->parent->lchild=leaf->rchild;
    }
    else if(leaf==leaf->parent->lchild){
        leaf->parent->lchild=leaf->rchild;
    }
    else{
        leaf->parent->rchild=leaf->rchild;
    }
    if(leaf->rchild!=NULL){
        leaf->rchild->parent=leaf->parent;
    }
    splice=leaf->rchild;
    para=leaf->parent;
    if(leaf->color=='r'){
        printf("%d ",black_height(*RT));
        (*RT)->color='b';
        return;
    }
}
else{
    if(root==*RT){
        *RT=root->lchild;
        // (*RT)->color='b';
        if(root->lchild!=NULL){
            (*RT)->color='b';
        }
        printf("%d ",black_height(*RT));
        return;
    }
    else{
        if(root->parent->lchild==NULL){
            root->parent->rchild=root->lchild;
        }
        else if(root->parent->rchild==NULL){
            root->parent->lchild=root->lchild;
        }
        else if(root==root->parent->lchild){
            root->parent->lchild=root->lchild;
        }
        else{
            root->parent->rchild=root->lchild;
        }
        if(root->lchild!=NULL){
            root->lchild->parent=root->parent;
        }
        splice=root->lchild;
        para=root->parent;
        if(root->color=='r'){
            printf("%d ",black_height(*RT));
            (*RT)->color='b';
            return;
        }
    }
}
delete_fixup(RT,splice,para);
printf("%d ",black_height(*RT));
}

void print_tree(node *root){
if(root==NULL){
    return;
}
if(root->lchild==NULL){
    printf("children of %d,%c are NIL and ",root->value,root->color);
}
else
{
    printf("children of %d,%c are %d,%c and ",root->value,root->color,root->lchild->value,root->lchild->color);
}
if(root->rchild==NULL){
    printf("NIL \n");
}
else{
    printf("%d,%c \n",root->rchild->value,root->rchild->color);
}
print_tree(root->lchild);
print_tree(root->rchild);
}

int main(){
int N1,N2,N3;
int i;
node* root=NULL;
scanf("%d",&N1);
int ins[N1];
for(i=0;i<N1;i++){
    scanf("%d",&ins[i]);
    insert(&root,ins[i]);
    printf("%d ",black_height(root));
}
// delete(&root,);
 //print_tree(root);
printf("\n");
scanf("%d",&N2);
int del[N2];
for(i=0;i<N2;i++){
    scanf("%d",&del[i]);
    delete(&root,del[i]);
    if(i==N2-3){
        print_tree(root);
    }
}
printf("\n");
scanf("%d",&N3);
int ser[N3];
for(i=0;i<N3;i++){
    scanf("%d",&ser[i]);
    search_by(root,ser[i]);
}
return 0;
}
