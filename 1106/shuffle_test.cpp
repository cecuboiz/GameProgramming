#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 3
#define TRIES 60000
int main(void)
{
    int cnt[2][6]={0}, o[N], i, k, m, rnd, temp;
    srand(time(NULL));
    for(m=0;m<2;m++)
        for(k=0;k<TRIES;k++)
        {
            for(i=0;i<N;i++) o[i]=i;
            if(m==0)                      /* ?? */
                for(i=0;i<N;i++) { rnd=rand()%N; temp=o[i]; o[i]=o[rnd]; o[rnd]=temp; }
            else                          /* Fisher-Yates */
                for(i=N-1;i>0;i--) { rnd=rand()%(i+1); temp=o[i]; o[i]=o[rnd]; o[rnd]=temp; }
            cnt[m][o[0]*2+(o[1]>o[2])]++; /* ?? 6??? ?? ??? */
        }
    printf("순서      원본    Fisher-Yates\n");
    for(i=0;i<6;i++)
        printf("%d번   %6.1f%%   %6.1f%%\n", i+1, cnt[0][i]*100.0/TRIES, cnt[1][i]*100.0/TRIES);
    return 0;
}
