#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100000000   //�������� ���� ����
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))    //SWAP�Լ� ����
int original[MAX_SIZE];    //�����Լ��� ���� �����͸� ������ ���� �迭
int list[MAX_SIZE];    //�� ���� �˰��򿡼� ����� ������ �迭

int sorted[MAX_SIZE]; //�պ����Ŀ��� ����� �����͸� ������ �迭
clock_t start, finish, used_time=0;    //���� �ð� ������ ���� ����
void insertion_sort(int list[], int n);
void shell_sort(int list[], int n);
void quick_sort(int list[], int left, int right);
void heap_sort(int *arr, int *size);
void heapify(int *list, int num);

//���� �迭�� �����ϴ� �Լ�

void CopyArr(int *arr, int num)
{
    int i;

     for(i=0; i<num; i++)
        list[i]=arr[i];
}

void print_list(char *msg, int num)
{

  int i=0;
  printf("\n%s, item(%d)\n", msg, num);
  for (i=0; i < num ; i++){
    printf("%d,", list[i]);
  }
  printf("\n");

}

//���� �ð��� ���� �� ����ϴ� �Լ�
void CalcTime(void)
{
    used_time=finish-start;
    printf("\n�ҿ� �ð� : \n");
    printf(" ms: %.4f", ((double)used_time) /CLOCKS_PER_SEC* 1000 );
    printf("\n");
}

 // �������� �Լ�
void ascending(int *arr, int num) 
{        
    for (int i=0; i < num; i++)
    {
        arr[i]=i+1;
    }
	printf("////////////////�������� �Է�////////////////\n\n");
    printf("<<Insertion Sort>>    ");

    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    insertion_sort(list, num);
    finish=clock();
    //print_list("After", num);
    CalcTime();

	printf("<<Shell Sort>>        ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    shell_sort(list, num);
    finish=clock();
    //print_list("After", num);
    CalcTime();
    
   
	printf("<<Quick Sort>>        ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    quick_sort(list, 0, num-1);
    finish=clock();
    //print_list("After", num);
    CalcTime();
    
	
	printf("<<Heap Sort>>         ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    heap_sort(list, &num);
    finish=clock();
    //print_list("After", num);
    CalcTime();
}

 // �������� �Լ�
void descending(int *arr, int num) 
{        
	int i, temp;
    for (i=0; i < num; i++)
    {
        arr[i]=i+1;
    }
    for (i=0; i<num/2; i++)
    {
    	temp=arr[i];
    	arr[i]=arr[num-i-1];
    	arr[num-i-1]=temp;
	}
	printf("////////////////�������� �Է�////////////////\n\n");
	printf("<<Insertion Sort>>    ");
    CopyArr(arr, num);
    start=clock();
    //print_list("Before", num);
    insertion_sort(list, num);
    finish=clock();
    //print_list("After", num);
    CalcTime();

	printf("<<Shell Sort>>        ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    shell_sort(list, num);
    finish=clock();
    //print_list("After", num);
    CalcTime();
    
    
	printf("<<Quick Sort>>        ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    quick_sort(list, 0, num-1);
    finish=clock();
    //print_list("After", num);
    CalcTime();
    
	
	printf("<<Heap Sort>>         ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    heap_sort(list, &num);
    finish=clock();
    //print_list("After", num);
    CalcTime();
}

void shuffle(int *arr, int num)
{
    srand(time(NULL));  
    int temp;
    int sh;
    for (int i=0; i < num-1; i++)
    {
        sh = rand() % (num - i) + i;    // i ���� num-1 ���̿� ������ ���� ����
        temp = arr[i];
        arr[i] = arr[sh];
        arr[sh] = temp;
    }
    
	printf("////////////////�������� �Է�////////////////\n\n");
    printf("<<Insertion Sort>>    ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    insertion_sort(list, num);
    finish=clock();
    //print_list("After", num);
    CalcTime();

	printf("<<Shell Sort>>        ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    shell_sort(list, num); 
    finish=clock();
    //print_list("After", num);
    CalcTime();

	printf("<<Quick Sort>>        ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    quick_sort(list, 0, num-1); 
    finish=clock();
    //print_list("After", num);
    CalcTime();
    
	
	printf("<<Heap Sort>>         ");
    CopyArr(arr, num);
    //print_list("Before", num);
    start=clock();
    for(int i=0; i<10; ++i){
    	heapify(list,num);
    	heap_sort(list, &num);
	}
    finish=clock();
    //print_list("After", num);
    CalcTime();
}


//���� ����///////////////////////////////////////
void insertion_sort(int list[], int num)
{
    int i, j, key;

    for(i=1; i<num; i++)
    {
        key=list[i];
        for(j=i-1; j>=0 && list[j]>key; j--)
            list[j+1]=list[j];
        list[j+1]=key;
    }
}
 ///////////////////////////////////////////////////////
 
 
 //������/////////////////////////////////////////////////
int shellify(int list[], int first, int last, int gap)
{
    int i,j,key;
 
    for(i=first+gap; i<=last; i=i+gap){
    	key = list[i];
    	for(j=i-gap; j>=first && list[j]>key; j=j-gap){
    		list[j+gap]=list[j];
		}
		list[j+gap]=key;
	}
}
void shell_sort(int list[], int num)
{
    int i, gap;
    
    for(gap=num/2; gap>0; gap=gap/=2){
        if(gap % 2 == 0)
			gap++;
		
		
		for(i=0; i<gap; i++){
			shellify(list, i, num-1, gap);
		}
    }
}
////////////////////////////////////////////////////////
 
 
//������/////////////////////////////////////////////////
int quickify(int list[], int left, int right)
{
    int pivot=list[left], temp, low=left, high=right+1;
 
    do{
        do{
        	low++;
    	}while(low<=right && list[low]<pivot);
        
        do{
        	high--;
        }while(high>=left && list[high]>pivot);
        
		if(low<high){
			SWAP(list[low], list[high], temp);
    	}
	}while(low<high);
 
    SWAP(list[left], list[high], temp);
    return high;
}
void quick_sort(int list[], int left, int right)
{
    if(left<right)
    {
        int q=quickify(list, left, right);
        quick_sort(list, left, q-1);
        quick_sort(list, q+1, right);
    }
}
////////////////////////////////////////////////////////


 /////////heap ����///////////////////////////// 
 void heapify(int *list, int num)
 {
 	for(int i=1; i<num; ++i){
 		int child = i;
 		do{
 			int root = (child-1)/2;
 			if(list[root]<list[child]){
 				int temp = list[root];
 				list[root] = list[child];
 				list[child] = temp;
			 }
			 child=root;
		 }while(child!=0);
	 }
 }
 
 void heap_sort(int *list, int *num)
 {
 	int temp = list[0];
 	list[0]=list[*num-1];
 	list[*num-1]=temp;
 	--(*num);
 }
 ///////////////////////////////////////////////////
 

int main ()
{
  int num;
  int *list;
  printf("N = ");
  scanf("%d", &num);    // �迭�� ũ�⸦ �Է¹���

  if (num > MAX_SIZE) {
    printf("�ִ� �Է°��� %d �Դϴ�.\n", MAX_SIZE);
    return 0;
  }
  
  list = (int *)malloc(sizeof(int) * num);    // �Է¹��� �迭�� ũ�⸸ŭ �޸� �Ҵ�
  for (int i=0; i < num; i++)
    list[i] = i+1;    // �迭�� 1���� num ������ ��ҷ� �ʱ�ȭ
 	printf("\n\n");
	ascending(list,num);
 	descending(list, num);
 	shuffle(list,num);

  free(list);

  return 0;
}
