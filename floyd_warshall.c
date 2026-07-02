#include <stdio.h>

#define MAX 505
#define INF 1000000000

/*
Algorithm (Floyd-Warshall):
1) Initialize dist matrix from graph weights.
2) dist[i][i] = 0, and missing edges = INF.
3) For each intermediate node k:
   For each pair (i, j):
   dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).
4) Final dist[i][j] gives shortest path from i to j.

Conclusion:
Floyd-Warshall computes all-pairs shortest paths in weighted graphs
(works with negative edges, but no negative cycles).
Time: O(V^3), Space: O(V^2).
*/

int dist[MAX][MAX];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (w < dist[u][v]) dist[u][v] = w;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (dist[k][j] == INF) continue;
                int through_k = dist[i][k] + dist[k][j];
                if (through_k < dist[i][j]) dist[i][j] = through_k;
            }
        }
    }

    printf("All-Pairs Shortest Delivery Times:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] >= INF / 2) printf("INF ");
            else printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
