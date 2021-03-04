#include<iostream>
using namespace std;

void merge(int arr[], int low, int mid, int high)
{
    int n1 = mid - low + 1;     // number of elements in leftSubArray
    int n2 = high - mid;        // number of elements in rightSubArray
    int leftSubArray[n1], rightSubArray[n2];
 
    for (int i = 0; i < n1; i++)
        leftSubArray[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        rightSubArray[j] = arr[mid + 1 + j];
 
    int i = 0,j = 0,k = low;
 
    while (i < n1 && j < n2) {
        if (leftSubArray[i] <= rightSubArray[j])
            arr[k++] = leftSubArray[i++];
        else
            arr[k++] = rightSubArray[j++];
    }
    while (i < n1)
        arr[k++] = leftSubArray[i++];

    while (j < n2)
        arr[k++] = rightSubArray[j++];
}

void mergeSort(int arr[],int low,int high){
    if(low >= high){
        return;
    }
    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr,mid + 1, high);
    merge(arr, low, mid, high);
}

void processHorizontalMRT(int programs[], int n_tapes, int capacity[], float horizontalMRT[], int n_programs){
	int j = 0;
	int sum[n_tapes];
	for(int i = 0; i < n_tapes; ++i)   			// initialising array to 0
		sum[i] = horizontalMRT[i] = 0;

	int temp = 0;
	for (int i = 0; i < n_programs && j < n_tapes; ++i) {
		if(sum[j] + programs[i] > capacity[j]){   	// capacity exceeded ?
			horizontalMRT[j] = horizontalMRT[j] / (i - temp);			// calculate MRT for tape
			j++;								// next tape
			temp = i;							// to calculate number of programs in particular tape
		}
		sum[j] += programs[i];
		horizontalMRT[j] += sum[j];
	}
	if(j < n_tapes){								// calculate hMRT for last tape
		horizontalMRT[j] = horizontalMRT[j] / (n_programs - temp);
	}
}

void processVerticalMRT(int programs[], int n_tapes, int capacity[], float verticalMRT[], int n_programs){
	int j = 0;
	int sum[n_tapes], total[n_tapes];

	for (int i = 0; i < n_tapes; ++i)         	// initialising array to 0
		sum[i] = verticalMRT[i] = total[i] = 0;

	for (int i = 0; i < n_programs && j < n_tapes; ++i)
	{
		j = i % n_tapes;										// find location for programs
		while(sum[j] + programs[i] > capacity[j] && j < n_tapes)	// if capacity is exceeded
			j++;
		
		if(j == n_tapes)
			break;
		sum[j] += programs[i];
		verticalMRT[j] += sum[j];
		total[j]++; 								// storing no of programs in each tape
	}

	for (int i = 0; i < n_tapes; ++i)					// calculate vMRT for each tape
		verticalMRT[i] = verticalMRT[i] / total[i];
}

void printTapes(float arr[], int n) {
	for (int i = 0; i < n;i++)
		cout << "Tape #" << i + 1 << ": " << arr[i] << endl;
}

int main(){
	int n_tapes, n_programs;
	int flag = 0, flag1 = 0;

	cout << "Number of tapes: ";
	cin >> n_tapes;
	int capacity[n_tapes];
	cout << "\nTape Capacities: \n" ;
	for (int i = 0;i < n_tapes;i++) {
        cout << "Tape #" << i + 1 << ": ";
        cin >> capacity[i];
    }

	cout << "\nNumber of Programs: ";
	cin >> n_programs;

	int programs[n_programs];
	float horizontalMRT[n_tapes], verticalMRT[n_tapes];
	cout << "\nProgram Lengths: \n";
	for (int i = 0; i < n_programs; ++i) {
	    cout << "Program #" << i + 1 << ": ";
		cin >> programs[i];
		if(i > 0) {
			if(programs[i - 1] >= programs[i])
				flag = 1;
			else
				flag1 = 1;
		}
	}
	if (flag1 == 0) {        // reverse sorted?
		for (int i = 0; i < (n_programs / 2);i++) {
			int temp = programs[i];
			programs[i] = programs[n_programs - i - 1];
			programs[n_programs - i - 1] = temp;
		}
	} else if(flag == 1 && flag1 == 1)  // not sorted?
		mergeSort(programs,0,n_programs - 1);

	cout << endl << "Programs: ";
	for (int i = 0; i < n_programs; ++i)
		cout << programs[i] << "\t";
	cout << endl;
	
	// Horizontal MRT
	processHorizontalMRT(programs, n_tapes, capacity, horizontalMRT, n_programs);
	cout << "\nHorizontal MRT" << endl;
	printTapes(horizontalMRT, n_tapes);

	// Vertical MRT
	processVerticalMRT(programs, n_tapes, capacity, verticalMRT, n_programs);
	cout << "\nVertical MRT" << endl;
	printTapes(verticalMRT, n_tapes);

	return 0;
}