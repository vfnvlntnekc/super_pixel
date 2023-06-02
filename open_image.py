import cv2
import numpy as np

image = cv2.imread("image_6.jpg", cv2.IMREAD_GRAYSCALE)

if image is not None:

    height, width = image.shape

    # Значения яркости
    bright = np.empty((height, width), dtype=np.uint8)

    # Проход по пикселю 
    for x in range(height):
        for y in range(width):
            # Получение яркости пикселя
            bright_pixel = image[x, y]

            # Добавление яркости в массив
            bright[x, y] = bright_pixel

    folder_path = "путь к файлу"
    file_path = folder_path + "/bright.txt"

    with open(file_path, "w") as file:
        file.write(f"{height} {width}\n")
    # Запись массива в файл
    with open(file_path, "a") as file:
        np.savetxt(file, bright, fmt="%d", delimiter=" ", newline="\n")

else:
    print("Ошибка при загрузке изображения.")
