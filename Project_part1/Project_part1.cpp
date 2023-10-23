#include <iostream>
#include <string>
#include <exception>
#include <cctype>

using namespace std;

double evaluate_expression(const string& expression, size_t& index) {
    double result = 0;
    char last_operator = '+';
    bool number_found = false;

    while (index < expression.length()) {
        char current_char = expression[index];

        if (current_char == ' ') {
            index++;
            continue;
        }
        else if (isdigit(current_char)) {
            double number = stod(expression.substr(index));

            while (index < expression.length() && (isdigit(expression[index]) || expression[index] == ' ')) {
                index++;
            }

            while (index < expression.length() && (expression[index] == '*' || expression[index] == '/')) {
                char op = expression[index];

                index++;
                if (index >= expression.length()) {
                    throw invalid_argument("Missing number after operator");
                }
                double next_number = stod(expression.substr(index));

                while (index < expression.length() && (isdigit(expression[index]) || expression[index] == ' ')) {
                    index++;
                }

                if (op == '*') {
                    number *= next_number;
                }
                else if (op == '/') {
                    if (next_number == 0) {
                        throw runtime_error("Division by zero");
                    }
                    number /= next_number;
                }
            }

            if (last_operator == '+') {
                result += number;
            }
            else if (last_operator == '-') {
                result -= number;
            }
            number_found = true;
        }
        else if (current_char == '+' || current_char == '-') {
            last_operator = current_char;
            index++;
        }
        else if (current_char == '(') {
            index++;

            double sub_result = evaluate_expression(expression, index);

            if (last_operator == '+') {
                result += sub_result;
            }
            else if (last_operator == '-') {
                result -= sub_result;
            }

            number_found = true;
        }
        else if (current_char == ')') {
            index++;
            break;
        }
        else {
            throw invalid_argument("Invalid character in expression");
        }
    }

    if (!number_found) {
        throw invalid_argument("No number found");
    }

    return result;
}

void function_for_read_data() {

    string input;

    do {
        cout << "Enter an expression  or 'q' to exit: ";
        getline(cin, input);

        if (input == "q") {
            break;
        }

        try {
            size_t index = 0;
            double result = evaluate_expression(input, index);

            cout << "Result: " << result << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    } while (true);
}

int main() {
    function_for_read_data();
    return 0;
}