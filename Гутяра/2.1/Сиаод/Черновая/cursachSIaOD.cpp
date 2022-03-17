#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
using namespace std;

int N = 4000;
int VR=0;
int HR=0;

struct record {
	//struct record* next;
    char a[30];
    short int b;
    char c[22];
    char d[10];
};



struct Ochered {
    Ochered *next;
    record Data;
    int b;
};


struct queue {
    Ochered *head;
    Ochered *tail;
};

void queueInit(queue *Q) {
    Q->head = NULL;
    Q->tail = (Ochered *)&(Q->head);
}

void moveElement(Ochered **head, queue *Q) {
    Q->tail->next = *head;
    Q->tail = *head;
    *head = (*head)->next;
    Q->tail->next = NULL;
}

 int lessOrEqual(Ochered *a, Ochered *b) {
    
    if(a->Data.d[0]<b->Data.d[0]) return 1;
    if(a->Data.d[0]>b->Data.d[0]) return -1;
    if(a->Data.d[1]<b->Data.d[1]) return 1;
    if(a->Data.d[1]>b->Data.d[1]) return -1;
    if(strcmp(a->Data.a,b->Data.a)<0) return 1;
    if(strcmp(a->Data.a,b->Data.a)>0) return -1;
    return 0;
}

void merge(Ochered **a, Ochered **b, int *q, queue *c, int *r) {
    while (*q != 0 && *r != 0) {
        if (lessOrEqual(*a, *b)>=0) {
            moveElement(a, c);
            (*q)--;
        } else {
            moveElement(b, c);
            (*r)--;
        }
    }
    while (*q > 0) {
        moveElement(a, c);
        (*q)--;
    }
    while (*r > 0) {
        moveElement(b, c);
        (*r)--;
    }
}

void split(Ochered **head, Ochered **a, Ochered **b, int *n) {
    Ochered *k, *p;
    *n = 1;
    *a = *head, *b = (*head)->next;
    k = *a, p = *b;
    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
}

void MergeSort(Ochered **head) {
    queue c[2];
    Ochered *a, *b;
    int i, n, m, q, p, r;
    split(head, &a, &b, &n);
    p = 1;
    n=4000;
    while (p < n) {
        queueInit(&c[0]);
        queueInit(&c[1]);
        i = 0;
        m = n;
        while (m > 0) {
            if (m >= p)
                q = p;
            else
                q = m;
            m = m - q;
            if (m >= p)
                r = p;
            else
                r = m;
            m = m - r;
            merge(&a, &b, &q, &c[i], &r);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
        p *= 2;
    }
    c[0].tail = NULL;
    *head = c[0].head;
}


void PrintBD(Ochered *head) {
    Ochered *p = head;
    int k = 0, flag;
    while (k < N - 1) 
    {
        for (int i = 0; i < 20; i++) {
        	if(p==NULL) break;
            cout << k + 1 << "\t" << p->Data.a << "\t" << p->Data.b << "\t"
                 << p->Data.c << "\t" << p->Data.d << endl;
            k++;
            p = p->next;
        }
        cout << ("\nPrint next 20? 1/0\n") << endl;
        cout << ("\nPrint all? 3/0\n") << endl;
        cin >> flag;
        cout << ("\n") << endl;
        if (flag == 3) {
            for (int i = 0; i < 4000; i++) {
            	if(p==NULL) break;
                cout << k + 1 << "\t" << p->Data.a << "\t" << p->Data.b << "\t"
                     << p->Data.c << "\t" << p->Data.d << endl;
                k++;
                p = p->next;
            }
        }
        if (flag == 0)
            break;
    }
}

void FillOchered(Ochered **head, Ochered *tail, FILE *fp) {
    struct record rec;
    struct Ochered *p;
    p = new Ochered;
    fread(&(p->Data), sizeof(record), 1, fp);
    p->next = NULL;
    *head = p;
    tail = p;
    for (int i = 1; i < N; i++) {
        p = new Ochered;
        fread(&(p->Data), sizeof(record), 1, fp);
        tail->next = p;
        tail = p;
    }
    tail->next = NULL;
    
}



int Sravn(Ochered* b,char a[]){
	if(strncmp(b->Data.d,a,2)==0) return 0;
	if(strncmp(b->Data.d,a,2)<0) return 1;
	if(strncmp(b->Data.d,a,2)>0) return -1;

}

 void MakeInd(Ochered* list, Ochered* base[]){ 
	Ochered *p=list;
	for(int i=0;i<4000;i++){
		base[i]=p;
		p=p->next;
	}
} 

Ochered* Search(Ochered* a[], int n, char x[])
{
    int L,R,m;
	L=0;
	R=n-1;
	while(L<R){
		m=(L+R)/2;
		if(Sravn(a[m],x)==1) L=m+1;
		else R=m;
		
	}
	if(Sravn(a[R],x)==0) return a[R];
	else { printf("Elements not found "); return NULL;}
 }

void PrintQue(Ochered* p,char search_key[],Ochered *&head,Ochered *&tail){
 	int k=0;
 	head=p;
 	while(p!=NULL && strncmp(p->Data.d,search_key,2)==0)
        {
        cout << k + 1 << "\t" << p->Data.a << "\t" << p->Data.b << "\t"
                 << p->Data.c << "\t" << p->Data.d << endl;
        tail=p;
		p=p->next;   
        k++;
		}	
 }


struct B2Vertex
{
   record* data;
   int Bal;
   B2Vertex *left;
   B2Vertex *right;
   B2Vertex *next;
};

void B2Next(B2Vertex *&p,Ochered* D){
	if(p==NULL){
		p=new B2Vertex;
		p->data=&D->Data;
		p->next=NULL;
	}
	else B2Next(p->next,D);
}



void B2Insert(B2Vertex *&p,Ochered* D){
	B2Vertex *q;
	if(p==NULL){
		p=new B2Vertex;
		p->data=&D->Data;
		p->left=p->right=p->next=NULL;
		p->Bal=0;
		VR=1;
	}
	else if(p->data->b>D->b){
		B2Insert(p->left,D);
		if(VR==1){
			if(p->Bal==0){
				q=p->left;
				p->left=q->right;
				q->right=p;
				p=q;
				q->Bal=1;
				VR=0;
				HR=1;
			}
			else {p->Bal=0; VR=1; HR=0;}
		}
		else HR=0;
	}
	else if(p->data->b<D->b){
		B2Insert(p->right,D);
		if(VR==1){
			p->Bal=1;
			HR=1;
			VR=0;
		}
		else if(HR==1){
			if(p->Bal==1){
				q=p->right;
				p->Bal=0;
				q->Bal=0;            
				p->right=q->left;
				q->left=p;
				p=q;
				VR=1; // vr-верт проверка hr-гориз. пров.
				HR=0;
			}
			else HR=0;
		}
	}
	else B2Next(p,D);
}
void AddToB2(Ochered* head, Ochered*tail,B2Vertex *&Root){
	if(head!=NULL){
	while(head!=tail){
		B2Insert(Root,head);
		head=head->next;
	} 
	B2Insert(Root,tail);	
	}
}



void PrintB2(B2Vertex *p,int &i,int &x){
	if(p!=NULL){
		if(i%20==0 && x!=110 && i!=0) x=getch();
		if(x==110) return;
		i++;
	 printf("%4d| %s| %5d| %s| %s\n",i,p->data->a,p->data->b,p->data->c,p->data->d);
		PrintB2(p->next,i,x);	
	}
}

void FindB2(B2Vertex *p,int D){
	int i=0,x=0;
	if(p==NULL) printf("Nothing to find");
	else if(p->data->b==D) PrintB2(p,i,x);
	else{
		if(p->data->b<D) FindB2(p->right,D);
		if(p->data->b>D) FindB2(p->left,D);
	}
}
void ObhodRightB2(B2Vertex *p,int &i,int &x){
	if(p!=NULL){
		ObhodRightB2(p->left,i,x);
		PrintB2(p,i,x);
		ObhodRightB2(p->right,i,x);
	}
}

struct sym{
	sym* next;
	float P;	
	unsigned char data;
	int num=0;		
};

struct Queue {
	sym *head;
	sym *tail;
};

struct s1{
	float P;
	unsigned char data;
	int num;
  	float Q;  
 	int L=0;
  	char *C;
};

void LoadToList(sym*&head,unsigned char ch,int &size)
{
	if(head==NULL){
		head=new sym;
		head->data=ch;
		head->num++;
		size++;
		head->next=NULL;
		
	}	
	else if(head->data==ch)
		head->num++;
	else LoadToList(head->next, ch, size);
}

void printinglist(sym* head,int size,int count, int a)
{
	while(head!=NULL)
	{	
		if(a==1)	
		head->P=(float)head->num/count;
		
		printf("\n%c\t%d\t%2.4f ",head->data, head->num,head->P);
		head=head->next;
	}	
}

void StackToQueue (struct sym**head, struct sym **tail) {
	(*tail)->next=*head;
	*tail=*head;
	*head=(*head)->next;
	(*tail)->next=NULL;
}

void MergeS (sym **head_a, sym **head_b, sym **tail, int q, int r) {
	while (q!=0 && r!=0) {
		
		if ((*head_a)->P<=(*head_b)->P) {
			StackToQueue (head_a, tail);	
			q--;
		}
		else {
			StackToQueue (head_b, tail);			
			r--;
		}
	}
	while (q>0) {
		StackToQueue (head_a, tail);		
		q--;
	}
	while (r>0) {
		StackToQueue (head_b, tail);	
		r--;
	}
}

void Split (sym **head, sym **head_a, sym **head_b) {
	sym *k, *p;
	*head_a=*head;
	*head_b=(*head)->next;
	k=*head_a;
	p=*head_b;	
	while (p!=NULL) {
		k->next=p->next;
		k=p;
		p=p->next;	
	}
}

void MergeSort (sym **head, sym **tail, int n) {
	int i, m, q, p=1, r;
	sym *a=NULL, *b=NULL;
	Queue c[2];
	Split (head, &a, &b);
	while (p<n) {
		c[0].tail=(sym*)&c[0].head;
		c[1].tail=(sym*)&c[1].head;
		i=0;
		m=n;
		while (m>0) {
			if (m>=p) q=p;
			else q=m;
			m-=q;
			if (m>=p) r=p;
			else r=m;
			m-=r;
			MergeS (&a, &b, &c[i].tail, q, r);
			i=1-i;
		}
		a=c[0].head;
		b=c[1].head;
		p*=2;
	}
	c[0].tail->next=NULL;
	*head=c[0].head;
}

sym* reversing(sym* head) 
{
	sym* new_head = NULL;
	while (head)
	{
		sym* next = head->next;
		head->next = new_head;
		new_head = head;
		head = next;
	}
	return new_head;
}

void to_array(s1 charac[], sym* head1,int size)
{
	for(int i=0;i<size; i++)
	{	
		charac[i].data=head1->data;	
	//	printf("%c\t",charac2[i].data);	
		charac[i].num=head1->num;
	//	printf("%d\t",charac2[i].num);
		charac[i].P=head1->P;
		//printf("%f\n",charac2[i].P);
		charac[i].C=new char[size];	
		head1=head1->next;
	}
}

int  Med(s1 charac[],int L,int R)
{
	float S_l=0, S_r;int m;
	for(int i=L;i<R;i++)
		S_l+=charac[i].P;
	S_r=charac[R].P;
		m=R;
	while(S_l>=S_r)
	{
		m=m-1;
		S_l=S_l-charac[m].P;
		S_r=S_r+charac[m].P;
		}	
		return m;
}

void coding_Fano(s1 charac[], int L, int R, int k)
{
	int m;
	if(L<R)
	{
		k++;
		 m=Med(charac,L,R);
		for(int i=L; i<=R;i++)
		{
			if(i<=m) 
			{
				charac[i].C[k]='0';
				charac[i].L=charac[i].L+1;
			}
			else{
				charac[i].C[k]='1';
				charac[i].L=charac[i].L+1;
			}	
		}
		coding_Fano(charac, L,m,k);
		coding_Fano(charac, m+1,R,k);	
	}			
}

float totalP(s1 symbols[],float P,int size)
{
	int i=0;
	while(i<size)
	{	
		P+=symbols[i].P;		
		i++;
	}
	return P;	
}



int main() {
//	int D;
//	char k[250];
//	Ochered* base[4000];
//	Ochered* aboba;
//	Ochered *head2, *tail2;
//    FILE *fp;
//    fp = fopen("testBase2.dat", "rb");
//    Ochered *head, *tail;
//    FillOchered(&head, tail, fp);
//    MergeSort(&head);
//    PrintBD(head);
//    printf("Vvedite kluch: ");
//    scanf("%s",&k);
//    MakeInd(head,base);
//    aboba=Search(base,4000,k);
//    PrintQue( aboba,k,head2,tail2);
//
//    int i=0;
//	int x=0;
//     
//    
//    B2Vertex *Root=NULL;
//    
//	AddToB2(head2,tail2,Root);
//	printf("Tree:\n");
//	ObhodRightB2(Root,i,x);
//	printf("What to find: ");
//	scanf("%d",&D);
//	FindB2(Root,D);
	
    FILE *p = fopen("testBase2.dat", "rb");
	unsigned char ch;
 	int count =0,size=0;float H=0,L_av=0,Ptotal=0;
  	sym *head1=NULL, *tail1=(sym*)&head1;
  	if(p==NULL){
 		printf("Can't open file");
 		return 0;
 	}
  	while(fread(&ch, sizeof(unsigned char), 1, p)!=0)
  	{
  			count++;
			LoadToList(head1,ch,size); 
  	}
  	s1 charac[size];
    fclose(p);
 	puts("Char\tNum\tP");
	printinglist(head1,size,count,1);
	
	MergeSort(&head1,&tail1,size);
	head1=reversing(head1);
	puts("\n\n")	;
		printinglist(head1,size,count,0);
	to_array(charac,head1,size);
	coding_Fano(charac, 0,size-1,-1);

	printf("\n\n\n i  Char  P   L  Code\n");
	for(int i=0;i<size;i++){
  		printf(" %3d %c  %.2f  %2d  ",i+1,charac[i].data,charac[i].P,charac[i].L);
  		for(int j=0;j<charac[i].L;j++)
			printf("%c",charac[i].C[j]);
			puts("");
		}
 	for(int i=0;i<size;i++){
  		H+=-charac[i].P*log2f(charac[i].P);
  		L_av+=charac[i].P*charac[i].L;
  	} 
  	printf("\n\nH: %.2f\nL_av: %.2f\nPtotal: %.2f\n",H,L_av,totalP(charac,Ptotal,size)); 

    system("pause");
    return 0;
}
