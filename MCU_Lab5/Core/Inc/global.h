#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

#define MAX_BUFFER_SIZE 30

// Các trạng thái của Command Parser
#define IDLE 0
#define RECEIVING 1

// Các trạng thái của UART Communication
#define WAIT_RST 10
#define WAIT_OK  11

// Khai báo biến extern (để các file khác biết sự tồn tại của nó)
extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

extern uint8_t command_flag; // 1: Có lệnh RST, 2: Có lệnh OK
extern uint8_t command_data;

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;

#endif /* INC_GLOBAL_H_ */
