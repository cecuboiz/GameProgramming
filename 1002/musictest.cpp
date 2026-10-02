#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

int calc_frequency(int octave, int inx);
void practice_piano(void);

int main(void)
{
    printf("1부터 8까지 숫자 키를 누르면\n");
    printf("각 음의 소리가 출력됩니다.\n\n");
    printf("1:도 2:레 3:미 4:파 5:솔 6:라 7:시 8:도\n");
    printf("프로그램 종료는 Esc키 \n");
    
    practice_piano();
    
    return 0;
}

// 옥타브와 음의 인덱스에 따른 주파수(Hz) 계산 함수
int calc_frequency(int octave, int inx)
{
    // 도, 레, 미, 파, 솔, 라, 시, 높은도 (C, D, E, F, G, A, B, C) 의 반음 오프셋 배열
    int offsets[8] = { 0, 2, 4, 5, 7, 9, 11, 12 };
    
    if (inx < 0 || inx > 7) return 0;
    
    // 표준 음계 주파수 공식 활용 (4옥타브 기준 A4 = 440Hz)
    int semitone = offsets[inx] + (octave - 4) * 12;
    double freq = 440.0 * pow(2.0, (semitone - 9.0) / 12.0);
    
    return (int)freq;
}

// 키보드 입력을 받아 피아노 소리를 내는 함수
void practice_piano(void)
{
    int key;
    int octave = 4; // 기본 옥타브 설정 (4옥타브)
    
    while (1) {
        if (_kbhit()) {
            key = _getch();
            
            // ESC 키(ASCII 코드 27)를 누르면 프로그램 종료
            if (key == 27) {
                printf("\n프로그램을 종료합니다.\n");
                break;
            }
            
            // '1' ~ '8' 숫자 키 입력 처리
            if (key >= '1' && key <= '8') {
                int inx = key - '1'; // 문자 '1'~'8'을 0~7 인덱스로 변환
                int freq = calc_frequency(octave, inx);
                
                printf("키 '%c' 입력 -> %d Hz 재생\n", key, freq);
                Beep(freq, 300); // 300 밀리초(ms) 동안 비프음 발생
            }
        }
    }
}
