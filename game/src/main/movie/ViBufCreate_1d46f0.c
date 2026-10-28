/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_ViBufCreate_1d46f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 m00, m04, m08, m0C, m10, m14, m18, m1C; } Sema_001d46f0;

extern s32 CreateSema(Sema_001d46f0 *p);
/*rgp*/

s32 ViBufCreate_1d46f0(void *param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, s32 param_6)
{
    u8 *obj = (u8 *)param_1;
    Sema_001d46f0 sema __attribute__((aligned(16)));

    *(s32 *)(obj + 0x0) = param_2;
    *(s32 *)(obj + 0x4) = (param_3);
    *(s32 *)(obj + 0x8) = param_4;
    *(s32 *)(obj + 0x18) = param_4 << 11;
    *(s32 *)(obj + 0x50) = param_5;
    *(s32 *)(obj + 0x54) = param_6;

    sema.m08 = 1;
    sema.m04 = 1;
    *(s32 *)(obj + 0x40) = CreateSema(&sema);

    ViBufReset_1d45b0(obj);
    *(s64 *)(obj + 0x48) = 0;

    return 1;
}
