#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100000000   //데이터의 개수 지정
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))    //SWAP함수 설정
int original[MAX_SIZE];    //랜덤함수로 만든 데이터를 저장할 원본 배열
int list[MAX_SIZE];    //각 정렬 알고리즘에서 사용할 데이터 배열

int sorted[MAX_SIZE]; //합병정렬에서 사용할 데이터를 저장할 배열
clock_t start, finish, used_time=0;    //실행 시간 측정을 위한 변수
void insertion_sort(int list[], int n);
void shell_sort(int list[], int n);
void quick_sort(int list[], int left, int right);
void heap_sort(int *arr, int *size);
void heapify(int *list, int num);

//원본 배열을 복사하는 함수

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

//실행 시간을 측정 및 출력하는 함수
void CalcTime(void)
{
    used_time=finish-start;
    printf("\n소요 시간 : \n");
    printf(" ms: %.4f", ((double)used_time) /CLOCKS_PER_SEC* 1000 );
    printf("\n");
}

 // 오름차순 함수
void ascending(int *arr, int num) 
{        
    for (int i=0; i < num; i++)
    {
        arr[i]=i+1;
    }
	printf("////////////////오름차순 입력////////////////\n\n");
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

 // 내림차순 함수
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
	printf("////////////////내림차순 입력////////////////\n\n");
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
        sh = rand() % (num - i) + i;    // i 부터 num-1 사이에 임의의 정수 생성
        temp = arr[i];
        arr[i] = arr[sh];
        arr[sh] = temp;
    }
    
	printf("////////////////랜덤순서 입력////////////////\n\n");
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


//삽입 정렬///////////////////////////////////////
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
 
 
 //셸정렬/////////////////////////////////////////////////
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
 
 
//퀵정렬/////////////////////////////////////////////////
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


 /////////heap 정렬///////////////////////////// 
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
  scanf("%d", &num);    // 배열의 크기를 입력받음

  if (num > MAX_SIZE) {
    printf("최대 입력값은 %d 입니다.\n", MAX_SIZE);
    return 0;
  }
  
  list = (int *)malloc(sizeof(int) * num);    // 입력받은 배열의 크기만큼 메모리 할당
  for (int i=0; i < num; i++)
    list[i] = i+1;    // 배열을 1부터 num 까지의 요소로 초기화
 	printf("\n\n");
	ascending(list,num);
 	descending(list, num);
 	shuffle(list,num);

  free(list);

  return 0;
}
