#ifndef MY_CMD_H
#define MY_CMD_H

#include <stdint.h>

#define CMD_SUCCESS       0
#define CMD_NOT_FOUND     1
#define CMD_TOO_LONG      2
#define CMD_TBL_NOT_FOUND 3
#define CMD_EMPTY         4

#define CMD_MAX_SIZE 12

typedef int32_t (*cmd_func_t)(uint8_t* argv);

typedef struct {
    const int8_t*  cmd;
    cmd_func_t  func;
    const int8_t*  info;
} cmd_t;
uint8_t cmd_parser(cmd_t* table, uint8_t* command);
void cmd_print_error(uint8_t error_code);

#endif