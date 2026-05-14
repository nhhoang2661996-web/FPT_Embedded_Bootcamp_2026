#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cmd_line.h"

static int total_pass = 0;
static int total_case = 6;

int32_t cmd_led(uint8_t* argv) {
    printf("[LED]: Received command: %s\n", argv);
    return 0;
}
cmd_line_t my_table[] = {
    {(const int8_t*)"led", cmd_led, (const int8_t*)"LED control"},
    {NULL, NULL, NULL}
};
cmd_line_t empty_table[] = {{NULL, NULL, NULL}};

void run_test(const char* test_name, cmd_line_t* table, const char* input_str, uint8_t expected_result) {
    uint8_t input[50];
    strcpy((char*)input, input_str);

    printf("Test: %s\n", test_name);
    printf("Input: \"%s\"\n", input_str);

    uint8_t result = cmd_line_parser(table, input);

    if (result == expected_result) {
        total_pass++;
        printf("=> PASS\n");
    } else {
        printf("=> FAIL (real: %d, expected: %d)\n", result, expected_result);
    }
    printf("---------------------------\n");
}
int main() {
    printf("==== START UNIT TEST ====\n\n");
    total_pass = 0;

    // 1. Valid command
    run_test("Valid command", my_table, "led on", CMD_SUCCESS);

    // 2. Command not found
    run_test("Command not found", my_table, "motor on", CMD_NOT_FOUND);

    // 3. Command too long
    run_test("Command too long", my_table, "nay_la_lenh_rat_dai", CMD_TOO_LONG);

    // 4. Command with argument
    run_test("Command with argument", my_table, "led 100", CMD_SUCCESS);

    // 5. Null table
    run_test("Null table", NULL, "led on", CMD_TBL_NOT_FOUND);

    // 6. Empty table
    run_test("Empty table", empty_table, "led on", CMD_NOT_FOUND);

    printf("\n==== COMPLET UNIT TEST ====\n");
    printf("PASS: %d\n", total_pass);
    printf("FAIL: %d\n", total_case-total_pass);
    printf("---------------------------\n");
    printf("TONG: %d\n", total_case);
    return 0;
}