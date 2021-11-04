#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <limits.h>

#define WIDTH   18
#define HEIGHT  10

char board[HEIGHT][WIDTH];

typedef struct {
    char no1[50];
    char no2[50];
} TOAST;

// 토스트_내용물 설정
int arr[5] = { "■", "Ξ", "∴", "∬", "△" };

void initialize(int, int);

void initialize(int start_x, int start_y) {
    // 위, 아래 가로벽 
    for (int i = 0; i < WIDTH; i++) {
        board[0][i] = board[HEIGHT - 1][i] = '#';
    }

    // 안쪽의 공백
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            board[i][j] = ' ';
        }
    }
    // 좌, 우 세로벽
    for (int i = 0; i < HEIGHT; i++) {
        board[i][0] = board[i][WIDTH - 1] = '#';
    }
}

// 손님 화면 출력 
void display() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void print_toast(TOAST pf);

void print_toast(TOAST pf) {
    printf("%s\n%s\n",
        pf.no2,
        pf.no1);

    //안쪽 샌드위치 설정
    char inner = arr[rand() % 5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            int rx = 8 - i;
            int ry = 4 + j;
            board[rx][ry] = inner; //문제: 상수로 출력됨.
        }
    }


}

int main(void) {
    TOAST toast_arr[2] =
    { "┖━━━━━━━━━┚", "┎━━━━━━━━━┒" };

    initialize(1, 1);

    //for (int i = 0; i < 4; i++) {
    //    printf("%s", toast_arr[i].no2);
    //    printf("\n");
    //}
    for (int i = 0; i < 2; i++) {
        print_toast(toast_arr[i]);
    }

    // 랜덤 실험
    for (int i = 0; i < 10; i++) {
        printf("%s", arr[rand() % 5]);
    }
    printf("\n");

    while (1) {
        display();
        Sleep(500);
        system("cls");
    }

    return 0;
}