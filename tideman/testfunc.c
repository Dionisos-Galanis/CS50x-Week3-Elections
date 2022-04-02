#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passarraypart(int n, int array[]);

// bool isalldigits(string str);

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Usage: testfun n1 n2 (n2>=n1; both >0 and <10)\n");
        return 1;
    }
    string str1 = argv[1];
    string str2 = argv[2];
    int n1 = 0, n2 = 0;

    if (strlen(str1) == 1 && strlen(str2) == 1)
    {
        if (isdigit(str1) && isdigit(str2))
        {
            n1 = (int) str1[0] - 48;
            n2 = (int) str2[0] - 48;
        }
    }
    else
    {
        printf("Usage: testfun n1 n2 (n2>=n1; both >0 and <10)\n");
        return 2;
    }

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    int newlength = n2 - n1 + 1;
    int arrpart[newlength];
    for (int i = 0; i < newlength; i++)
    {
        arrpart[i] = arr[i + n1 - 1];
    }

    passarraypart(newlength, arrpart);
}


// bool isalldigits(string str)
// {
//     for (int i = 0; i < strlen(str); i++)
//     {
//         if (!isdigit(str[i]))
//         {
//             return false;
//         }
//     }
//     rturn true;
// }

void passarraypart(int n, int array[])
{
    for (int i = 0; i < n; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}