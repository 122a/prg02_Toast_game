#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <process.h>

#define WIDTH   18
#define HEIGHT  10
#define _B 1975.533
#define _F 1396.913

char board_1[HEIGHT][WIDTH];
char board_2[HEIGHT][WIDTH];

int arr[5] = { '@', '*', '^', '%', '=' };
int input;
int second = 0;
int a, check, count, min = 0;
int price, price_e, clean = 0;

void initialize(int, int);
void gotoxy(int x, int y);
void play();
void print_toast();

// x,y 좌표를 사용
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void initialize(int start_x, int start_y) {
    /*첫 번째 보드*/
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

    /*두 번째 보드*/
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
    //쓰레드 겹침을 막기 위함
    clean = 1;
    system("cls");

    //보드_1 화면
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board_1[i][j]);
        }
        printf("\n");
    }

    //보드_2 화면
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

    //주문 시 대사
    if (check == 0) {
        gotoxy(24, 5);
        printf("손님:\t샌드위치 하나 주세요.\n");

        gotoxy(24, 6);
        printf("알바:\t네, 알겠습니다!\n");
    }

    //틀린 주문 시 대사
    else if (check == 1) {
        gotoxy(24, 5);
        printf("손님:\t제가 시킨 거랑 다르잖아요!");

        gotoxy(24, 6);
        printf("알바:\t으악! 죄송합니다!");
    }

    clean = 0;

    gotoxy(24, 8);
    printf("시간: \t%d분 %02d초\n", min, second);

    gotoxy(24, 9);
    printf("판매 금:%05d원\n", price);

    //gotoxy(24, 9);
    //printf("판매 수:%03d개\n", count);

    gotoxy(24, 10);
    printf("-------------------------------------\n");

    gotoxy(24, 12);
    printf("1: 빵 | 2: 치즈 | 3: 햄 | 4: 피클 | 5: 양배추\n");

    gotoxy(24, 14);
    printf("[  @\t   *\t     ^\t      %%\t\t=   ]\n");

    gotoxy(24, 16);
    printf("무엇을 올릴까?\n");

    gotoxy(24, 17);
    printf("ANSWER: ");

    //재료 입력
    if (check == 0) {
        while (1) {
            gotoxy(24, 17);
            printf("ANSWER: ");
            scanf_s(" %d", &input);

            //1 ~ 5입력 시
            if (6 > input && input > 0) {
                play();
                break;
            }
            //샌드위치 제출
            else if (input == 0) {
                play();
            }
            //아예 번호가 틀리면 재개
            else {
                printf("\a");
                continue;
            }
        }
    }

    check = 0;
    gotoxy(24, 23);

}

void sell() {
    gotoxy(24, 5);
    printf("손님:\t와! 맛있겠다! 감사합니다.");

    gotoxy(24, 6);
    printf("알바:\t샌드위치 나왔습니다!");

    price += price_e;
    Beep(_F, 100);
    Sleep(200);
    Beep(_B, 100);
    Sleep(1800);
    count++;
    initialize(1, 1);
    print_toast();
    price_e, a = 0;
    display();
}

//주문 샌드위치 설정
void print_toast() {
    //샌드위치 높이 설정
    int SIZE = rand() % 7;

    switch (SIZE) {
    case 0:
        SIZE += 3;

    case 1:
        SIZE += 2;
    }

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
        if (board_1[8 - a][4] == ' ' && input == 0) {
            sell();
        }
        //번호가 맞을 경우
        else if (arr[input - 1] == board_1[8 - a][4]) {
            for (int j = 0; j < 10; j++) {
                board_2[8 - a][4 + j] = arr[input - 1];
            }

            if (arr[input - 1] == '@')
                price_e += 800;
            else
                price_e += 1000;

            a++;
            display();
            //다음 단계로 넘어가야 함.
        }
        //번호가 틀렸을 경우
        else {
            if (input == 0) {
                for (int j = 0; j < 10; j++) {
                    board_2[8 - a][4 + j] = ' ';
                }
            }
            else {
                for (int j = 0; j < 10; j++) {
                    board_2[8 - a][4 + j] = arr[input - 1];
                }
            }
            price_e = 0;
            printf("\a");
            check = 1;
            display();
            Sleep(1800);
            initialize(1, 1);
            print_toast();
            a = 0;
            display();
        }
    }
}

unsigned _stdcall Thread_A(void* arg)
{
    while (1)
    {
        Sleep(1000);
        second++;
        if (second == 60) {
            min++;
            second = 0;
        }
        while (clean != 0) {
            Sleep(10);
        }
        gotoxy(24, 8);
        printf("시간: \t%d분 %02d초\n", min, second);
        gotoxy(32, 17);

        if (min == 3) {
            break;
        }
    }
    system("cls");

    //결과 화면
    for (int i = 0; i < 1; i++) {
        gotoxy(10, 3);
        printf("\t<샌드위치 짱!> 아르바이트 끝!");

        gotoxy(10, 5);
        printf("-----------------------------------------\n");

        gotoxy(10, 7);
        printf("[ 게임 오버 ]");

        gotoxy(10, 9);
        printf("#############\n");
        printf("          #           #\n");
        printf("          #  @@@@@@@  #\n");
        printf("          #  *******  #\n");
        printf("          #  =======  #\n");
        printf("          #  @@@@@@@  #\n");
        printf("          #############\n");

        gotoxy(26, 9);
        printf(":: 결과물 ::");
        gotoxy(26, 10);
        printf("-------------------------\n");
        gotoxy(26, 11);
        printf("총 판매 개수: %d개",count);
        gotoxy(26, 12);
        printf("총 판매 금액: %d원", price);
        gotoxy(26, 14);
        printf("완전 힘든 하루였다!!\n\n\n");
    }
    exit(0);
}

int main(void) {
    //시작 화면
    for (int i = 0; i < 1; i++) {
        gotoxy(10, 3);
        printf("<샌드위치 짱!> 가게에 오신 걸 환영합니다!");

        gotoxy(10, 5);
        printf("-----------------------------------------\n");

        gotoxy(10, 7);
        printf("[ 게임 방법 ]");

        gotoxy(10, 9);
        printf("#############\n");
        printf("          #           #\n");
        printf("          #  @@@@@@@  #\n");
        printf("          #  *******  #\n");
        printf("          #  =======  #\n");
        printf("          #  @@@@@@@  #\n");
        printf("          #############\n");

        gotoxy(10, 17);
        printf("#############\n");
        for (int i = 0; i < 4; i++) {
            printf("          #           #\n");
        }
        printf("          #  @@@@@@@  #\n");
        printf("          #############\n");

        gotoxy(26, 9);
        printf("첫 번째 보드: 손님 칸");
        gotoxy(26, 10);
        printf("-------------------------\n");
        gotoxy(26, 11);
        printf("위쪽의 보드에서 손님이 주문하신 샌드위치가 나타난다.");
        gotoxy(26, 12);
        printf("플레이어는 위쪽의 보드와 똑같이 샌드위치를 쌓아 올린다.");
        gotoxy(26, 13);
        printf("3분 안으로 최대한 많이 만들어 파는 게 목적!");
        gotoxy(26, 14);
        printf("빵은 800원! 다른 재료는 1000원으로 계산!");

        gotoxy(26, 17);
        printf("두 번째 보드: 플레이어 칸");
        gotoxy(26, 18);
        printf("-------------------------\n");
        gotoxy(26, 19);
        printf("1: 빵 | 2: 치즈 | 3: 햄 | 4: 피클 | 5: 양배추\n");

        gotoxy(26, 20);
        printf("[  @\t     *\t      ^\t       %%\t  =   ]\n");

        gotoxy(26, 22);
        printf("무엇을 올릴까?    ANSWER 칸에 위 모양을");
        gotoxy(26, 23);
        printf("ANSWER: Ex)1   <= 가리키는 숫자를 입력 후 Enter!");
        gotoxy(26, 25);
        printf("샌드위치 완료 시 0을 입력 후 Enter하면 제출!");

        gotoxy(10, 28);
        printf("Enter 키 입력 시 시작합니다!");
        getchar();
    }

    _beginthreadex(NULL, 0, Thread_A, 0, 0, NULL);

    initialize(1, 1);
    print_toast();
    display();
    return 0;
}
