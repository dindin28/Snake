#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

struct node{
    int x, y;
    struct node *next = NULL;
};


inline void showGF(char *ptrhead, int size){
    for(int i = 0; i < size + 2; i++){
        cout << "-";
    }
    cout << endl;
    char *ptrbuff = ptrhead;
    for(int i = 0; i < size; i++){
        cout << "|";
        for(int j = 0; j < size; j++, ptrbuff++){
            cout << *ptrbuff;
        }
        cout << "|" << endl;
    }
    for(int i = 0; i < size + 2; i++){
        cout << "-";
    }
}
void clearGF(char *ptrhead, int size){
    for(char *iter = ptrhead; iter != (ptrhead + size * size); iter++){
        *iter = ' ';
    }
}

inline int checkPressedButtons(){
    /*
     * Up-arrow => return 1
     * Right-arrow => return 2
     * Down-arrow => return 3
     * Left-arrow => return 4
     * else return 0
     */
    if(GetKeyState(VK_UP) == -127 || GetKeyState(VK_UP) == -128){
        return 1;
    }else if(GetKeyState(VK_RIGHT) == -127 || GetKeyState(VK_RIGHT) == -128){
        return 2;
    }else if(GetKeyState(VK_DOWN) == -127 || GetKeyState(VK_DOWN) == -128){
        return 3;
    }else if(GetKeyState(VK_LEFT) == -127 || GetKeyState(VK_LEFT) == -128){
        return 4;
    }else return 0;
}
inline bool checkBorder(int size, int x, int y){
    if(x < 0 || x >= size || y < 0 || y >= size) return false;
    return true;
}

node* moveSnake(node *head, char* GF, int size, int movement){
    int x = head->x;
    int y = head->y;
    switch(movement) {
        case (1): {
            y--;
            break;
        }
        case (2): {
            x++;
            break;
        }
        case (3): {
            y++;
            break;
        }
        case (4): {
            x--;
            break;
        }
    }
    if(checkBorder(size, x, y)){
        if(head->next == NULL){
            *(GF + head->y * size + head->x) = ' ';
            head->x = x;
            head->y = y;
            //cout << "head->x = "<< head->x << " head->y = "<<head->y << endl;
            *(GF + head->y * size + head->x) = 'O';
        }
    }else{
        showGF(GF, size);
        cout << "\nGame is over\n";
        system("pause");
        exit(0);
    }
    return head;
}
void spawnFood(char *GF, int size, node *head){
    int sizeOfSnake;
    node *tempSnake = head;
    for(sizeOfSnake = 0; tempSnake != NULL; sizeOfSnake++){tempSnake = tempSnake->next;}
    int *Xs = (int*)malloc(size * size - sizeOfSnake);
    int *Ys = (int*)malloc(size * size - sizeOfSnake);
    int *Xstemp = Xs;
    int *Ystemp = Ys;
    for(int i = size - 1; i >= 0; i--){
        for(int j = 0; j < size; j++){
            if(head->x != i || head->y != j){
                //cout << i << " "<< j << endl;
                *Xstemp = i;
                Xstemp++;
                *Ystemp = j;
                Ystemp++;
            }
        }
    }
    int temp = rand() % (size * size - sizeOfSnake);
    cout << temp;
    *(GF + size * (*(Xs + temp)) + *(Ys + temp)) = 'X';
}

int main(){
    srand(time(NULL));
    clock_t start_t, end_t;
    system("title Snake");
    int size = 2;
    char *GF = (char *) malloc(size*size);
    clearGF(GF, size);
    node *head = (node*)malloc (sizeof(node));
    head->x = 0;
    head->y = size - 1;
    head->next = nullptr;
    *(GF + head->y * size + head->x) = 'O';
    spawnFood(GF, size, head);
    //system("pause");
    int movement = 2;// at the beginning move right
    int buff = checkPressedButtons();
    if(buff) movement = buff;
    showGF(GF, size);
    start_t = clock();
    while(1){
        if(clock() - start_t > 1000){
            system("cls");
            head = moveSnake(head, GF, size, movement);
            showGF(GF, size);
            start_t = clock();
        }
        buff = checkPressedButtons();
        if(buff) movement = buff;
        if(GetKeyState(VK_ESCAPE) == -127 || GetKeyState(VK_ESCAPE) == -128) return 0;
    }
    /*
     * Up-arrow => return 1
     * Right-arrow => return 2
     * Down-arrow => return 3
     * Left-arrow => return 4
     * else return 0
     */
}
