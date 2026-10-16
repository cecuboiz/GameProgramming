# Slide Bar Control Program

경성대학교 게임프로그래밍 실습 및 과제 프로그램으로, Windows 콘솔 환경에서 화살표 키를 이용해 수평 및 수직 슬라이드 바를 조절하고 현재 위치의 좌표값을 실시간으로 표시하는 C 언어 프로그램입니다.

## 주요 기능 (Key Features)
- **테두리 및 박스 생성 (`draw_rectangle`)**: 확장 아스키 코드를 활용하여 콘솔 화면에 깔끔한 사각형 테두리를 그립니다.
- **수직 슬라이드 바 (`draw_vertical_slide`)**: 상하 방향키(`↑`, `↓`)를 이용해 바를 이동시키고 현재 `y` 좌표를 숫자로 출력합니다.
- **수평 슬라이드 바 (`draw_horizontal_slide`)**: 좌우 방향키(`←`, `→`)를 이용해 바를 이동시키고 현재 `x` 좌표를 숫자로 출력합니다.
- **방향키 이동 제어 (`move_arrow_key`)**: 입력된 키에 따라 좌표를 갱신하며, 지정된 최소/최대 범위를 벗어나지 않도록 안전장치를 포함하고 있습니다.
- **콘솔 커서 제어 (`gotoxy`)**: `windows.h` 라이브러리의 `SetConsoleCursorPosition`을 사용하여 화면의 원하는 위치에 자유롭게 도형과 텍스트를 출력합니다.

## 시스템 구성 (Functions Overview)
- `void gotoxy(int x, int y)`: 콘솔 커서의 위치를 지정 좌표로 이동
- `void draw_rectangle(int c, int r)`: 지정된 크기의 사각형 테두리 출력
- `void draw_vertical_slide(...)`: 수직 슬라이드 바와 바디, 위치값 렌더링
- `void draw_horizontal_slide(...)`: 수평 슬라이드 바와 바디, 위치값 렌더링
- `void move_arrow_key(...)`: 화살표 키 입력에 따른 좌표 증감 및 유효성 검사

## 개발 환경 (Development Environment)
- **Language**: C
- **Compiler**: GCC (MinGW-w64), Dev-C++
- **OS**: Windows (CMD / PowerShell)
- **Libraries**: `stdio.h`, `stdlib.h`, `conio.h`, `windows.h`

## 실행 방법 (How to Run)
1. 소스 코드를 컴파일합니다.
   ```cmd
   gcc program.c -o program.exe
