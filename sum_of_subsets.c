#include <stdio.h>

#define MAX 100

/*
Algorithm (Backtracking - Sum of Subsets):
1) Start from index 0 with current sum = 0.
2) At each index, make two choices:
   - Include current element in subset.
   - Exclude current element.
3) If current sum becomes target, print the subset.
4) If current sum exceeds target or index reaches n, backtrack.
5) Continue until all possibilities are explored.

Conclusion:
Backtracking explores all candidate subsets and prints every subset
whose sum is exactly equal to the target amount.
*/

int arr[MAX], subset[MAX], n, target, found;

void printSubset(int len) {
    printf("{");
    for (int i = 0; i < len; i++) {
        printf("%d", subset[i]);
        if (i + 1 < len) printf(", ");
    }
    printf("}\n");
}

void solve(int idx, int sum, int len) {
    if (sum == target) {
        printSubset(len);
        found = 1;
        return;
    }

    if (idx == n || sum > target) return;

    subset[len] = arr[idx];
    solve(idx + 1, sum + arr[idx], len + 1);
    solve(idx + 1, sum, len);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    scanf("%d", &target);

    printf("Subsets with sum %d:\n", target);
    solve(0, 0, 0);

    if (!found) printf("No subset found\n");
    return 0;
}
