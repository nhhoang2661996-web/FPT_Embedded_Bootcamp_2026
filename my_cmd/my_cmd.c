#include <string.h>
#include <stdio.h>
#include "my_cmd.h"

uint8_t cmd_parser(cmd_t* table, uint8_t* command) {
    if (table == NULL) return CMD_TBL_NOT_FOUND;

    if (*command == '\0' || *command == '\n' || *command == '\r' || *command == ' ')return CMD_EMPTY;

    uint8_t cmd[CMD_MAX_SIZE];
    uint8_t index = 0;
    uint8_t* input = command;

    while (*input){
        if (*input == ' ' || *input == '\r' || *input == '\n') break;
        cmd[index++] = *input;
        input++;
        if (index >= CMD_MAX_SIZE) return CMD_TOO_LONG;
    }
    cmd[index] = '\0';

    while (table->cmd) {
        if (strcmp((const char*)table->cmd, (const char*)cmd) == 0) {
            table->func(command);
            return CMD_SUCCESS;
        }
        table++;
    }
    return CMD_NOT_FOUND;
}

void cmd_print_error(uint8_t error_code) {
    switch (error_code) {
        case CMD_NOT_FOUND:     printf("[ERROR]: Command not found\n");   break;
        case CMD_EMPTY:         printf("[ERROR]: Empty command\n");        break;
        case CMD_TOO_LONG:      printf("[ERROR]: Command too long\n");     break;
        case CMD_TBL_NOT_FOUND: printf("[ERROR]: Table not found\n");      break;
        default: break;
    }
}