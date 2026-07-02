#include <stdio.h>

#define N 100005
#define M 400005

/*
Algorithm (BFS for Unweighted Graph):
1) Build adjacency list for the graph.
2) Initialize dist[] = -1 and parent[] = -1.
3) Push source node into queue, set dist[source] = 0.
4) Run BFS:
   - Pop a node u.
   - For each neighbor v of u, if dist[v] == -1:
     dist[v] = dist[u] + 1, parent[v] = u, push v.
5) If dist[target] is still -1, no path exists.
6) Otherwise, shortest distance is dist[target].
7) Reconstruct path by moving target -> parent[target] until -1, then print in reverse.

Conclusion:
In an unweighted graph, BFS always finds the shortest path in terms of number of edges.
Time Complexity: O(V + E)
Space Complexity: O(V + E)
*/

int head[N], to[M], nxt[M], idx;
int q[N], dist[N], parent[N], path[N];

void addEdge(int u, int v) {
    to[idx] = v;
    nxt[idx] = head[u];
    head[u] = idx++;
}

int main() {
    int n, m, u, v, s, t;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    scanf("%d %d", &s, &t);

    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
        parent[i] = -1;
    }

    int front = 0, rear = 0;
    q[rear++] = s;
    dist[s] = 0;

    while (front < rear) {
        int cur = q[front++];
        for (int e = head[cur]; e != -1; e = nxt[e]) {
            int nx = to[e];
            if (dist[nx] == -1) {
                dist[nx] = dist[cur] + 1;
                parent[nx] = cur;
                q[rear++] = nx;
            }
        }
    }

    if (dist[t] == -1) {
        puts("No Path Exists");
        return 0;
    }

    printf("Shortest Distance: %d\n", dist[t]);

    int cnt = 0;
    for (int x = t; x != -1; x = parent[x]) path[cnt++] = x;

    printf("Path: ");
    for (int i = cnt - 1; i >= 0; i--) printf("%d ", path[i]);
    puts("");

    return 0;
}
