#include <stdio.h>
#include <math.h>


void print_frequency(int octave);

int main(void)
{
    
    const char *scale[] = {
        "도", "도#", "레", "레#", "미", 
        "파", "파#", "솔", "솔#", "라", "라#", "시", "도"
    };
    
    int i, octave;
    
    printf("음계와 주파수\n\n음계\t   ");
    for (i = 0; i < 12; i++)
        printf("%-5s", scale[i]);
    printf("\n");
    
    for (i = 0; i <= 70; i++)
        printf("-");
    printf("\n");
    
    for (octave = 1; octave < 7; octave++)
        print_frequency(octave);
        
    return 0;
}


void print_frequency(int octave)
{
    int i;
    printf("%d옥타브\t", octave);
    
    for (i = 0; i < 12; i++) {
     
        double freq = 16.3516 * pow(2.0, (double)octave + (double)i / 12.0);
        printf("%-5.1f", freq);
    }
    printf("\n");
}
