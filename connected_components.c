#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

/*
Algorithm (DFS for Connected Components):
1) Build adjacency list for the undirected graph.
2) Initialize visited[i] = false for all nodes.
3) Component counter = 0.
4) For each unvisited node i:
   - Increment component counter.
   - Run DFS(i) to mark all reachable nodes as visited.
   - Store all nodes visited in this DFS as one component.
5) After processing all nodes:
   - Number of times DFS was initiated = number of components.
   - Each component is a group of connected nodes.

Conclusion:
Finding connected components identifies isolated groups in a graph.
Useful for social networks (friend groups), network partitioning, and clustering.
Time Complexity: O(V + E)
Space Complexity: O(V + E)
*/

int h[MAX], to[MAX*2], nxt[MAX*2], idx;
int vis[MAX], comp[MAX];
int compNode[MAX][MAX], compSize[MAX];

void add(int u, int v) {
    to[idx] = v;
    nxt[idx] = h[u];
    h[u] = idx++;
}

void dfs(int u, int c) {
    vis[u] = 1;
    compNode[c][compSize[c]++] = u;

    for (int e = h[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (!vis[v]) dfs(v, c);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) h[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }

    int compCount = 0;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, compCount);
            compCount++;
        }
    }

    printf("Number of Connected Components: %d\n", compCount);

    for (int c = 0; c < compCount; c++) {
        printf("Component %d: ", c + 1);
        for (int j = 0; j < compSize[c]; j++) {
            printf("%d ", compNode[c][j]);
        }
        printf("\n");
    }

    return 0;
}
