#include<stdio.h>


int xof(int Point[][2],int j){
    return Point[j][0];
}

int yof(int Point[][2],int j){
    return Point[j][1];
}

void merge(int Array[], int Point[][2], int start1, int end1, int end2){
    int start2=end1+1,i,j;
    int l1=end1-start1+1;
    int l2=end2-start2+1;
    int l=l1+l2;

    int temp[l];
    int cnt1=0,cnt2=0;

    for(i=0;i<l;i++){
        if(cnt1==l1){
            temp[i]=Array[end2-cnt2];
            cnt2++;
        }
        else if(cnt2==l2){
            temp[i]=Array[end1-cnt1];
            cnt1++;
        }
        else if(xof(Point,Array[end1-cnt1])>xof(Point,Array[end2-cnt2])){
            temp[i]=Array[end1-cnt1];
            cnt1++;
        }
        else{
            temp[i]=Array[end2-cnt2];
            cnt2++;
        }
    }

    for(j=0;j<l;j++){
        Array[end2-j]=temp[j];
    }
    return;
}

void mergesort(int Array[], int Point[][2], int start, int end){
    if(start>=end){
        return;
    }
    int mid=(start+end)/2;

    mergesort(Array,Point,start,mid);
    mergesort(Array,Point,mid+1,end);

    merge(Array,Point,start,mid,end);
}

int merge_dom(int Array[], int Point[][2], int start1, int end1, int start2, int end2){
    
    int l1=end1-start1+1;
    int l2=end2-start2+1;
    int l=l1+l2;

    int i,cnt1=0,cnt2=0;
    
    while(yof(Point,Array[start2+cnt2])<yof(Point,Array[start1+cnt1])&&cnt1<l1&&cnt2<l2){
        if(xof(Point,Array[start2+cnt2])==xof(Point,Array[start1+cnt1])){
            cnt1++;
            cnt2++;
        }
        else{
        cnt1++;
        }
    }
    
    
    for(i=start1+cnt1;i<start1+cnt1+l2-cnt2;i++){
        Array[i]=Array[start2+cnt2+i-start1-cnt1];
    }

    return start1+cnt1+l2-cnt2-1;
}

int Dominators(int Array[],int Point[][2], int start, int end){
    if(start==end){
        return start;
    }
    int mid=(start+end)/2;
    int l1=Dominators(Array,Point,start,mid);
    int l2=Dominators(Array,Point,mid+1,end);
    int index=merge_dom(Array,Point,start,l1,mid+1,l2);
    
    return index;
}

int main(){
    
    int n,i,j;
    scanf("%d",&n);
    int Point[n][2];
    int A[n];

    for(j=0;j<n;j++){
        scanf("%d %d",&Point[j][0],&Point[j][1]);
        A[j]=j;
    }
    mergesort(A,Point,0,n-1);

    int end=Dominators(A,Point,0,n-1);
    //printf("%d\n",end);
    for(i=0;i<=end;i++){
        printf("%d %d\n",xof(Point,A[i]),yof(Point,A[i]));
        //printf("%d ",A[i]);
    }
    return 0;
}