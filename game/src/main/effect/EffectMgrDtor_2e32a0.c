/* rgp:protos */
#define RGP_SELF_EffectMgrDtor_2e32a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj_FUN_002e32a0 {
    u8 pad0000[0x4078];
    s16 m4078;
};

void *EffectMgrDtor_2e32a0(struct Obj_FUN_002e32a0 *o, s16 flag)
{
    void *p;

    if (o != 0) {
        o->m4078 = 0;
        p = (u8 *)o + 0x1674;
        if (p != 0) {
            DestroyArray_1005b0(p, (void *)EffectEntryDtor_2e3360, 0xE0, 0x30);
        }
        p = (u8 *)o + 0x58;
        if (p != 0) {
            EffTableRelease_1a0fd0(p);
            EffInstHdlTableDtorMaybe_1a1300((u8 *)o + 0x13C, -1);
            EffHdlTableDtor_1a13f0((u8 *)o + 0x108, -1);
            EffHdlTableDtor_1a1490((u8 *)o + 0xD4, -1);
            EffHdlTableDtor_1a1530((u8 *)o + 0xA0, -1);
            EffHdlTableDtor_1a15d0((u8 *)o + 0x6C, -1);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
