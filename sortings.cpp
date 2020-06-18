/*
    Sylar Zhang - March 2020
   
    5 sortings:
       (1) SelectionSort
       (2) InsertionSort
       (3) MergeSort
       (4) QuickSort
       (5) BubbleSort
       
    Note: 
       (1) Time & Space Complexity in worst case scenario.
       (2) Algorithm realization with address of elements can use "void" return.
*/

#include <iostream>
#include <assert.h>

using namespace std;

int* selectionSort(int* _a, int _size);
int* insertionSort(int* _a, int _size);
int* mergeSort(int* _a, int l, int r);
int* merge(int* _a, int l, int r, int m);
int* quickSort(int* _a, int start, int end);
int partition(int* a, int start, int end);
int* bubbleSort(int* _a, int _size);

/* 
// For C cases - Define swap(&a, &b);
void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
} 
*/ 

template <class T>
void printArray(T* _a, int _size) {
    cout << "size: "<<_size<<endl;
    for (int i = 0; i < _size; ++i) {
        if (i == _size - 1)
            cout << _a[i] << endl;
        else
            cout << _a[i] << ", ";
    }
}

template <class T>
void compareArray(T* _a, T* _b, int _size) {
    for (int i = 0; i < _size; ++i)
        assert(_a[i] == _b[i]); // fail
    return;
}

int main () {
    int a[] =   {1, 5, 6, 8, 12, 5, -99, 99, 4, 3, 3, 1, 7, 10, -1, -2, -9, 11};
    int ans[] = {-99, -9, -2, -1, 1, 1, 3, 3, 4, 5, 5, 6, 7, 8, 10, 11, 12, 99};
    int *res = 0;
    int size = sizeof(a)/sizeof(*a);
    //res = selectionSort(a, size);
    //res = insertionSort(a, size);
    //res = mergeSort(a, 0, size - 1);
    //res = quickSort(a, 0, size - 1);
    res = bubbleSort(a, size);
    printArray(res, size);
    compareArray(res, ans, size);
    cout << "Success!\n";
    return 0;
}

// Pass an array: (int* _a) or (int _a[]) 
// Return an array: return _a; 
int* selectionSort(int* _a, int _size) {
    // Time: n^2 (for all cases), Space 1
    for (int i = 0; i < _size; ++i) {
        int min_ind = i;
        for (int j = i + 1; j < _size; ++j) {
            if (_a[j] < _a[min_ind])
                min_ind = j;
        }
        swap(_a[i], _a[min_ind]);
    }
    return _a;
}

int* insertionSort(int* _a, int _size) {
    // Time: n^2, Space 1
    // Note that the best Time Complexity is n
    if (_size <= 1)
        return _a;
    
    for (int i = 1; i < _size; ++i) {
        int value = _a[i];
        int hole = i;
        while (hole > 0 && _a[hole - 1] > value) {
            _a[hole--] = _a[hole - 1];
        }
        _a[hole] = value;
    }
    return _a;
}

int* mergeSort(int* _a, int l, int r) {
    // Time: nlogn (for all cases), Space n 
    int m;
	if (l < r) {
		//mid=(low+high)/2;
        m = l + (r - l)/2;
		// Split the data into two half.
		mergeSort(_a, l, m);
		mergeSort(_a, m + 1, r);
 
		// Merge them to get sorted output.
		_a = merge(_a, l, r, m);    
	}
    return _a;
}

int* merge(int* _a, int l, int r, int m)
{
	// i for left array index, j for right array index, k for temp (new) array index.
	int i, j, k, temp[r - l + 1];
	i = l;
	k = 0;
	j = m + 1;
 
	// Merge the two parts into temp[].
	while (i <= m && j <= r) {
		if (_a[i] < _a[j])
			temp[k++] = _a[i++];
		else
			temp[k++] = _a[j++];
	}
 
	// Insert all the remaining values from i to mid into temp[].
	while (i <= m)
		temp[k++] = _a[i++];
 
	// Insert all the remaining values from j to right into temp[].
	while (j <= r)
		temp[k++] = _a[j++];

	// Assign sorted data stored in temp[] to a[].
	for (i = l; i <= r; ++i)
		_a[i] = temp[i - l];
    
    return _a;
}

int* quickSort(int* _a, int start, int end) {
    // Time: n^2, Space logn 
    // Note that average and best Time Complexity is nlogn
    // which is most likly to happen.
    if (start < end) {
        int p_index = partition(_a, start, end); 
        quickSort(_a, start, p_index - 1);
        quickSort(_a, p_index + 1, end);
    }
    return _a;
}

int partition(int* _a, int start, int end) {
    int pivot = _a[end];
    int p_index = start;
    for (int i = start; i < end; ++i) {
        if (_a[i] <= pivot)
            swap(_a[i], _a[p_index++]);
    }
    swap(_a[p_index], _a[end]);
    return p_index;
}

int* bubbleSort(int* _a, int _size) {
    // Time: n^2 (Worst = Ave), Space 1 
    // Note that the best case of Time Complexity is n
    if (_size < 2) 
        return _a;
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size - i - 1; ++j) {
            if (_a[j] > _a[j + 1])
                swap(_a[j], _a[j + 1]);
        }
    }
    return _a;
}
