/* rgp:protos */
#define RGP_SELF_MapSceneCfgVariableInfo_192580 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern u8 *D_004812F4;
extern s32 D_004812F8;
extern s32 D_0048130C;

static inline s32 *get(s32 idx) {
    s32 base = *(s32 *)(D_004812F4 + 0x204);
    if (base == 0) {
        return NULL;
    }
    if (idx < 0 || idx >= *(s32 *)(D_004812F4 + 0x200)) {
        return NULL;
    }
    return (s32 *)(base + idx * 8);
}

s32 MapSceneCfgVariableInfo_192580(s32 arg0)
{
    s32 base;
    s32 idx;
    s32 *slot;

    slot = get(D_0048130C);
    if (slot == NULL) {
        return 0;
    }
    slot[0] = ((s32)MemStackStrDup_14cff0(SlotGetInt_15f720(arg0), D_004812F8));
    slot[1] = ((s32)MemStackStrDup_14cff0(SlotGetInt_15f720(arg0 + 8), D_004812F8));
    return 1;
}
