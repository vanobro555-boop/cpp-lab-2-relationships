#include <iostream>

using namespace std;

class ComplexNumber {
private:
    double m_real;
    double m_imaginary;

public:
    // Конструктор
    ComplexNumber(double real, double imaginary) : m_real(real), m_imaginary(imaginary) {
        cout << "Объект [ComplexNumber] успешно создан!" << endl;
    }

    bool operator==(const ComplexNumber& other) const {
        return (m_real == other.m_real) && (m_imaginary == other.m_imaginary);
    }

    void print() const {
        cout << m_real << " + " << m_imaginary << "i";
    }
};

int main(void) {
    setlocale(LC_ALL, "RU");

    double real1, imaginary1;
    double real2, imaginary2;

    cout << "Введите действительную и мнимую часть первого числа: ";
    cin >> real1 >> imaginary1;

    cout << "Введите действительную и мнимую часть второго числа: ";
    cin >> real2 >> imaginary2;

    ComplexNumber complex_number1(real1, imaginary1);
    ComplexNumber complex_number2(real2, imaginary2);

    cout << "\nСравниваем: ";
    complex_number1.print();
    cout << " и ";
    complex_number2.print();
    cout << endl;

    if (complex_number1 == complex_number2) {
        cout << "Эти числа равны между собой!" << endl;
    }
    else {
        cout << "Эти числа не равны между собой!" << endl;
    }

    return 0;
}