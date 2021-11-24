#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <limits.h>

#define WIDTH   18
#define HEIGHT  10

char board_1[HEIGHT][WIDTH];
char board_2[HEIGHT][WIDTH];

// 토스트_내용물 설정
int arr[5] = {'@', '*', '^', '%', '='};
int input;
int a = 0;

void initialize(int, int);
void gotoxy(int x, int y);
void play();

void gotoxy(int x, int y) { // x,y 좌표를 사용
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void initialize(int start_x, int start_y) {
    // 위, 아래 가로벽 
    for (int i = 0; i < WIDTH; i++) {
        board_1[0][i] = board_1[HEIGHT - 1][i] = '#';
    }

    // 안쪽의 공백
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            board_1[i][j] = ' ';
        }
    }
    // 좌, 우 세로벽
    for (int i = 0; i < HEIGHT; i++) {
        board_1[i][0] = board_1[i][WIDTH - 1] = '#';
    }

    /////////////////////////////////////////////////
    
    // 위, 아래 가로벽 
    for (int i = 0; i < WIDTH; i++) {
        board_2[0][i] = board_2[HEIGHT - 1][i] = '#';
    }

    // 안쪽의 공백
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            board_2[i][j] = ' ';
        }
    }
    // 좌, 우 세로벽
    for (int i = 0; i < HEIGHT; i++) {
        board_2[i][0] = board_2[i][WIDTH - 1] = '#';
    }
}

// 화면 출력 
void display() {
    system("cls");
    //예시 화면
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board_1[i][j]);
        }
        printf("\n");
    }

    //참여 화면
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board_2[i][j]);
        }
        printf("\n");
    }

    //대사 출력
    gotoxy(24, 3);
    printf("\t<< 샌드위치 짱!! >>\n");

    gotoxy(24, 4);
    printf("-------------------------------------\n");

    gotoxy(24, 5);
    printf("손님:\t샌드위치 하나 주세요.\n");

    gotoxy(24, 6);
    printf("알바:\t네, 알겠습니다!\n");

    gotoxy(24, 8);
    printf("시간: \t000\n");

    gotoxy(24, 9);
    printf("판매 수:000개\n");

    gotoxy(24, 10);
    printf("-------------------------------------\n");

    gotoxy(24, 12);
    printf("1: 빵 | 2: 치즈 | 3: 햄 | 4: 피클 | 5: 양배추\n");

    gotoxy(24, 14);
    printf("[  @\t   *\t     ^\t      %%\t\t=   ]\n");

    gotoxy(24, 16);
    printf("무엇을 올릴까?\n");

    //재료 입력
    while (1)
    {
        gotoxy(24, 17);
        printf("ANSWER: ");
        scanf_s("%d", &input);

        //1 ~ 5입력 시
        if (6 > input && input > 0){
            play();
            break;
        }

        //아예 번호가 틀리면 재개
        else{
            printf("\a");
            continue;
        }

        //햄버거 제출 생각해야 함.
    }
    gotoxy(24, 23);
}

void print_toast() {
    //주문 샌드위치 설정
    int SIZE = rand() % 7;
    for (int i = 0; i < SIZE; i++) {
        char inner = arr[rand() % 5];
        for (int j = 0; j < 10; j++) {
            if (i == 0 || i == (SIZE - 1)) {
                inner = '@';
                board_1[8][4 + j] = inner;
                board_1[8 - i][4 + j] = inner;
            }
            else {
                if (inner == '@') {
                    i--;
                    continue;
                }
                else {
                    int rx = 8 - i;
                    int ry = 4 + j;
                    board_1[rx][ry] = inner;
                }
            }
        }
    }
}

void play() {
    while (1) {
        if (board_1[8 - a][4] == ' ') {
            break;
        }
        //번호가 맞을 경우
        else if (arr[input - 1] == board_1[8 - a][4]) {
            for (int j = 0; j < 10; j++) {
                board_2[8 - a][4 + j] = arr[input - 1];
            }
            a++;
            display();
            //다음 단계로 넘어가야 함.
        }
        //번호가 틀렸을 경우
        else
            for (int j = 0; j < 10; j++) {
                board_2[8 - a][4 + j] = arr[input - 1];
            }
        printf("\a");
        display();
        //초기화 해야함.
        break;
    }
}


int main(void) {
    printf("샌드위치 가게에 오신 걸 환영합니다!\n\n\n");

    initialize(1, 1);
    print_toast();
    display();

    printf("\n");
    return 0;
}
