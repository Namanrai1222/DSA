#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* adjList[MAX];
int visited[MAX];

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = createNode(u);
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

int detectCycle(int v, int parent) {
    struct Node* temp;
    int adjVertex;

    visited[v] = 1;
    temp = adjList[v];

    while (temp != NULL) {
        adjVertex = temp->vertex;

        if (!visited[adjVertex]) {
            if (detectCycle(adjVertex, v))
                return 1;
        }
        else if (adjVertex != parent) {
            return 1;
        }

        temp = temp->next;
    }
    return 0;
}

int main() {
    int n, m, u, v;
    int i;
    int cycleFound = 0;

    printf("=== Task Dependency Graph (Cycle Detection) ===\n");

    printf("Enter number of tasks (vertices): ");
    scanf("%d", &n);

    printf("Enter number of dependencies (edges): ");
    scanf("%d", &m);

    for (i = 0; i < n; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    printf("Enter dependencies (u v):\n");

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            if (detectCycle(i, -1)) {
                cycleFound = 1;
                break;
            }
        }
    }

    if (cycleFound)
        printf("\nCycle Detected: Circular dependency exists!\n");
    else
        printf("\nNo Cycle Detected: Tasks can be completed safely.\n");

    return 0;
}
