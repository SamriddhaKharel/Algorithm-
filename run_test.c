//Samriddha Kharel 1001918169
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"
int main()
{
    char filename[50];
    int arrNode;
    char value[100];
    int operation;
    printf("This program will create a max-heap and perform operations on it based on data from a file.\n\n");
    printf("Enter the filename: ");
    scanf("%s",filename);
    FILE *file = fopen(filename, "r");
    if(file ==NULL)    //check if file was successfully opened
    {
        printf("File could not be opened.\n");
        return 1;
    }
    fscanf(file, "%d", &arrNode);

    //read in the size of the heap and allocate memory for it
    int *arr =(int*)calloc(arrNode,sizeof(int));
    for(int i=0; i<arrNode;i++)
    {
        int num;
        fscanf(file,"%d",&num);
        arr[i] = num;
    }
    struct heap_struct heap;
    heap= make_heap(arrNode,arr);
    print_heap(heap);
    fscanf(file, "%d",&operation);

    for (int i = 0; i < operation; i++)    //loop through each operation
    {
        char operationString[10];
        int itemsRead = fscanf(file, "%s", operationString);
        if (itemsRead != 1)
        {
            printf("Error reading input\n");
            break;
        }
        printf("Operation number %d, string: %s\n", i + 1, operationString);
        int sz = atoi(operationString);
        if (sz != 0)
        {
            printf("add:\t%d\n", sz);
            add(&heap, sz);
        }
        else
        {
            char op = operationString[0];
            switch (op)
            {
                case '*':
                    if (heap.N != 0)
                    {
                            printf("removed:\t%d\n", poll(&heap));
                    }
                    else
                    {
                        printf("Empty heap it can't be removed:      0\n");
                    }
                    break;

                case 'p':
                case 'P':
                    printf("peek:\t%d\n", peek(heap));
                    break;

                default:
                    printf("Invalid operation: %c\n", op);
                    break;
            }
        }

        print_heap(heap);        //print the updated heap after each operation
    }
    destroy(&heap);
    free(arr);
    fclose(file);
    return 0;
}
