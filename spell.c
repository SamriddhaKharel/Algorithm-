/*  Samriddha Kharel
    1001918169      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spell.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as
they are declared before the array in the parameter list. See:
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(T*D)


Worst case to do an unsuccessful binary search in a dictionary with D words, when
all dictionary words and the searched word have length MAX_LEN
Student answer:  Theta(log D)
*/


/* Write helper functions here */

int min_num(int num1, int num2, int num3)
{
    int min = num1;
    if (num2 < min)
    {
        min = num2;
    }
    if (num3 < min)
    {
        min = num3;
    }
    return min;
}

/*
Parameters:
  - first_string - pointer to the first string (displayed vertical in the table)
  - second_string - pointer to the second string (displayed horizontal in the table)
  - print_table - If 1, the table with the calculations for the edit distance will be printed.
                  If 0 (or any value other than 1)it will not print the table
Return:  the value of the edit distance
*/


void print_table(char *first_str, char *second_str, int **table, int n, int m)
{

    int row = strlen(second_str);
    int col = strlen(first_str);

	printf("\n  |   |");
    for (int i = 0;i < m;i++)
    {
        printf("%3c|", second_str[i]);
    }
    printf("\n");
    for(int x = 1; x < (row+2) * 4; x++)
    {
        printf("-");
    }
    printf("\n");
    for(int i = 0;i <= col;i++)
    {
        if (i == 0)
        {
            printf("  |");
        }
    }
    for (int i = 0;i <= n;i++)
    {
        if (i == 0)
        {
            printf(" \b");
        }
        else
        {
            printf(" %c|", first_str[i - 1]);
        }
        for (int j = 0; j <= m; j++)
        {
            printf("%3d|", table[i][j]);
        }
        printf("\n");
        for(int x = 1;x < (row+2)*4;x++)
        {
            printf("-");
        }
        printf("\n");
    }
    printf("\n");
}

int edit_distance(char *first_str,char *second_str,int print_on)
{
    int col = strlen(first_str);
    int row = strlen(second_str);

    int **table = (int **) malloc((col+1) * sizeof(int *));
    for (int i = 0;i <= col;i++)
    {
        table[i] = (int *) malloc((row+1) * sizeof(int));
    }

    for (int i = 0;i <= col;i++)
    {
        table[i][0] = i;
    }

    for (int j = 0;j <= row;j++)
    {
        table[0][j] = j;
    }

    for(int i = 1;i <= col;i++)
    {
        for(int j = 1; j <= row; j++)
        {
            if(first_str[i-1] == second_str[j-1])
            {
                table[i][j] = table[i-1][j-1];
            }
            else
            {
                table[i][j] = 1 + min_num(table[i-1][j], table[i][j-1], table[i-1][j-1]);
            }
        }
    }
    int distance = table[col][row];
    if(print_on == 1)
    {
        print_table(first_str, second_str, table, col, row);
    }
    for(int i = 0;i <= col;i++)
    {
        free(table[i]);
    }
    free(table);
    return distance;
}
/*
Parameters:
  - testname - string containing the name of the file with the paragraph to spell check, includes file extenssion e.g. "text1.txt"
  - dictname - name of file with dictionary words. Includes file extenssion, e.g. "dsmall.txt"
Behavior: If any of the files cannot be open displays a message and returns. (Does not exit the program.)
*/
void spell_check(char *testname,char *dictname)
{
    FILE *filename1, *filename2;
    int size = 0, bin = 0;
    char word[100] = {0}, search[100] = {0}, temp[100] = {0}, option[3] = {0};
    char **list, **list2;
    int low,mid,high,wordsCompared;
    int found,distance;

    filename1=fopen(dictname,"r");
    filename2=fopen(testname,"r");

    if (filename1 == NULL||filename2 == NULL)
    {
        printf("\nCould not open file %s. Exit\n\nGood bye!", dictname);
        exit(0);
    }

    fscanf(filename1,"%d",&size);

    list = (char **) malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        list[i] = (char *)malloc(100 * sizeof(char));
        fscanf(filename1,"%s", word);
        strcpy(list[i],word);
    }

    printf("\nLoaded the dictionary %s has size:%d",dictname,size);

    fscanf(filename2,"%d",&bin);

    list2 = (char **) malloc(bin * sizeof(char *));
    for (int i = 0; i< bin;i++)
    {
        list2[i] = (char *) malloc(101 * sizeof(char));
        fscanf(filename2, "%s",search);
        printf("\n---> |%s|\n",search);
        strcpy(temp,search);
        strcpy(list2[i],temp);

        found = 0;
        printf("-1 - to type a correction\n 0 - leave the word as is (do not fix spelling)\n     Minimum distance: 2\n     Words that give minimum distance:\n");

        char *temp;
        int sim_count = 0;
        char **similar =(char **) malloc(size * sizeof(char *));
        for (int j = 0; j < size; j++)
        {
            distance = edit_distance(list[j],search,0);
            if (distance <= 2)
            {
                similar[sim_count] =(char *)malloc(101 * sizeof(char));
                strcpy(similar[sim_count],list[j]);
                sim_count++;
            }
        }
        if (sim_count > 0)
        {
            option[0] = '\0';
            for (int k = 0; k < sim_count;k++)
            {
                printf(" %d - %s\n",k+1,similar[k]);
                temp =similar[k];
                free(similar[k]);
            }
            free(similar);
            printf("Enter your choice: ");
            scanf("%s",option);
            if (strcmp(option, "-1") == 0)
            {
                printf("Enter a correction:");
                scanf("%s",search);
                strcpy(temp,search);
                strcpy(list2[i],temp);
                printf("The corrected word is: %s\n\n",search);
            }
            if (strcmp(option, "0") == 0)
            {
                printf("The corrected word is: %s\n\n",search);
            }
            if (atoi(option) > 0 &&atoi(option)<=sim_count)
            {
                int choice = atoi(option);
                printf("The corrected word is: %s\n\n",similar[choice-1]);
                strcpy(list2[i],temp);
            }
            else
            {
                printf("Invalid choice. Original word will be kept.\n");
                printf("The corrected word is: %s\n\n",search);
            }
        }
    }
    for(int i = 0;i < size;i++)
    {
        free(list[i]);
    }
    free(list);

    for(int i = 0;i < bin;i++)
    {
        free(list2[i]);
    }
    free(list2);

    fclose(filename1);
    fclose(filename2);
}
