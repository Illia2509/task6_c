#include <iostream>
#include <fstream>

const int MAX_SIZE = 100; // Максимальний розмір матриці

// Функція для сортування масиву методом "бульбашки"
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) { // Якщо елемент більший за наступний, міняємо місцями
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Функція для зчитування матриці з файлу
void readFromFile(const char* inputFileName, int& n, int matrix[MAX_SIZE][MAX_SIZE]){
    std::ifstream inputFile(inputFileName); // Відкриваємо файл
    if (!inputFile){ // Якщо файл не відкрито
        std::cerr << "Файл не відкрито" << std::endl;
        return;
    }

    inputFile >> n; // Зчитуємо розмір матриці

    // Зчитуємо саму матрицю
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close(); // Закриваємо файл
}

// Функція для запису матриці у файл
void writeToFile(const char* outputFileName, int& n, int matrix[MAX_SIZE][MAX_SIZE]){
    std::ofstream outputFile(outputFileName); // Відкриваємо файл для запису

    if (!outputFile){ // Якщо файл не вдалося відкрити
        std::cerr << "Файл не заповнено" << std::endl;
        return;
    }

    // Записуємо матрицю в файл
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            outputFile << matrix[i][j] << " ";
        }
        outputFile << std::endl;
    }

    outputFile.close(); // Закриваємо файл
}

// Функція для заміни елементів на головній діагоналі найбільшими числами з матриці
void exchangeMatrix(const char* outputFileName, int& n, int matrix[MAX_SIZE][MAX_SIZE]){
    int sorted[n * n]; // Масив для всіх елементів матриці
    int index = 0;

    // Записуємо всі елементи матриці в одновимірний масив
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sorted[index++] = matrix[i][j];
        }
    } 

    bubbleSort(sorted, n * n); // Сортуємо масив

    // Змінні для зберігання тимчасових значень
    int tempOldNumber = 0; 
    int positionForIinMatrix = 0; 
    int positionForJinMatrix = 0;

    // Проходимо по головній діагоналі
    for (int i = 0; i < n; ++i) {
        tempOldNumber = matrix[i][i]; // Запам'ятовуємо поточне число з діагоналі
        int bigestNumberInSortedList = sorted[n * n - 1 - i]; // Беремо найбільше доступне число

        // Знаходимо позицію найбільшого числа в матриці
        for (int q = 0; q < n; ++q) {
            for (int j = 0; j < n; ++j) {
                if (matrix[q][j] == bigestNumberInSortedList){
                    positionForIinMatrix = q;
                    positionForJinMatrix = j;
                }
            } 
        }

        // Міняємо місцями елементи діагоналі та найбільше число
        matrix[i][i] = bigestNumberInSortedList;
        matrix[positionForIinMatrix][positionForJinMatrix] = tempOldNumber;
    }
}

// Основна функція
int main() {
    int n; // Розмір матриці
    int matrix[MAX_SIZE][MAX_SIZE]; // Матриця

    const char* inputFileName = "input.txt"; // Ім'я вхідного файлу
    const char* outputFileName = "output.txt"; // Ім'я вихідного файлу

    readFromFile(inputFileName, n, matrix); // Зчитуємо матрицю з файлу

    exchangeMatrix(inputFileName, n, matrix); // Змінюємо матрицю

    if (n > 0) { // Якщо розмір матриці коректний
        writeToFile(outputFileName, n, matrix); // Записуємо матрицю у файл
    }

    return 0;
}
