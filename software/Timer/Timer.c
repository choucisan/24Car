#include "timer.h"
#include "xunji.h"
#include "A_include.h"
#include "math.h"

void xun_ji(void);
void function(void);
//int Delay_500ms(int num);


#define WHITE 0
#define BLACK 1

int currentState = 0, last_currentState = 3; 
int stateChangeCount = 0; 
int stateChangeConfirmed = 0; // 状态变化确认标志
uint32_t stateChangeTimer = 0,B_stateCount,W_stateCount; // 状态变化计时器
bool B_flag=0, W_flag=0;
uint32_t Length = 0,xie_length1,xie_length2;
unsigned char xiexian_flag = 0,circle_count = 0, encoder_cnt = 0;
unsigned char jiance_mode;//第一题检测到一次就停 2.检测2次转弯
unsigned char jiance_time = 0;//第一题检测到一次就停 2.检测2次转弯
unsigned char zhixian_flag = 0;//第2题用于switch
unsigned char distance = 0;//第4题超声波检测
int mode_time = 0;     //计数时间
float angle_diff[6] = {0, 3, 3, 3, 3, 3};
int speed_l,speed_r;
void Timer_Init(void)
{
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
	DL_TimerG_startCounter(TIMER_0_INST);
}
int tt;

uint16_t xx_delay;
void TIMER_0_INST_IRQHandler(void)
{
    if(DL_Timer_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO)
    {
			if(beep_cnt > 0)beep_cnt--;
			if(jiance_time > 0)jiance_time--;

}
void Black_Control(void)
{
	if (L2 ) PWM_SET(800, 1800);
		else if(L1) PWM_SET(800, 1200);
			else if (R2) PWM_SET(1800, 800); 
			else if(R1)PWM_SET(1250, 800); 
			else if (M0) PWM_SET(800, 800); 
}
void Black_Control_Left(void)//左转进入
{
			if (L2 ) PWM_SET(800, 1900);
		else if(L1) PWM_SET(800, 1250);
			else if (R2) PWM_SET(1600, 800); 
			else if(R1)PWM_SET(1200, 800); 
			else if (M0) PWM_SET(800, 800); 
}


void judge_way(void)
{
	static int cnt;
	if((L2 || L1 || R2 || R1 || M0) && currentState == WHITE && jiance_time == 0)
	{
		cnt++;
		if (jiance_mode == 1 && cnt > 0) 
		{
			stateChangeCount++;
			currentState = BLACK;
			beep_cnt = 20;
			cnt = 0;
			
		}
		if (jiance_mode == 2 && cnt > 1 && (xie_length2 - xie_length1 > 1150) && stateChangeCount == 1) 
		{
			stateChangeCount++;
			currentState = BLACK;
			beep_cnt = 20;
			cnt = 0;
			jiance_time = 50;
		}
		else if(jiance_mode == 2 && stateChangeCount != 1)
		{
			stateChangeCount++;
			currentState = BLACK;
			beep_cnt = 20;
			cnt = 0;
			jiance_time = 50;
		}
		if (jiance_mode >= 3 && cnt > 4) 
		{
			stateChangeCount++;
			currentState = BLACK;
			beep_cnt = 20;
			cnt = 0;
			jiance_time = 50;
		}

	}
	else if(!(L2 || L1 || R2 || R1 || M0) && currentState == BLACK && jiance_time == 0)
	{
		cnt++;
		if(jiance_mode ==3 && stateChangeCount == 1 && xie_length2- xie_length1 >= 1150)
		{
			stateChangeCount++;
			currentState = WHITE;
			beep_cnt = 20;
			cnt = 0;
			jiance_time = 50;
		}
		else if(jiance_mode ==3 && stateChangeCount == 3 && xie_length2 - xie_length1 > 1150)
		{
			stateChangeCount++;
			currentState = WHITE;
			beep_cnt = 20;
			cnt = 0;
			jiance_time = 50;
		}
		else if(jiance_mode ==2 && (xie_length2 - xie_length1 > 1150) && stateChangeCount == 1)
		{
			stateChangeCount++;
			currentState = WHITE;
			beep_cnt = 20;
			cnt = 0;
			jiance_time = 50;
		}
		else if(jiance_mode ==2 && stateChangeCount != 1)
		{
			stateChangeCount++;
			currentState = WHITE;
			beep_cnt = 20;
			cnt = 0;
			jiance_time = 50;
		}
	}
	else cnt = 0;
	function();
}

unsigned char angle_turn(float target_angle)
{
    float angle_diff = YAW_out - Last_YAW_out - target_angle;

    // 处理角度跨越360度的情况
    if (angle_diff > 180) {
        angle_diff -= 360;
    } else if (angle_diff < -180) {
        angle_diff += 360;
    }

    // 判断角度差
    if (angle_diff > 1) {
        PWM_SET(400, 0); // 向右转
    } else if (angle_diff < -1) {
        PWM_SET(0, 400); // 向左转
    } else {
        PWM_SET(0, 0); // 停止
        return 1; // 表示角度已经调整到位
    }
    return 0; // 表示角度仍在调整中
}
//直行
void zhixing(float target_angle)
{
	if (Last_YAW_out > 300) PWM_SET(1500-Angle_PID(YAW_out,Last_YAW_out-360+target_angle), 1500+Angle_PID(YAW_out,Last_YAW_out-360+target_angle));
	else if (Last_YAW_out < 20) PWM_SET(1500-Angle_PID(YAW_out,target_angle-Last_YAW_out), 1500+Angle_PID(YAW_out,target_angle-Last_YAW_out));
}
void avoid_thing(void)
{
	distance = HC_Length();
	if(distance > 20 && distance < 40)
	{
		PWM_SET(0,1000);
		delay_ms(500);
		PWM_SET(1000,1000);
		delay_ms(500);
		PWM_SET(1000,0);
		delay_ms(500);
	}
}
void function(void)
{
	Length = length*3/10;//mm
	if(mode_flag == 1 && enter_flag == 1)
	{
		jiance_mode = 1;
		// 将小车放在位置A点，小车能自动行驶到B点停车
		if (currentState == BLACK) {
			PWM_SET(0,0);
			enter_flag = 0;
		}
		else PWM_SET(800-Angle_PID(YAW_out,Last_YAW_out), 800+Angle_PID(YAW_out,Last_YAW_out));
//		else 	PWM_SET(1000-Speed_PID(speed_l, speed_r),1000+Speed_PID(speed_l, speed_r));
	}
	else if(mode_flag == 2 && enter_flag == 2)
	{
		jiance_mode = 2;
		//A->B->C->D->A
		if(stateChangeCount == 0)
		{
			zhixing(0);
		}
		else if(stateChangeCount == 1 && Length >= 950)
		{
			switch (zhixian_flag)
			{
				case 0:
					xie_length1 = Length;
					zhixian_flag = 1;
				break;
				case 1:
					xie_length2 = Length;
					Black_Control();
				break;
				default:
					break;
			}
			
		}
		else if(stateChangeCount == 2 && Length >= 1800)
		{
//			switch
//			if(Last_YAW_out+180>360) Last_YAW_out -=180;
			switch (zhixian_flag)
			{
				case 1:
						if(angle_turn(183)) 		zhixian_flag = 2;		
				break;
				case 2:
					zhixing(183);
				break;
				default:
					break;
			}
		}
		else if(stateChangeCount == 3 && Length >= 2500)
		{
			Black_Control();
			zhixian_flag = 0;
		}
		else if(stateChangeCount >= 4 && Length >= 3500)
		{
			PWM_SET(0, 0);
			enter_flag = 0;
		}
	}
	else if(mode_flag == 3 && enter_flag == 3)
	{
		jiance_mode = 3;
		if(stateChangeCount == 0)
		{
			switch (xiexian_flag) {
				case 0://偏30
						if(angle_turn(323)) 		xiexian_flag = 1,		xie_length1 = Length;
					break;
				case 1://直行1200
						xie_length2 = Length;
						zhixing(323);
						if(xie_length2 - xie_length1 >= 1200)xiexian_flag = 2;
						break;
				case 2://回正30
						if(angle_turn(0)) PWM_SET(500,500);
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}
		}
		else if(stateChangeCount == 1)
		{
			switch (xiexian_flag) {
				case 1:
						xie_length1 = Length;
						xiexian_flag = 3;
						break;
				case 2: 
						xie_length1 = Length;
						xiexian_flag = 3;
						break;
				case 3:
						xie_length2 = Length;
						Black_Control_Left();
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}	
		}
		else if(stateChangeCount == 2)
		{
			switch (xiexian_flag) {
				case 3:
//						Last_YAW_out += 180;
//						if(Last_YAW_out > 360) Last_YAW_out -= 360;
						xiexian_flag = 4;
				break;
				case 4://160  ----  40    再加30	
						if(angle_turn(220)) 		xiexian_flag = 5,		xie_length1 = Length;
				break;
				case 5:
						xie_length2 = Length;
						zhixing(220);
						if(xie_length2 - xie_length1 >= 1200)xiexian_flag = 6;	
				break;				
				case 6:
						if(angle_turn(180)) 		PWM_SET(300,300);
						break;
				default:
						break;
			}
		}
		else if(stateChangeCount == 3)
		{
			switch (xiexian_flag) {
				case 6:
						Black_Control();
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}	
		}
		else if(stateChangeCount == 4)
		{
			PWM_SET(0,0);
		}
	}
	else if(mode_flag == 4 && enter_flag == 4)
	{
		jiance_mode = 3;
		if(stateChangeCount == 0)
		{
			switch (xiexian_flag) {
				case 0://偏30
						if(angle_turn(323)) 		xiexian_flag = 1,		xie_length1 = Length;

					break;
				case 1://直行1200
						xie_length2 = Length;
						zhixing(323);
						if(xie_length2 - xie_length1 >= 1200)xiexian_flag = 2;
						break;
				case 2://回正30
						if(angle_turn(0)) PWM_SET(500,500);
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}
		}
		else if(stateChangeCount == 1)
		{
			switch (xiexian_flag) {
				case 1:
						xie_length1 = Length;
						xiexian_flag = 3;
						break;
				case 2: 
						xie_length1 = Length;
						xiexian_flag = 3;
						break;
				case 3:
						xie_length2 = Length;
						Black_Control_Left();
						avoid_thing();
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}	
		}
		else if(stateChangeCount == 2)
		{
			switch (xiexian_flag) {
				case 3:
//						Last_YAW_out += 180;
//						if(Last_YAW_out > 360) Last_YAW_out -= 360;
						xiexian_flag = 4;
				break;
				case 4://160  ----  40    再加30	
						if(angle_turn(220)) 		xiexian_flag = 5,		xie_length1 = Length;
				break;
				case 5:
						xie_length2 = Length;
						zhixing(220);
						if(xie_length2 - xie_length1 >= 1200)xiexian_flag = 6;	
				break;				
				case 6:
						if(angle_turn(180)) 		PWM_SET(300,300);
						break;
				default:
						break;
			}
		}
		else if(stateChangeCount == 3)
		{
			switch (xiexian_flag) {
				case 6:
						Black_Control();
						avoid_thing();
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}	
		}
		else if(stateChangeCount == 4)
		{
			PWM_SET(0,0);
		}
	}
	else if(mode_flag == 6 && enter_flag == 6)
	{
		if(circle_count < 6)
		{
			if(circle_count == 1 || circle_count == 3 || circle_count == 5)
			{
				jiance_mode = 3;
				if(stateChangeCount == 0)
				{
					switch (xiexian_flag) {
						case 0://偏30
								if(angle_turn(325)) 		xiexian_flag = 1,		xie_length1 = Length;
							break;
						case 1://直行1200
								xie_length2 = Length;
								zhixing(325);
								if(xie_length2 - xie_length1 >= 1175)xiexian_flag = 2;
								break;
						case 2://回正30
								if(angle_turn(0)) PWM_SET(500,500);
								break;
						default:
								// 可选：添加默认处理逻辑
								break;
					}
				}
				else if(stateChangeCount == 1)
				{
					switch (xiexian_flag) {
						case 1:
								xie_length1 = Length;
								xiexian_flag = 3;
								break;
						case 2: 
								xie_length1 = Length;
								xiexian_flag = 3;
								break;
						case 3:
								xie_length2 = Length;
								Black_Control_Left();
								break;
						default:
								// 可选：添加默认处理逻辑
								break;
					}	
				}
				else if(stateChangeCount == 2)
				{
					switch (xiexian_flag) {
						case 3:
		//						Last_YAW_out += 180;
		//						if(Last_YAW_out > 360) Last_YAW_out -= 360;
								xiexian_flag = 4;
						break;
						case 4://160  ----  40    再加30	
								if(angle_turn(215)) 		xiexian_flag = 5,		xie_length1 = Length;
						break;
						case 5:
								xie_length2 = Length;
								zhixing(215);
								if(xie_length2 - xie_length1 >= 1175)xiexian_flag = 6;	
						break;				
						case 6:
								if(angle_turn(180)) 		PWM_SET(300,300);
								break;
						default:
								break;
					}
				}
				else if(stateChangeCount == 3)
				{
					switch (xiexian_flag) {
						case 6:
								Black_Control();
								break;
						default:
								// 可选：添加默认处理逻辑
								break;
					}	
				}
				if(stateChangeCount >= 4)
				{
					switch (xiexian_flag) {
						case 6://回正120
								if(angle_turn(0)) xiexian_flag = 7;
								break;
						case 7:
								circle_count++;
								xiexian_flag = 0;
//								Last_YAW_out += 120;
								length = 0;
								stateChangeCount = 0;
								xie_length2 = 0;
								xie_length1 = 0;
						default:
								// 可选：添加默认处理逻辑
								break;
					}
				}
			}
			else if(circle_count == 0 || circle_count == 2 || circle_count == 4)
			{
				jiance_mode = 2;
				//A->B->C->D->A
				if(stateChangeCount == 0)
				{
					zhixing(0+angle_diff[circle_count]);
				}
				else if(stateChangeCount == 1 && Length >= 950)
				{
					switch (zhixian_flag)
					{
						case 0:
							xie_length1 = Length;
							zhixian_flag = 1;
						break;
						case 1:
							xie_length2 = Length;
							Black_Control();
						break;
						default:
							break;
					}
					
				}
				else if(stateChangeCount == 2 && Length >= 1800)
				{
		//			switch
		//			if(Last_YAW_out+180>360) Last_YAW_out -=180;
					switch (zhixian_flag)
					{
						case 1:
								if(angle_turn(183)) 		zhixian_flag = 2;;		
						break;
						case 2:
							zhixing(183);xie_length1 = Length;
						break;
						default:
							break;
					}
				}
				else if(stateChangeCount == 3 && Length >= 2500)
				{
					Black_Control();
					xie_length2 = Length;
					zhixian_flag = 1;
				}
				else if(stateChangeCount >= 4 && Length >= 3500)
				{
					switch (zhixian_flag) {
						case 1://回正120
								if(angle_turn(0)) zhixian_flag = 2;
								break;
						case 2:
								circle_count++;
								zhixian_flag = 0;
								stateChangeCount = 0;
								xie_length2 = 0;
								xie_length1 = 0;
						break;
						default:
								// 可选：添加默认处理逻辑
								break;
					}
				}
			}
		
		if(circle_count > 5) {PWM_SET(0, 0);enter_flag = 0;}
		}
	}
	else if(mode_flag == 5 && enter_flag == 5)  //4圈循迹
	{
		jiance_mode = 3;
		if(circle_count < 4)
		{
		jiance_mode = 3;
		if(stateChangeCount == 0)
		{
			switch (xiexian_flag) {
				case 0://偏30
						if(angle_turn(325)) 		xiexian_flag = 1,		xie_length1 = Length;
					break;
				case 1://直行1200
						xie_length2 = Length;
						zhixing(325);
						if(xie_length2 - xie_length1 >= 1175)xiexian_flag = 2;
						break;
				case 2://回正30
						if(angle_turn(0)) PWM_SET(500,500);
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}
		}
		else if(stateChangeCount == 1)
		{
			switch (xiexian_flag) {
				case 1:
						xie_length1 = Length;
						xiexian_flag = 3;
						break;
				case 2: 
						xie_length1 = Length;
						xiexian_flag = 3;
						break;
				case 3:
						xie_length2 = Length;
						Black_Control_Left();
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}	
		}
		else if(stateChangeCount == 2)
		{
			switch (xiexian_flag) {
				case 3:
//						Last_YAW_out += 180;
//						if(Last_YAW_out > 360) Last_YAW_out -= 360;
						xiexian_flag = 4;
				break;
				case 4://160  ----  40    再加30	
						if(angle_turn(215)) 		xiexian_flag = 5,		xie_length1 = Length;
				break;
				case 5:
						xie_length2 = Length;
						zhixing(215);
						if(xie_length2 - xie_length1 >= 1175)xiexian_flag = 6;	
				break;				
				case 6:
						if(angle_turn(180)) 		PWM_SET(300,300);
						break;
				default:
						break;
			}
		}
		else if(stateChangeCount == 3)
		{
			switch (xiexian_flag) {
				case 6:
						Black_Control();
						break;
				default:
						// 可选：添加默认处理逻辑
						break;
			}	
		}
		if(stateChangeCount >= 4)
		{
			switch (xiexian_flag) {
				case 6://回正120
						if(angle_turn(0)) xiexian_flag = 7;
						break;
				case 7:
						circle_count++;
						xiexian_flag = 0;
						stateChangeCount = 0;
						xie_length2 = 0;
						xie_length1 = 0;
				default:
						// 可选：添加默认处理逻辑
						break;
			}
		}
		if(circle_count > 4) {PWM_SET(0, 0);enter_flag = 0;}
	}
	}
}
















//第一圈跑的非常好
//else if(mode_flag == 5 && enter_flag == 5)
//	{
//		//A->C->B->D->A
//		if(stateChangeCount == 0)
//		{
//			switch (xiexian_flag) {
//				case 0:
//						xie_length1 = Length;
//						xiexian_flag = 1;
//					break;
//				case 1:
//						PWM_SET(2700 + Angle_PID(YAW_out, Last_YAW_out - 60), 2700 - Angle_PID(YAW_out, Last_YAW_out - 60));
//						xie_length2 = Length;
//						if(xie_length2 - xie_length1 > 1300 + circle_count*100){PWM_SET(300 + Angle_PID(YAW_out, Last_YAW_out - 40), 300 - Angle_PID(YAW_out, Last_YAW_out - 40));}
//						if(xie_length2 - xie_length1 > 1350 + circle_count*100) {xiexian_flag = 2; stateChangeTimer =  0;}
////						if(stateChangeTimer >= 180) {xiexian_flag = 2; stateChangeTimer =  0;}
//						break;
//				case 2:
//						PWM_SET(300 + Angle_PID(YAW_out, Last_YAW_out), 300 - Angle_PID(YAW_out, Last_YAW_out));
////						while(YAW_out >= Last_YAW_out + 1 || YAW_out <= Last_YAW_out - 1);
//						break;
//				default:
//						// 可选：添加默认处理逻辑
//						break;
//			}
//		}
//		else if(stateChangeCount == 1)
//		{
//			Black_Control();
//			if (xiexian_flag == 2) xiexian_flag = 3;
//			stateChangeTimer =  0;
//			xie_length1 = Length;
//		}
//		else if(stateChangeCount == 2)
//		{
//			switch (xiexian_flag) {
//				case 3:
//						xie_length1 = Length;
//						xiexian_flag = 4;
//				break;
//				case 4:
//					
//						PWM_SET(2700 + Angle_PID(YAW_out, Last_YAW_out + 45), 2700 - Angle_PID(YAW_out, Last_YAW_out + 45));
//						xie_length2 = Length;
//						if(xie_length2 - xie_length1 > 1250){PWM_SET(300 + Angle_PID(YAW_out, Last_YAW_out + 42), 300 - Angle_PID(YAW_out, Last_YAW_out + 42));}
//						if(xie_length2 - xie_length1 > 1300) {xiexian_flag = 5; stateChangeTimer =  0;}
////						if(stateChangeTimer >= 150) {xiexian_flag = 4; stateChangeTimer =  0;}
//						break;
//				case 5:
//						PWM_SET(300 + Angle_PID(YAW_out, Last_YAW_out), 300 - Angle_PID(YAW_out, Last_YAW_out));
//						break;
//				default:
//						// 可选：添加默认处理逻辑
//						
//						break;
//			}
//		}
//		else if(stateChangeCount == 3)
//		{
//			Black_Control();
//		}
//		else if(stateChangeCount >= 4)
//		{
//			circle_count++;
//			xiexian_flag = 0;
//			stateChangeCount = 0;
//			xie_length2 = 0;
//			xie_length1 = 0;
//			if(circle_count >= 3) {PWM_SET(0, 0);enter_flag = 0;}
//			
//		}
//	}
//}
