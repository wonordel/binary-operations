
#include <bitset>
#include <cassert>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <ctime>

using namespace std;

unsigned short bits = 8;
int number1 = -1;
int number2 = -1;
bool in_binary = true;

string int_to_string_binary(int n, size_t width = bits) {
    constexpr size_t storage_bits = 64;

    if (width == 0 || width > storage_bits) {
        throw invalid_argument(
            "Bit width must be between 1 and 64"
        );
    }

    string binary = bitset<storage_bits>(
        static_cast<unsigned long long>(n)
    ).to_string();

    return binary.substr(binary.size() - width);
}

void test_int_to_string_binary() {
    clock_t start = clock();
    assert(int_to_string_binary(0, 8) == "00000000");
    assert(int_to_string_binary(2, 8) == "00000010");
    assert(int_to_string_binary(61,8) == "00111101");
    double seconds = double(clock() - start) / CLOCKS_PER_SEC;
    cout << "test_string_number: 3 calls PASSED in " << seconds << " seconds" << endl;
}

int __input_binary_number() {
    string number;
    cin >> number;

    if (number.empty()) {
        throw invalid_argument("Empty input");
    }

    for (char c : number) {
        if (c != '0' && c != '1') {
            throw invalid_argument(number + " is not a binary number");
        }
    }

    if (number.size() > bits) {
        throw invalid_argument("Binary number must contain at most " + to_string(bits) + " bits");
    }

    return stoi(number, nullptr, 2);
}

int input_number(int n = 0) {
    if (n == 0) {
        cout << "Enter binary number: ";
    } else {
        cout << "Enter " << n << "th binary number: ";
    }
    return __input_binary_number();
}

int check_enter(bool number2_needed = true, int numberf = number1, int numbers = number2) {
    if (numberf < 0) {
        cout << "Enter first number" << endl;
        return false;
    }
    if (number2_needed && numbers < 0) {
        cout << "Enter second number" << endl;
        return false;
    }
    return true;
}

void test_check_enter() {
    clock_t start = clock();
    assert(check_enter(true, -1, 1) == false);
    assert(check_enter(false, 1, -1) == true);
    assert(check_enter(true, -1, -1) == false);
    double seconds = double(clock() - start) / CLOCKS_PER_SEC;
    cout << "test_check_enter: 3 calls PASSED in " << seconds << " seconds" << endl;
}

string string_number(int a, bool in_binaryf = in_binary) {
    if (in_binaryf) {
        return int_to_string_binary(a);
    } else {
        return to_string(a);
    }
}

void test_string_binary() {
    clock_t start = clock();
    assert(string_number(5, true) == int_to_string_binary(5));
    assert(string_number(10, false) == "10");
    double seconds = double(clock() - start) / CLOCKS_PER_SEC;
    cout << "test_string_binary: 2 calls PASSED in " << seconds << " seconds" << endl;
}

int main() {
    bool running = true;
    string bits_input;

    cout << "Enter number of bits in numbers (press enter for 8)" << endl;
    cout << "> ";

    getline(cin, bits_input);

    if (!bits_input.empty()) {
        bits = stoi(bits_input);
    }

    while (running) {
        short n;

        cout << "\n[1] Run tests" << endl;
        cout << "[2] enter first number" << endl;
        cout << "[3] enter second number" << endl;
        if (!in_binary) {
            cout << "[4] switch to binary number printing";
        } else {
            cout << "[4] switch to decimal number printing";
        }
        cout << endl;
        cout << "[5] AND &" << endl;
        cout << "[6] OR +" << endl;
        cout << "[7] NOT ! ~" << endl;
        cout << "[8] XOR ^" << endl;
        cout << "[9] 10 base to 2 base" << endl;
        cout << "[10] 2 base to 10 base" << endl;
        cout << "[11] switch first and second number" << endl;
        cout << "[12] shift to left" << endl;
        cout << "[13] shift to right" << endl;
        cout << "[0] Exit" << endl;
        cout << "> ";

        if (!(cin >> n)) {
            cerr << "Invalid menu input" << endl;
            return 1;
        }

        try {
            switch (n) {
                case 0:
                    running = false;
                    break;

                case 1:
                    test_int_to_string_binary();
                    test_check_enter();
                    test_string_binary();
                    break;

                case 2: {
                    unsigned short choice;
                    cout << "    [1] in binary" << endl;
                    cout << "    [2] in decimal" << endl;
                    cout << "    [3] cancel" << endl;
                    cout << "> ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            number1 = input_number();
                            break;
                        }
                        case 2: {
                            cout << "Enter decimal number: ";
                            cin >> number1;
                            break;
                        }

                        case 3: {
                            break;
                        }

                        default: cout << "Unknown menu option" << endl; break;
                    }
                    break;
                }

                case 3: {
                    unsigned short choice;
                    cout << "    [1] in binary" << endl;
                    cout << "    [2] in decimal" << endl;
                    cout << "    [0] cancel" << endl;
                    cout << "> ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            number2 = input_number();
                            break;
                        }
                        case 2: {
                            cout << "Enter decimal number: ";
                            cin >> number2;
                            break;
                        }

                        case 0: {
                            break;
                        }

                        default: cout << "Unknown menu option" << endl; break;
                    }
                    break;
                }

                case 4: {
                    in_binary = !in_binary;
                    cout << "switched to ";
                    if (in_binary) {
                        cout << "binary";
                    } else {
                        cout << "decimal";
                    }
                    cout << endl;
                    break;
                }

                case 5: {
                    if (!check_enter(true)) {
                        break;
                    }
                    int and_answ = number1 & number2;

                    cout << string_number(number1)
                         << " AND "
                         << string_number(number2)
                         << " = "
                         << string_number(and_answ)
                         << endl;
                    break;
                }

                case 6: {
                    if (!check_enter(true)) {
                        break;
                    }
                    int or_answ = number1 | number2;

                    cout << string_number(number1)
                         << " OR "
                         << string_number(number2)
                         << " = "
                         << string_number(or_answ)
                         << endl;
                    break;
                }

                case 7: {
                    if (!check_enter(false)) {
                        break;
                    }
                    int not_answ = ~number1;

                    cout << "NOT "
                         << string_number(number1)
                         << " = "
                         << string_number(not_answ)
                         << endl;
                    break;
                }

                case 8: {
                    if (!check_enter(true)) {
                        break;
                    }

                    int xor_answ = number1 ^ number2;

                    cout << string_number(number1)
                         << " XOR "
                         << string_number(number2)
                         << " = "
                         << string_number(xor_answ)
                         << endl;
                    break;
                }

                case 9: {
                    int number;
                    cout << "Enter number: ";
                    cin >> number;
                    cout << number
                         << "_10 = "
                         << string_number(number)
                         << "_2"
                         << endl;
                    break;
                }

                case 10: {
                    int number = input_number();
                    cout << string_number(number)
                         << "_2 = "
                         << number
                         << "_10"
                         << endl;
                    break;
                }

                case 11: {
                    int temp1 = number1;
                    number1 = number2;
                    number2 = temp1;
                    cout << "switched" << endl;
                    break;
                }

                case 12: {
                    if (!check_enter(true)) {
                        break;
                    }
                    int shift_answ = number1 << number2;

                    cout << string_number(number1)
                         << " << "
                         << string_number(number2)
                         << " = "
                         << string_number(shift_answ)
                         << endl;
                    break;
                }

                case 13: {
                    if (!check_enter(true)) {
                        break;
                    }
                    int shift_answ = number1 >> number2;
                    cout << string_number(number1)
                         << " >> "
                         << string_number(number2)
                         << " = "
                         << string_number(shift_answ)
                         << endl;
                    break;
                }

                default:
                    cout << "Unknown menu option" << endl;
                    break;
            }
        } catch (const invalid_argument& e) {
            cerr << "Input error: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cerr << "Number is out of range: " << e.what() << endl;
        }
    }

    return 0;
}
