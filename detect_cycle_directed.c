#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Algorithm (DFS + Recursion Stack) for Directed Cycle Detection:
1) Keep two arrays:
    visited[node]  -> node was seen before
    recStack[node] -> node is in current DFS path
2) Run DFS from every unvisited node.
3) For each edge node -> next:
    - if next is unvisited, DFS(next)
    - else if recStack[next] is true, back-edge found => cycle
4) Before returning from DFS(node), set recStack[node] = false.
5) If any DFS reports cycle, graph has circular dependency.
*/

#define MAX 100005

int n, m;
int *adj[MAX];
int size[MAX];

bool visited[MAX];
bool recStack[MAX];

bool detectCycle(int node) {
    visited[node] = true;
    recStack[node] = true;

    for (int i = 0; i < size[node]; i++) {
        int next = adj[node][i];

        if (!visited[next]) {
            if (detectCycle(next))
                return true;
        }
        else if (recStack[next]) {
            return true;
        }
    }

    recStack[node] = false;
    return false;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        adj[i] = (int *)malloc(n * sizeof(int));
        size[i] = 0;
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][size[u]++] = v;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (detectCycle(i)) {
                printf("Cycle Detected\n");
                return 0;
            }
        }
    }

    printf("No Cycle Detected\n");
    return 0;
}
