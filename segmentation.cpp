#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

// Проверка вхождения элемента в сегмент
bool pixel_in_segment(int value_pixel, int value_segment) {
    return value_pixel == value_segment;
}

// Деление на сегменты
vector<vector<int>> divi_into_SP(int** bright, int height, int width) {
    vector<vector<int>> all_SP;
    vector<vector<bool>> check_of_use(height, vector<bool>(width, false));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!check_of_use[i][j]) {
                int bright_SP = bright[i][j];
                vector<int> one_SP;
                queue<pair<int, int>> q;
                q.push({ i, j });
                check_of_use[i][j] = true;
                one_SP.push_back(bright[i][j]);

                while (!q.empty()) {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    one_SP.push_back(x * width + y);

                    for (int k = 0; k < 4; ++k) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];

                        if (nx >= 0 && nx < height && ny >= 0 && ny < width &&
                            !check_of_use[nx][ny] && pixel_in_segment(bright[nx][ny], bright_SP)) {
                            q.push({ nx, ny });
                            check_of_use[nx][ny] = true;
                        }
                    }
                }
                all_SP.push_back(one_SP);
            }
        }
    }

    return all_SP;
}

// Сохранениу сегментов в файл
void file_SPs(const vector<vector<int>>& all_SP) {
    std::ofstream file("one_SP.txt");

    if (!file.is_open()) {
        cout << "Ошибка при открытии файла." << endl;
        return;
    }

    for (const auto& one_SP : all_SP) {
        file << one_SP.size();
        for (int ind : one_SP) {
            file << " " << ind;
        }
        file << "\n";
    }

    file.close();
}

int main() {
    ifstream file("output.txt"); 


    if (file.is_open()) {
        int height, width;

        // Чтение размеров массива
        file >> height >> width;

        int** bright = new int* [height];
        for (int i = 0; i < height; ++i) {
            bright[i] = new int[width];
        }

        // Чтение из файла и сохранение в массив
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                file >> bright[i][j];
            }
        }

        file.close();

        vector<vector<int>> all_SP = divi_into_SP(bright, height, width);

        file_SPs(all_SP);

        for (int i = 0; i < height; ++i) {
            delete[] bright[i];
        }
        delete[] bright;

    }
    else {
        cout << "Ошибка при открытии файла." << endl;
    }

    return 0;
}