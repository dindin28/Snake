#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

typedef struct node{
    int x = 0, y = 0;
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

int main(){
    system("title Snake");
    int size;
    cout << "Enter size of Gaming Field: ";
    cin >> size;
    char *GF = new char(size*size);
    clearGF(GF, size);
    struct node head;
    struct node tail = head;
    /*
     * Up-arrow => return 1
     * Right-arrow => return 2
     * Down-arrow => return 3
     * Left-arrow => return 4
     * else return 0
     */
        int movement = checkPressedButtons();
        switch(movement) {
            case (1): {
                cout << "Moving up";
                break;
            }
            case (2): {
                cout << "Moving right";
                break;
            }
            case (3): {
                cout << "Moving down";
                break;
            }
            case (4): {
                cout << "Moving left";
                break;
            }
            case (0): {
                cout << "No pressed buttons";
                break;
            }
        }
    showGF(GF, size);
    cout << "\n";
    getch();
}
