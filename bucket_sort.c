/*
 * Updated 03/4/2023 - Samriddha Kharel
 */

/*
compile with -g to collect debugging info needed for Valgrind ( -lm links the math library):
gcc -g bucket_sort.c list.c -lm

run with Valgrind:
valgrind --leak-check=full ./a.out

On some systems, but not all, you can also use the --show-leak-kinds=all flag:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/

// This program sorts a number in ascending order using bucket sort Algorithm.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "list.h"   // useful if you want to use functions from list.c

void print_array(int arr[], int N);
void run1();
void bucket_sort(int * arr, int N);
/*
// function to insert a new node in a sorted list. E.g.:
nodePT insert_sorted(nodePT L, nodePT newP);
//or
nodePT insert_sorted(nodePT L, int elem);
//  function to sort an array sing bucket sort. E.g.:
void bucket_sort(int * arr, int N);
*/
struct Node
{
    int data;
    struct Node* next;
};

nodePT insert_sorted(nodePT L, int elem)
{
    nodePT newNode = (nodePT)malloc(sizeof(struct node));
    newNode->data = elem;
    newNode->next = NULL;

    if (L == NULL || elem < (L)->data)
    {
        newNode->next = L;
        L = newNode;
    }
    else
    {
        nodePT current = L;
        while (current->next != NULL && elem >= current->next->data)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
void bucket_sort(int *arr, int N)
{
    double min;
    double max;
    int indx;
    int indexarr[N];
//---------------------------------------------------------------------
    nodePT buckets[N];
    for (int i = 0; i < N; i++)
    {
        buckets[i] = NULL;
    }

    int arrsize = sizeof(arr) / sizeof(arr[0]);
    max = *(arr+0);
    for (int i = 1; i < N; i++)
    {
        if (*(arr+i) > max)
        {
            max = *(arr+i);
        }
    }
    min = *(arr+0);
    for (int i = 1; i < N; i++)
    {
        if (*(arr+i) < min)
        {
            min = *(arr+i);
        }
    }
//---------------------------------------------------------------------
    printf("\n\nBucketsort: min=%d, max=%d, N=%d buckets\n",(int)min,(int)max,N);

    for (int i = 0; i < N; i++)
    {
        indx = floor((arr[i] - min) *N/ (1 + max- min));
        indexarr[i]=indx;
        printf("arr[%d]=    %d, idx = %d\n",i,arr[i],indx);
        buckets[indx] = insert_sorted(buckets[indx], arr[i]);

    }

    for (int i = 0; i < N; i++)
    {
    // Sort the linked list using insertion sort
        nodePT curr = buckets[i];
        while (curr != NULL && curr->next != NULL)
        {
            nodePT prev = NULL;
            nodePT innerCurr = curr->next;
            while (innerCurr != NULL)
            {
                if (innerCurr->data < curr->data)
                {
                    if (prev != NULL)
                    {
                        prev->next = innerCurr;
                    }
                    else
                    {
                        buckets[i] = innerCurr;
                    }
                    curr->next = innerCurr->next;
                    innerCurr->next = curr;
                    prev = innerCurr;
                    innerCurr = curr->next;
                }
                else
                {
                    prev = curr;
                    curr = innerCurr;
                    innerCurr = innerCurr->next;
                }
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        int flag = 0;
        printf("------ List at index %d :\n",i);
        nodePT curr = buckets[i];
        if(curr != NULL)
        {
            printf(" List items:     ");
            while (curr != NULL)
            {
                printf("%d        ", curr->data);
                flag++;
                curr = curr->next;

            }
            printf("\nLength of above list = %d",flag);
        }
        else
        {
            printf("<print_list_horiz> : List is NULL");
        }
        printf("\n");
    }

    // Copy elements from buckets back into array in sorted order
    int index = 0;
    for (int i = 0; i < N; i++)
    {
        nodePT current = buckets[i];
        while (current != NULL)
        {
            arr[index++] = current->data;
            current = current->next;
        }
    }

    // Free memory
    for (int i = 0; i < N; i++)
    {
        nodePT current = buckets[i];
        while (current != NULL)
        {
            nodePT tempfree = current;
            current = current->next;
            free(tempfree);
        }
    }

}

void print_array(int arr[], int N)
{
	int j;
	printf("\n array: ");
	for(j= 0; j<N; j++)
    {
		printf("%5d,", arr[j]);
	}
	printf("\n");
}

//-------------------------------------------------------------

void run1()
{
	// Fill in your code here. You should not write everything in this function.
	// Write some helper functions to separate the work.
        char fname[50];
        int min;
        int max;
        int N;
        FILE *fp;
        printf("Enter the filename: ");
        scanf("%s", fname);
        fp =fopen(fname, "r");
        if (fp == NULL)
        {
            printf("File could not be opened.\n");
            exit(0);
        }
       fscanf(fp, "%d", &N);
       int arr[N];
       for (int i = 0; i < N; i++)
       {
            fscanf(fp, "%d", &arr[i]);
       }

        fclose(fp);  // Close the file
        print_array(arr,N);
        bucket_sort(arr,N);
        print_array(arr,N);


	printf("\n-------run1 - this is a place holder. You need to edit this function.------ \n");
}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option = 1;
	do
    {
        run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		char ch;
		scanf("%d%c",&option, &ch);  // ch is used to remove the Enter from the input buffer

 	} while (option == 1);


   return 0;
}
