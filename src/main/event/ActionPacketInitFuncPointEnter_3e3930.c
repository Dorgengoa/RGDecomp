#include "types.h"

extern u8 *D_00483990;
extern u8 *D_00483994;
extern s32 PartyGetLocationGroupIdMaybe_3cb150(s32);
extern s32 GroupGetRecordChecked_411340(s32, s16, s16, s32);
extern void ActionPacketClear_3e3e90(void *);

/* Both globals are %gp_rel, so plain scalar externs.  ActionPacketClear_3e3e90's argument
   is the `daddu $4,$18,$0` sitting in the bnel delay slot. */

u8 *ActionPacketInitFuncPointEnter_3e3930(u8 *p0, s32 p1, s32 p2)
{
    u8 *h;
    s32 r;
    u8 *tbl;

    if (D_00483994 == 0) {
        return 0;
    }
    r = PartyGetLocationGroupIdMaybe_3cb150(*(s32 *)(D_00483990 + 0x18));
    /* the gp re-read is emitted BEFORE the narrowing of r -- naming it is what
       puts the `lw %gp_rel` ahead of the dsll32 pair. */
    tbl = D_00483994;
    h = (u8 *)GroupGetRecordChecked_411340(*(s32 *)(tbl + 0x34), r, 2, p2);
    if (h == 0) {
        return 0;
    }
    ActionPacketClear_3e3e90(p0);
    *(s8 *)(p0 + 0x2) = 4;
    *(s8 *)(p0 + 0x3) = 0x18;
    *(s16 *)(p0 + 0x0) = 2;
    *(s32 *)(p0 + 0xC) = p1;
    *(s32 *)(p0 + 0x10) = *(s32 *)(h + 0x4);
    *(s16 *)(p0 + 0x14) = *(s16 *)(h + 0x0);
    return p0;
}
