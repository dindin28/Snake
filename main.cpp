#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <time.h>

int prevMovement;
const int sizeGF = 10;
const int bodyRadius = 10;
const int borderThickness = 2;

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
    //Console Version
    for (int i = 0; i < size + 2; i++) std::cout << "-";
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "|";
        for (int j = 0; j < size; j++) {
            std::cout << *(GF + i * size + j);
        }
        std::cout << "|\n";
    }
    for (int i = 0; i < size + 2; i++) std::cout << "-";
    std::cout << std::endl;

}

void showGF(sf::RenderWindow &window, char* GF, int size) {
    //SFML Version
    //Making borders
    window.clear(sf::Color(255, 255, 255, 0));
    sf::RectangleShape rectangle(sf::Vector2f(borderThickness, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2));
    rectangle.setFillColor(sf::Color(0, 0, 0));
    window.draw(rectangle);
    rectangle.rotate(90);
    rectangle.setPosition((borderThickness, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2), 0);
    window.draw(rectangle);
    rectangle.rotate(90);
    rectangle.setPosition((borderThickness, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2), (borderThickness, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2));
    window.draw(rectangle);
    rectangle.rotate(90);
    rectangle.setPosition(0, (borderThickness, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2));
    window.draw(rectangle);
    //Making squares
    rectangle.setSize(sf::Vector2f(1, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2));
    for (int position = borderThickness + 2 * bodyRadius; position < borderThickness + (sizeGF - 1) * (1 + bodyRadius * 2); position += 2 * bodyRadius + 1) {
        rectangle.setRotation(270);
        rectangle.setPosition(0, position);
        window.draw(rectangle);
        rectangle.setRotation(0);
        rectangle.setPosition(position, 0);
        window.draw(rectangle);
    }
    sf::CircleShape body(bodyRadius);
    body.setFillColor(sf::Color::Black);
    sf::CircleShape food(bodyRadius);
    food.setFillColor(sf::Color::Red);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(GF + i * size + j) == 'o' || *(GF + i * size + j) == 'O') {
                body.setPosition(borderThickness + j * (bodyRadius * 2 + 1), borderThickness + i * (bodyRadius * 2 + 1) - 1);
                window.draw(body);
            }
            else if (*(GF + i * size + j) == 'X') {
                food.setPosition(borderThickness + j * (bodyRadius * 2 + 1), borderThickness + i * (bodyRadius * 2 + 1) - 1);
                window.draw(food);
            }
        }
    }
    window.display();
}

node* createSnake(char *GF, int size) {
    node* head = new node;
    const int sizeOfSnake = 4;
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
struct point {
    int x, y;
};

void spawnFood(sf::RenderWindow& window, char* GF, int size) {
    int sizeOfSnake = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(GF + i * size + j) == 'o' || *(GF + i * size + j) == 'O')
                sizeOfSnake++;
        }
    }
    if (sizeOfSnake == size * size) {
        showGF(window, GF, size);
        std::cout << "You win!!!" << std::endl;
        system("pause");
        exit(0);
    }
    int counter = 0;
    point* ptr = new point[size * size - sizeOfSnake];
    for (int i = 0; i < size ; i++) {
        for (int j = 0; j < size; j++) {
            if (*(GF + i * size + j) != 'o' && *(GF + i * size + j) != 'O') {
                ptr[counter].x = j; ptr[counter].y = i;
                counter++;
            }
        }
    }
    /*cout << "size = " << sizeOfSnake << endl;
    for (int counter = 0; counter < size * size - sizeOfSnake; counter++) {
        cout << ptr[counter].x << " " << ptr[counter].y << endl;
    }*/
    int randBuff = rand() % (size * size - sizeOfSnake);
    *(GF + ptr[randBuff].y * size + ptr[randBuff].x) = 'X';
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

node* moveSnake(sf::RenderWindow& window, char* GF, int size, node *head, int movement) {
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
            showGF(window, GF, size);
            std::cout << "Game over" << std::endl;
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
            spawnFood(window, GF, size);
            return temp;
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode((borderThickness, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2), (borderThickness, borderThickness * 2 + (sizeGF - 1) + bodyRadius * sizeGF * 2)), "Snake");
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "Snake");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.clear(sf::Color(255, 255, 255, 0));
    srand(time(NULL));
    clock_t start_t;
    system("title Snake");
    const int size = sizeGF;
    char GF[size][size];
    clearGF(&GF[0][0], size);
    head = createSnake(&GF[0][0], size);
    spawnFood(window, &GF[0][0], size);
    showGF(window, &GF[0][0], size);
    std::cout << std::endl << "Score: " << calcSizeOfSnake(head) << std::endl;
    int movement = 1;
    int buffer = checkPressedButton();
    int delay = 1000;
    if (buffer) {
        movement = buffer;
        prevMovement = movement;
    }
    start_t = clock();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            /*
            * Up-arrow => return 1
            * Right-arrow => return 2
            * Down-arrow => return 3
            * Left-arrow => return 4
            * else return 0
            */
            buffer = 0;
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    buffer = 1;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    buffer = 2;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    buffer = 3;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    buffer = 4;
                }
            }
        }

        if (clock() - start_t > delay) {
            system("cls");
            head = moveSnake(window, &GF[0][0], size, head, movement);
            showGF(window, &GF[0][0], size);
            std::cout << std::endl << "Score: " << calcSizeOfSnake(head) << std::endl;
            start_t = clock();
        }

        //buffer = checkPressedButton();
        if (buffer == 1 && prevMovement != 3 || buffer == 2 && prevMovement != 4 || buffer == 3 && prevMovement != 1 || buffer == 4 && prevMovement != 2){
            movement = buffer;
        }
        if (calcSizeOfSnake(head) < 16) {
            delay = 1000 - calcSizeOfSnake(head) * 50;
        }
    }
}
