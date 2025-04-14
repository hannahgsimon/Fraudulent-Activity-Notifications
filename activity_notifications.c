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

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

double find_median(int* count, int d) {
    int count_left = 0;
    int median_index = d / 2;

    if (d % 2 == 1) {
        for (int i = 0; i < 201; i++) {
            count_left += count[i];
            if (count_left > median_index) {
                return (double)i;
            }
        }
    } else {
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
        return (left + right) / 2.0;  // Use floating-point division
    }

    return -1.0;
}

int activityNotifications(int expenditure_count, int* expenditure, int d) {
    int notifications = 0;
    int count[201] = {0};

    for (int i = 0; i < d; i++) {
        count[expenditure[i]]++;
    }

    for (int i = d; i < expenditure_count; i++) {
        double median = find_median(count, d);
        if (expenditure[i] >= 2 * median) {
            notifications++;
        }

        count[expenditure[i - d]]--;
        count[expenditure[i]]++;
    }

    return notifications;
}

int main() {
    printf("Enter the total number of days (n) and the number of previous/trailing days (d) to calculate the median:\n");
    char* first_line = rtrim(readline());
    char** first_multiple_input = split_string(first_line);

    int n = parse_int(first_multiple_input[0]);
    int d = parse_int(first_multiple_input[1]);

    // Constraint checks: 1 ≤ d ≤ n ≤ 2×10^5
    if (n < 1 || n > 200000) {
        fprintf(stderr, "Invalid input: you entered n=%d, but n must be between 1 and 200000.\n", n);
        return 1;
    }
    if (d < 1 || d > n) {
        fprintf(stderr, "Invalid input: you entered d=%d, but d must be between 1 and n=%d.\n", d, n);
        return 1;
    }

    printf("Enter the expenditures for %d days (space-separated values):\n", n);
    char* raw_input = rtrim(readline());
    char** expenditure_temp = split_string(raw_input);

    // Count number of tokens entered
    int exp_count = 0;
    while (expenditure_temp[exp_count] != NULL) {
        exp_count++;
    }

    // Validate that user entered exactly n values
    if (exp_count != n) {
        fprintf(stderr, "Invalid input: expected n=%d expenditures, but got %d.\n", n, exp_count);
        return 1;
    }

    int* expenditure = malloc(n * sizeof(int));
    if (expenditure == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int expenditure_item = parse_int(expenditure_temp[i]);

        // Constraint check: 0 ≤ expenditure[i] ≤ 200
        if (expenditure_item < 0 || expenditure_item > 200) {
            fprintf(stderr, "Invalid expenditure at day %d: must be 0–200\n", i + 1);
            free(expenditure);
            return 1;
        }

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(n, expenditure, d);

    printf("Total notifications: %d\n", result);

    free(expenditure);
    return 0;
}


char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);
        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

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

    // Add null terminator
    splits = realloc(splits, sizeof(char*) * (spaces + 1));
    splits[spaces] = NULL;

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
