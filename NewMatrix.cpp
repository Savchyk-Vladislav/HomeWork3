#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<double>> data; // Двохвимірний вектор для зберігання даних матриці
    int rows;
    int cols;

public:
    // Конструктор для створення матриці заданних розмірів
    Matrix(int numRows, int numCols) : rows(numRows), cols(numCols) {
        data.resize(rows, vector<double>(cols, 0.0));
    }

    // Встановлення значення елемента матриці
    void setValue(int row, int col, double value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = value;
        } else {
            cerr << "Error: Invalid indexes" << endl;
        }
    }

    // Отримання значення елемента матриці
    double getValue(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        } else {
            cerr << "Error: Invalid indexes" << endl;
            return 0.0;
        }
    }

    // Отримання кількості рядків матриці
    int getRows() const {
        return rows;
    }

    // Отримання кількості стовпців матриці
    int getCols() const {
        return cols;
    }

    // Зміна розмерів матриці з зберіганням вмісту
    void resize(int newRows, int newCols) {
        if (newRows <= 0 || newCols <= 0) {
            cerr << "Error: Invalid dimensions" << endl;
            return;
        }

        vector<vector<double>> newData(newRows, vector<double>(newCols, 0.0));
        for (int i = 0; i < min(rows, newRows); ++i) {
            for (int j = 0; j < min(cols, newCols); ++j) {
                newData[i][j] = data[i][j];
            }
        }

        data = newData;
        rows = newRows;
        cols = newCols;
    }

    // Виведення матриці на екран
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Збереження матриці в файл
    bool saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file" << endl;
            return false;
        }

        file << rows << " " << cols << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file << data[i][j] << " ";
            }
            file << endl;
        }

        file.close();
        return true;
    }

    // Зчитування матриці з файлу
    bool readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file" << endl;
            return false;
        }

        int newRows, newCols;
        file >> newRows >> newCols;
        if (newRows <= 0 || newCols <= 0) {
            cerr << "Error: Invalid dimensions" << endl;
            file.close();
            return false;
        }

        vector<vector<double>> newData(newRows, vector<double>(newCols, 0.0));
        for (int i = 0; i < newRows; ++i) {
            for (int j = 0; j < newCols; ++j) {
                if (!(file >> newData[i][j])) {
                    cerr << "Error: Failed to read data from file" << endl;
                    file.close();
                    return false;
                }
            }
        }

        data = newData;
        rows = newRows;
        cols = newCols;

        file.close();
        return true;
    }

    // Операції матричної арифметики
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cerr << "Error: Unable to add matrices of different sizes" << endl;
            return *this;
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cerr << "Error: Unable to subtract matrices of different sizes" << endl;
            return *this;
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            cerr << "Error: Unable to perform matrix multiplication" << endl;
            return *this;
        }

        int resultRows = rows;
        int resultCols = other.cols;
        Matrix result(resultRows, resultCols);

        for (int i = 0; i < resultRows; ++i) {
            for (int j = 0; j < resultCols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }
};

int main() {
    // Приклад використання
    Matrix A(2, 3);
    A.setValue(0, 0, 1.0);
    A.setValue(0, 1, 2.0);
    A.setValue(0, 2, 3.0);
    A.setValue(1, 0, 4.0);
    A.setValue(1, 1, 5.0);
    A.setValue(1, 2, 6.0);

    Matrix B(3, 2);
    B.setValue(0, 0, 7.0);
    B.setValue(0, 1, 8.0);
    B.setValue(1, 0, 9.0);
    B.setValue(1, 1, 10.0);
    B.setValue(2, 0, 11.0);
    B.setValue(2, 1, 12.0);

    cout << "Matrix A:" << endl;
    A.print();

    cout << "Matrix B:" << endl;
    B.print();

    Matrix C = A * B;
    cout << "Result multiplication A * B:" << endl;
    C.print();

    Matrix D = A + B;
    cout << "Result addition A + B:" << endl;
    D.print();

    Matrix E = A - B;
    cout << "Result subtraction A - B:" << endl;
    E.print();

    Matrix F = A * 2.0;
    cout << "Result multiplication A * 2:" << endl;
    F.print();

    A.saveToFile("matrix.txt");
    Matrix G(0, 0);
	G.readFromFile("matrix.txt");
    cout << "Matrix read from file:" << endl;
    G.print();

    cout << "Matrix with new dimensions:" << endl;
    G.resize(3,4);
    G.print();

    return 0;
}
