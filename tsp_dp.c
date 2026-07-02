#include <stdio.h>
#include <string.h>

#define MAXN 15
#define INF 1000000000

/*
Algorithm (TSP with Bitmask DP):
1) Let dp[mask][u] = minimum cost to start from city 0,
   visit all cities in mask, and end at city u.
2) Initialize dp[1][0] = 0 (only city 0 visited).
3) For each state (mask, u), try going to unvisited city v:
   dp[mask | (1<<v)][v] = min(dp[mask][u] + cost[u][v]).
4) Final answer:
   min over u: dp[(1<<n)-1][u] + cost[u][0].

Conclusion:
Bitmask DP solves TSP optimally for small n (typically n <= 15-20).
Time Complexity: O(n^2 * 2^n)
Space Complexity: O(n * 2^n)
*/

int cost[MAXN][MAXN];
int dp[1 << MAXN][MAXN];
int parent[1 << MAXN][MAXN];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    int totalMask = 1 << n;

    for (int m = 0; m < totalMask; m++) {
        for (int u = 0; u < n; u++) {
            dp[m][u] = INF;
            parent[m][u] = -1;
        }
    }

    dp[1][0] = 0;

    for (int mask = 1; mask < totalMask; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;

            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;

                int nextMask = mask | (1 << v);
                int newCost = dp[mask][u] + cost[u][v];

                if (newCost < dp[nextMask][v]) {
                    dp[nextMask][v] = newCost;
                    parent[nextMask][v] = u;
                }
            }
        }
    }

    int full = totalMask - 1;
    int ans = INF, lastCity = -1;

    for (int u = 0; u < n; u++) {
        if (dp[full][u] == INF) continue;
        int tourCost = dp[full][u] + cost[u][0];
        if (tourCost < ans) {
            ans = tourCost;
            lastCity = u;
        }
    }

    if (ans >= INF / 2) {
        printf("No Hamiltonian Tour Possible\n");
        return 0;
    }

    printf("Minimum Tour Cost: %d\n", ans);

    int route[MAXN + 1], idx = 0;
    int mask = full, cur = lastCity;

    while (cur != -1) {
        route[idx++] = cur;
        int p = parent[mask][cur];
        mask ^= (1 << cur);
        cur = p;
    }

    printf("Tour: 0 ");
    for (int i = idx - 2; i >= 0; i--) printf("-> %d ", route[i]);
    printf("-> 0\n");

    return 0;
}
