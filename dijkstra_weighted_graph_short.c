#include <stdio.h>
#include <limits.h>

#define MAX 1005

/*
Algorithm (short):
1) dist[i]=INF, parent[i]=-1, vis[i]=0; dist[s]=0.
2) Repeat n times: pick unvisited u with minimum dist[u].
3) Mark u visited and relax all neighbors v.
4) If dist[t]==INF -> no path, else reconstruct via parent[].

Conclusion:
Dijkstra gives shortest path for graphs with non-negative weights.
Time: O(n^2), Space: O(n^2) using adjacency matrix.
*/

int g[MAX][MAX], d[MAX], p[MAX], vis[MAX], path[MAX];

int main() {
    int n, m, s, t;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) g[i][j] = 0;
        d[i] = INT_MAX;
        p[i] = -1;
        vis[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (g[u][v] == 0 || w < g[u][v]) g[u][v] = g[v][u] = w;
    }

    scanf("%d %d", &s, &t);
    d[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, mn = INT_MAX;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && d[j] < mn) mn = d[j], u = j;

        if (u == -1) break;
        vis[u] = 1;

        for (int v = 1; v <= n; v++)
            if (g[u][v] > 0 && !vis[v] && d[u] != INT_MAX && d[u] + g[u][v] < d[v])
                d[v] = d[u] + g[u][v], p[v] = u;
    }

    if (d[t] == INT_MAX) return puts("No Path Exists"), 0;

    printf("Shortest Distance: %d\nPath: ", d[t]);
    int c = 0;
    for (int x = t; x != -1; x = p[x]) path[c++] = x;
    while (c--) printf("%d ", path[c]);
    puts("");
    return 0;
}
