/* rgp:protos */
#define RGP_SELF_EffectResFindByNameIdx_2e2e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 strcmp(const char *, const char *);

void *EffectResFindByNameIdx_2e2e60(s32 arg0, s32 arg1, s16 *arg2) {
    s32 var_18;
    s32 temp_17;
    void *temp_16;

    temp_17 = ((unsigned short)NameHash16_2e3470(arg1)) & 0xFFFF;
    var_18 = 0;
    while (var_18 < 0x30) {
        temp_16 = (void *)(arg0 + (var_18 * 0x70));
        if (temp_17 == *(u16 *)((u8 *)temp_16 + 0x1C4) && strcmp((const char *)arg1, (const char *)((u8 *)temp_16 + 0x1A4)) == 0) {
            *arg2 = var_18;
            return (u8 *)temp_16 + 0x174;
        }
        var_18 += 1;
    }
    return NULL;
}
