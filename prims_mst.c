#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 1005

/*
Algorithm (Prim's MST - short):
1) Start from any vertex and mark it visited.
2) Pick the minimum weight edge from visited to unvisited vertex.
3) Add that edge to MST and mark the new vertex visited.
4) Repeat until all vertices are included.
5) The sum of selected edges gives the minimum cost.

Conclusion:
Prim's algorithm builds a minimum spanning tree by always choosing
an edge with the smallest weight that expands the current tree.
It is useful for designing low-cost networks.
Time Complexity: O(V^2) using adjacency matrix.
*/

int graph[MAX][MAX], key[MAX], parent[MAX];
bool vis[MAX];

int main() {
    int n, m, cost = 0;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) graph[i][j] = 0;

    for (int i = 1; i <= n; i++) key[i] = INT_MAX, vis[i] = false, parent[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (!graph[u][v] || w < graph[u][v]) graph[u][v] = graph[v][u] = w;
    }

    key[1] = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1, mn = INT_MAX;
        for (int j = 1; j <= n; j++) if (!vis[j] && key[j] < mn) mn = key[j], u = j;
        if (u == -1) break;
        vis[u] = true;
        for (int v = 1; v <= n; v++)
            if (graph[u][v] && !vis[v] && graph[u][v] < key[v]) key[v] = graph[u][v], parent[v] = u;
    }

    printf("Edges in MST:\n");
    for (int i = 2; i <= n; i++)
        if (parent[i] != -1) printf("%d - %d : %d\n", parent[i], i, graph[i][parent[i]]), cost += graph[i][parent[i]];

    printf("Minimum Cost: %d\n", cost);
    return 0;
}
