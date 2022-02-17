/* Mental Math Trainer
A simple tool for practicing your multiplication skills!
By Kenneth Burchfiel
Released under the MIT License
*/

// Used A Tour of C++ (2nd Edition) and cppreference.com as my main references

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

    cout << "Welcome to the Mental Math Trainer! This program allows you \
to practice multiplying 1-2 digit numbers by other 1-2 digit numbers. Try \
to complete these problems in your head if you can.\n\n\
Hint: to complete problems involving 2-digit numbers in your head, try \
dividing the problem up into a series of single-digit multiplication problems. \
For instance, to multiply 74 by 8, first multiply 70 by 8 to get 560, then \
multiply 4 by 8 to get 32. Finally, add 560 and 32 together to get 592.\n\n\
Similarly, to multiply 48 by 37, multiply 40 by 30 (producing 1200); 8 by \
30 (producing 240 and a running sum of 1440); 40 by 7 (producing 280 and a \
running sum of 1720); and 8 by 7 (producing 56 and a final sum of 1776).\n\n";

    while (true)

    {

        cout << "To start a training session, enter four integers \
separated by spaces.\nThe first integer \
represents the number of digits (1 or 2) of the first number to multiply.\n\
The second integer represents the number of digits (1 or 2) of the second \
number to multiply.\nThe third integer represents how many trials you would \
like.\nThe fourth integer represents whether you would like to see the time \
it took you to complete these trials. (Enter 1 for Yes and 0 for No).\
\nFor instance, to multiply a one-digit number by a 2-digit number 5 times \
and see how long that takes, enter 1 2 5 1.\n";

        while (true) /* This while loop allows for the validity of each number
        to be checked, and also lets users retry their inputs.*/
        {

            cin >> first_num_digits;

            if (!cin or first_num_digits < 0 or first_num_digits > 2)
            {
                cout << "The value for the first number to multiply \
should be either 1 (for a one digit number) or 2 (for a 2-digit number). \
Please try entering the four numbers again.\n";
                cin.clear();             
            // From https://developers.google.com/edu/c++/solutions/1-3
                cin.ignore(10000, '\n'); 
            // Also from https://developers.google.com/edu/c++/solutions/1-3
                continue;
            }
            cin >> second_num_digits;

            if (!cin or second_num_digits < 0 or second_num_digits > 2)
            {
                cout << "The value for the second number to multiply \
should be either 1 (for a one digit number) or 2 (for a 2-digit number). \
Please try entering the four numbers again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            cin >> trials_count;

            if (!cin or trials_count < 0)
            {
                cout << "The trials count should be a positive integer. \
Please try entering the four numbers again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin >> reveal_time;

            if (!cin or reveal_time < 0 or reveal_time > 1)
            {
                cout << "The fourth number should be a 0 if you do not wish \
to reveal your time or a 1 if you do wish to. Please try entering the four \
numbers again.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            break;
        }

        int correct_answers = 0;
        /* The use of chrono::high_resolution_clock allows users to time
        how long it takes to complete the challenge. */
        
        auto start_time = chrono::high_resolution_clock::now();
        // From p. 179 of A Tour of C++ (2nd Edition)
        int num_1 = 0;
        int num_2 = 0;
        while (correct_answers < trials_count) /* This loop creates new
        random numbers for the user to multiply as long as the number of 
        correct answers is lower than the number of trials requested. */
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
            while (true) /* This loop continues until the user selects the 
            correct answer.*/
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
