#include "uart_communication_fsm.h"
#include <stdio.h>
#include <string.h>
#include "software_timer.h"

uint32_t adc_value = 0;
char str_output[50];
uint32_t tick_start = 0;

void uart_communiation_fsm() {
	static uint8_t comm_state = WAIT_RST;

	switch (comm_state) {
	case WAIT_RST:
		// Nếu nhận được cờ RST từ Parser
		if (command_flag == 1) {
			command_flag = 0; // Xóa cờ

			// Đọc ADC
			// (Giả sử ADC đã Start ở main rồi)
			adc_value = HAL_ADC_GetValue(&hadc1);

			// Gửi dữ liệu
			sprintf(str_output, "!ADC=%lu#\r\n", adc_value);
			HAL_UART_Transmit(&huart2, (uint8_t*)str_output, strlen(str_output), 100);

			// Chuyển trạng thái và lưu thời gian
			comm_state = WAIT_OK;
			setTimer1(300);
		}
		break;

	case WAIT_OK:
		// Nếu nhận được cờ OK
		if (command_flag == 2) {
			command_flag = 0; // Xóa cờ
			comm_state = WAIT_RST; // Xong nhiệm vụ, quay về chờ RST tiếp
		}
		// Kiểm tra Timeout 3 giây (3000ms)
		else if (timer1_flag == 1) {
			// Gửi lại dữ liệu cũ
			HAL_UART_Transmit(&huart2, (uint8_t*)str_output, strlen(str_output), 100);
			// Reset lại bộ đếm thời gian
			setTimer1(300);
		}
		break;
	}
}
