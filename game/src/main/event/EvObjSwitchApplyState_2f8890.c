/* rgp:protos */
#define RGP_SELF_EvObjSwitchApplyState_2f8890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN EvObjSwitchApplyState_2f8890.  The `sh $0,0x32($16)` in the beql delay slot is
   the ELSE arm's first store duplicated by mwcc. */

typedef struct Rec36 { s32 a; s32 b[8]; } Rec36;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00461DC8[];
extern u8 D_00461DD0[];

void EvObjSwitchApplyState_2f8890(u8 *p)
{
    Rec36 rec __attribute__((aligned(16)));
    u8 *r;

    r = ((u8 *)TargetRefGetMapObj_2e7050(p + 0xA0));
    if (r != 0) {
        rec.a = -1;
        rec.b[0] = 0;
        rec.b[1] = 0;
        rec.b[2] = 0;
        rec.b[3] = 0;
        rec.b[4] = 0;
        rec.b[5] = 0;
        rec.b[6] = 0;
        rec.b[7] = 0;
        rec.a = EventRecGetId_2e5710(p);
        if (((unsigned char)EvObjSwitchGetState_2f89e0(p)) != 0) {
            *(s16 *)(r + 0x32) = 1;
            *(s32 *)(r + 0x3C) = *(s32 *)(r + 0x3C) & -2;
            EvScriptDispatchByName_2f9bb0(p, &rec, D_00461DC8);
        } else {
            *(s16 *)(r + 0x32) = 0;
            *(s32 *)(r + 0x3C) = *(s32 *)(r + 0x3C) | 1;
            EvScriptDispatchByName_2f9bb0(p, &rec, D_00461DD0);
        }
    }
}
