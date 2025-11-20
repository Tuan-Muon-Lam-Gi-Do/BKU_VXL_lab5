#include "command_parser.h"

void command_parser_fsm() {
	// 1. Lấy ký tự mới nhất vừa nhận được
	// (Do index_buffer luôn trỏ vào ô trống tiếp theo, nên ký tự vừa nhận nằm ở ô trước đó)
	uint8_t index = index_buffer - 1;
	if (index_buffer == 0) index = MAX_BUFFER_SIZE - 1; // Xử lý quay vòng

	uint8_t data = buffer[index];

	// 2. Máy trạng thái phát hiện chuỗi "!RST#" và "!OK#"
	// status là biến static, nó sẽ nhớ trạng thái giữa các lần gọi hàm
	static uint8_t status = 0;

	switch (status) {
	case 0: // Trạng thái chờ ký tự bắt đầu '!'
		if (data == '!') status = 1;
		break;

	case 1: // Đã có '!', chờ 'R' hoặc 'O'
		if (data == 'R') status = 2;      // Đi theo đường RST
		else if (data == 'O') status = 10; // Đi theo đường OK
		else if (data == '!') status = 1; // Gặp lại '!' thì reset
		else status = 0;
		break;

	// --- NHÁNH RST (!RST#) ---
	case 2: // Đã có "!R", chờ 'S'
		if (data == 'S') status = 3;
		else status = 0;
		break;

	case 3: // Đã có "!RS", chờ 'T'
		if (data == 'T') status = 4;
		else status = 0;
		break;

	case 4: // Đã có "!RST", chờ '#'
		if (data == '#') {
			command_flag = 1; // PHÁT HIỆN THÀNH CÔNG LỆNH RST
			status = 0;      // Reset về đầu
		}
		else status = 0;
		break;

	// --- NHÁNH OK (!OK#) ---
	case 10: // Đã có "!O", chờ 'K'
		if (data == 'K') status = 11;
		else status = 0;
		break;

	case 11: // Đã có "!OK", chờ '#'
		if (data == '#') {
			command_flag = 2; // PHÁT HIỆN THÀNH CÔNG LỆNH OK
			status = 0;       // Reset về đầu
		}
		else status = 0;
		break;

	default:
		status = 0;
		break;
	}
}
