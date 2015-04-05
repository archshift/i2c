#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "draw.h"
#include "hid.h"
#include "i2c.h"

void ClearTop()
{
    ClearScreen(TOP_SCREEN, RGB(255, 255, 255));
    current_y = 0;
}

int main()
{
    ClearTop();

    // Example code
    while (true) {
        u32 pad_state = InputWait();
        if (pad_state & BUTTON_B) {
            Debug("%02X", i2cReadRegister(I2C_DEV_MCU, 0xB));
        }
        if (pad_state & BUTTON_X)
            Debug("%02X", i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2));
        if (pad_state & BUTTON_Y)
            while(i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 3));
        if (pad_state & BUTTON_START)
            while(i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0));

    }

    return 0;
}
