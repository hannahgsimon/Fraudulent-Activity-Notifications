#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

// Parses a string as an integer and stores the result in 'out'
// Returns true if the entire string is a valid integer
bool try_parse_int(char* str, int* out) {
    char* endptr;
    *out = strtol(str, &endptr, 10);
    return !(endptr == str || *endptr != '\0');
}

// Calculates the median from a frequency count array
// Used to avoid sorting actual expenditure data for performance
double find_median(int* count, int d) {
    int count_left = 0;
    int median_index = d / 2;

    if (d % 2 == 1) {
        // Odd number of days: find the middle element
        for (int i = 0; i < 201; i++) {
            count_left += count[i];
            if (count_left > median_index) {
                return (double)i;
            }
        }
    } else {
        // Even number of days: find the average of two middle elements
        int left = -1, right = -1;
        for (int i = 0; i < 201; i++) {
            count_left += count[i];
            if (count_left >= median_index && left == -1) {
                left = i;
            }
            if (count_left > median_index) {
                right = i;
                break;
            }
        }
        return (left + right) / 2.0;
    }

    return -1.0; // Should never reach here
}

// Main logic to count the number of notifications
// A notification is sent when today's spending is at least 2× median of trailing `d` days
int activityNotifications(int expenditure_count, int* expenditure, int d) {
    int notifications = 0;
    int count[201] = {0}; // Frequency array (since expenditure values are [0,200])

    // Initialize count array with the first `d` days
    for (int i = 0; i < d; i++) {
        count[expenditure[i]]++;
    }

    // Process the rest of the days
    for (int i = d; i < expenditure_count; i++) {
        double median = find_median(count, d);
        if (expenditure[i] >= 2 * median) {
            notifications++;
        }
        // Update frequency array (slide the window)
        count[expenditure[i - d]]--;
        count[expenditure[i]]++;
    }

    return notifications;
}

int main() {
    // Print program header
    printf("--------------------------------------------------\n");
    printf("Author: Hannah G. Simon\n");
    printf("Program: Fraudulent Activity Notifications\n");
    printf("Description: This program simulates a bank system that sends notifications to clients if their spending on a given day is at least twice the median of their spending over a trailing number of days.\n");
    printf("--------------------------------------------------\n\n");

    // Prompt user for n (days) and d (trailing days)
    printf("Enter the total number of days (n) and the number of previous/trailing days (d) to calculate the median:\n");
    char* first_line = rtrim(readline());
    char** first_multiple_input = split_string(first_line);

    // Count number of input values
    int first_input_count = 0;
    while (first_multiple_input[first_input_count] != NULL) {
        first_input_count++;
    }

    // Validate the number of inputs
    if (first_input_count != 2) {
        fprintf(stderr, "Invalid input: expected 2 values for n and d, but got %d.\n", first_input_count);
        return 1;
    }

    int n, d;
    // Validate that inputs are integers
    if (!try_parse_int(first_multiple_input[0], &n) || !try_parse_int(first_multiple_input[1], &d)) {
        fprintf(stderr, "Invalid input: both n and d must be integers.\n");
        return 1;
    }

    // Range checks
    if (n < 1 || n > 200000) {
        fprintf(stderr, "Invalid input: you entered n=%d, but n must be between 1 and 200000.\n", n);
        return 1;
    }
    if (d < 1 || d > n) {
        fprintf(stderr, "Invalid input: you entered d=%d, but d must be between 1 and n=%d.\n", d, n);
        return 1;
    }

    // Prompt for expenditures
    printf("Enter the expenditures for %d days (space-separated values):\n", n);
    char* raw_input = rtrim(readline());
    char** expenditure_temp = split_string(raw_input);

    // Count expenditures entered
    int exp_count = 0;
    while (expenditure_temp[exp_count] != NULL) {
        exp_count++;
    }

    // Validate number of expenditures
    if (exp_count != n) {
        fprintf(stderr, "Invalid input: expected n=%d expenditures, but got %d.\n", n, exp_count);
        return 1;
    }

    // Allocate array for expenditures
    int* expenditure = malloc(n * sizeof(int));
    if (expenditure == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Convert each input to integer and validate
    for (int i = 0; i < n; i++) {
        int expenditure_item;
        if (!try_parse_int(expenditure_temp[i], &expenditure_item)) {
            fprintf(stderr, "Invalid input at day %d: '%s' is not an integer.\n", i + 1, expenditure_temp[i]);
            free(expenditure);
            return 1;
        }

        if (expenditure_item < 0 || expenditure_item > 200) {
            fprintf(stderr, "Invalid expenditure at day %d: all expenditures must be between 0 and 200.\n", i + 1);
            free(expenditure);
            return 1;
        }

        expenditure[i] = expenditure_item;
    }

    // Call main logic and display result
    int result = activityNotifications(n, expenditure, d);
    printf("Total notifications: %d\n", result);

    free(expenditure); // Clean up allocated memory
    return 0;
}

// ---------------- Utility Functions ----------------

// Reads a full line of input from the user
char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;

        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;

        alloc_length <<= 1; // Double the buffer size
        data = realloc(data, alloc_length);
        if (!data) return NULL;
    }

    // Remove newline if present
    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);
        if (data) data[data_length] = '\0';
    }

    return data;
}

// Trims leading whitespace
char* ltrim(char* str) {
    if (!str) return NULL;
    while (*str && isspace(*str)) str++;
    return str;
}

// Trims trailing whitespace
char* rtrim(char* str) {
    if (!str) return NULL;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

// Splits a string into tokens by space delimiter
// Returns a NULL-terminated array of tokens
char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * (spaces + 1));
        if (!splits) return NULL;
        splits[spaces++] = token;
        token = strtok(NULL, " ");
    }

    splits = realloc(splits, sizeof(char*) * (spaces + 1));
    splits[spaces] = NULL;
    return splits;
}
