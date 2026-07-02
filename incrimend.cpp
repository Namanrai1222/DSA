#include <iostream>
using namespace std;


void incrementArrayValueByOne(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = arr[i] + 1;
    }
}

int main()
{
    int n;

    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Function call
    incrementArrayValueByOne(arr, n);

    cout << "Array after incrementing by 1: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}