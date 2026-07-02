#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

/*
Algorithm (Kruskal's MST):
1) Read all edges of the weighted undirected graph.
2) Sort edges in non-decreasing order of weight.
3) Use Disjoint Set Union (DSU) to track connected components.
4) Pick the smallest edge that does not form a cycle.
5) Add it to MST and union the two sets.
6) Stop when MST has (V - 1) edges.

Conclusion:
Kruskal's algorithm connects all vertices with minimum total cost.
It is ideal for road, cable, and island-connection problems.
Time Complexity: O(E log E)
*/

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX];
int parent[MAX], rankv[MAX];

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (rankv[a] < rankv[b]) parent[a] = b;
    else if (rankv[a] > rankv[b]) parent[b] = a;
    else parent[b] = a, rankv[a]++;
    return 1;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    for (int i = 1; i <= V; i++) parent[i] = i, rankv[i] = 0;

    for (int i = 0; i < E; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    qsort(edges, E, sizeof(Edge), cmp);

    int cost = 0, cnt = 0;
    printf("Edges in MST:\n");

    for (int i = 0; i < E && cnt < V - 1; i++) {
        if (unite(edges[i].u, edges[i].v)) {
            cost += edges[i].w;
            cnt++;
            printf("%d - %d : %d\n", edges[i].u, edges[i].v, edges[i].w);
        }
    }

    if (cnt != V - 1) {
        printf("MST not possible\n");
    } else {
        printf("Minimum Cost: %d\n", cost);
    }

    return 0;
}
