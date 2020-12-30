#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

typedef struct node{
    int x, y;
    struct node *next = nullptr;
} node;

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
inline void clearGF(char *ptrhead, int size){
    for(char *ptrbuff = ptrhead; ptrbuff != (ptrhead + size * size); ptrbuff++){
        *ptrbuff = ' ';
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
node* moveSnake(node *head, char* GF,int size,int movement){
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
    if(head->next == NULL){
        *(GF + head->y * size + head->x) = ' ';
        head->x = x;
        head->y = y;
        cout << "head->x = " << head->x << "head->y = " << head->y << "\n";
        *(GF + head->y * size + head->x) = 'O';
    }
    return head;
}

int main(){
    clock_t start_t, end_t;
    system("title Snake");
    int size = 3;
    cout << "Enter size of Gaming Field: ";
    //cin >> size;
    char *GF = new char(size*size);
    clearGF(GF, size);
    node* head = (node*) malloc(sizeof(node));
    head->x = 0;
    head->y = size - 1;
    head->next = nullptr;
    int movement = 2;// at the beginning move right
    int buff = checkPressedButtons();
        if(buff) movement = buff;
    showGF(GF, size);
    start_t = clock();
    while(1){
        if(clock() - start_t > 2000){
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
    cout << endl;
    cout << "\n" << (clock() - start_t);

    getch();
}
