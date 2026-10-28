#include "types.h"
extern u8 *IconRec_3ae3e0(void *);

s32 IconRecId_2a2230(void *c)
{
    return *(s16 *)(IconRec_3ae3e0(c) + 0x2C);
}
