#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0

int vertices;

struct node {
    int data;
    struct node* next;
};

    /* print Graph */

void printGraph(int vertices, int adj[vertices][vertices]){
    for(int i = 0 ; i < vertices ; i++){
        for(int j = 0 ; j < vertices ; j++){
            printf(" %d  ", adj[i][j]);
        }
        printf("\n");
    }
}

void readGraph( struct node *adj[]){

    struct node *newNode;
    int n, data;

    for(int i = 0 ; i < vertices ; i++){

        struct node *last = NULL;
        printf("How many vertices adjacent to %d : ", i);
        scanf("%d", &n);

        for(int j = 1 ; j <= n ; j++){

            newNode = (struct node *)malloc(sizeof(struct node *));
            printf("Enter the %d neighbour of %d : ", j, i);
            scanf("%d", &data);
            newNode -> data = data;
            newNode -> next = NULL;

            if(adj[i] == NULL){
                adj[i] = newNode;
            } else {
                last -> next = newNode;
            }
            last = newNode;
        }
    }
}


    /* Bearth First Search */

void bfs(int vertices, int adj[vertices][vertices], int start){

    int visited[vertices], queue[vertices], front = 0 , r = 0, cpt = 0, boolean = false, remp = vertices - 1;

    for(int i = 0 ; i < vertices ; i++) visited[i] = false;

    queue[r] = start;
    visited[start - 1] = 1;

    while(cpt < vertices){
        if(!boolean){
            start--;
            boolean = true;
        }

        printf("\n\n pour cpt = %d ", cpt);
        printf("\n Je suis avec le noeus %d", start);

        for(int i = 0 ; i < vertices ; i++){
            if((adj[start][i] == 1) && (visited[i] != 1) && (start != i)){
                queue[++r] = i + 1;
                visited[cpt + 1] = true;
            }
        }
        start = (start + 1) % remp;
        cpt++;
    }

    for(int i = 0 ; i < vertices ; i++){
        printf("The result : | %d\t", queue[i]);
    }

}

    /* Deapth First Search */
void dfs(int vertices, int adj[vertices][vertices], int visited[vertices], int start){
    visited[start] = 1;
    printf("%d\t", start + 1);

    for(int i = 0 ; i < vertices ; i++){
        if((visited[i] != 1) && (adj[start][i])){
            visited[i] = 1;
            dfs(vertices, adj, visited, i);
        }
    }
}


int main()
{

    /* Adjacency matrix */

    int vertices, s, d, ch, start;
    bool continu = true;
    printf("Enter the number of vertices : ");
    scanf("%d", &vertices);

    int adj[vertices][vertices], visited[vertices];

    for(int i = 0 ; i < vertices ; i++) visited[i] = 0;

    for(int i = 0; i < vertices ; i++){
        for(int j = 0 ; j < vertices ; j++) {
            adj[i][j] = 0;
        }
    }

    while(s != (-1) && d != (-1)){
        printf("If the adges are finished enter -1, else enter an Edge from node ( %d to %d) :", vertices, vertices);
        scanf("%d%d", &s, &d);
        if(s > vertices || d > vertices) {
            printf("Error, those vertices don't exist");
            continu = false;
        }
        adj[s - 1][d - 1] = 1;
        adj[d - 1][s - 1] = 1;
        if (!continu) break;
    }

    /* bfs */

    do {
        printf(" > Enter 1 to print adjacency matrix\n  > Enter 2 for BFS\n > Enter 3 for DFS\n > Enter 4 to Exit : \n > Your choice : ");
        scanf("%d", &ch);
        switch(ch){
        case 1:
            printGraph(vertices, adj);
            break;
        case 2:
            printf("Enter the Vertex from which do you wanted to start : ");
            scanf("%d", &start);
            bfs(vertices, adj, start);
            break;
        case 3:
            printf("Enter the vertex from which do you wanted to start : ");
            scanf("%d", &start);
            dfs(vertices, adj, visited, start - 1);
            break;
        case 4:
            break;
        }
    } while(ch != 3);


    return 0;
}
