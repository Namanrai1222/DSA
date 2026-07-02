#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];

    // Input using pointer
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> *(arr + i);
    }

    // Print using pointer
    cout << "Array elements are: ";
    for (int i = 0; i < n; i++) {
        cout << *(arr + i) << " ";
    }

    return 0;
}