#!/usr/bin/env python3

import sys  # For stderr output and exit codes

def find_median(count, d):
    """Calculate the median of expenditures from a frequency array.
    
    Uses a counting sort histogram (count array of size 201) to find the median efficiently
    without needing to sort the actual data.
    """
    count_left = 0
    median_index = d // 2

    if d % 2 == 1:
        # Odd d: the median is the middle element
        for i in range(201):
            count_left += count[i]
            if count_left > median_index:
                return float(i)
    else:
        # Even d: the median is the average of two middle elements
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

    return -1.0  # Should not reach here with valid inputs

def activity_notifications(expenditure, d):
    """Count the number of notifications for suspicious activity.
    
    A notification is sent if today's expenditure is at least twice the median
    of the last `d` days of expenditures.
    """
    expenditure_count = len(expenditure)
    notifications = 0
    count = [0] * 201  # Counting sort histogram: 0–200 inclusive

    # Initialize the count histogram for the first `d` days
    for i in range(d):
        count[expenditure[i]] += 1

    # Slide the window through the expenditure list
    for i in range(d, expenditure_count):
        median = find_median(count, d)

        # If current day's spending is at least double the median, notify
        if expenditure[i] >= 2 * median:
            notifications += 1

        # Update the count histogram:
        # - Remove the oldest element (i - d)
        # - Add the current element (i)
        count[expenditure[i - d]] -= 1
        count[expenditure[i]] += 1

    return notifications

def try_parse_int(s):
    """Safely attempt to parse an integer from string input.
    
    Returns a tuple: (parsed_value, success_flag)
    """
    try:
        return int(s), True
    except ValueError:
        return None, False

def main():
    """Main function to handle input, validation, and trigger computation."""
    # Print program header
    print("--------------------------------------------------")
    print("Author: Hannah G. Simon (Python version)")
    print("Program: Fraudulent Activity Notifications")
    print("Description: This program simulates a bank system that sends notifications to clients if their spending on a given day is at least twice the median of their spending over a trailing number of days.")
    print("--------------------------------------------------\n")

    # Step 1: Read and validate the first line input (n and d)
    print("Enter the total number of days (n) and the number of previous/trailing days (d) to calculate the median:")
    try:
        first_line = input().strip()
        first_multiple_input = first_line.split()

        # Ensure exactly two values were entered
        if len(first_multiple_input) != 2:
            print(f"Invalid input: expected 2 values for n and d, but got {len(first_multiple_input)}.", file=sys.stderr)
            return 1

        # Parse and validate integers
        n, valid_n = try_parse_int(first_multiple_input[0])
        d, valid_d = try_parse_int(first_multiple_input[1])

        if not (valid_n and valid_d):
            print("Invalid input: both n and d must be integers.", file=sys.stderr)
            return 1

        # Check input constraints
        if n < 1 or n > 200000:
            print(f"Invalid input: you entered n={n}, but n must be between 1 and 200000.", file=sys.stderr)
            return 1

        if d < 1 or d > n:
            print(f"Invalid input: you entered d={d}, but d must be between 1 and n={n}.", file=sys.stderr)
            return 1

        # Step 2: Read and validate expenditure list
        print(f"Enter the expenditures for {n} days (space-separated values):")
        raw_input = input().strip()
        expenditure_temp = raw_input.split()

        if len(expenditure_temp) != n:
            print(f"Invalid input: expected n={n} expenditures, but got {len(expenditure_temp)}.", file=sys.stderr)
            return 1

        # Convert expenditure strings to integers with validation
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

        # Step 3: Run fraud detection algorithm and print result
        result = activity_notifications(expenditure, d)
        print(f"Total notifications: {result}")

    except EOFError:
        # Handle unexpected end of input
        print("Error: Input terminated unexpectedly.", file=sys.stderr)
        return 1

    return 0

# Entry point for script execution
if __name__ == "__main__":
    sys.exit(main())
