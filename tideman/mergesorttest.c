#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mergesort(int arrLen, int inputArr[], int outArr[]);

const int LARR = 10;

int main(void)
{
    // int inArr[LARR];
    int outArray[LARR];
    // for (i = 0; i < LARR; i++)
    // {
    //     inARR[i] = rand();
    // }
    int inArr[] = {2, 1, 3, 8, 1, 7, 3, 2, 10, 6};

    mergesort(LARR, inArr, outArray);

    for (int i = 0; i < LARR; i++)
    {
        printf("%i ", outArray[i]);
    }
    printf("\n");
}

void mergesort(int arrLen, int inputArr[], int outArr[])
{
    if (arrLen > 1)
    {
        // Divide into 2 halves
        int lLeft = arrLen / 2;
        int lRight = arrLen - lLeft;

        int leftArr[lLeft];
        int rightArr[lRight];

        // Copy halves to the new arrays
        for (int i = 0; i < lLeft; i++)
        {
            leftArr[i] = inputArr[i];
        }
        for (int i = 0; i < lRight; i++)
        {
            rightArr[i] = inputArr[i + lLeft];
        }

        // Recursively call mergesort
        int leftArrSorted[lLeft];
        int rightArrSorted[lRight];

        mergesort(lLeft, leftArr, leftArrSorted);
        mergesort(lRight, rightArr, rightArrSorted);

        // Merge sorted halves
        int k = 0, l = 0;
        for (int n = 0; n < arrLen; n++)
        {
            if (k == lLeft)
            {
                outArr[n] = rightArrSorted[l];
                l++;
            }
            else if (l == lRight)
            {
                outArr[n] = leftArrSorted[k];
                k++;
            }
            else
            {
                if (leftArrSorted[k] <= rightArrSorted[l])
                {
                    outArr[n] = leftArrSorted[k];
                    k++;
                }
                else if (leftArrSorted[k] > rightArrSorted[l])
                {
                    outArr[n] = rightArrSorted[l];
                    l++;
                }
            }
        }

    }
    else
    {
        outArr[0] = inputArr[0];
    }
}