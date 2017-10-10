#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    void* pData;
    int datatype; // 1 int , 2 char , 3 double
    struct list* pNext;
}*List;
const int listsize=sizeof(struct list);

List listInitilization(); //生成空链表
int listLength(List p); //返回链表长度
void listOutput(List &p); //输出链表内所有内容
void listInsertHead(List &p,void* data,int typ); //从链表头插入
void listInsertTail(List &p,void* data,int typ); //从链表尾插入
void listDelete(List &p,void* data); //删除链表内元素与data内容相同的
void listReverse(List &p); //链表转置
void listDestroy(List &p); //链表清空
void listMerge(List &p,List &q); //链表合并

int main()
{
    int a[3]={2,4,6};
    char b[3]={'a','d','h'};
    double c[3]={3.14,0.5,6.666};

    List p=listInitilization();
    List q=listInitilization();

    listInsertHead(p,&a[0],1);
    listInsertHead(p,&b[0],2);
    listOutput(p);
    printf("List size: %d \n\n",listLength(p));
    listInsertTail(p,&c[0],3);
    listOutput(p);
    printf("List size: %d \n\n",listLength(p));


    listInsertHead(q,&a[1],1);
    listInsertHead(q,&b[1],2);
    listInsertTail(q,&c[1],3);
    listInsertHead(q,&a[2],1);
    listInsertHead(q,&b[2],2);
    listInsertTail(q,&c[2],3);
    listOutput(q);
    printf("List size: %d \n\n",listLength(q));

    listMerge(p,q);
    listOutput(p);
    printf("List size: %d \n\n",listLength(p));

    listDestroy(q);
    listOutput(q);
    printf("List size: %d \n\n",listLength(q));
}

List listInitilization()
{
    List ret=NULL;
    return ret;
}

int listLength(List p)
{
    List now=p;
    int cnt=0;
    while (now!=NULL)
    {
        cnt++;
        now=now->pNext;
    }
    return cnt;
}

void listOutput(List &p)
{
    printf("------------------------------\n");
    List now=p;
    while (now!=NULL)
    {
        if (now->datatype==1) printf("%d  ",*(int*)(now->pData));
        else if (now->datatype==2) printf("%c  ",*(char*)(now->pData));
        else if (now->datatype==3) printf("%lf  ",*(double*)(now->pData));
        now=now->pNext;
    }
    printf("\n------------------------------\n");
    return;
}

void listInsertHead(List &p,void* data,int typ)
{
    List now=(List)malloc(listsize);
    now->pData=data;
    now->pNext=p;
    now->datatype=typ;
    p=now;
    return;
}

void listInsertTail(List &p,void* data,int typ)
{
    if (p==NULL) {
        p=(List)malloc(listsize);
        p->pData=data;
        p->datatype=typ;
        p->pNext=NULL;
        return;
    }
    List now=p;
    while (now->pNext!=NULL) now=now->pNext;
    List newnode=(List)malloc(listsize);
    newnode->pData=data;
    newnode->pNext=NULL;
    newnode->datatype=typ;
    now->pNext=newnode;
    return;
}

void listDelete(List &p,void* data)
{
    List now=p;
    if (now==NULL) return;
    while (now->pNext!=NULL && now->pNext->pData!=data)
        now=now->pNext;
    if (now!=NULL && now->pNext!=NULL) now->pNext=now->pNext->pNext;
    return;
}

void listReverse(List &p)
{
    List now=NULL;
    while (p!=NULL) listInsertTail(now,now->pData,now->datatype),now=now->pNext;
    p=now;
    return;
}

void listDestroy(List &p)
{
    p=NULL;
}

void listMerge(List &p,List &q)
{
    List now=q;
    while (now!=NULL) listInsertTail(p,now->pData,now->datatype),now=now->pNext;
    return;
}
