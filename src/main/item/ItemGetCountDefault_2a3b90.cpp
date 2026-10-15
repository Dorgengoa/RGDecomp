#include "types.h"
extern "C" s32 ItemPosInvalid_3d49a0(void);
extern "C" u8 ItemGetCountDefault_2a3b90(void)
{
    bool b = ItemPosInvalid_3d49a0();
    return b ^ 1;
}
