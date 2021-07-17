#include <iostream>
//#define SIZE (1 << 4) // 2^19  524288
#define SIZE 10
using namespace std;

void bucketSort(int a[], int n)
{
     int i, j, k, buckets[SIZE];

     for (i = 0; i < SIZE; ++i)
          buckets[i] = 0;

     for (i = 0; i < n; ++i)
     {
          ++buckets[a[i]];
          cout << buckets[a[i]] << "\t";
     }
     cout << endl;

     // cout << "BUCKET" << endl;
     // for (i = 0; i < SIZE; i++)
     //      cout << buckets[i] << "\t";
     // cout << "END BUCKET" << endl;

     for (i = 0, j = 0; j < SIZE; ++j)
          for (k = buckets[j]; k > 0; --k)
          {
               a[i++] = j;
               //cout<<a[i]<<"\t";
          }
}

int main()
{
     int i, a[] = {3, 6, 5, 1, 8, 3, 9, 4}, n = 8;
     // float m[SIZE];
     // /* 2^11 = 2048 and 2^12 = 4096 */
     // srand(time(NULL));

     // for (i = 0; i < SIZE; i++)
     // {
     //      m[i] = (float)(rand() % SIZE) + (float)(rand() % SIZE) * 0.01;
     //      printf("%.2f ", m[i]);
     // }

     cout << "Before sorting:\n";
     for (i = 0; i < n; ++i)
          cout << a[i] << " ";
     cout << endl;

     bucketSort(a, n);

     cout << "\n\nAfter sorting:\n";
     for (i = 0; i < n; ++i)
          cout << a[i] << " ";
     cout << endl;

     return 0;
}
