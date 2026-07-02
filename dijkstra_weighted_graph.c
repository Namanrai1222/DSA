#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 1005

/*
Algorithm (Dijkstra for non-negative weighted graph):
1) Build adjacency matrix graph[u][v] with edge weight w.
2) Initialize:
   dist[i] = INF, visited[i] = false, parent[i] = -1.
3) Set dist[start] = 0.
4) Repeat up to n times:
   - Pick unvisited node u with minimum dist[u].
   - If no such node exists, stop.
   - Mark u visited.
   - Relax every neighbor v of u:
     if dist[u] + graph[u][v] < dist[v], update dist[v] and parent[v].
5) If dist[end] is INF, path does not exist.
6) Else dist[end] is shortest distance; recover route via parent[] from end to start.

Conclusion:
Dijkstra finds the fastest route in a weighted graph with non-negative edge weights.
Time Complexity: O(n^2) with adjacency matrix.
Space Complexity: O(n^2).
*/

int graph[MAX][MAX], dist[MAX], parent[MAX], path[MAX];
bool visited[MAX];

int main(void) {
    int n, m;
    int start, end;

    printf("Enter number of cities (vertices) and roads (edges): ");
    if (scanf("%d %d", &n, &m) != 2) return 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) graph[i][j] = 0;
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    printf("Enter edges in format (u v w):\n");
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (w < 0) {
            printf("Negative weight not allowed for Dijkstra\n");
            return 0;
        }
        if (graph[u][v] == 0 || w < graph[u][v]) {
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }

    printf("Enter start city and destination city: ");
    scanf("%d %d", &start, &end);

    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, mn = INT_MAX;

        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < mn) {
                mn = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] > 0 && !visited[v] && dist[u] != INT_MAX) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    if (dist[end] == INT_MAX) {
        printf("No Path Exists\n");
        return 0;
    }

    printf("Shortest distance from %d to %d is: %d\n", start, end, dist[end]);

    int cnt = 0;
    for (int x = end; x != -1; x = parent[x]) path[cnt++] = x;

    printf("Path: ");
    for (int i = cnt - 1; i >= 0; i--) printf("%d ", path[i]);
    printf("\n");

    return 0;
}
