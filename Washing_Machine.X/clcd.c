#include <xc.h>
#include "clcd.h"

// Send higher nibble to RD4?RD7
static void send_nibble(unsigned char nibble)
{
    CLCD_DATA_PORT &= 0x0F;               // Clear upper 4 bits
    CLCD_DATA_PORT |= (nibble & 0xF0);    // Load upper 4 bits
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;
    __delay_us(100);
}

void clcd_write(unsigned char byte, unsigned char mode)
{
    CLCD_RS = (mode !=0);

    send_nibble(byte & 0xF0);             // Send higher nibble
    send_nibble((byte << 4) & 0xF0);      // Send lower nibble

    __delay_us(100);
}

static void init_display_controller(void)
{
    __delay_ms(20);           // Power-on delay

    // Initialization sequence for 4-bit mode
    send_nibble(0x30);        // Function set
    __delay_ms(5);
    send_nibble(0x30);
    __delay_us(100);
    send_nibble(0x30);
    __delay_us(100);
    send_nibble(0x20);        // Set to 4-bit mode
    __delay_us(100);

    clcd_write(TWO_LINES_5x8_4_BIT_MODE, INST_MODE);
    clcd_write(DISP_ON_AND_CURSOR_OFF, INST_MODE);
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    clcd_write(ENTRY_MODE_INC_SHIFT_OFF, INST_MODE);
}

void init_clcd(void)
{
    // Set RD4?RD7 as output
    CLCD_DATA_PORT_DDR &= 0x0F; // Only RD4?RD7 are used

    // Set RS and EN as output
    CLCD_RS_DDR = 0;
    CLCD_EN_DDR = 0;

    init_display_controller();
}

void clcd_putch(const char data, unsigned char addr)
{
    clcd_write(addr, INST_MODE);
    clcd_write(data, DATA_MODE);
}

void clcd_print(const char *str, unsigned char addr)
{
    clcd_write(addr, INST_MODE);
    
    while (*str != '\0')
    {
        clcd_write(*str, DATA_MODE); 
        str++;
    }
}
