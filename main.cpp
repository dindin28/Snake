#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

struct node {
    int x, y;
    node* next = NULL;
    node* prev = NULL;
};

void clearGF(char *GF, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(GF + (i * size) + j) = ' ';
        }
    }
}

void showGF(char *GF, int size) {
    for (int i = 0; i < size + 2; i++) cout << "-";
    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << "|";
        for (int j = 0; j < size; j++) {
            cout << *(GF + i * size + j);
        }
        cout << "|\n";
    }
    for (int i = 0; i < size + 2; i++) cout << "-";
    cout << endl;
}

// make prev pointer
node* createSnake(char *GF, int size) {
    node* head = new node;
    head->x = size / 2;
    head->y = size / 2;
    node* iteratorBuffer = head;
    node* iterator;
    int sizeOfSnake = 5;
    for (int i = 1; i < sizeOfSnake; i++) {
        iterator = new node;
        iterator->x = head->x;
        iterator->y = size / 2 + i;
        iteratorBuffer->next = iterator;
        iteratorBuffer = iterator;
    }
    iterator = head;
    while (iterator) {
        *(GF + size * iterator->y + iterator->x) = 'o';
        iterator = iterator->next;
    }
    *(GF + size * head->y + head->x) = 'O';
    return head;
}

int checkPressedButton(){
    /*
    * Up-arrow => return 1
    * Right-arrow => return 2
    * Down-arrow => return 3
    * Left-arrow => return 4
    * else return 0
    */ 
    if(GetKeyState(VK_UP) == -127 || GetKeyState(VK_UP) == -128) {
        return 1;
    }else if (GetKeyState(VK_RIGHT) == -127 || GetKeyState(VK_RIGHT) == -128) {
       return 2;
    }else if (GetKeyState(VK_DOWN) == -127 || GetKeyState(VK_DOWN) == -128) {
       return 3;
    }else if (GetKeyState(VK_LEFT) == -127 || GetKeyState(VK_LEFT) == -128) {
       return 4;
    }else return 0;
}

node* moveSnake(char* GF, int size, node *head, int movement) {
    int x = head->x, y = head->y;
    *(GF + head->y * size + head->x) = 'o';
    switch (movement) {
        case(1): {
            y--;
            break;
        }
        case(2): {
            x++;
            break;
        }
        case(3): {
            y++;
            break;
        }
        case(4): {
            x--;
            break;
        }
    }
    node* iterator = head;
    while (iterator->next) iterator = iterator->next;
    *(GF + iterator->y * size + iterator->x) = ' ';
    iterator->x = x; iterator->y = y;
    
}

int main()
{
    clock_t start_t;
    system("title Snake");
    const int size = 30;
    char GF[size][size];
    clearGF(&GF[0][0], size);
    node* head = createSnake(&GF[0][0], size);
    showGF(&GF[0][0], size);
    int movement = 1;
    int buffer = checkPressedButton();
    if (buffer) movement = buffer;
    start_t = clock();
    while (1) {
        if (clock() - start_t > 2000) {
            system("cls");

            start_t = clock();
        }
        buffer = checkPressedButton();
        if (buffer) movement = buffer;
    }
    _getch();
}
