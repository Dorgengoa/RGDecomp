/* rgp:protos */
#define RGP_SELF_AmixerCfgTrackCmd_16ff80 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00481188;
extern s32 D_0048118C;
extern void *D_00481194;
extern s32 D_004811A0;
extern s32 D_004811A4;

static inline void *get(void *t, s32 i) {
    if (i < 0 || i >= *(s32 *)((u8 *)t + 0)) {
        return NULL;
    }
    return *(u8 **)((u8 *)t + 4) + i * 0x14;
}
s32 AmixerCfgTrackCmd_16ff80(s64 *arg0) {
    D_00481194 = get(D_00481188, D_004811A0);
    if (D_00481194 == NULL) {
        return 0;
    }
    *(s32 *)((u8 *)D_00481194 + 8) = ((s32)MemStackStrDup_14cff0(SlotGetInt_15f720((s32)arg0++), D_0048118C));
    *(s32 *)((u8 *)D_00481194 + 0xC) = VariantGetInt_15f780((s32)arg0);
    D_004811A4 = 0;
    D_004811A0 += 1;
    return 1;
}
