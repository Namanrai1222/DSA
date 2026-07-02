#include <stdio.h>
#include <string.h>

#define MAX 1005

/*
Algorithm (LCS - Dynamic Programming):
1) Let dp[i][j] be LCS length for prefixes s1[0..i-1] and s2[0..j-1].
2) If s1[i-1] == s2[j-1], dp[i][j] = 1 + dp[i-1][j-1].
3) Else dp[i][j] = max(dp[i-1][j], dp[i][j-1]).
4) LCS length is dp[n][m].
5) Reconstruct LCS by backtracking from dp[n][m].

Conclusion:
LCS helps identify common DNA patterns between two sequences.
Time Complexity: O(n*m), Space Complexity: O(n*m).
*/

int dp[MAX][MAX];
char s1[MAX], s2[MAX], lcs[MAX];

int main() {
    scanf("%s", s1);
    scanf("%s", s2);

    int n = (int)strlen(s1), m = (int)strlen(s2);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    int len = dp[n][m];
    lcs[len] = '\0';

    int i = n, j = m, k = len - 1;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[k--] = s1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS Length: %d\n", len);
    printf("LCS: %s\n", lcs);
    return 0;
}
