#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int N = 4000;

struct record {
    char a[30];
    short int b;
    char c[22];
    char d[10];
};

struct Ochered {
    Ochered *next;
    record Data;
};
//----------------------------------------------------------

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
//----------------------------------

void PrintBD(Ochered *head) {
    Ochered *p = head;
    int k = 0, flag;
    while (k < N - 1) //����� ��
    {
        for (int i = 0; i < 20; i++) {
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

int main() {
    FILE *fp;
    fp = fopen("testBase2.dat", "rb");
    Ochered *head, *tail;
    FillOchered(&head, tail, fp);
    //PrintBD(head);
    MergeSort(&head);
    PrintBD(head);
    system("pause");
    return 0;
}
