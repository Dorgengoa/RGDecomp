/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00507170 -- rebuilds the normal_D_00525A10 id list.  Iterates the party
 * roster, and for every member whose slot-238 query is true records the
 * iteration index into the next list slot and raises the gp `any` flag; if any
 * survived, refreshes the 0xF gauge through normal_LeaderHudBossGaugeUpdate_506fe0.
 *
 * C++ virtual: `lw $25,0x3C0($25)` -> slot (0x3C0-8)/4 = 238.
 * The two `dsll32/dsra32 ..,16` pairs are explicit `(s16)` casts on s32
 * counters, not s16 locals.
 *
 * BYTE-IDENTICAL (s23), 26 bad -> MATCH on ONE TOKEN, found by
 * build/wf-normal/s23/bl_screen.py: retail has `bnel` at the iterator latch
 * where ours had `bne`.  `while ((e = f(&it)) != 0)` tests the ASSIGNMENT
 * EXPRESSION -- the call's return in $2 -- so the coalescing copy into `e`'s
 * register is independent of the branch and mwcc SINKS it into the delay slot.
 * `while (e = f(&it), e != 0)` tests the NAMED `e`, the copy must precede the
 * branch, and mwcc falls back to the likely-branch strategy retail has.
 * Same close as normal_TransWarpListCollapse_51ad60; see its header for the measured
 * alternatives.  [[mwcc-branch-likely-duplication]] read in REVERSE. */
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s238() { return VCM0(s32, 0x3C0); }
};

typedef struct It  { u8 pad00[8]; } It;
typedef struct Ctx { u8 pad00[0x1C]; void *f1C; } Ctx;

extern "C" s16 normal_D_00525A10[64];

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern u8    D_00484570;          /* gp - 0xC00 */
extern f32   D_0047D34C;          /* gp - 0x7E24 */

extern Ctx  *GetGameData_1fede0(void);
extern void IterInit_370170(It *, void *, int, int);
extern Ent  *IterNext_370040(It *it);
extern void  memset(void *p, s32 v, s32 n);
extern void  UiSetWidgetVisible_290010(void *p, u16 id, s32 c, s32 d);
extern void  UiSetWidgetAlpha_2907a0(void *p, u16 id, f32 v);
extern void  UiFadeWidgetAlpha_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  normal_LeaderHudBossGaugeUpdate_506fe0(void);
}

extern "C" s32 normal_LeaderHudBossGaugeRebuild_507170(void)
{
    It   it __attribute__((aligned(16)));
    Ctx *c;
    Ent *e;
    s32  i;
    s32  n;

    c = GetGameData_1fede0();
    IterInit_370170(&it, c->f1C, 0, 0);
    D_00484570 = 0;
    memset(normal_D_00525A10, -1, 0x20);
    UiSetWidgetVisible_290010(D_00484564, 0xE, 0, -1);
    i = 0;
    n = 0;
    while (e = IterNext_370040(&it), e != 0) {
        if (e->s238() != 0) {
            D_00484570 = 1;
            normal_D_00525A10[(s16)n] = i;
            n = (s16)(n + 1);
        }
        i = (s16)(i + 1);
    }
    if (D_00484570 != 0) {
        normal_LeaderHudBossGaugeUpdate_506fe0();
        UiSetWidgetVisible_290010(D_00484564, 0xE, 1, -1);
        UiSetWidgetAlpha_2907a0(D_00484564, 0xF, 0.0f);
        UiFadeWidgetAlpha_290690(D_00484564, 0xF, 1.0f, D_0047D34C, -1.0f);
    }
    return 0;
}
