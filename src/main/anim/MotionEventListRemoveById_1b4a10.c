#include "types.h"

void MotionEventListRemoveById_1b4a10(void *param_1, s32 param_2)
{
    u8 *node = *(u8 **)param_1;
    u8 *w;
    u8 *next;
    u8 *other;

    while (node != 0)
    {
        next = *(u8 **)(node + 0x0);
        if (param_2 == *(s32 *)(node + 0x14))
        {
            other = *(u8 **)(node + 0x4);
            if (other != 0)
            {
                *(u8 **)(other + 0x0) = next;
                if (next != 0)
                {
                    *(u8 **)(next + 0x4) = other;
                }
                w = *(u8 **)(node + 0x4);
                while (*(u8 **)(w + 0x4) != 0)
                {
                    w = *(u8 **)(w + 0x4);
                }
                *(s32 *)(node + 0x4) = 0;
            }
            else
            {
                if (next != 0)
                {
                    *(s32 *)(next + 0x4) = 0;
                }
                w = *(u8 **)(node + 0x0);
                *(s32 *)(node + 0x4) = 0;
            }
            *(s32 *)(node + 0x0) = 0;
            *(u8 **)param_1 = w;
        }
        node = next;
    }
}
