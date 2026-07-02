#include <stdio.h>

#define N 100005
#define M 200005

/*
Algorithm (Kahn's Algorithm - BFS Topological Sort):
1) Build directed graph and compute in-degree of each node.
2) Push all nodes with in-degree 0 into a queue.
3) While queue is not empty:
   - Pop a node u and add it to topological order.
   - For each edge u -> v, decrement in-degree[v].
   - If in-degree[v] becomes 0, push v into queue.
4) If processed nodes count is n, topological order exists.
5) If processed nodes count is less than n, graph has a cycle,
   so valid task scheduling is not possible.

Conclusion:
Topological sort gives a valid dependency-based task schedule for DAGs.
Kahn's algorithm also detects cycles: if a cycle exists, no valid order exists.
Time Complexity: O(V + E)
Space Complexity: O(V + E)
*/

int head[N], to[M], nxt[M], indeg[N], q[N], order[N], idx;

void addEdge(int u, int v) {
    to[idx] = v;
    nxt[idx] = head[u];
    head[u] = idx++;
    indeg[v]++;
}

int main() {
    int n, m, u, v;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int front = 0, rear = 0, cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) q[rear++] = i;
    }

    while (front < rear) {
        int cur = q[front++];
        order[cnt++] = cur;

        for (int e = head[cur]; e != -1; e = nxt[e]) {
            int nx = to[e];
            indeg[nx]--;
            if (indeg[nx] == 0) q[rear++] = nx;
        }
    }

    if (cnt != n) {
        printf("Cycle Detected: Topological order not possible\n");
        return 0;
    }

    printf("Topological Order: ");
    for (int i = 0; i < cnt; i++) printf("%d ", order[i]);
    printf("\n");

    return 0;
}
