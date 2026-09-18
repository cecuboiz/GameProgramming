#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int r[], int n);

int main(void)
{
    int i, j, lotto[6];
    srand(time(NULL));
    
    for(i=0; i<=5; i++)
    {
        lotto[i] = rand() % 45 + 1;
        for(j=0; j<i; j++)
        {
            if (lotto[i] == lotto[j])
            {
                i--;
                break;
            }
        }
    }
    
    selection_sort(lotto, 6);
    return 0;
}

void selection_sort(int r[], int n)
{
    int i, j, min, temp;
    
    // 수정: i는 n-1 까지만 반복 (0부터 4까지)
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        // 수정: j는 n 까지만 반복 (i+1부터 5까지)
        for (j = i + 1; j < n; j++)
        {
            if (r[j] < r[min])
                min = j;
        }
        temp = r[min];
        r[min] = r[i];
        r[i] = temp;
    }
    
    // 결과 출력
    for(i = 0; i < n; i++)
        printf("%2d\n", r[i]);
}
