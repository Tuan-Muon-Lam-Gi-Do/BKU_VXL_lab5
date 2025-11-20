#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;
void setTimer1(int duration); // Hàm cài đặt giờ
void setTimer2(int duration); // Hàm cài đặt giờ
void timerRun(); // Hàm đếm ngược (đặt trong ngắt)

#endif /* INC_SOFTWARE_TIMER_H_ */
