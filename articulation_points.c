#include <stdio.h>

#define N 100005
#define M 400005

/*
Algorithm (Articulation Points - DFS):
1) Run DFS and store discovery time disc[u] and low[u].
2) For each tree edge u -> v, after DFS(v):
   - low[u] = min(low[u], low[v]).
   - If u is not root and low[v] >= disc[u], u is articulation point.
3) Root is articulation point if it has more than one DFS child.
4) For back edge u -> v (v != parent[u]), update low[u] = min(low[u], disc[v]).

Conclusion:
Articulation points are critical servers: removing them disconnects the network.
Time Complexity: O(V + E), Space Complexity: O(V + E).
*/

int head[N], to[M], nxt[M], idx;
int disc[N], low[N], par[N], ap[N], timer;

void addEdge(int u, int v) {
    to[idx] = v;
    nxt[idx] = head[u];
    head[u] = idx++;
}

void dfs(int u) {
    disc[u] = low[u] = ++timer;
    int child = 0;

    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];

        if (!disc[v]) {
            par[v] = u;
            child++;
            dfs(v);

            if (low[v] < low[u]) low[u] = low[v];
            if (par[u] != -1 && low[v] >= disc[u]) ap[u] = 1;
        } else if (v != par[u] && disc[v] < low[u]) {
            low[u] = disc[v];
        }
    }

    if (par[u] == -1 && child > 1) ap[u] = 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) head[i] = -1, par[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    for (int i = 1; i <= n; i++) if (!disc[i]) dfs(i);

    int found = 0;
    printf("Articulation Points: ");
    for (int i = 1; i <= n; i++) {
        if (ap[i]) {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found) printf("None");
    printf("\n");
    return 0;
}
