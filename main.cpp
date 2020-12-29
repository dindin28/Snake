#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

typedef struct node{
    int x, y;
} node;

void showGF(char *ptrhead, int size){
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
    for(char *ptrbuff = ptrhead; ptrbuff != (ptrhead + size * size); ptrbuff++){
        *ptrbuff = NULL;
    }
}
int main(){
    int size;
    cout << "Enter size of Gaming Field: ";
    cin >> size;
    char *GF = new char(size*size);
    clearGF(GF, size);
    node head;
    head.x = 0;
    head.y = 0;
    node tail = head;
    int prev;
    while(1){
        cout << GetKeyState(VK_SHIFT);

    }
    /*int j = 2, i = 4;
    *(GF + j * size + i) = 'O';*/
    int movement = 77;

    showGF(GF, size);
    cout << "\n";
    getch();
}
