#ifndef __USART_H__
#define __USART_H__
void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_Array(uint8_t *Array,uint16_t Lenth);
void Serial_String(uint8_t *String);

#define Move_Forward 0x20
#define Move_Backward 0x21
#define Stop 0x22
#define Turn_Left 0x23
#define Turn_Right 0x24

#endif
