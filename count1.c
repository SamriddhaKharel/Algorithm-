/*
Count negative numbers in a 1D array using functions:
- return count
- use pass-by-reference to update a count
*/

#include<stdio.h>

#define SIZE1 7

int count_neg_ret(int* arr);
void count_neg_update(int sz, int* arr, int* count);

int main(){
    int arr1[SIZE1] = {9, -3, 6, 2, -21, -8, 20};
    // call count_neg_ret
    int count2 = -1;
    int count1 = count_neg_ret(arr1);
    printf("count1 = %d\n", count1);

    count_neg_update(7, arr1, &count2);
    printf("count 2 = %d\n", count2);


}

int count_neg_ret(int* arr){
    int ct = 0;
    for(int k = 0; k <SIZE1; k++){
        if(arr[k]<0) ct++;
    }
    return ct;
}


void count_neg_update(int sz, int* arr, int* countP){
    *countP = 0;
    for(int k = 0; k <sz; k++){
        if(arr[k]<0) (*countP)++;
    }
    printf("in fct *countP = %d\n", *countP);
}