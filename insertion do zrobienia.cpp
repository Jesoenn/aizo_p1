#include <iostream>

//wstawianie
template <typename T>
void insertionSort(T* array, int arrSize){
    for(int i=1; i<arrSize; i++) {
        T key = array[i];
        int j = i-1;
        while(j>=0 && array[j]>key){
            array[j+1]=array[j];
            j--;
        }
        array[j+1]=key; //j+1 because j i decreased
    }
}

int main() {
    int size = 10;
    int* tab = new int[10]{10,9,8,7,6,5,4,3,2,1};
    insertionSort(tab,size);
    for(int i =0 ; i<size; i++)
        std::cout<<tab[i]<<" ";
    return 0;
}
