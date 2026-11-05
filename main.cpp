
#include <bitset>
#include <iostream>
#include <limits>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <cstdint>
using namespace std;

unsigned short bits = 8;
optional<uint64_t> number1;
optional<uint64_t> number2;
bool in_binary = true;

uint64_t mask() {
    if (bits == 64) {
        return numeric_limits<uint64_t>::max();
    }
    return (uint64_t{1} << bits) - 1;
}

int tests_failed = 0;

void check(bool condition, const char* expression) {
    if (!condition) {
        ++tests_failed;
        cerr << "  FAILED: " << expression << endl;
    }
}

#define CHECK(expr) check((expr), #expr)

string int_to_string_binary(uint64_t n, size_t width = bits) {
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
    CHECK(int_to_string_binary(0, 8) == "00000000");
    CHECK(int_to_string_binary(2, 8) == "00000010");
    CHECK(int_to_string_binary(61, 8) == "00111101");
    CHECK(int_to_string_binary(255, 8) == "11111111");

    bool thrown = false;
    try { int_to_string_binary(1, 0); } catch (const invalid_argument&) { thrown = true; }
    CHECK(thrown);
}

uint64_t input_binary_number() {
    string number;
    cin >> number;

    if (number.empty() || number.find_first_not_of("01") != string::npos) {
        throw invalid_argument("Invalid binary number");
    }

    if (number.size() > bits) {
        throw invalid_argument("Too many bits");
    }

    return stoull(number, nullptr, 2);
}

uint64_t input_number() {
    cout << "Enter binary number: ";
    return input_binary_number();
}

uint64_t input_decimal_number() {
    string number;
    cin >> number;

    if (number.empty() || number.find_first_not_of("0123456789") != string::npos) {
        throw invalid_argument(number + " is not a non-negative decimal number");
    }
    uint64_t value = stoull(number);
    if (value > mask()) {
        throw out_of_range(number + " does not fit in " + to_string(bits) +
                           " bits (0.." + to_string(mask()) + ")");
    }
    return value;
}

int input_menu_choice() {
    int choice;
    if (!(cin >> choice)) {
        if (!cin.eof()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return -1;
    }
    return choice;
}

void input_number_menu(optional<uint64_t>& target) {
    cout << "    [1] in binary" << endl;
    cout << "    [2] in decimal" << endl;
    cout << "    [0] cancel" << endl;
    cout << "> ";
    switch (input_menu_choice()) {
        case 1:
            target = input_number();
            break;
        case 2:
            cout << "Enter decimal number: ";
            target = input_decimal_number();
            break;
        case 0:
            break;
        default:
            cout << "Unknown menu option" << endl;
            break;
    }
}

int check_enter(bool number2_needed = true) {
    if (!number1) {
        cout << "Enter first number" << endl;
        return false;
    }
    if (number2_needed && !number2) {
        cout << "Enter second number" << endl;
        return false;
    }
    return true;
}

string string_number(uint64_t a, bool in_binaryf = in_binary) {
    if (in_binaryf) {
        return int_to_string_binary(a);
    } else {
        return to_string(a);
    }
}

void test_string_number() {
    CHECK(string_number(5, true) == int_to_string_binary(5));
    CHECK(string_number(10, false) == "10");
}

int main() {
    bool running = true;
    string bits_input;

    while (true) {
        cout << "Enter number of bits in numbers, 1-64 (press enter for 8)" << endl;
        cout << "> ";
        getline(cin, bits_input);

        if (bits_input.empty()) {
            break;
        }
        try {
            size_t pos = 0;
            int value = stoi(bits_input, &pos);
            if (pos == bits_input.size() && value >= 1 && value <= 64) {
                bits = static_cast<unsigned short>(value);
                break;
            }
        } catch (const exception&) {
        }
    cerr << "Bit width must be a number from 1 to 64" << endl;
    }

    while (running) {
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
        cout << "[6] OR |" << endl;
        cout << "[7] NOT ~" << endl;
        cout << "[8] XOR ^" << endl;
        cout << "[9] 10 base to 2 base" << endl;
        cout << "[10] 2 base to 10 base" << endl;
        cout << "[11] switch first and second number" << endl;
        cout << "[12] shift to left <<" << endl;
        cout << "[13] shift to right >>" << endl;
        cout << "[14] plus +" << endl;
        cout << "[15] minus" << endl;
        cout << "[0] Exit" << endl;
        cout << "> ";

        int n = input_menu_choice();
        if (!cin) {
            break;
        }

        try {
            switch (n) {
                case 0:
                    running = false;
                    break;

                case 1:
                    tests_failed = 0;
                    test_int_to_string_binary();
                    test_string_number();
                    cout << (tests_failed == 0 ? "All tests PASSED" : "Some tests FAILED") << endl;
                    break;

                case 2:
                    input_number_menu(number1);
                    break;

                case 3:
                    input_number_menu(number2);
                    break;

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
                    uint64_t and_answ = *number1 & *number2;

                    cout << string_number(*number1)
                         << " AND "
                         << string_number(*number2)
                         << " = "
                         << string_number(and_answ)
                         << endl;
                    break;
                }

                case 6: {
                    if (!check_enter(true)) {
                        break;
                    }
                    uint64_t or_answ = *number1 | *number2;

                    cout << string_number(*number1)
                         << " OR "
                         << string_number(*number2)
                         << " = "
                         << string_number(or_answ)
                         << endl;
                    break;
                }

                case 7: {
                    if (!check_enter(false)) {
                        break;
                    }
                    uint64_t not_answ = ~*number1 & mask();

                    cout << "NOT "
                         << string_number(*number1)
                         << " = "
                         << string_number(not_answ)
                         << endl;
                    break;
                }

                case 8: {
                    if (!check_enter(true)) {
                        break;
                    }

                    uint64_t xor_answ = *number1 ^ *number2;

                    cout << string_number(*number1)
                         << " XOR "
                         << string_number(*number2)
                         << " = "
                         << string_number(xor_answ)
                         << endl;
                    break;
                }

                case 9: {
                    uint64_t number;
                    cout << "Enter number: ";
                    if (!(cin >> number) || number > mask()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw invalid_argument("Number does not fit in selected bit width");
                    }
                    cout << number
                         << "_10 = "
                         << int_to_string_binary(number)
                         << "_2"
                         << endl;
                    break;
                }

                case 10: {
                    uint64_t number = input_number();
                    cout << int_to_string_binary(number)
                         << "_2 = "
                         << number
                         << "_10"
                         << endl;
                    break;
                }

                case 11: {
                    swap(number1, number2);
                    cout << "switched" << endl;
                    break;
                }

                case 12: {
                    if (!check_enter(true)) {
                        break;
                    }

                    if (*number2 >= bits) {
                        cout << "Shift amount must be less than " << bits << endl;
                        break;
                    }

                    uint64_t shift_answ = (*number1 << *number2) & mask();

                    cout << string_number(*number1)
                         << " << "
                         << string_number(*number2)
                         << " = "
                         << string_number(shift_answ)
                         << endl;
                    break;
                }

                case 13: {
                    if (!check_enter(true)) {
                        break;
                    }

                    if (*number2 >= bits) {
                        cout << "Shift amount must be less than " << bits << endl;
                        break;
                    }

                    uint64_t shift_answ = *number1 >> *number2;
                    cout << string_number(*number1)
                         << " >> "
                         << string_number(*number2)
                         << " = "
                         << string_number(shift_answ)
                         << endl;
                    break;
                }

                case 14: {
                    if (!check_enter(true)) break;
                    uint64_t plus_answ = *number1 + *number2;

                    cout << string_number(*number1)
                         << " + "
                         << string_number(*number2)
                         << " = "
                         << string_number(plus_answ)
                         << endl;
                    break;
                }

                case 15: {
                    if (!check_enter(true)) break;

                    if (*number2 > *number1) {
                        d 
                    }
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
