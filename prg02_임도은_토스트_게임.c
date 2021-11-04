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

// �佺Ʈ_���빰 ����
int arr[5] = { "��", "��", "��", "��", "��" };

void initialize(int, int);

void initialize(int start_x, int start_y) {
    // ��, �Ʒ� ���κ� 
    for (int i = 0; i < WIDTH; i++) {
        board[0][i] = board[HEIGHT - 1][i] = '#';
    }

    // ������ ����
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            board[i][j] = ' ';
        }
    }
    // ��, �� ���κ�
    for (int i = 0; i < HEIGHT; i++) {
        board[i][0] = board[i][WIDTH - 1] = '#';
    }
}

// �մ� ȭ�� ��� 
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

    //���� ������ġ ����
    char inner = arr[rand() % 5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            int rx = 8 - i;
            int ry = 4 + j;
            board[rx][ry] = inner; //����: ����� ��µ�.
        }
    }


}

int main(void) {
    TOAST toast_arr[2] =
    { "�Ŧ�������������������", "�Ǧ�������������������" };

    initialize(1, 1);

    //for (int i = 0; i < 4; i++) {
    //    printf("%s", toast_arr[i].no2);
    //    printf("\n");
    //}
    for (int i = 0; i < 2; i++) {
        print_toast(toast_arr[i]);
    }

    // ���� ����
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