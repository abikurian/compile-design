
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_EXPR 50

struct expr {
    char op[10];
    char op1[10];
    char op2[10];
    char res[10];
    int flag;  // 1 if eliminated
} arr[MAX_EXPR];

int n;

// Helper function to check whether a string
// represents a valid integer (including negative numbers)
bool is_number(const char *str)
{
    if (str == NULL || *str == '\0')
        return false;

    int i = 0;

    if (str[0] == '-') {
        if (str[1] == '\0')
            return false;
        i = 1;
    }

    for (; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i]))
            return false;
    }

    return true;
}

// Function to substitute a target variable
// with a constant value from line start_idx onwards
void propagate(int start_idx, const char *target,
               const char *value)
{
    for (int i = start_idx; i < n; i++) {

        if (arr[i].flag)
            continue;

        // Stop propagation if target variable is redefined
        if (strcmp(arr[i].res, target) == 0) {
            break;
        }

        // Substitute operand 1 if it matches
        if (strcmp(arr[i].op1, target) == 0) {
            strcpy(arr[i].op1, value);
        }

        // Substitute operand 2 if it matches
        if (strcmp(arr[i].op2, target) == 0) {
            strcpy(arr[i].op2, value);
        }
    }
}

void optimize()
{
    bool changed = true;

    // Fixed-Point Iteration:
    // Keep running passes until no more optimizations occur
    while (changed) {
        changed = false;

        for (int i = 0; i < n; i++) {

            if (arr[i].flag)
                continue;

            // Case 1: Simple Assignment of a Constant
            if (strcmp(arr[i].op, "=") == 0 &&
                is_number(arr[i].op1)) {

                arr[i].flag = 1;
                propagate(i + 1, arr[i].res, arr[i].op1);
                changed = true;
            }

            // Case 2: Both operands are constants - Fold the constant
            else if (is_number(arr[i].op1) &&
                     is_number(arr[i].op2)) {

                int val1 = atoi(arr[i].op1);
                int val2 = atoi(arr[i].op2);
                int result = 0;
                bool valid = true;

                char c_op = arr[i].op[0];

                switch (c_op) {
                    case '+':
                        result = val1 + val2;
                        break;

                    case '-':
                        result = val1 - val2;
                        break;

                    case '*':
                        result = val1 * val2;
                        break;

                    case '/':
                        if (val2 != 0) {
                            result = val1 / val2;
                        } else {
                            valid = false;
                        }
                        break;

                    default:
                        valid = false;
                        break;
                }

                if (valid) {

                    // Turn arithmetic expression into
                    // a constant assignment
                    strcpy(arr[i].op, "=");
                    sprintf(arr[i].op1, "%d", result);
                    strcpy(arr[i].op2, "-");
                    arr[i].flag = 1;

                    // Propagate the newly folded constant
                    propagate(i + 1, arr[i].res, arr[i].op1);

                    changed = true;
                }
            }
        }
    }
}

void input()
{
    printf("\nEnter the maximum number of expressions: ");

    if (scanf("%d", &n) != 1 || n < 1 ||
        n > MAX_EXPR) {
        printf("Invalid number of expressions!\n");
        exit(1);
    }

    printf("\nEnter the input (Format: op op1 op2 res):\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%9s %9s %9s %9s",
                  arr[i].op,
                  arr[i].op1,
                  arr[i].op2,
                  arr[i].res) != 4) {
            printf("Invalid input!\n");
            exit(1);
        }

        arr[i].flag = 0;
    }
}

void output()
{
    printf("\nOptimized code is:\n");

    for (int i = 0; i < n; i++) {

        if (!arr[i].flag) {
            printf("%s %s %s %s\n",
                   arr[i].op,
                   arr[i].op1,
                   arr[i].op2,
                   arr[i].res);
        }
    }
}

int main()
{
    input();
    optimize();
    output();

    return 0;
}

/*
SAMPLE INPUT:

4
= 3 - a
+ a b t1
+ a c t2
+ t1 t2 t3

*/
