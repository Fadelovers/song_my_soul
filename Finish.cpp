#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

class Calculator {
public:
    // Binary operations
    double add(double a, double b) { 
        return a + b; 
    }
    double subtract(double a, double b) {
        return a - b; 
    }
    double multiply(double a, double b) {
        return a * b; 
    }
    double divide(double a, double b) {
        if (b == 0) throw runtime_error("Division by zero!");
        return a / b;
    }
    double modulo(double a, double b) {
        if (b == 0) throw runtime_error("Modulo by zero!");
        return fmod(a, b);
    }

    // Unary operations
    double sqr(double x) {
        return x * x; 
    }
    double sqrt(double x) {
        if (x < 0) throw runtime_error("Square root of negative number!");
        return std::sqrt(x);
    }
    double log(double x) {
        if (x <= 0) throw runtime_error("Logarithm of non-positive number!");
        return std::log(x);
    }
    long long factorial(int n) {
        if (n < 0) throw runtime_error("Factorial of negative number!");
        long long result = 1;
        for (int i = 2; i <= n; ++i) result *= i;
        return result;
    }
};

class CalculatorInterface {
private:
    Calculator calc;

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void waitForEnter() {
        cout << "\nPress Enter to continue...";
        cin.ignore(10000, '\n');
        cin.get();
    }

    void showMenu() {
        clearScreen();
        cout << "=== ADVANCED CALCULATOR ===\n\n"
            << "Available operations:\n"
            << "+  Addition\n"
            << "-  Subtraction\n"
            << "*  Multiplication\n"
            << "/  Division\n"
            << "%  Modulo\n"
            << "s  Square\n"
            << "q  Square root\n"
            << "l  Logarithm\n"
            << "!  Factorial\n"
            << "0  Exit\n\n";
    }

public:
    void run() {
        char operation;
        double a, b;
        int n;

        while (true) {
            showMenu();
            cout << "Choose operation: ";
            cin >> operation;

            if (operation == '0') break;

            try {
                clearScreen();
                cout << "=== ADVANCED CALCULATOR ===\n\n";

                switch (operation) {
                case '+':
                    cout << "ADDITION\n";
                    cout << "Enter two numbers: ";
                    cin >> a >> b;
                    cout << "Result: " << a << " + " << b << " = " << calc.add(a, b) << "\n";
                    break;
                case '-':
                    cout << "SUBTRACTION\n";
                    cout << "Enter two numbers: ";
                    cin >> a >> b;
                    cout << "Result: " << a << " - " << b << " = " << calc.subtract(a, b) << "\n";
                    break;
                case '*':
                    cout << "MULTIPLICATION\n";
                    cout << "Enter two numbers: ";
                    cin >> a >> b;
                    cout << "Result: " << a << " * " << b << " = " << calc.multiply(a, b) << "\n";
                    break;
                case '/':
                    cout << "DIVISION\n";
                    cout << "Enter two numbers: ";
                    cin >> a >> b;
                    cout << "Result: " << a << " / " << b << " = " << calc.divide(a, b) << "\n";
                    break;
                case '%':
                    cout << "MODULO\n";
                    cout << "Enter two numbers: ";
                    cin >> a >> b;
                    cout << "Result: " << a << " % " << b << " = " << calc.modulo(a, b) << "\n";
                    break;
                case 's':
                    cout << "SQUARE\n";
                    cout << "Enter a number: ";
                    cin >> a;
                    cout << "Result: " << a << "^2 = " << calc.sqr(a) << "\n";
                    break;
                case 'q':
                    cout << "SQUARE ROOT\n";
                    cout << "Enter a number: ";
                    cin >> a;
                    cout << "Result: sqrt(" << a << ") = " << calc.sqrt(a) << "\n";
                    break;
                case 'l':
                    cout << "LOGARITHM\n";
                    cout << "Enter a number: ";
                    cin >> a;
                    cout << "Result: ln(" << a << ") = " << calc.log(a) << "\n";
                    break;
                case '!':
                    cout << "FACTORIAL\n";
                    cout << "Enter an integer: ";
                    cin >> n;
                    cout << "Result: " << n << "! = " << calc.factorial(n) << "\n";
                    break;
                default:
                    cout << "Unknown operation!\n";
                }

                waitForEnter();

            }
            catch (const exception& e) {
                clearScreen();
                cout << "=== ADVANCED CALCULATOR ===\n\n";
                cout << "Error: " << e.what() << "\n";
                waitForEnter();
            }
        }

        clearScreen();
        cout << "=== ADVANCED CALCULATOR ===\n\n";
        cout << "Thank you for using the calculator!\n";
    }
};

int main() {
    CalculatorInterface ci;
    ci.run();
    return 0;
}
