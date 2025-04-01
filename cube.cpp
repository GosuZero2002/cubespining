#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <thread>
#ifdef _WIN32
#include <windows.h>
void usleep(__int64 usec) {
    HANDLE timer;
    LARGE_INTEGER ft;
    ft.QuadPart = -(10 * usec);
    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
#else
#include <unistd.h>
#endif

const int width = 100, height = 50;
const float K1 = 50;
const int distanceFromCam = 70;
const char backgroundChar = ' ';
float A = 0, B = 0, C = 0;

std::vector<float> zBuffer(width * height, 0);
std::vector<char> buffer(width * height, backgroundChar);

float calculateX(float i, float j, float k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
           j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(float i, float j, float k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
           j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
           i * cos(B) * sin(C);
}

float calculateZ(float i, float j, float k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void drawSurface(float cubeX, float cubeY, float cubeZ, char ch) {
    float x = calculateX(cubeX, cubeY, cubeZ);
    float y = calculateY(cubeX, cubeY, cubeZ);
    float z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;
    float ooz = 1 / z;
    int xp = static_cast<int>(width / 2 + K1 * ooz * x * 2);
    int yp = static_cast<int>(height / 2 + K1 * ooz * y);
    int idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

void renderCube() {
    float cubeSize = 20;
    for (float x = -cubeSize; x < cubeSize; x += 1.5f) {
        for (float y = -cubeSize; y < cubeSize; y += 1.5f) {
            drawSurface(x, y, -cubeSize, '0');
            drawSurface(cubeSize, y, x, '~');
            drawSurface(-cubeSize, y, -x, '"');
            drawSurface(-x, y, cubeSize, '#');
            drawSurface(x, -cubeSize, -y, ';');
            drawSurface(x, cubeSize, y, '+');
        }
    }
}

void display() {
    std::cout << "\x1b[H"; // Di chuyển con trỏ về đầu màn hình
    for (int i = 0; i < width * height; i++) {
        std::cout.put(i % width ? buffer[i] : '\n');
    }
}

int main() {
    std::cout << "\x1b[2J"; // Xóa màn hình
    while (true) {
        std::fill(buffer.begin(), buffer.end(), backgroundChar);
        std::fill(zBuffer.begin(), zBuffer.end(), 0);
        renderCube();
        display();
        A += 0.05f;
        B += 0.05f;
        C += 0.01f;
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // ~60 FPS
    }
    return 0;
}
