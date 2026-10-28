/* rgp:protos */
#define RGP_SELF_ProgressSetByCode_3ccf10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
} In;

typedef struct {
    s16 unk0;
    u8 pad2[0x8 - 0x2];
    s16 unk8;
    u8 padA[0x10 - 0xA];
    s16 *unk10;
} Info;

typedef struct {
    u8 pad0[0x4];
    In *unk4;
} Arg0;

/*rgp*/
/*rgp*/
/*rgp*/

s32 ProgressSetByCode_3ccf10(Arg0 *arg0, s32 pd1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 idx;
    s32 a;
    s32 b;
    s32 ok;
    s16 *p;
    Info *info;

    if (arg0->unk4 == NULL) {
        return 0;
    }
    info = ((Info *)GroupTableFindEntryByCode_422910(arg0->unk4->unk8, (int)pd1, (int)arg2, (int)arg3));
    if (info == NULL) {
        return 0;
    }
    idx = info->unk8;
    if (idx < 0 || idx >= 0xF) {
        return 0;
    }
    a = info->unk0;
    p = info->unk10;
    if (p == NULL) {
        return 0;
    }
    b = *p;
    if (((s32)GroupTableFindSubEntry_422880(arg0->unk4->unk8, b, a, arg2)) != 0) {
        return ProgressSlotSet_3cd130(arg0, b, a, idx, arg2, arg3, arg4);
    }
    return 0;
}
