#include <iostream>
using namespace std;
bool isPrime(int n, int i) {
    if (n <= 1)
        return false;

    if (i == 1)
        return true;

    if (n % i == 0)
        return false;

    return isPrime(n, i - 1);
}

int main() {
    int num;

    cout << "Enter a number: ";
    cin >> num;

    if (isPrime(num, num / 2))
        cout << num << " is a Prime Number.";
    else
        cout << num << " is not a Prime Number.";

    return 0;
}