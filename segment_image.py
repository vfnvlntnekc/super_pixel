import numpy as np
import cv2

file_path = "путь к файлу"

with open(file_path, 'r') as file:
    lines = file.readlines()

# Размеры матрицы
height = 4032
width = 3024

# Массив значений яркости
bright = np.empty((height, width), dtype=np.uint8)

# Заполнение матрицы яркостей
for i, line in enumerate(lines):
    data = line.split()
    bright_pixel = int(data[1])
    pixels = [int(pixel) for pixel in data[2:]]
    for pixel in pixels:
        x = pixel % width
        y = pixel // width
        bright[y][x] = bright_pixel

cv2.imwrite("segment_image.png", bright)
