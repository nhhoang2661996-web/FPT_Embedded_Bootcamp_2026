#include <stdio.h>
#include <stdint.h>
#include "my_cmd.h"

int32_t cmd_led(uint8_t* argv) {
    printf("[LED]: Received command: %s\n", argv);
    return 0;
}

cmd_t my_table[] = {
    {(const int8_t*)"led", cmd_led, (const int8_t*)"LED control"},
    {NULL, NULL, NULL}
};

void cmd_run(cmd_t* table, uint8_t* command) {
    uint8_t ret = cmd_parser(table, command);
    cmd_print_error(ret);
}

int main() {
    cmd_run(my_table, (uint8_t*)"led on");
    cmd_run(my_table, (uint8_t*)"motor on");
    cmd_run(my_table, (uint8_t*)"");
    return 0;
}