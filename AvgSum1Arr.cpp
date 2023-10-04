#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    if (n <= 0) {
        cout << "The array size must be a positive number." << endl;
        return 1;
    }

    // Створюємо масив з n дійсних чисел
    vector<double> arr(n);

    // Заполняем массив
    cout << "Enter Array Elements:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Знаходимо среднє значення елементів масиву
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    double average = sum / n;

    // Підрахунок кількості елементів, які більше среднього значення
    int countAboveAverage = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > average) {
            countAboveAverage++;
        }
    }

    // Знаходимо перший від'ємний елемент
    int firstNegativeIndex = -1;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0) {
            firstNegativeIndex = i;
            break;
        }
    }

    // Рахуємо суму модулей елементів, які розміщені після першого від'ємного елементу
    double sumOfAbsoluteValues = 0;
    if (firstNegativeIndex != -1) {
        for (int i = firstNegativeIndex + 1; i < n; ++i) {
            sumOfAbsoluteValues += abs(arr[i]);
        }
    }

    // Виведення результатів
    cout << "Number of elements is greater than average: " << countAboveAverage << endl;
    cout << "Sum of modul of elements after the first negative element: " << sumOfAbsoluteValues << endl;

    return 0;
}
