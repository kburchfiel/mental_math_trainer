/* Mental Math Trainer
A simple tool for practicing your multiplication skills!
By Kenneth Burchfiel
Released under the MIT License

*/

// Chose GDB/LLDB compiler, then selected g++.exe. This worked fine

// Using A Tour of C++ (2nd Edition) as a reference

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
using namespace std;

int main()

{
    // The random number generation code was based on
    // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

    // static random_device random_seed;
    mt19937 generator;
    generator.seed(time(0));
    // The above line is based on:
    // https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine/seed
    // and https://stackoverflow.com/a/34493057/13097194
    uniform_int_distribution<> random_one_digit_num(2, 9); // Multiplying 
    // a number by 1 isn't much of a challenge, so 1 is excluded from these
    // options.
    uniform_int_distribution<> random_two_digit_num(10, 99);

    int first_num_digits;
    int second_num_digits;
    int trials_count;
    int reveal_time;

    cout << "Welcome to the mental math trainer! This program allows you \
to practice multiplying 1-2 digit numbers by other 1-2 digit numbers.\n";

    while (true)

    {

        cout << "Please enter four integers separated by spaces.\nThe first integer \
represents the number of digits (1 or 2) of the first number to multiply.\n\
The second integer represents the number of digits (1 or 2) of the second \
number to multiply.\nThe third integer represents how many trials you would \
like.\nThe fourth integer represents whether you would like to see the time \
it took you to complete these trials. (Enter 1 for Yes and 0 for No).\
\nFor instance, to multiply a one-digit number by a 2-digit number 5 times \
and see how long that takes, enter 1 2 5 1.\n";

        while (true)
        {

            cin >> first_num_digits;

            if (!cin or first_num_digits < 0 or first_num_digits > 2)
            {
                cout << "The value for the first number to multiply \
    should be either 1 or 2.";
                cin.clear();             // From https://developers.google.com/edu/c++/solutions/1-3
                cin.ignore(10000, '\n'); // Also from https://developers.google.com/edu/c++/solutions/1-3
                continue;
            }
            cin >> second_num_digits;

            if (!cin or second_num_digits < 0 or second_num_digits > 2)
            {
                cout << "The value for the second number to multiply \
should be either 1 or 2.";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            cin >> trials_count;

            if (!cin or trials_count < 0)
            {
                cout << "The trials count should be a positive integer.";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin >> reveal_time;

            if (!cin or reveal_time < 0 or reveal_time > 1)
            {
                cout << "The fourth number should be a 0 if you do not wish \
to reveal your time or a 1 if you do wish to.";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            break;
        }

        int correct_answers = 0;
        auto start_time = chrono::high_resolution_clock::now();
        // From p. 179 of A Tour of C++ (2nd Edition)
        int num_1 = 0;
        int num_2 = 0;
        while (correct_answers < trials_count)
        {
            if (first_num_digits == 1)
            {
                num_1 = random_one_digit_num(generator);
            }
            if (first_num_digits == 2)
            {
                num_1 = random_two_digit_num(generator);
            }

            if (second_num_digits == 1)
            {
                num_2 = random_one_digit_num(generator);
            }
            if (second_num_digits == 2)
            {
                num_2 = random_two_digit_num(generator);
            }

            int answer = num_1 * num_2;
            while (true)
            {
                cout << "What is " << num_1 << " times " << num_2 << "?\n";
                int response;
                cin >> response;
                if (response == answer)
                {
                    cout << "Correct!\n";
                    correct_answers++;
                    break;
                }
                else
                {
                    cout << "Incorrect. Try again!\n";
                }
            }
        }
        auto end_time = chrono::high_resolution_clock::now();
        double milliseconds = chrono::duration_cast<chrono::milliseconds>(
                                  end_time - start_time).count();
        double seconds = milliseconds / 1000;
        double average_time_per_question = seconds / trials_count;
        // Based on p. 179 of A Tour of C++, 2nd Edition
        // and https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
        if (reveal_time == 1)
        {
            cout << "You completed this challenge in " << seconds << " seconds. \n";
            cout << "You took " << average_time_per_question << 
            " seconds on average to correctly answer each question.\n";
        }
        string retry_key; // Using a string to accept non-integer types
        cout << "Press 1 to try again or any other key to exit the program.\n";
        cin >> retry_key;
        if (retry_key == "1")
        {
            continue;
        }
        break;
    }
}
