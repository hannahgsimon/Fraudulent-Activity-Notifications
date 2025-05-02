#!/usr/bin/env python3

import sys

def find_median(count, d):
    """Calculate the median from a counting array"""
    count_left = 0
    median_index = d // 2

    if d % 2 == 1:  # Odd number of elements
        for i in range(201):
            count_left += count[i]
            if count_left > median_index:
                return float(i)
    else:  # Even number of elements
        left = -1
        right = -1
        for i in range(201):
            count_left += count[i]
            if count_left >= median_index and left == -1:
                left = i
            if count_left > median_index:
                right = i
                break
        return (left + right) / 2.0

    return -1.0  # This should not happen if the input is valid

def activity_notifications(expenditure, d):
    """Calculate the number of fraud notifications"""
    expenditure_count = len(expenditure)
    notifications = 0
    count = [0] * 201  # Counting array for expenditures (0-200)

    # Initialize the sliding window
    for i in range(d):
        count[expenditure[i]] += 1

    # Process each day after the initial window
    for i in range(d, expenditure_count):
        median = find_median(count, d)
        if expenditure[i] >= 2 * median:
            notifications += 1
        count[expenditure[i - d]] -= 1  # Remove the oldest day
        count[expenditure[i]] += 1      # Add the current day

    return notifications

def try_parse_int(s):
    """Safely parse an integer with error checking"""
    try:
        return int(s), True
    except ValueError:
        return None, False

def main():
    """Main function that handles user input and runs the algorithm"""
    # Program header
    print("--------------------------------------------------")
    print("Author: Hannah G. Simon (Python version)")
    print("Program: Fraudulent Activity Notifications")
    print("Description: This program simulates a bank system that sends notifications to clients if their spending on a given day is at least twice the median of their spending over a trailing number of days.")
    print("--------------------------------------------------\n")

    # Begin user input
    print("Enter the total number of days (n) and the number of previous/trailing days (d) to calculate the median:")
    try:
        first_line = input().strip()
        first_multiple_input = first_line.split()

        if len(first_multiple_input) != 2:
            print(f"Invalid input: expected 2 values for n and d, but got {len(first_multiple_input)}.", file=sys.stderr)
            return 1

        n, valid_n = try_parse_int(first_multiple_input[0])
        d, valid_d = try_parse_int(first_multiple_input[1])

        if not (valid_n and valid_d):
            print("Invalid input: both n and d must be integers.", file=sys.stderr)
            return 1

        if n < 1 or n > 200000:
            print(f"Invalid input: you entered n={n}, but n must be between 1 and 200000.", file=sys.stderr)
            return 1

        if d < 1 or d > n:
            print(f"Invalid input: you entered d={d}, but d must be between 1 and n={n}.", file=sys.stderr)
            return 1

        print(f"Enter the expenditures for {n} days (space-separated values):")
        raw_input = input().strip()
        expenditure_temp = raw_input.split()

        if len(expenditure_temp) != n:
            print(f"Invalid input: expected n={n} expenditures, but got {len(expenditure_temp)}.", file=sys.stderr)
            return 1

        expenditure = []
        for i, exp_str in enumerate(expenditure_temp):
            expenditure_item, valid = try_parse_int(exp_str)
            
            if not valid:
                print(f"Invalid input at day {i + 1}: '{exp_str}' is not an integer.", file=sys.stderr)
                return 1

            if expenditure_item < 0 or expenditure_item > 200:
                print(f"Invalid expenditure at day {i + 1}: all expenditures must be between 0 and 200.", file=sys.stderr)
                return 1

            expenditure.append(expenditure_item)

        result = activity_notifications(expenditure, d)
        print(f"Total notifications: {result}")

    except EOFError:
        print("Error: Input terminated unexpectedly.", file=sys.stderr)
        return 1

    return 0

if __name__ == "__main__":
    sys.exit(main())