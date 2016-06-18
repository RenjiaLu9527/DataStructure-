#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10

typedef struct
{
    int r[MAXSIZE+1];
    int len;
}SqList;

void Swap(SqList *L,int i,int j)
{
    int temp=L->r[i];
    L->r[i]=L->r[j];
    L->r[j]=temp;
}
/*’€∞Î≤Â»Î≈≈–Ú*/
void TwoSort(SqList *L)
{
    int i,j;
    for(i=1;i<=L->len;i++)
    {
        int	tmp=L->r[i];
        int low=1;
        int hight=i-1;
        while(low<=hight)
        {
           int  mid = (low+hight)/2;
           if(tmp > L->r[mid])
              low = mid+1;
           else
            hight = mid-1;
        }
        for(j=i-1;j>=low;j--)
           L->r[j+1]=L->r[j];
        L->r[low]=tmp;
    }
}
/*√∞≈›≈≈–Ú*/
void BuddleSort(SqList *L)
{
    int i,j;
    for(i=1;i<L->len;i++)
    {
        for(j=L->len-1;j>=1;j--)
        {
            if(L->r[j]>L->r[j+1])
            {
                Swap(L,j,j+1);
            }
        }
    }
}

int Partition(SqList *L,int low,int high);
/*øÏÀŸ≈≈–Ú*/
void QSort(SqList *L,int low,int high)
{
    int pivot;
    if(low<high)
    {
        pivot=Partition(L,low,high);
        QSort(L,low,pivot-1);
        QSort(L,pivot+1,high);
    }
}
int Partition(SqList *L,int low,int high)
{
    int pivotkey;
    int m=low+(high-low)/2;
    if(L->r[low]>L->r[high])
        Swap(L,low,high);
    if(L->r[m]>L->r[high])
        Swap(L,high,m);
    if(L->r[m]>L->r[low])
        Swap(L,m,low);
    pivotkey=L->r[low];
    L->r[0]=pivotkey;
    while(low<high)
    {
        while(low<high&&L->r[high]>=pivotkey)
            high--;
        L->r[low]=L->r[high];
        while(low<high&&L->r[low]<=pivotkey)
            low++;
        L->r[high]=L->r[low];
    }
    L->r[low]=L->r[0];
    return low;
}
void QuickSort(SqList *L)
{
    QSort(L,1,L->len);
}

/*ºÚµ•—°‘Ò≈≈–Ú*/
void SelectSort(SqList *L)
{
    int i,j,min;
    for(i=1;i<L->len;i++)
    {
        min=i;
        for(j=i+1;j<=L->len;j++)
        {
            if(L->r[min]>L->r[j])
                min=j;
        }
        if(i!=min)
            Swap(L,i,min);
    }
}

void MSort(int SR[],int TR1[],int s,int t);
void Merge(int SR[],int TR[],int i,int m,int n);
/*πÈ≤¢≈≈–Ú*/
void Merge(int sourceArr[],int tempArr[], int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j=midIndex+1, k = startIndex;
    while(i!=midIndex+1 && j!=endIndex+1)
    {
        if(sourceArr[i] >= sourceArr[j])
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++] = sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++] = sourceArr[j++];
    for(i=startIndex; i<=endIndex; i++)
        sourceArr[i] = tempArr[i];
}
 
//ƒ⁄≤ø π”√µ›πÈ
void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = (startIndex + endIndex) / 2;
        MergeSort(sourceArr, tempArr, startIndex, midIndex);
        MergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}
 
/*
void MergeSort(SqList *L)
{
    MSort(L->r,L->r,1,L->len);
}
void MSort(int SR[],int TR1[],int s,int t)
{
    int m;
    int TR2[MAXSIZE+1];
    if(s==t)
        TR1[s]=SR[s];
    else
    {
        m=(s+t)/2;
        MSort(SR,TR2,s,m);
        MSort(SR,TR2,m+1,t);
        Merge(TR2,TR1,s,m,t);
    }
}
void Merge(int SR[],int TR[],int i,int m,int n)
{
    int j,k,l;
    for(j=m+1,k=i;i<=m&&j<=n;k++)
    {
        if(SR[i]<SR[j])
            TR[k]=SR[i++];
        else
            TR[k]=SR[j++];
    }
    if(i<=m)
    {
        for(l=0;l<=m-i;l++)
            TR[k+1]=SR[i+1];
    }
    if(j<=n)
    {
        for(l=0;l<=n-j;l++)
         TR[k+1]=SR[j+1];
    }
}
*/

void HeapAdujst(SqList *L,int s,int m);
/*∂—≈≈–Ú*/
void HeapSort(SqList *L)
{
    int i;
    for(i=L->len/2;i>0;i--)
    {
        HeapAdujst(L,i,L->len);
    }
    for(i=L->len;i>1;i--)
    {
        Swap(L,1,i);
        HeapAdujst(L,1,i-1);
    }
}
void HeapAdujst(SqList *L,int s,int m)
{
    int temp,j;
    temp=L->r[s];
    for(j=2*s;j<=m;j*=2)
    {
        if(j<m&&L->r[j]<L->r[j+1])
            ++j;
        if(temp>=L->r[j])
            break;
        L->r[s]=L->r[j];
        s=j;
    }
    L->r[s]=temp;
}

int main()
{
    SqList l;
		int b[1000];
    printf(" ‰»Î≥§∂»º∞¥˝≈≈–Úµƒ ˝◊È£∫\n");
    scanf("%d",&l.len);

    int i;
     for(i=1;i<=l.len;i++)
        scanf("%d",&l.r[i]);

    printf("—°‘Ò≈≈–Ú∑Ω∑®£∫1.’€∞Î≤Â»Î≈≈–Ú£ª\n2.√∞≈›≈≈–Ú£ª\n3.øÏÀŸ≈≈–Ú£ª\n4.ºÚµ•—°‘Ò≈≈–Ú£ª\n5.πÈ≤¢≈≈–Ú£ª\n6.∂—≈≈–Ú\n");
    int n;
 

		scanf("%d",&n);
//MergeSort
		switch(n)
		{
			case 1:TwoSort(&l); break;
			case 2:BuddleSort(&l); break;
			case 3:QuickSort(&l); break;
			case 4:SelectSort(&l); break;
			case 5:{
				
				MergeSort(l.r,b,0,l.len); break;
				   }
			case 6:HeapSort(&l); break;
		}

 
    for(i=1;i<=l.len;i++)
        printf("%d ",l.r[i]);
	 
    return 0;
}
