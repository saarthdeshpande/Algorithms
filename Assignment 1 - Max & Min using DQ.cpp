#include<iostream>
using namespace std;

void MinMax(int arr[], int low, int high, int &max, int &min) {
    int min1, min2, max1, max2;
    if(low == high) {         // only 1 element in array
        max = arr[low];
        min = arr[low];
        return;
    }
    if(high == low + 1) {       // two elements in array
        if(arr[low] > arr[high]) {
            min = arr[high];
            max = arr[low];
        } else {
            min = arr[low];
            max = arr[high];
        }
        return;
    }

    int mid = low + (high - low) / 2;             // more than 2 elements in an array
    MinMax(arr, low, mid,max1,min1);
    MinMax(arr,mid + 1, high,max2,min2);

    min1 < min2 ? min = min1 : min = min2;
    max1 > max2 ? max = max1 : max = max2;

    return;
}

int main() {
    int n, max, min, asc_flag = 1, desc_flag = 1;
    cout << "Size of Array: ";
    cin >> n;
    int a[n];
    cout << "Enter elements of array: ";
    for (int i = 0;i < n;i++) {
        cin >> a[i];
        if (i > 0) {
            a[i - 1] >= a[i] ? asc_flag = 0 : desc_flag = 0;
        }
    }

    if (asc_flag) {
        cout << "Smallest element: " << a[0] << endl;
        cout << "Largest element: " << a[n - 1] << endl;
    } else if (desc_flag) {
        cout << "Smallest element: " << a[n - 1] << endl;
        cout << "Largest element: " << a[0] << endl;
    } else {
        MinMax(a, 0, n - 1, max, min);
        cout << "Smallest element: " << min << endl;
        cout << "Largest element: " << max << endl;
    }
    return 0;
}

