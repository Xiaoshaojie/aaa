#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>  // For std::setprecision
#include <sstream>  // For std::stringstream

using namespace std;

// 生成随机数
int randomInt(int max) {
    return rand() % max + 1;
}

// 生成随机小数
double randomDouble(int max) {
    double num = rand() % max + (rand() % 100) / 100.0;
    return num;
}

// 生成随机运算符
char randomOperator(const vector<char>& operators) {
    int index = rand() % operators.size();
    return operators[index];
}

// 将数值格式化为字符串
string formatNumber(double number) {
    stringstream stream;
    stream << fixed << setprecision(2) << number;
    return stream.str();
}

// 生成题目
string generateQuestion(int maxNumber, const vector<char>& operators, bool useDecimals, bool useParentheses) {
    string question;
    double num1 = useDecimals ? randomDouble(maxNumber) : randomInt(maxNumber);
    double num2 = useDecimals ? randomDouble(maxNumber) : randomInt(maxNumber);
    char op = randomOperator(operators);

    string formattedNum1 = formatNumber(num1);
    string formattedNum2 = formatNumber(num2);

    if (useParentheses) {
        question = "(" + formattedNum1 + " " + op + " " + formattedNum2 + ")";
    }
    else {
        question = formattedNum1 + " " + op + " " + formattedNum2;
    }
    return question;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));  // 初始化随机种子

    int numQuestions, maxNumber;
    bool useDecimals, useParentheses;
    string outputMethod, outputFile;
    vector<char> operators;

    cout << "Enter the number of questions: ";
    cin >> numQuestions;
    cout << "Enter the maximum number (e.g., 10 for up to 10): ";
    cin >> maxNumber;
    cout << "Enter operators to use (+, -, *, /) separated by space: ";
    char op;
    while (cin >> op) {
        operators.push_back(op);
        if (cin.peek() == '\n') break;
    }
    cout << "Use decimals? (1 for yes, 0 for no): ";
    cin >> useDecimals;
    cout << "Use parentheses? (1 for yes, 0 for no): ";
    cin >> useParentheses;
    cout << "Output method (print or file): ";
    cin >> outputMethod;

    if (outputMethod == "file") {
        cout << "Enter output file name: ";
        cin >> outputFile;
        ofstream file(outputFile);
        if (!file.is_open()) {
            cout << "Failed to open file." << endl;
            return 1;
        }
        for (int i = 0; i < numQuestions; i++) {
            file << generateQuestion(maxNumber, operators, useDecimals, useParentheses) << " = ?\n";
        }
        file.close();
        cout << "Questions written to " << outputFile << endl;
    }
    else {
        for (int i = 0; i < numQuestions; i++) {
            cout << generateQuestion(maxNumber, operators, useDecimals, useParentheses) << " = ?\n";
        }
    }

    return 0;
}