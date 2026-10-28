/* rgp:protos */
#define RGP_SELF_EffectEntriesSetId_2ddf00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct ElemFUN_002ddf00 {
    u8 pad0[0xE];
    s16 unkE;
} ElemFUN_002ddf00;

typedef struct Arg1FUN_002ddf00 {
    u8 pad0[0x8];
    s32 unk8;
} Arg1FUN_002ddf00;

typedef struct RetFUN_002da140 {
    u8 pad0[0x4];
    s16 unk4;
} RetFUN_002da140;

/*rgp*/

s32 EffectEntriesSetId_2ddf00(ElemFUN_002ddf00 *arg0, Arg1FUN_002ddf00 *arg1, s16 arg2)
{
    s32 i;
    ElemFUN_002ddf00 *elem;
    RetFUN_002da140 *ret;

    for (i = 0; i < 0x30; i++) {
        elem = (ElemFUN_002ddf00 *)((u8 *)arg0 + i * 0xE0);
        if (elem->unkE == arg1->unk8) {
            ret = ((RetFUN_002da140 *)EffectEntryFindNodeById_2da140(elem, arg1));
            if (ret != NULL) {
                ret->unk4 = arg2;
            }
        }
    }
    return 0;
}
