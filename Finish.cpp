#include <iostream>
#include <cmath>
#include <stdexcept>
#include <map>
#include <functional>
#include <vector>
#include <memory>

using namespace std;

// Abstract class for operations
class Operation {
public:
    virtual ~Operation() = default;
    virtual double execute(const vector<double>& operands) = 0;
    virtual int getOperandCount() const = 0;
    virtual string getDescription() const = 0;
};

// Classes for specific operations
class Addition : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 2) throw runtime_error("2 operands required");
        return operands[0] + operands[1];
    }
    int getOperandCount() const override { return 2; }
    string getDescription() const override { return "Addition"; }
};

class Subtraction : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 2) throw runtime_error("2 operands required");
        return operands[0] - operands[1];
    }
    int getOperandCount() const override { return 2; }
    string getDescription() const override { return "Subtraction"; }
};

class Multiplication : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 2) throw runtime_error("2 operands required");
        return operands[0] * operands[1];
    }
    int getOperandCount() const override { return 2; }
    string getDescription() const override { return "Multiplication"; }
};

class Division : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 2) throw runtime_error("2 operands required");
        if (operands[1] == 0) throw runtime_error("Division by zero!");
        return operands[0] / operands[1];
    }
    int getOperandCount() const override { return 2; }
    string getDescription() const override { return "Division"; }
};

class Modulo : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 2) throw runtime_error("2 operands required");
        if (operands[1] == 0) throw runtime_error("Division by zero!");
        return fmod(operands[0], operands[1]);
    }
    int getOperandCount() const override { return 2; }
    string getDescription() const override { return "Modulo"; }
};

class Absolute : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 1) throw runtime_error("1 operand required");
        return abs(operands[0]);
    }
    int getOperandCount() const override { return 1; }
    string getDescription() const override { return "Absolute value"; }
};

class Square : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 1) throw runtime_error("1 operand required");
        return operands[0] * operands[0];
    }
    int getOperandCount() const override { return 1; }
    string getDescription() const override { return "Square"; }
};

class SquareRoot : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 1) throw runtime_error("1 operand required");
        if (operands[0] < 0) throw runtime_error("Square root of negative number!");
        return sqrt(operands[0]);
    }
    int getOperandCount() const override { return 1; }
    string getDescription() const override { return "Square root"; }
};

class Logarithm : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 1) throw runtime_error("1 operand required");
        if (operands[0] <= 0) throw runtime_error("Logarithm of non-positive number!");
        return log(operands[0]);
    }
    int getOperandCount() const override { return 1; }
    string getDescription() const override { return "Natural logarithm"; }
};

class Factorial : public Operation {
public:
    double execute(const vector<double>& operands) override {
        if (operands.size() != 1) throw runtime_error("1 operand required");
        int n = static_cast<int>(operands[0]);
        if (n < 0) throw runtime_error("Factorial of negative number!");
        unsigned long long result = 1;
        for (int i = 2; i <= n; ++i) result *= i;
        return static_cast<double>(result);
    }
    int getOperandCount() const override { return 1; }
    string getDescription() const override { return "Factorial"; }
};

// Main calculator class
class Calculator {
private:
    map<char, unique_ptr<Operation>> operations;

public:
    Calculator() {
        // Register operations
        operations['+'] = make_unique<Addition>();
        operations['-'] = make_unique<Subtraction>();
        operations['*'] = make_unique<Multiplication>();
        operations['/'] = make_unique<Division>();
        operations['%'] = make_unique<Modulo>();
        operations['a'] = make_unique<Absolute>();
        operations['s'] = make_unique<Square>();
        operations['r'] = make_unique<SquareRoot>();
        operations['l'] = make_unique<Logarithm>();
        operations['f'] = make_unique<Factorial>();
    }

    void displayMenu() const {
        cout << "\n=== CALCULATOR ===" << endl;
        for (const auto& op : operations) {
            cout << op.first << " - " << op.second->getDescription() << endl;
        }
        cout << "q - Exit" << endl;
    }

    void run() {
        char choice;

        while (true) {
            displayMenu();
            cout << "\nSelect operation: ";
            cin >> choice;

            if (choice == 'q') {
                cout << "Goodbye!" << endl;
                break;
            }

            auto it = operations.find(choice);
            if (it == operations.end()) {
                cout << "Unknown operation!" << endl;
                continue;
            }

            try {
                Operation* operation = it->second.get();
                int operandCount = operation->getOperandCount();
                vector<double> operands(operandCount);

                for (int i = 0; i < operandCount; ++i) {
                    cout << "Enter operand " << (i + 1) << ": ";
                    cin >> operands[i];
                }

                double result = operation->execute(operands);
                cout << "Result: " << result << endl;

            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
};

int main() {
    Calculator calculator;
    calculator.run();
    return 0;
}
