#include "software_timer.h"

int timer1_counter = 0; // Biến đếm ngược
int timer1_flag = 0;    // Cờ báo trạng thái
int timer2_counter = 0; // Biến đếm ngược
int timer2_flag = 0;    // Cờ báo trạng thái

// Hàm này quy định tần số quét của timer.
// Ví dụ: TICK bên dưới là 10ms, nếu setTimer1(200) nghĩa là 200*10 = 2000ms = 2s
// Nếu TICK là 1ms thì nhập thẳng số ms.
void setTimer1(int duration){
	timer1_counter = duration;
	timer1_flag = 0;
}

void setTimer2(int duration){
	timer2_counter = duration;
	timer2_flag = 0;
}

// Hàm này sẽ được gọi bên trong System Tick Interrupt
void timerRun(){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0){
			timer1_flag = 1; // Hết giờ -> Bật cờ
		}
	}

	if(timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter <= 0){
			timer2_flag = 1; // Hết giờ -> Bật cờ
		}
	}
}
