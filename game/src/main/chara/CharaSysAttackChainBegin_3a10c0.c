/* rgp:protos */
#define RGP_SELF_CharaSysAttackChainBegin_3a10c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct { u8 b0:1; u8 b1:1; u8 b2:1; u8 b3:1; u8 b4:1; u8 b5:1; u8 b6:1; u8 b7:1; } Bits;

typedef struct {
    u8 pad0[0x2C];
    s16 unk2C;
    u8 pad2E[0x172 - 0x2E];
    Bits f172;
    u8 pad173[0x1CC - 0x173];
    u16 unk1CC;
} Sub;

typedef struct {
    u8 pad0[0x238];
    Sub *unk238;
    u8 pad23C[0x24C - 0x23C];
    Bits f24C;
} Obj;

s32 CharaSysAttackChainBegin_3a10c0(Obj *arg0)
{
    arg0->unk238->unk1CC++;
    CharaSysStatusClearAll_3a1460((void *)arg0);
    arg0->f24C.b4 = 1;
    if (arg0->unk238->unk2C == 2) {
        arg0->unk238->f172.b3 = 1;
    }
    return 1;
}
