#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;
int prevMovement;

struct node {
    int x, y;
    node* next = NULL;
    node* prev = NULL;
};

node* head;

void clearGF(char *GF, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(GF + (i * size) + j) = ' ';
        }
    }
}

int calcSizeOfSnake(node* head) {
    int counter = 0;
    while (head) {
        counter++;
        head = head->next;
    }
    return counter;
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
    cout << endl << "Score: " << calcSizeOfSnake(head) << endl;
}

node* createSnake(char *GF, int size) {
    node* head = new node;
    const int sizeOfSnake = 2;
    node* temp;
    for (int i = 0; i < sizeOfSnake - 1; i++) {
        temp = new node;
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    temp = head;
    for (int i = 0; i < sizeOfSnake; i++) {
        temp->x = size / 2;
        temp->y = size / 2 + i;
        *(GF + temp->y * size + temp->x) = 'o';
        temp = temp->next;
    }

    //Check_Snake
    /*temp = head;
    cout << endl;
    while (temp) {
        cout << temp << ": " << temp->x << " " << temp->y << " " << temp->next << " " << temp->prev << " " << endl;
        temp = temp->next;
    }*/

    *(GF + head->y * size + head->x) = 'O';
    return head;
}

void spawnFood(char* GF, int size) {
    char* temp;
    int counter = 0;
    for (temp = GF; temp != GF + size * size; temp++) {
        if (*temp != 'o' && *temp != 'O')
            counter++;
    }
    int* freeCoord = new int[2 * counter];
    int* tempCoord = freeCoord;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(GF + size * i + j) != 'o' && *(GF + size * i + j) != 'O') {
                *tempCoord = j; *(tempCoord + 1) = i;
                tempCoord += 2;
            }
        }
    }

    /*for (tempCoord = freeCoord; tempCoord != freeCoord + 2 * counter;) {
        cout << *tempCoord << " " << *(tempCoord + 1) << endl;
        tempCoord += 2;
    }
    cout << counter;*/

    int buffer = rand() % counter;
    //cout << *(freeCoord + buffer) << " " << *(freeCoord + buffer + 1) << endl;
    *(GF + size * (*(freeCoord + buffer)) + *(freeCoord + buffer + 1)) = 'X';
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

int checkBorders(char* GF, int size, int x, int y) {
    if (x >= size || x < 0 || y >= size || y < 0 || *(GF + size * y + x) == 'o') {
        return 0;
    }
    else if (*(GF + size * y + x) == 'X') {
        return 2;
    }
    else return 1;
}

node* moveSnake(char* GF, int size, node *head, int movement) {
    int x = head->x, y = head->y;
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
    prevMovement = movement;
    switch (checkBorders(GF, size, x, y)) {
        case(0): {
            showGF(GF, size);
            cout << "Game over" << endl;
            system("pause");
            exit(0);
        }
        case(1): {
            *(GF + head->y * size + head->x) = 'o';
            node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->prev->next = NULL;
            *(GF + temp->y * size + temp->x) = ' ';
            temp->x = x; temp->y = y;
            *(GF + temp->y * size + temp->x) = 'O';
            head->prev = temp;
            temp->next = head; temp->prev = NULL;
            return temp;
        }
        case(2): {
            *(GF + head->y * size + head->x) = 'o';
            node* temp = new node;
            temp->next = head;
            head->prev = temp;
            temp->x = x; temp->y = y;
            *(GF + temp->y * size + temp->x) = 'O';
            spawnFood(GF, size);
            return temp;
        }
    }
}

int main()
{
    srand(time(NULL));
    clock_t start_t;
    system("title Snake");
    const int size = 10;
    char GF[size][size];
    clearGF(&GF[0][0], size);
    head = createSnake(&GF[0][0], size);
    spawnFood(&GF[0][0], size);
    showGF(&GF[0][0], size);
    int movement = 1;
    int buffer = checkPressedButton();
    int delay = 1000;
    if (buffer) {
        movement = buffer;
        prevMovement = movement;
    }
    start_t = clock();
    while (1) {
        if (clock() - start_t > delay) {
            system("cls");
            head = moveSnake(&GF[0][0], size, head, movement);
            showGF(&GF[0][0], size);
            cout << prevMovement << " " << buffer;
            start_t = clock();
        }

        buffer = checkPressedButton();
        if (buffer == 1 && prevMovement != 3 || buffer == 2 && prevMovement != 4 || buffer == 3 && prevMovement != 1 || buffer == 4 && prevMovement != 2){
            movement = buffer;
        }
        if (calcSizeOfSnake(head) < 16) {
            delay = 1000 - calcSizeOfSnake(head) * 50;
        }
    }
}
