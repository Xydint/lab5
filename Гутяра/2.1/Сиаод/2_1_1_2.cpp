#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

struct tData 
{
	char author[12];
	char publisher[16];
	char title[32];
	short int year;
	short int num_of_page;
};

struct st  
{
   struct st* next;
   union{      
   	tData data;   
   	unsigned char digit[sizeof(tData)];  
   };                                  
};                                      

struct Queue { 
	st *head;
	st *tail;
};


void DigitalSort (st **head, st **tail)   
{
	int d, i, j, k, l=28;  
	st *p;             
	                    
	struct Queue q[256];  
	int KDI[l];   
	for(i=0;i<16;i++) 
	KDI[i]=12+i;
	for(i=0;i<12;i++) 
	KDI[16+i]=i;			
	
	for (j=l-1; j>=0; j--)   
    {
		for (i=0; i<256; i++) q[i].tail=(st*)&q[i].head;  
		p=*head;  
		k=KDI[j];    
		while (p!=NULL)   
        {
			d=p->digit[k];
			q[d].tail->next=p;
			q[d].tail=p;
			p=p->next;
		}
		p=(st*)&(*head);
		for (i=0; i<256; i++)   
        {
			if (q[i].tail!=(st*)&q[i].head) 
            {
				p->next=q[i].head;
				p=q[i].tail;
			}
		}
		p->next=NULL;
	}
}

int Sravn(st* b,char a[]){
	if(strncmp(b->data.publisher,a,3)<0) return 1;
	if(strncmp(b->data.publisher,a,3)>0) return -1;
	return 0;

}

st* Search(st* a[], int n, char x[])
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
	else { printf("Elements not found"); return NULL;}
 }
 
 void PrintQue(st* p,char search_key[]){
 	int b=1;
 	while(p!=NULL && strncmp(p->data.publisher,search_key,3)==0)
        {
        cout<<b<<"  "<<p->data.author<<"  "<<p->data.title<<"  "<<p->data.publisher<<"  "<<p->data.year<<"  "<<p->data.num_of_page<<endl;
		p=p->next;   
        b++;
		}		
 }
 
 void MakeInd(st* list, st* base[]){ 
	st *p=list;
	for(int i=0;i<4000;i++){
		base[i]=p;
		p=p->next;
	}
}

int main()
{
	st * list = NULL; 
    st * temp;
	FILE *fp;
	fp=fopen("testBase2.dat", "rb");
	
        for(int i=0;i<4000;i++)
	{
		temp=new st;
		fread(temp->data.author,sizeof(char),12,fp); 
		fread(temp->data.title,sizeof(char),32,fp);
		fread(temp->data.publisher,sizeof(char),16,fp);
		fread(&temp->data.year,sizeof(short int),1,fp);
		fread(&temp->data.num_of_page,sizeof(short int),1,fp);
		temp->next=list; 
		list=temp;
	}
    DigitalSort(&list,&temp);
    st *base[4000];
    temp = list;
    int i=0;
    MakeInd(list, base);
    char search_key[150];
	char ch;
	int k=1;
	st* search;
	int enter=0;
    temp = list;
	i=0;
    do {
	cout<<"1-output of 20 values, 2-output all values, 3-search, 4-exit"<<endl;
	cin>>enter;
	switch (enter)
	{
		case 1:
		i=0;
		k=1;
		while(temp!=NULL)
    	{ 
    	for(int j=0;j<20;j++){  
        cout<<k<<"  "<<temp->data.author<<"  "<<temp->data.title<<"  "<<temp->data.publisher<<"  "<<temp->data.year<<"  "<<temp->data.num_of_page<<endl;
		temp=temp->next;   
        k++;}
        cout<<endl<<"Continue? y/n"; 
        while(1){
        	cin>>ch;  
        	if(ch=='y' || ch=='n' || ch=='Y' || ch=='N') break;
		}
		if(ch=='n' || ch=='N') break;
    	}
    	break;
    	
    	case 2:
		k=1;
    	for(int j=0;j<4000;j++){  
        cout<<k<<"  "<<temp->data.author<<"  "<<temp->data.title<<"  "<<temp->data.publisher<<"  "<<temp->data.year<<"  "<<temp->data.num_of_page<<endl;
		temp=temp->next;   
        k++;}
        break;
        
        case 3:
    	cout<<"Enter search key"<<endl;
        cin>>search_key;
        search=Search(base, 4000, search_key);
        PrintQue(search, search_key);
        
	}
}while(enter!=4);
    while(list!=NULL)
    {
        temp = list->next; 
        free(list); 
        list = temp; 
    }
    return 0;
}

