#include <iostream>
#include <string>
#include <sstream>
#include <exception>

using namespace std;

int function_operation(int number1, char math_operator, int number2) {
    int result;

    switch (math_operator) {
    case '+':
        result = number1 + number2;
        break;

    case '-':
        result = number1 - number2;
        break;

    case '*':
        result = number1 * number2;
        break;

    case '/':
        if (number2 == 0) {
            throw runtime_error("Division by zero");
        }
        result = number1 / number2;
        break;

    default:
        throw invalid_argument("Invalid operator.");
    }

    return result;
}

void function_for_read_data() {
    int number1, number2, result;
    char math_operator;
    string input;

    do {
        cout << "Enter an expression in the format 'int math_operator int' with space between numbers or 'q' for exit" << endl;
        getline(cin, input);

        if (input == "q") {
            break;
        }

        try {
            istringstream(input) >> number1 >> math_operator >> number2;
            result = function_operation(number1, math_operator, number2);
            cout << "Result: " << result << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    } while (true);
}
int main()
{
    function_for_read_data();
    return 0;
}
