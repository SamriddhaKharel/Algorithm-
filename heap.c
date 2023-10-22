// Samriddha Kharel 1001918169
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

#define DEBUG 1
//#define DEBUG 0
// uncomment and write your code

void print_array(int* arr, int N)
{

    printf("Heap:  size: %2d, capacity : %2d\n",N,N);
    printf("indexes: ");
    printf("   ");
    for (int i = 0; i < N; i++)
    {
        printf("%5d,", i);
    }
    printf("\nvalues:\t");
    printf("    ");
    for (int i = 0; i < N; i++)
    {
        printf("%5d,", arr[i]);
    }
    printf("\n");
}
struct heap_struct make_heap_empty(int cap)
{
    // Create an empty heap with the given capacity
    struct heap_struct heapS;
    heapS.items= malloc(cap*sizeof(int));
    heapS.N = 0;
    heapS.capacity = cap;
    return heapS;
}
struct heap_struct make_heap(int N,int*arr)
{
    // Create a heap from an array of integers
    struct heap_struct heap;
    heap.capacity= N;
    heap.N= N;
    heap.items= malloc(N*sizeof(int));
    for (int i = 0; i < N; i++)
    {
        heap.items[i] = arr[i];
    }
    printf("in function make_heap, in DEBUG MODE, printing array BEFORE it gets turned into a heap :\n");
    print_array(heap.items, heap.N);
    for (int j=(N-1)/2;j>=0;j--)
    {
        sink_down(j, N - 1, heap.items);
    }
    printf("\nin function make_heap, in DEBUG MODE, printing array after sink_down at index 1.\n");
    print_array(heap.items, heap.N);
    for (int k = (N-1)/2; k >= 0; k--)
    {
        sink_down(k, 0, heap.items);
    }

    printf("\nin function make_heap, in DEBUG MODE, printing array after sink_down at index 0.\n");
    print_array(heap.items, heap.N);
    for (int l = 0; l < N; l++)
    {
        sink_down(l,0, heap.items);
    }
    printf("\n");
    return heap;
}


void destroy(struct heap_struct * heapP)
{
        // Free the memory
        free(heapP->items);
        heapP->items = NULL;
        heapP->capacity=0;
        heapP->N=0;
}

void print_heap(struct heap_struct heapS)
{
    // Print the contents of the heap
    printf("Heap:  size: %d, capacity : %d\n", heapS.N, heapS.capacity);
    printf("indexes:");
    if(heapS.items!= NULL)
    {
        printf("%9d,", 0);
        for(int i =1;i<heapS.N;i++)
        {
            printf("%5d,", i);
        }
    }
    printf("\nvalues:");
    if(heapS.items!= NULL)
    {
        printf("%10d,",heapS.items[0]);
        for(int i=1;i<heapS.N;i++)
        {
            printf("%5d,",heapS.items[i]);
        }
    }
    printf("\n\n");

}


void swim_up(int idx,int* arr)
{
    int parent=(idx-1)/2;
    while(idx >0&&arr[idx]>arr[parent])
    {
        int temp= arr[parent];
        arr[parent]= arr[idx];
        arr[idx]= temp;
        idx = parent;
        parent =(idx-1)/2;
    }
}

void sink_down(int i,int N,int*arr)
{
    while ((2*i)+1<= N)
    {
        int leftCh_idx= (2*i)+1;
        int rightCh_idx= leftCh_idx+1;
        int largeCh_idx= leftCh_idx;
        if (rightCh_idx <= N && arr[rightCh_idx] > arr[leftCh_idx])
        {
            largeCh_idx=rightCh_idx;
        }
        if (arr[i]>= arr[largeCh_idx])
        {
            break;
        }
        int temp= arr[i];
        arr[i]= arr[largeCh_idx];
        arr[largeCh_idx]= temp;
        i = largeCh_idx;
    }
}
void add(struct heap_struct * heapP, int new_item)
{
    if(heapP->capacity==heapP->N)
    {
        printf("\nresizing\n");
        int cap = heapP->capacity * 2;
        int *new_items= realloc(heapP->items, cap*sizeof(int));
        if (new_items == NULL)
        {
            printf("\nFailed to resize heap.\n");
            return;
        }
        heapP->items=new_items;
        heapP->capacity = cap;
    }
    int size = heapP->N;
    heapP->items[size] = new_item;
    heapP->N++;
    swim_up(size, heapP->items);

}

int peek(struct heap_struct heapS)
{
	return heapS.items[0];
}

int poll(struct heap_struct * heapP)
{
    if(heapP->N == 0)
    {
        printf("\nEmpty heap. no remove performed.removed:");
        return 0;
    }
    int remove= heapP->items[0];
    heapP->N--;
    heapP->items[0] = heapP->items[heapP->N];
    sink_down(0, heapP->N, heapP->items);
    return remove;
}

