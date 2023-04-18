#include <stdio.h>
#include <stdlib.h>

int vertices;

struct node {
    int data;
    struct node* next;
};

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

void printGraph(struct node *adj[]){

    struct node *tmp;

    for(int i = 0 ; i < vertices ; i++){
        tmp = adj[i];
        printf(" \n > Vertices adjacent to [%d] are : ", i);
        while(tmp != NULL){
            printf("%d\t", tmp -> data);
            tmp = tmp -> next;
        }
    }
}

    /* bfs */

void bfs(struct node *ad[], int start, int visited[]){
    int queue[vertices], front = 0, r = 0, cpt = 0;
    struct node *p;
    queue[r] = start;

    printf("BFS trav from [%d] is : ", start);

    while(front <= r){
        start = queue[front];
        p = ad[start];
        printf("%d\t", start);
        cpt++;
        front++;
        while(p != NULL){
            if(visited[p -> data] != 1){
                 r++;
                queue[r] = p -> data;
                visited[p -> data] = 1;
            }
            p = p -> next;
        }
    }

}

    /* dfs */
void dfs(struct node *ad[], int start, int visited[]){

    visited[start] = 1;
    printf("%d\t", start);

    struct node* p = ad[start];
    while(p != NULL){
        if(visited[p -> data] != 1){
            dfs(ad, p -> data, visited);
            p = p -> next;
        }
    }

}

int main()
{
    int data, choice, visited[vertices];
    printf("Enter the number of vertices in the graph : ");
    scanf("%d", &vertices);

    struct node *adj[vertices];

    for(int i = 0 ; i < vertices ; i++){
        adj[i] = NULL;
    }

    readGraph(adj);

    do {
        printf(" > Enter 1 for the BFS\n > Enter 2 for DFS\n > Enter 3 to print Adjacency List \n > Enter 4 to Exit");
        printf("Your choice : ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter the vertex from which you are going to start : ");
                scanf("%d", &data);
                for(int i = 0 ; i < vertices ; ++i){
                    visited[i] = 0;
                }
                visited[data] = 1;
                bfs(adj, data, visited);
            case 2:
                printf("Enter the vertex from which you are going to start : ");
                scanf("%d", &data);
                for(int i = 0 ; i < vertices ; ++i){
                    visited[i] = 0;
                }
                dfs(adj, data, visited);
            case 3:
                printGraph(adj);
                break;
            case 4: break;

        }
    } while (choice != 4);




    return 0;
}
