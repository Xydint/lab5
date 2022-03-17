#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define max(a,b)  (((a) > (b)) ? (a) : (b))



int collisionsLP=0;
int collisionsQP=0;
int cLP_total=0;
int cQP_total=0;

struct Tree
{
    int data;
    struct Tree* left;
    struct Tree* right;
};

typedef struct stack
{
   struct stack* next;
   int data;
}st;


void Fillrand(int a[],int n)
{
	int i;
	srand(time(NULL));
	for(i=0;i<n;i++)
		a[i]= rand()%100;	
}

void Printmas(int a[],int n)
{
	printf("\n");
	int i;
	for(i=0;i<n;i++)
	{
		if(a[i]==-1 && (i+1)%15==0)
		printf("|_|\n");
		else if(a[i]==-1 && (i+1)%15!=0)
		printf("|_|\t");
		else if((i+1)%15==0)
		printf("|%d|\n",a[i]);
		else
		printf("|%d|\t",a[i] );
		
	}
}	

 void printlist(st* h)
{
	while(h!=NULL)
	{
		printf("%d ",h->data);
		h=h->next;
	}	
}

st* Hash_Insert_DLmethod(int i, st* head){
	
   st *p=(st*)malloc(sizeof(st));
   p->data=i;
   p->next=head;
   //head->next=p;
   return p;
}

int Hash_Search_DLmethod(int find, st* head){
	st* p;
	int i;
	  	
    p=head;
  	
  	while(p!=NULL){ 
  		if(p->data==find) return i; 
  		i++;
  		p=p->next;          
	  }	
	return -1;
}

void Hash_Insert_OAmethod_LP(int H[],int k, int m)
{	
	collisionsLP=0;	
	int j,i=0;
	do{
		j=(k%m+i)%m;
		if(H[j]==-1)
		{		
			H[j]=k;
			break;
		}
		i++;
		collisionsLP++;
	}while(i<=m);
	cLP_total+=collisionsLP;
}

void Hash_Insert_OAmethod_QP(int H[],int k, int m)
{	
	collisionsQP=0;	
	int j,i=0;
	do{
		j=(k%m+i*i)%m;
		if(H[j]==-1)
		{		
			H[j]=k;
			break;
		}
		i++;
		collisionsQP++;
	}while(i<=m);
	cQP_total+=collisionsQP;
}

int check_IsPrimeNum(int m)
{
	int i;
	for(i=2;i<m;i++)
	{
		if(m%i==0 && m!=i)
		return 0;
	}
	return 1;
}

int TreeSize(Tree* p)
{
	int n=0;
	if(p!=NULL)
	n=1+TreeSize(p->left)+TreeSize(p->right);
	
	return n;
}

int C_Sum(Tree* p)
{
	int s=0;
	if(p!=NULL)
		s=p->data+C_Sum(p->left)+C_Sum(p->right);
	return s;
}

int TreeHeight(Tree* p)
{
	int h=0;
	if(p!=NULL)
		h=1+max(TreeHeight(p->left),TreeHeight(p->right));
	return h;
}

Sum_Of_Paths(Tree* p, int L)
{
	int s=0;
	if(p!=NULL)
		s=L+Sum_Of_Paths(p->left,L+1)+Sum_Of_Paths(p->right,L+1);
	return s;
}

void INfix_PrintTree(Tree* Root)
{
	if(Root==NULL)
	return;
	if(Root->left!=NULL)
	INfix_PrintTree(Root->left);
	printf(" %d ", Root->data);
	if(Root->right!=NULL)
	INfix_PrintTree(Root->right);	
}

int main()
{
  	int n,m,i,h; 
  	float k;
	Tree* a[6];
	srand(time(NULL));
	for(i=0;i<6;i++){
		a[i] = (Tree*)malloc(sizeof(Tree));
		a[i]->data=rand()%100+1;
		a[i]->left=a[i]->right=NULL;
		printf("%d ",a[i]->data);	
	}
	a[0]->right=a[1];
	a[1]->right=a[3]; 
	a[1]->left=a[2]; 	
  	a[3]->left=a[4];
  	a[4]->right=a[5];
	n=TreeSize(a[0]);
	m=C_Sum(a[0]);
	h=TreeHeight(a[0]);
	k=float(Sum_Of_Paths(a[0],1))/float(6);
	printf("\nTree Size= %d Control Sum= %d Tree height= %d Average height= %2.2f\n", n, m, h, k);
	INfix_PrintTree(a[0]);
    return 0;
}
