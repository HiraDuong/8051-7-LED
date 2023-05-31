/*
 */

#include <mcs51/8051.h>
#define LED7SEG_DATA P0
#define LED7SEG_ADDR0 P2_2
#define LED7SEG_ADDR1 P2_3
#define LED7SEG_ADDR2 P2_4

int count = 0;
void delay(int ms){
    int i,j;
    for(i =0;i<60;i++){
        for(j = 0;j<ms;j++);
    }
}
void init(){
    P3_0 = 1;
    EX0 = 1;
    IT0 = 1;

    P3_3 = 1;
    EX1 = 1;
    IT1 = 1;
    EA = 1;
}

unsigned char const mask[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D
,0x07,0x7F,0x6F};

void output_7seg_off()
{
    P0 = 0x00;
}
void output_7seg(unsigned char value)
{
    if (value < 10){
        P0 = mask [value];
    }
}

void display_number(unsigned char iNum){
    unsigned char i;
    unsigned char temp;
    for (i = 0;i<3;i++){
        temp = iNum%10;
        iNum = iNum /10;

        LED7SEG_ADDR0 = i&0x01;
        LED7SEG_ADDR1 = i&0x02;
        LED7SEG_ADDR2 = i&0x04;

        output_7seg(temp);

        delay(1);
        output_7seg_off();
    }
}

void EXT0_Process() __interrupt IE0_VECTOR
{
    EA = 0;
    count++;
    EA = 1;
}

void EXT1_Process() __interrupt IE1_VECTOR
{
    EA = 0;
    count--;
    EA = 1;
}


void main(void)
{

    init();

    while(1){
          display_number(count);
          }
        ;

}
