/* rgp:protos */
#define RGP_SELF_EffectMgrCtor_2e33b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    u8 unk0[4];
    s32 unk4;
    u8 padTail[0x70 - 8];
} Elem002E33B0;

void *EffectMgrCtor_2e33b0(void *arg0) {
    Elem002E33B0 *p;
    Elem002E33B0 *end;

    MemStackCtor_14e030((void *)arg0);
    EffTableCtor_1a11b0((u8 *)arg0 + 0x58);
    p = (Elem002E33B0 *)((u8 *)arg0 + 0x174);
    end = (Elem002E33B0 *)((u8 *)arg0 + 0x1674);
    do {
        p->unk4 = 0;
        p++;
    } while (p < end);
    ConstructArray_100620((u8 *)arg0 + 0x1674, (void *)EffectEntryCtor_2e3430, (void *)EffectEntryDtor_2e3360, 0xE0, 0x30);
    *(s16 *)((u8 *)arg0 + 0x4078) = 0;
    EffectResSlotsReset_2e30c0(arg0);
    return arg0;
}
