/* rgp:protos */
#define RGP_SELF_CharaResRecInit_1f4ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct BF1f4ad0 {
    u8 b0 : 1;
    u8 b1 : 1;
} BF1f4ad0;

/*rgp*/

void CharaResRecInit_1f4ad0(void *self)
{
    u8 *p = (u8 *)self;

    *(s16 *)(p + 0x0) = -1;
    *(s16 *)(p + 0x2) = -1;
    *(s16 *)(p + 0x4) = -1;
    *(s32 *)(p + 0x8) = 0;
    *(u8 *)(p + 0x6) = 0;
    *(u8 *)(p + 0x7) = 0xFF;
    *(s16 *)(p + 0x64) = 0;
    MemStackClear_14dff0(p + 0xC);
    ((BF1f4ad0 *)(p + 0x66))->b0 = 0;
    ((BF1f4ad0 *)(p + 0x66))->b1 = 0;
}
