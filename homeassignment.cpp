#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T> //шаблон для матриц разного типа
class Matrix
{
private:
    int rows; //строки
    int cols; //столбцы
    T* pMatrix; //указатель на массив матриц

public:
    Matrix(int valueRows, int valueCols) // конструктор матрицы, создает матрицу с заданным количеством строк и столбцов
    {
        rows = valueRows;
        cols = valueCols;

        pMatrix = new T[rows * cols];

    }

    Matrix ( )
    {
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    Matrix (const Matrix & matrix) //конструктор копирования
    {   rows = matrix.rows;
        cols = matrix.cols;

        pMatrix = new T[rows * cols];

        for (int i = 0; i < rows * cols; i++)
        {
            pMatrix[i] = matrix.pMatrix[i];
        }
    }

    void inputFromConsole() //ввод с консоли элементов матрицы
    { 
        cout << "Введите элементы матрицы:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Введите значение элемента [" << i << "][" << j << "]:" ;
                cin >> pMatrix[i * cols + j];
            }
        }
    }

    void outputFromConsole() //вывод с консоли элементов матрицы
    {
        cout << "Ваша матрица:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++){
                cout << pMatrix[i * cols + j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void inputFromFile(const char* filename) { //ввод с файла элементов матрицы
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Невозможно открыть файл" << endl;
        return;
    }
    infile >> rows >> cols;
    pMatrix = new T[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            infile >> pMatrix[i * cols + j];
        }
    }
    infile.close();
    }

    void outputToFile(const char* filename) { 
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Error: Невозможно открыть файл" << endl;
        return;
    }
    outfile << rows << " " << cols << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outfile << pMatrix[i * cols + j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
    }

    void printMatrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << pMatrix[i * cols + j] << " ";
        }
        cout << endl;
    }
    }

    Matrix operator + (const Matrix & matrix) //перегрузка оператора + для сложения матриц
    {
        if (rows == matrix.rows && cols == matrix.cols) {
            Matrix result(rows, cols);
            for (int i = 0; i < rows * cols; i++){
                result.pMatrix[i] = pMatrix[i] + matrix.pMatrix[i];
            }
            return result;
        }
        else cout << "Матрицы имеют разную размерность, сложить их невозможно" << endl << endl;
        return matrix; //сложить невозможно
    }

    Matrix operator - (const Matrix & matrix) //перегрузка оператора - для вычитания матриц
    {
        if (rows == matrix.rows && cols == matrix.cols) {
            Matrix result(rows, cols);
            for (int i = 0; i < rows * cols; i++) {
                result.pMatrix[i] = pMatrix[i] - matrix.pMatrix[i];
            }
            return result;
        }
        else cout << "Матрицы имеют разную размерность, вычесть их невозможно" << endl << endl;
        return matrix; //вычесть невозможно
    }

    Matrix operator * (const Matrix & matrix) //перегрузка оператора * для умножения матриц
    {
        if (cols == matrix.rows) {
            Matrix result(rows, matrix.cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < matrix.cols; j++) {
                    result.pMatrix[i * result.cols + j] = 0;
                    
                    for (int k = 0; k < cols; k++){
                        result.pMatrix[i * result.cols + j] += pMatrix[i * cols + k] * matrix.pMatrix[k * matrix.cols + j];
                    }
                }
            }
            return result;
        }
        else
        {   
            cout << "Умножить матрицы невозможно" << endl <<  endl;
            return matrix; // Умножить невозможно
        }
    }

    Matrix operator *(double scalar) //Умножение матрицы на скаляр
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.pMatrix[i * result.cols + j] = pMatrix[i* result.cols + j] * scalar;
                }
            }
        return result;
    }

    bool operator == (const Matrix & matrix) //перегрузка оператора == для сравнения матриц
    {
        if (rows == matrix.rows && cols == matrix.cols) {
            for (int i = 0; i < rows * cols; i++) {
                if (pMatrix[i] != matrix.pMatrix[i]) {
                    return 0;
                }
            }
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator != (const Matrix & matrix) //перегрузка оператора != для сравнения мтариц
    {
        if (rows == matrix.rows && cols == matrix.cols){
            for (int i = 0; i < rows * cols; i++){
                if (pMatrix[i] == matrix.pMatrix[i]){
                    return 0;
                }
            }
            return 1;
        }
        else {
            return 0;
        }
    }

    bool operator == (double scalar) // перегрузка оператора == для сравнения скаляра и матрицы
    {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == j) { // если элемент на главной диагонали
                    if (pMatrix[i * cols + j] != scalar){
                        return false;
                    } 
                }    
                else {
                    if (pMatrix[i * cols + j] != 0){
                        return false;
                    }    
                }        
            }
        return true;
        }
    }

    bool operator != (double scalar) // перегрузка оператора != для сравнения скаляра и матрицы
    {
        return !(*this == scalar);
    }

    void swap(T& a, T& b) { //используется для обмена значения двух переменных
    T temp = a;
    a = b;
    b = temp;
    }

    void First(int num1, int num2, bool isRow) // 1 элементарное преобразование 
    {
        if (isRow){
            if (0 < num1 && num1 <= rows && 0 < num2 && num2 <= rows) {
                T swap; 
                for (int i = 0; i < cols; i ++) {
                    swap = pMatrix[cols * (num1 - 1) + i];
                    pMatrix[cols * (num1 - 1) + i] = pMatrix[cols * (num2 - 1) + i];
                    pMatrix[cols * (num2 - 1) + i] = swap;
                }
            }
        }
        else {
            if (0 < num1 && num1 <= cols && 0 < num2 && num2 <= cols) {
                T swap; 
                for (int i = 0; i < rows; i ++) {
                    swap = pMatrix[cols * i + num1 - 1];
                    pMatrix[cols * i + num1 - 1] = pMatrix[cols * i + num2 - 1];
                    pMatrix[cols * i + num2 - 1] = swap;
                }
            }
        }
    }

    void Second(int num, T chisl, bool isRow) // 2 элементарное преобразование 
    {
        if (isRow){
            if (0 < num && num <= rows) {
                for (int i = 0; i < cols; i ++) {
                    pMatrix[cols * (num - 1) + i] *= chisl;
                }
            }
        }
        else {
            if (0 < num && num <= cols) {
                for (int i = 0; i < rows; i ++) {
                    pMatrix[cols * i + num - 1] *= chisl;
                }
            }
        }
    }

    void Third(int num1, int num2, T chisl, bool isRow) // 3 элементарное преобразование 
    {
        if (isRow){
            if (0 < num1 && num1 <= rows && 0 < num2 && num2 <= rows) {
                for (int i = 0; i < cols; i ++) {
                    pMatrix[cols * (num1 - 1) + i] += chisl * pMatrix[cols * (num2 - 1) + i];
                }
            }
        }
        else {
            if (0 < num1 && num1 <= cols && 0 < num2 && num2 <= cols) { 
                for (int i = 0; i < rows; i ++) {
                    pMatrix[cols * i + num1 - 1] += chisl * pMatrix[cols * i + num2 - 1];
                }
            }
        }
    }

    Matrix Minor_Matrix(int Row, int Col) //вычисление минора для определителя
    {
        if (Row <= rows && Col <= cols){
            Matrix result(rows - 1, cols -1);
            int curi = 0, curj = 0;
            for (int i = 0; i < rows; i ++) {
                if ( i == Row - 1) 
                    curi--;
                for (int j = 0; j < cols; j ++){
                    if ( j == Col -1){
                        curj--;
                    }
                    if (i != Row - 1 && j != Col - 1){
                        result.pMatrix[curi * (cols - 1) + curj] = pMatrix[i * cols + j];
                        }    
                    curj++;
                    }
                curj = 0;
                curi++;
            }
            return result;
        }
    }
    
    T Minor(int Row, int Col) 
    {
        if (rows == cols && Row <= rows && Col <= cols) {
            return this -> Minor_Matrix(Row, Col).Det();
        }
        else {
            return 0;
        }
    }

    T AlgDop(int Row, int Col) //вычисление алгебраических дополнений
    {
        if (rows == cols && Row <= rows && Col <= cols){
                return (((Row + Col) % 2 == 0) ? 1 : -1) * this -> Minor(Row, Col);
        }
        else{
            return 0;
        }
    }

    T Det() //Поиск определителя
    {
        if (rows == cols){
            if (rows == 1) {
                return pMatrix[0];
            }
            else if (rows == 2){
                return pMatrix[0] * pMatrix[3] - pMatrix[1] * pMatrix[2];
            }
            else {
                T det = pMatrix[0] * AlgDop(1, 1);
                for (int i = 2; i <= rows; i++){
                    det += pMatrix[(i - 1) * cols] * AlgDop(i, 1);
                }
                return det;
            }
        }
        else {
            cout << "Невозможно найти определитель";
            return 0;
        }
    } 


    ~Matrix() //дектруктор 
    {
        delete[] pMatrix;
    }
};


int main () 
{
    cout << "Матрица из файла:" << endl;
    Matrix <int> A_file;
    A_file.inputFromFile("Matrix.txt");
    A_file.printMatrix();

    int rows1, cols1;
    cout << "Введите количество строк и столбцов матрицы A: ";
    cin >> rows1 >> cols1;
    Matrix <int> A(rows1, cols1);
    A.inputFromConsole();
    A.outputFromConsole();

    int rows2, cols2;
    cout << "Введите количество строк и столбцов матрицы B: ";
    cin >> rows2 >> cols2;
    Matrix <int> B(rows2, cols2);
    B.inputFromConsole();
    B.outputFromConsole();

    int rows3, cols3;
    cout << "Введите количество строк и столбцов матрицы C: ";
    cin >> rows3 >> cols3;
    Matrix <int> C(rows3, cols3);
    C.inputFromConsole();
    C.outputFromConsole();

    double scalar;
    cout << "Введите скаляр: ";
    cin >> scalar;

    cout << "A + B = " << endl; //сложили две матрицы
    (A + B).outputFromConsole(); 
    cout << "A + C = " << endl;
    (A + C).outputFromConsole();

    cout << "A - B = " << endl; //из одной матрицы вычли вторую
    (A - B).outputFromConsole(); 
    cout << "A - C = " << endl;
    (A - C).outputFromConsole();

    cout << "A * B = " << endl; //умножили две матрицы
    (A * B).outputFromConsole(); 
    cout << "A * C = " << endl;
    (A * C).outputFromConsole();

    cout << "A * Скаляр =" << endl; //умножили матрицу на скаляр
    (A * scalar).outputFromConsole(); 
    cout << "B * Скаляр =" << endl; 
    (B * scalar).outputFromConsole();
    cout << "C * Скаляр =" << endl; 
    (C * scalar).outputFromConsole();

    if (bool Raven = (A_file == A)) cout << " A_file == A " << endl; 
    else cout << " A_file != A " << endl;
    if (bool Raven = (A == B)) cout << " A == B " << endl;  //проверка на равенство матрицы 
    else cout << " A != B " << endl;
    if (bool Raven = (B == C)) cout << " B == C " << endl; 
    else cout << " B != C " << endl;
    if (bool Raven = (C == A)) cout << " C == A " << endl; 
    else cout << " C != A " << endl;

    if (bool Raven = (A == scalar)) cout << " A == scalar " << endl; //проверка на равенство матрицы и скаляра
    else cout << " A != scalar " << endl; 
    if (bool Raven = (B == scalar)) cout << " B == scalar " << endl;
    else cout << " B != scalar " << endl; 
    if (bool Raven = (C == scalar)) cout << " C == scalar " << endl << endl;
    else cout << " C != scalar " << endl << endl; 

    cout << "Элементраное преобразование 1 для матрицы А" << endl;
    A.First(1, 2, 1);
    A.outputFromConsole();

    cout << "Элементраное преобразование 2 для матрицы В" << endl;
    B.Second(1, 2, 1);
    B.outputFromConsole();

    cout << "Элементраное преобразование 3 для матрицы С" << endl;
    C.Third(1, 2, 2, 1);
    C.outputFromConsole();

    cout << "Определитель матрицы А:" << endl;
    cout << A.Det() << endl << endl;
    cout << "Определитель матрицы B:" << endl;
    cout << B.Det() << endl << endl;
    cout << "Определитель матрицы C:" << endl;
    cout << C.Det() << endl << endl;

    return 0;
}