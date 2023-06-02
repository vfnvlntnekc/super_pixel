#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream file("bright.txt");

    if (file.is_open()) {
        int height, width;

        file >> height >> width;

        int** bright = new int* [height];
        for (int i = 0; i < height; ++i) {
            bright[i] = new int[width];
        }

        // Чтение значений из файла и сохранение в массив
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                file >> bright[i][j];
            }
        }

        file.close(); 

        int** bright_new = new int* [height];
        for (int i = 0; i < height; ++i) {
            bright_new[i] = new int[width];
        }

        // Допустимое значение отклонения яркости
        int delta = 20;

        // Изменение значений яркости пикселей по eps
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                bright_new[i][j] = delta * round(bright[i][j] / delta);
            }
        }

        ofstream file("output.txt");

        file << height << " " << width;
        file << "\n";

        if (file.is_open()) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    file << bright_new[i][j] << " ";
                }
                file << "\n";
            }
        }

        for (int i = 0; i < height; ++i) {
            delete[] bright[i];
        }
        delete[] bright;

        for (int i = 0; i < height; ++i) {
            delete[] bright_new[i];
        }
        delete[] bright_new;

    }
    else {
        cout << "Ошибка при открытии файла." << endl;
    }

    return 0;
}
