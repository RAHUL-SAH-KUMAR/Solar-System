#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

const double PI = 3.141592653589793;
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24;
const double SUN_X = 40.0, SUN_Y = 12.0;
const int NUM_PLANETS = 3;

struct Planet {
    string name;
    double distance;
    double speed;
    char symbol;
};

Planet planets[NUM_PLANETS] = {
    {"Mercury", 5.0, 4.0, 'M'},
    {"Venus", 8.0, 2.5, 'V'},
    {"Earth", 12.0, 2.0, 'E'}
};

void drawSolarSystem(int step) {
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    for (int i = 0; i < SCREEN_HEIGHT; ++i)
        for (int j = 0; j < SCREEN_WIDTH; ++j)
            screen[i][j] = ' ';
    
    screen[(int)SUN_Y][(int)SUN_X] = 'O'; // Sun
    
    for (int i = 0; i < NUM_PLANETS; ++i) {
        double angle = step * planets[i].speed * PI / 180.0;
        int x = (int)(SUN_X + planets[i].distance * cos(angle));
        int y = (int)(SUN_Y + planets[i].distance * sin(angle));
        
        if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
            screen[y][x] = planets[i].symbol;
    }
    
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j)
            cout << screen[i][j];
        cout << endl;
    }
}

int main() {
    int step = 0;
    while (true) {
        system("clear");
        cout << "Simple Solar System Simulation" << endl;
        drawSolarSystem(step);
        this_thread::sleep_for(chrono::milliseconds(500));
        step++;
    }
    return 0;
}