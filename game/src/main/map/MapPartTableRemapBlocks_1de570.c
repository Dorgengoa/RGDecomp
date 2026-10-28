/* rgp:protos */
#define RGP_SELF_MapPartTableRemapBlocks_1de570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0xCC]; } E001de570;

typedef struct {
    u8 pad0[0x4];
    s32 *unk4;
    s16 unk8;
    s16 unkA;
} Obj0Arg0;

/*rgp*/
/*rgp*/

s32 MapPartTableRemapBlocks_1de570(Obj0Arg0 *arg0, s32 arg1, E001de570 *arg2, s32 arg3)
{
    s32 *buf;
    s32 n;
    s32 i;
    s32 j;
    s32 k;

    buf = ((s32 *)MemStackNew_14e1b0(arg0->unkA * 4, arg1));
    if (buf == 0) return 0;
    n = 0;
    for (i = 0; i < arg0->unk8; i++) {
        if (arg0->unk4[i] != 0) {
            for (j = 0; j < arg3; j++) {
                k = ((short)MapDataGetId_1e7bd0(arg0->unk4[i]));
                if (k == ((short)MapDataGetId_1e7bd0((s32)&arg2[j]))) break;
            }
            if (j < arg3) {
                buf[n++] = (s32)&arg2[j];
            }
        }
    }
    arg0->unk8 = n;
    arg0->unk4 = buf;
    return 1;
}
