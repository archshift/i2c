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
        if (pad_state & BUTTON_A)
            Debug("%02X", i2cReadRegister(I2C_DEV_MCU, 0x9));
        if (pad_state & BUTTON_B) {
            Debug("%02X", i2cReadRegister(I2C_DEV_MCU, 0xB));

            u8 battery = 0;
            i2cReadRegisterBuffer(I2C_DEV_MCU, 0xB, &battery, 1);
            Debug("%02X", battery);

            u16 battery16 = 0;
            i2cReadRegisterBuffer(I2C_DEV_MCU, 0xB, &battery16, 2);
            Debug("%04X", battery);

            u32 battery32 = 0;
            i2cReadRegisterBuffer(I2C_DEV_MCU, 0xB, &battery32, 4);
            Debug("%08X", battery);
        }
        if (pad_state & BUTTON_X)
            Debug("%02X", i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2));
    }

    return 0;
}
