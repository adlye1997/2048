#include "2048.h"
#include "delay.h"
#include "uart.h"

Box box[16];
Game game;

void g2048_Init(void){
	u8 i;
	for(i = 0; i < 16; i++){
		box[i].sx = 118*(i % 4) + 8;
		box[i].ex = 118*(i % 4) + 118;
		box[i].sy = 118*(i / 4) + 168;
		box[i].ey = 118*(i / 4) + 278;
		box[i].num = 0;
	}
	LCD_Color_Fill(0, 480, 160, 640, 0x8451);
	for(i = 0; i < 16; i++){
		LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xce78);
	}
	g2048_Refresh();
	g2048_Creat_And_Lcd_Refresh();
	g2048_Refresh();
	g2048_Creat_And_Lcd_Refresh();
	game.point = 0;
	LCD_ShowString(100,100,60,24,24,"DONE ",BLACK,YELLOW);
	LCD_ShowString(116, 766, 364, 24, 24, "2048_Init DONE",BLACK,YELLOW);
}

void g2048_Refresh(void){
	u8 i, j;
	game.up = 0;
	for(i = 4; i < 16; i++){
		if(box[i].num == 0)
			continue;
		if( (box[i-4].num == 0) || (box[i-4].num == box[i].num) ){
			game.up = 1;
			break;
		}
	}
	game.down = 0;
	for(i = 12; i >= 1; i--){
		if(box[i-1].num == 0)
			continue;
		if( (box[i+3].num == 0) || (box[i+3].num == box[i-1].num) ){
			game.down = 1;
			break;
		}
	}
	game.left = 0;
	for(i = 1; i < 4; i++){//列
		for(j = 0; j < 4; j++){//行
			if(box[i+j*4].num == 0)
				continue;
			if( (box[i+j*4-1].num == 0) || (box[i+j*4-1].num == box[i+j*4].num) ){
				game.left = 1;
				break;
			}
		}
	}
	game.right = 0;
	for(i = 3; i >= 1; i--){
		for(j = 0; j < 4; j++){
			if(box[(i-1)+j*4].num == 0)
				continue;
			if( (box[i-1+j*4+1].num == 0) || (box[i-1+j*4+1].num == box[i-1+j*4].num) ){
				game.right = 1;
				break;
			}
		}
	}
	game.empty=0;
	for(i=0;i<16;i++){
		if(box[i].num==0){
			game.empty++;
		}
	}
}

void g2048_Lcd_Refresh(void){
	u8 i;
	for(i = 0; i < 16; i++){
		switch(box[i].num){
			case 0:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xce78);
				break;
			case 2:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xf79c);
				g2048_ShowChar(box[i].sx+43, box[i].sy+31, 2, 1, BLACK, 0xf79c);
				break;
			case 4:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xeef9);
				g2048_ShowChar(box[i].sx+43, box[i].sy+31, 4, 1, BLACK, 0xeef9);
				break;
			case 8:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xddd0);
				g2048_ShowChar(box[i].sx+43, box[i].sy+31, 8, 1, BLACK, 0xddd0);
				break;
			case 16:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xf52c);
				g2048_ShowChar(box[i].sx+31, box[i].sy+31, 16, 2, BLACK, 0xf52c);
				break;
			case 32:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xfbea);
				g2048_ShowChar(box[i].sx+31, box[i].sy+31, 32, 2, BLACK, 0xfbea);
				break;
			case 64:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xf800);
				g2048_ShowChar(box[i].sx+31, box[i].sy+31, 64, 2, BLACK, 0xf800);
				break;
			case 128:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xeef0);
				g2048_ShowChar(box[i].sx+19, box[i].sy+31, 128, 3, BLACK, 0xeef0);
				break;
			case 256:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xfea0);
				g2048_ShowChar(box[i].sx+19, box[i].sy+31, 256, 3, BLACK, 0xfea0);
				break;
			case 512:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xfe04);
				g2048_ShowChar(box[i].sx+19, box[i].sy+31, 512, 3, BLACK, 0xfe04);
				break;
			case 1024:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xfdc4);
				g2048_ShowChar(box[i].sx+7, box[i].sy+31, 1024, 4, BLACK, 0xfdc4);
				break;
			case 2048:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0xed61);
				g2048_ShowChar(box[i].sx+7, box[i].sy+31, 2048, 4, BLACK, 0xed61);
				break;
			case 4096:
				LCD_Color_Fill(box[i].sx, box[i].ex, box[i].sy, box[i].ey, 0x0000);
				g2048_ShowChar(box[i].sx+7, box[i].sy+31, 4096, 4, BLACK, 0x0000);
				break;
			default:
				break;
		}
	}
}

void g2048_Direction_Judge_And_Game(void){
	u16 i;
	if(game.right == 1){
		if(game.down == 1){
			game.down = 0;
			for(i = 3; i > 0; i--){
				if(box[i*4-1].num != 0){
					if(box[i*4+3].num == 0){
						game.down = 1;
						break;
					}
					else if(box[i*4+3].num == box[i*4-1].num){
						game.down = 1;
						break;
					}
				}
			}
			if(game.down == 1)
				g2048_Game(2);
			else g2048_Game(4);
		}
		else g2048_Game(4);
	}
	else if(game.down == 1){
		g2048_Game(2);
	}
	else if(game.up == 1){
		g2048_Game(1);
		g2048_Creat_And_Lcd_Refresh();
		delay_ms(1000);
		g2048_Refresh();
		if((game.up + game.down + game.left + game.right) == 0){
			g2048_Game(0);
		}
		else if(box[15].num == 0)
			g2048_Game(2);
		else g2048_Direction_Judge_And_Game();
	}
	else if(game.left == 1){
		g2048_Game(3);
	}
	else {
		g2048_Game(0);
	}
}

void g2048_Game(u8 Direction){
	u8 i, j, k;
	LCD_ShowString(116, 766, 364, 24, 24, "g2048_Game",BLACK,YELLOW);
	for(i=0;i<16;i++){
		box[i].flag = 0;
	}
	switch(Direction){
		case 0:
			LCD_ShowString(100,100,60,24,24,"die  ",BLACK,YELLOW);
			break;
		case 1:
			LCD_ShowString(100,100,60,24,24,"up   ",BLACK,YELLOW);
			for(i=0;i<3;i++){
				for(j=4;j<16;j++){
					if(box[j].num==0)
						continue;
					if(box[j-4].num==0){
						box[j-4].num = box[j].num;
						box[j-4].flag = box[j].flag;
						box[j].num = box[j].flag = 0;
					}
					else if(box[j-4].num==box[j].num){
						if(box[j-4].flag + box[j].flag == 0){
							game.point += box[j-4].num;
							box[j-4].num *= 2;
							box[j-4].flag = 1;
							box[j].num = box[j].flag = 0;
						}
						
					}
				}
			}
			break;
		case 2:
			LCD_ShowString(100,100,60,24,24,"down ",BLACK,YELLOW);
			for(i=0;i<3;i++){
				for(j=12;j>0;j--){
					if(box[j-1].num==0)
						continue;
					if(box[j+3].num==0){
						box[j+3].num = box[j-1].num;
						box[j+3].flag = box[j-1].flag;
						box[j-1].num = box[j-1].flag = 0;
					}
					else if(box[j+3].num==box[j-1].num){
						if(box[j+3].flag + box[j-1].flag == 0){
							game.point += box[j+3].num;
							box[j+3].num *= 2;
							box[j+3].flag = 1;
							box[j-1].num = box[j-1].flag = 0;
						}
					}
				}
			}
			break;
		case 3:
			LCD_ShowString(100,100,60,24,24,"left ",BLACK,YELLOW);
			for(i=0;i<3;i++){
				for(j=1;j<4;j++){//列
					for(k=0;k<4;k++){//行
						if(box[k*4+j].num==0)
							continue;
						if(box[k*4+j-1].num==0){
							box[k*4+j-1].num = box[k*4+j].num;
							box[k*4+j-1].flag = box[k*4+j].flag;
							box[k*4+j].num = box[k*4+j].flag = 0;
						}
						else if(box[k*4+j-1].num==box[k*4+j].num){
							if(box[k*4+j-1].flag + box[k*4+j].flag == 0){
								game.point += box[k*4+j-1].num;
								box[k*4+j-1].num *= 2;
								box[k*4+j-1].flag = 1;
								box[k*4+j].num = box[k*4+j].flag = 0;
							}
						}
					}
				}
			}
			break;
		case 4:
			LCD_ShowString(100,100,60,24,24,"right",BLACK,YELLOW);
			for(i=0;i<3;i++){
				for(j=3;j>0;j--){//列
					for(k=0;k<4;k++){//行
						if(box[k*4+j-1].num==0)
							continue;
						if(box[k*4+j].num==0){
							box[k*4+j].num = box[k*4+j-1].num;
							box[k*4+j].flag = box[k*4+j-1].flag;
							box[k*4+j-1].num = box[k*4+j-1].flag = 0;
						}
						else if(box[k*4+j].num==box[k*4+j-1].num){
							if(box[k*4+j-1].flag + box[k*4+j].flag == 0){
								game.point += box[k*4+j].num;
								box[k*4+j].num *= 2;
								box[k*4+j].flag = 1;
								box[k*4+j-1].num = box[k*4+j-1].flag = 0;
							}
						}
					}
				}
			}
			break;
		default:
			break;
	}
}

void g2048_Creat_And_Lcd_Refresh(void){
	u8 i, temp, num;
	if(game.empty != 0){
		num = RTC_GetCounter();
		temp = num % 10;
		if(temp==0)
			game.start_num = 4;
		else game.start_num = 2;
		game.start_box = num % game.empty;
		temp = 0;
		for(i=0;i<16;i++){
			if(box[i].num == 0){
				if(temp == game.start_box){
					box[i].num = game.start_num;
					break;
				}
				else temp++;
			}
		}
		g2048_Lcd_Refresh();
	}
}

void g2048_Unauto_Creat(u8 cbox,u16 num){
	box[cbox].num = num;
}

u16 g2048_Get_Direction(Point p){
	float point_sum, point_max, point_min, point;
	float point_direction[4];
	u16 i, j, k, flag, max_k, min_k, max_num, min_num;
	u8 direction, m[4];
	Point q, q1;
	LCD_ShowString(116, 766, 364, 24, 24, "g2048_Get_Direction Start",BLACK,YELLOW);
	m[0] = p.up;
	m[1] = p.down;
	m[2] = p.left;
	m[3] = p.right;
	for(i=0;i<4;i++){
		q = p;
		if(m[i]==1){
			point_direction[i] = 1;
			q1 = g2048_Point_Game(q, i+1);
			q1 = g2048_Point_Refresh(q1);
			for(j=0;j<16;j++){
				if(q1.num[j]==0){
					q1.num[j] = 2;
					point_min = g2048_Only_Get_Point(q1);
					point_max = point_min;
					min_k = max_k = j;
					min_num = max_num = 2;
					q1.num[j]=0;
					break;
				}
			}
			for(j=0;j<q1.empty;j++){
				flag = 0;
				for(k=0;k<16;k++){
					if(q1.num[k] == 0){
						if(flag == j){
							q1.num[k] = 2;
							point = g2048_Only_Get_Point(q1);
							if(point>point_max){
								point_max = point;
								max_k = k;
								max_num = 2;
							}
							else if(point<point_min){
								point_min = point;
								min_k = k;
								min_num = 2;
							}
							q1.num[k] = 4;
							point = g2048_Only_Get_Point(q1);
							if(point>point_max){
								point_max = point;
								max_k = k;
								max_num = 4;
							}
							else if(point<point_min){
								point_min = point;
								min_k = k;
								min_num = 4;
							}
							q1.num[k] = 0;
							break;
						}
						else flag++;
					}
				}
			}//j
			q1.num[max_k] = max_num;
			point_max = g2048_Get_Point(q1, 2);
			q1.num[max_k] = 0;
//			LCD_ShowString(0,700,480,24,24,"reach_1",BLACK,YELLOW);
//			LCD_ShowNum(0, 676,min_k,4,24,BLACK,YELLOW);
			q1.num[min_k] = min_num;
//			LCD_ShowString(0,700,480,24,24,"reach_2",BLACK,YELLOW);
			point_min = g2048_Get_Point(q1, 2);
			q1.num[min_k] = 0;
			point_direction[i] += point_max * Max_Point + point_min * Min_Point;
		}
		else point_direction[i] = 0;
	}
	point_sum = 0;
	direction = 0;
	for(i=0;i<4;i++){
		if(point_direction[i] > point_sum){
			point_sum = point_direction[i];
			direction = i+1;
		}
	}
	LCD_ShowString(116, 766, 364, 24, 24, "g2048_Get_Direction DONE",BLACK,YELLOW);
	return direction;
}

float g2048_Get_Point(Point p, u8 times){
	float point_sum, point, point_max, point_min;
	float point_direction[4];
	u16 i, j, k, flag, max_k, min_k, max_num, min_num;
	u8 m[4];
	Point q, q1;
	p = g2048_Point_Refresh(p);
	point_sum = 0;
	m[0] = p.up;
	m[1] = p.down;
	m[2] = p.left;
	m[3] = p.right;
	q = p;
	if(times < Max_Times){
		for(i=0;i<4;i++){
			if(m[i]==1){
				point_direction[i] = 1;
				q1 = g2048_Point_Game(q, i+1);
				q1 = g2048_Point_Refresh(q1);
				for(j=0;j<16;j++){
					if(q1.num[j]==0){
						q1.num[j] = 2;
						point_min = g2048_Only_Get_Point(q1);
						point_max = point_min;
						min_k = max_k = j;
						min_num = max_num = 2;
						q1.num[j]=0;
						break;
					}
				}
				for(j=0;j<q1.empty;j++){
					flag = 0;
					for(k=0;k<16;k++){
						if(q1.num[k] == 0){
							if(flag == j){
								q1.num[k] = 2;
								point = g2048_Only_Get_Point(q1);
								if(point>point_max){
									point_max = point;
									max_k = k;
									max_num = 2;
								}
								else if(point<point_min){
									point_min = point;
									min_k = k;
									min_num = 2;
								}
								q1.num[k] = 4;
								point = g2048_Only_Get_Point(q1);
								if(point>point_max){
									point_max = point;
									max_k = k;
									max_num = 4;
								}
								else if(point<point_min){
									point_min = point;
									min_k = k;
									min_num = 4;
								}
								q1.num[k] = 0;
								break;
							}
							else flag++;
						}
					}
				}
				q1.num[max_k] = max_num;
				point_max = g2048_Get_Point(q1, 3);
				q1.num[max_k] = 0;
//				LCD_ShowString(0,700,480,24,24,"reach_3",BLACK,YELLOW);
//				LCD_ShowNum(0, 676,min_k,4,24,BLACK,YELLOW);
				q1.num[min_k] = min_num;
//				LCD_ShowString(0,700,480,24,24,"reach_4",BLACK,YELLOW);
				point_min = g2048_Get_Point(q1, 3);
				q1.num[min_k] = 0;
				point_direction[i] += point_max * Max_Point + point_min * Min_Point;
			}
			else point_direction[i] = 0;
		}
		point_sum = 0;
		for(i=0;i<4;i++){
			if(point_direction[i] > point_sum){
				point_sum = point_direction[i];
			}
		}
		return point_sum;
	}
	else {
		for(i=0;i<4;i++){
			if(m[i]==1){
				point_direction[i] = 1;
				q1 = g2048_Point_Game(q, i+1);
				q1 = g2048_Point_Refresh(q1);
				point_max = g2048_Only_Get_Point(q1);
				for(j=0;j<16;j++){
					if(q1.num[j]==0){
						q1.num[j] = 2;
						point_min = g2048_Only_Get_Point(q1);
						q1.num[j]=0;
						break;
					}
				}
				for(j=0;j<q1.empty;j++){
					flag = 0;
					for(k=0;k<16;k++){
						if(q1.num[k] == 0){
							if(flag == j){
								q1.num[k] = 2;
								point = g2048_Only_Get_Point(q1);
								if(point>point_max){
									point_max = point;
								}
								else if(point<point_min){
									point_min = point;
								}
								q1.num[k] = 4;
								point = g2048_Only_Get_Point(q1);
								if(point>point_max){
									point_max = point;
								}
								else if(point<point_min){
									point_min = point;
								}
								q1.num[k] = 0;
								break;
							}
							else flag++;
						}
					}
				}
				point_direction[i] += (point_max * Max_Point + point_min * Min_Point);
			}
			else point_direction[i] = 0;
		}
		point_sum = 0;
		for(i=0;i<4;i++){
			if(point_direction[i] > point_sum){
				point_sum = point_direction[i];
			}
		}
		return point_sum;
	}
}

Point g2048_Point_Game(Point p, u8 Direction){
	u8 i, j, k;
	for(i=0;i<16;i++){
		p.flag[i] = 0;
	}
	switch(Direction){
		case 1:
			for(i=0;i<3;i++){
				for(j=4;j<16;j++){
					if(p.num[j]==0)
						continue;
					if(p.num[j-4] == 0){
						p.num[j-4] = p.num[j];
						p.flag[j-4] = p.flag[j];
						p.num[j] = p.flag[j] = 0;
					}
					else if(p.num[j-4] == p.num[j]){
						if(p.flag[j-4] + p.flag[j] == 0){
							p.point += p.num[j-4];
							p.num[j-4] *= 2;
							p.flag[j-4] = 1;
							p.num[j] = p.flag[j] = 0;
						}
					}
				}
			}
			break;
		case 2:
			for(i=0;i<3;i++){
				for(j=12;j>0;j--){
					if(p.num[j-1]==0)
						continue;
					if(p.num[j+3] == 0){
						p.num[j+3] = p.num[j-1];
						p.flag[j+3] = p.flag[j-1];
						p.num[j-1] = p.flag[j-1] = 0;
					}
					else if(p.num[j+3] == p.num[j-1]){
						if(p.flag[j+3] + p.flag[j-1] == 0){
							p.point += p.num[j+3];
							p.num[j+3] *= 2;
							p.flag[j+3] = 1;
							p.num[j-1] = p.flag[j-1] = 0;
						}
					}
				}
			}
			break;
		case 3:
			for(i=0;i<3;i++){
				for(j=1;j<4;j++){
					for(k=0;k<4;k++){
						if(p.num[k*4+j]==0)
							continue;
						if(p.num[k*4+j-1] == 0){
							p.num[k*4+j-1] = p.num[k*4+j];
							p.flag[k*4+j-1] = p.flag[k*4+j];
							p.num[k*4+j] = p.flag[k*4+j] = 0;
						}
						else if(p.num[k*4+j-1] == p.num[k*4+j]){
							if(p.flag[k*4+j-1] + p.flag[k*4+j] == 0){
								p.point += p.num[k*4+j-1];
								p.num[k*4+j-1] *= 2;
								p.flag[k*4+j-1] = 1;
								p.num[k*4+j] = p.flag[k*4+j] = 0;
							}
						}
					}
				}
			}
			break;
		case 4:
			for(i=0;i<3;i++){
				for(j=3;j>0;j--){
					for(k=0;k<4;k++){
						if(p.num[k*4+j-1]==0)
							continue;
						if(p.num[k*4+j] == 0){
							p.num[k*4+j] = p.num[k*4+j-1];
							p.flag[k*4+j] = p.flag[k*4+j-1];
							p.num[k*4+j-1] = p.flag[k*4+j-1] = 0;
						}
						else if(p.num[k*4+j] == p.num[k*4+j-1]){
							if(p.flag[k*4+j-1] + p.flag[k*4+j] == 0){
								p.point += p.num[k*4+j];
								p.num[k*4+j] *= 2;
								p.flag[k*4+j] = 1;
								p.num[k*4+j-1] = p.flag[k*4+j-1] = 0;
							}
						}
					}
				}
			}
			break;
		default:
			break;
	}
	return p;
}

Point g2048_Point_Refresh(Point p){
	u8 i, j;
	p.up = 0;
	for(i = 4; i < 16; i++){
		if(p.num[i] == 0)
			continue;
		if( (p.num[i-4] == 0) || (p.num[i-4] == p.num[i]) ){
			p.up = 1;
			break;
		}
	}
	p.down = 0;
	for(i = 12; i >= 1; i--){
		if(p.num[i-1] == 0)
			continue;
		if( (p.num[i+3] == 0) || (p.num[i+3] == p.num[i-1]) ){
			p.down = 1;
			break;
		}
	}
	p.left = 0;
	for(i = 1; i < 4; i++){//列
		for(j = 0; j < 4; j++){//行
			if(p.num[i+j*4] == 0)
				continue;
			if( (p.num[i+j*4-1] == 0) || (p.num[i+j*4-1] == p.num[i+j*4]) ){
				p.left = 1;
				break;
			}
		}
	}
	p.right = 0;
	for(i = 3; i >= 1; i--){
		for(j = 0; j < 4; j++){
			if(p.num[(i-1)+j*4] == 0)
				continue;
			if( (p.num[i-1+j*4+1] == 0) || (p.num[i-1+j*4+1] == p.num[i-1+j*4]) ){
				p.right = 1;
				break;
			}
		}
	}
	p.empty = 0;
	p.max = 0;
	for(i=0;i<16;i++){
		if(p.num[i] == 0){
			p.empty++;
		}
		if(p.num[i] > p.max)
			p.max = p.num[i];
	}
	return p;
}

float g2048_Get_Monotony_Point(Point p){
	float point;
	u16 i, num[16];
	for(i=0;i<16;i++){
		if(i/4%2==0){
			num[i] = p.num[i];
		}
		else if(i/4==1){
			num[i] = p.num[11-i];
		}
		else {
			num[i] = p.num[17-i];
		}
	}
	point = 0;
	if(num[0]==p.max)
		point+=p.max*2;
	for(i=1;i<16;i++){
		if(num[i]<num[i-1])
			point+=num[i]*2;
		else if(num[i]==num[i-1])
			point+=num[i];
		else break;
	}
	return point;
}

float g2048_Get_Empty_Point(Point p){
	u16 i;
	float point;
	for(i=0;i<16;i++){
		if(p.num == 0){
			point += 2.5*(i/4+1);
		}
	}
	return point;
}


float g2048_Only_Get_Point(Point p){
	float point_monotony, point_empty, point_sum;
	point_monotony = g2048_Get_Monotony_Point(p);
	point_empty = g2048_Get_Empty_Point(p);
	point_empty *= Empty_Point;
	point_monotony *= Monotony_Point;
	point_sum = point_empty+point_monotony+p.point;
	return point_sum;
}

















