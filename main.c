#include <stdint.h>
#include <stdbool.h>

#define GPIO_BASE	(0x20000000)
#define PHY_PERI_ADDR(x) (0x20000000 + (x))

#define GPFSEL1		((volatile uint32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x04))

/*static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index){
	
	*((uint32_t*)(0x20200000 + register_num * 0x4)) &= ~(uint32_t)(0x7 << (index * 3)); 
 000000...111000 -> ~ -> 111111...000111 　：　ビットシフトと反転により特定のビットを0にセットするためのマスクを用意
 111111...000111 && XXXXXX...XXXXXX -> XXXXXX...000XXX　：　マスクともとのビット列とandをとることにより、特定のビット列のみを000とできる
 続けて, XXXXXX...000XXXの 000 を操作するために, マスクを用意した時と同様ビットシフトを利用して適切なビット列(000000...YYY000)を作成
 作成したビット列とのORを取ることにより, XXXXXX...000XXXのXXXの部分はもとのまま, 000の部分はYYYとして, XXXXXX...YYYXXXというビット列を作れる

	*((uint32_t*)(0x20200000 + register_num * 0x4)) |= (uint32_t)(mode << (index * 3));

}*/



int main(void)
{
	// GPIO初期化
	/*	
	setGPIO(1, 0x4, 4);		//	GPIO 14
	setGPIO(1, 0x4, 5);		//	GPIO 15 を UARTピン化
	*/

	*GPFSEL1 &= ~((uint32_t)0x07 << ((14 % 10) * 3));
	*GPFSEL1 &= ~((uint32_t)0x07 << ((15 % 10) * 3));
	*GPFSEL1 |= ((uint32_t)0x04 << ((14 % 10) * 3));
	*GPFSEL1 |= ((uint32_t)0x04 << ((15 % 10) * 3));

	// GPIO初期化ここまで
	

	// UARTレジスタ初期化
	// 設定不要 -> 初期値のままでよいもの
	// Control Register : TXE -> 1 , RXE -> 1
	// Stop bit 	    :  1bit -> LCRH RegisterのSTP2 -> 0
	// Parity           : None 
	// FIFO             : None

	// Disable UARTEN  
	// BitMASK

	
	// String : "Hello World"
	
	int  i=0;
	/*char str[11] = "HelloWorld";
	
	while(str[i]!='\0'){
		*((uint32_t*)(0x20201000)) = (uint32_t)(str[i]);
		for(int j=0; j<500000; j++){}
		i++;
	}*/

	while(1){
		*((uint32_t*)(0x20201000)) = (uint32_t)('a');
		for(int j=0; j<100000; j++){}
	}
	return 0;
}
