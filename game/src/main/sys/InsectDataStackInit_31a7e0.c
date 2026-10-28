/* rgp:protos */
#define RGP_SELF_InsectDataStackInit_31a7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strlen(void *);
extern void strcpy(void *, void *);
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004623B8[];
extern u8 D_004623C8[];
extern s32 D_0047F230;
extern u8 D_004E7FB0[];

s32 InsectDataStackInit_31a7e0(void)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 rv9;
    s32 r2;
    s32 r3;
    s32 r5;
    s32 t1;

    t0 = D_0047F230;
    if (t0 >= 0) {
        return t0;
    }
    r0 = GetCurrentScene_1f5be0();
    r1 = RecStackPush_1c4240(r0, D_004623B8);
    D_0047F230 = r1;
    if (r1 < 0) {
        rv9 = -1;
    } else {
        r2 = ((s32)RecStackGetSlot_1c4330(r0, r1));
        r3 = MemStackAllocAligned64_14da10(r2, 0x3B333);
        MemStackHeapInit_14dee0(D_004E7FB0, r3, 0x3B333);
        r5 = strlen(D_004623C8);
        if ((u32)r5 < 0x10) {
            strcpy(D_004E7FB0, D_004623C8);
        }
        MemStackHeapReinit_14de90(D_004E7FB0);
        MemStackAlign64_14d8e0(D_004E7FB0);
        t1 = D_0047F230;
        rv9 = t1;
    }
    return rv9;
}
