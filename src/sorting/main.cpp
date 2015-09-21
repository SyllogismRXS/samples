#include <iostream>
#include <queue>
#include <stdio.h>

#define DEBUG 1

void print(int s[], int size)
{
     for (int i = 0; i < size; i++) {
          printf("%d ",s[i]);
     }
     printf("\n");
}

void merge(int s[], int low, int middle, int high)
{
#if DEBUG
     printf("Low: %d\tMiddle: %d\tHigh: %d\n", low, middle, high);
#endif

     std::queue<int> q1, q2;
     
     for (int i = low; i <= middle; i++) {
#if DEBUG
          printf("q1 Pushing: %d\n", s[i]);
#endif
          q1.push(s[i]);
     }

     for (int i = middle+1; i <= high; i++) {
#if DEBUG
          printf("q2 Pushing: %d\n", s[i]);
#endif
          q2.push(s[i]);
     }

     // While both queues have elements remaining, pop from the array that has
     // the smaller element
     int k = low;
     while (!q1.empty() && !q2.empty()) {
          if (q1.front() <= q2.front()) {
               s[k++] = q1.front();
               q1.pop();
          } else {
               s[k++] = q2.front();
               q2.pop();
          }
     }

     // One of the queues still has elements in it, empty all elements and add to 
     // back of sorted array
     while (!q1.empty()) {
          s[k++] = q1.front();
          q1.pop();
     }

     while (!q2.empty()) {
          s[k++] = q2.front();
          q2.pop();
     }     
}

void mergesort(int s[], int low, int high)
{
     if (low < high) {
          int middle = (high + low) / 2;
          mergesort(s, low, middle);
          mergesort(s, middle+1, high);
          merge(s, low, middle, high);
     }
}

int main(int argc, char *argv[])
{
     printf("Sorting!\n");
 
#define ARRAY_SIZE 10
         
     int array[ARRAY_SIZE];
     array[0] = 5;
     array[1] = 2;
     array[2] = 7;
     array[3] = 3;
     array[4] = 11;
     array[5] = 15;
     array[6] = 1;
     array[7] = 0;
     array[8] = 4;
     array[9] = 20;

     printf("Unsorted: ");
     print(array, ARRAY_SIZE);

     mergesort(array, 0, ARRAY_SIZE-1);

     printf("Sorted: ");
     print(array, ARRAY_SIZE);
     
     return 0;
}
