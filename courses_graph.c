// Samriddha Kharel 1001918169
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_COURSE_LENGTH 30
#define MAX_LINE_LENGTH 1000

int main()
{
    FILE *filename;
    char name[MAX_COURSE_LENGTH];

    printf("This program reads a list of courses and their prerequisites from a file and outputs the recommended order in which to take the courses.\n");
    printf("Enter filename: ");
    scanf("%s",name);
    filename =fopen(name,"r");
    if(filename ==NULL)
    {
        printf("Bad File Name");
        exit(0);
    }

    int vertexNum =0;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, filename)!= NULL &&vertexNum<MAX_VERTICES)
    {
        vertexNum++;
    }

    if(vertexNum ==MAX_VERTICES)
    {
        printf("Too many vertices in file. Increase MAX_VERTICES and recompile.\n");
        exit(1);
    }

    char vertexList[MAX_VERTICES][MAX_LINE_LENGTH];
    char fileCopy[MAX_VERTICES][MAX_LINE_LENGTH];
    printf("\nNumber of vertices in graph: %d\n", vertexNum);
    fclose(filename);
    filename = fopen(name,"r");

    // Read each line from the input file and extract the course name
    for (int i = 0;i <vertexNum;i++)
    {
        fgets(line, MAX_LINE_LENGTH,filename);

        // Extract the course name from the line
        char *list = strtok(line, "\n");
        char *courseName = strtok(line, " ");
        courseName = strtok(courseName, "\n");
        strcpy(vertexList[i],courseName);
        strcpy(fileCopy[i],list);
        printf("Vertex %d - %s\n",i,courseName);
    }

    // resets the file position indicator to the beginning of a file.
    fclose(filename);
    filename = fopen(name,"r");

    int matrix[MAX_VERTICES][MAX_VERTICES];
    int toporder[2][MAX_VERTICES];
    for(int i = 0; i< vertexNum;i++)
    {
        for(int j = 0;j < vertexNum;j++)
        {
            matrix[i][j] = 1;
        }
    }
    printf("\nAdjacency matrix:\n");
    printf("    |");
    for (int i = 0;i < vertexNum;i++)
    {
        printf("%4d",i);
    }
    printf("\n");
    printf("-----------------\n");

    for(int i = 0; i < vertexNum;i++)
    {
        toporder[0][i] = vertexNum;
        toporder[1][i] = i;
        fgets(line, MAX_LINE_LENGTH,filename);
        printf("%4d|", i);
        char *temp = strtok(line," ");
        while(temp != NULL)
        {
            for(int j = 0;j < vertexNum;j++)
            {
                int ch = strcmp(vertexList[j],temp);
                if (ch == 0 ||ch == -10||ch == -1)
                {
                    matrix[i][j] = 0;
                    toporder[0][i]--;
                }
            }
            temp = strtok(NULL, " ");
        }
        for (int j = 0; j < vertexNum; j++)
        {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    int hasCycle = 0;
    // Check for cycles in the graph
    for(int i = 0; i < vertexNum;i++)
    {
        for (int j = i+1;j < vertexNum;j++)
        {
            if (toporder[0][j] ==toporder[0][i])
            {
                hasCycle = 1;
                break;
            }
        }
    }
    // Sort the courses in descending order of difficulty
    for(int i = 0; i < vertexNum; i++)
    {
        for(int j = i+1;j < vertexNum;j++)
        {
            if(toporder[0][i] < toporder[0][j])
            {
                int temp = toporder[0][i];
                int tempVertex = toporder[1][i];
                toporder[0][i] = toporder[0][j];
                toporder[1][i] = toporder[1][j];
                toporder[0][j] = temp;
                toporder[1][j] = tempVertex;
            }
        }
    }
    // Print the error message if there was a cycle
    if(hasCycle)
    {
        printf("\nIt is not possible to arrange the courses in a order due to the presence of cycle in their prerequisites.\n");
    }
    else
    {
        printf("\n\nOrder in which to take courses:\n");
        for(int i = 0; i < vertexNum; i++)
        {
            printf("%d. - %s (corresponds to graph at vertex %d)\n", i+1,vertexList[toporder[1][i]],toporder[1][i]);
        }
    }
    fclose(filename);

    return 0;
}
