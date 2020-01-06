#include<stdio.h>

//sort algorithm

void swap (int *a , int *b)
{
    int temp= *a ;
    *a = *b ;
    *b = temp ;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1) , j;

    for (j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {

            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int partition_r(int arr[], int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);

    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//structures

struct Film
{
    int movieLen;
    char act[10][20] ;
};
struct Saans
{
    struct Film film ;
    int capacity ;
    int start , ending ;
};
struct Salons
{
    struct Saans saans[10];
};
struct Cinema
{
    struct Salons salons[10] ;
};
int main()
{

    return 0;
}
