#include "calculate.h"

void Sort_Up(u32 *t, u32 num){
	u32 i, j, m;
	for(i = 0; i < num-1; i++){
		for(j = 0; j < num-i-1; j++){
			if((*(t+i))>(*(t+i+1))){
				m = *(t+i);
				*(t+i) = *(t+i+1);
				*(t+i+1) = m;
			}
		}
		
	}
}

void Sort_Down(u32 *t, u32 num){
	u32 i, j, m;
	for(i = 0; i < num-1; i++){
		for(j = 0; j < num-i-1; j++){
			if((*(t+i))<(*(t+i+1))){
				m = *(t+i);
				*(t+i) = *(t+i+1);
				*(t+i+1) = m;
			}
		}
		
	}
}

