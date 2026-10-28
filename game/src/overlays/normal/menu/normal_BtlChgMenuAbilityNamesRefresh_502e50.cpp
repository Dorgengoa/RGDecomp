/* rgp:protos */
#line 1
/* SESSION 32 (lane nc32q): BYTE-IDENTICAL -- 137 words, 0 bad, MATCH under
 * build/wf-normal/s32/nscore.py.  Reached from the s31 draft (137 w / 12 bad)
 * by a THREE-EDIT CROSS in which no single edit pays:
 *   1. the o-guard became an assignment INSIDE the condition, and the guard
 *      exits with `return 0;` (with `goto _x29;` it is 139 words / 92 bad);
 *   2. `p = func_36FFF0(&it, st); if (p != 0)` became
 *      `if ((p = func_36FFF0(&it, st)) != 0)` -- retail tests the RAW call
 *      result with a non-likely branch and sinks the copy into the delay slot;
 *   3. `lim = it.f04;` moved from before func_3A8180 to after func_370170
 *      (it is only meaningful there -- func_370170 fills `it`).
 * Then the last two words: `o` is TWO variables.  o2 is the short-lived
 * caller-saved copy ($2) that feeds func_3A8180's second argument, `o` is the
 * callee-saved one ($19) the loop uses; and the `o = o2` copy must sit BEFORE
 * the guard, which is what turns `bnel $2,$0` into retail's plain `bne`.
 * Deck: 107 arms over 3 bulk32 decks; see build/wf-normal/s32/reports/nc32q.md
 */
#include "types.h"
/* normal 0x00502E50 -- paints `cnt` inventory cells starting at widget id
 * `base`, three ids apart.  Each cell is cleared, then in `mode` 0 it takes the
 * next item's icon and is greyed 0xFF202020, darkened to 0xFF404040 when the
 * owner's slot-178 query claims it; past the end of the list, or in any other
 * mode, the cell is just blanked.
 *
 * C++ virtual: `lw $25,0x2D0($25)` -> slot (0x2D0-8)/4 = 178, taking the item's
 * s16 id straight from an `lh` -- the callee parameter is `s16`.
 * `andi $22,$17,0xFFFF` hoisted above the loop is the NAMED `u16` base id. */
class Own {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 owns(s16 k) { return VCM(s32, (void *, s16), 0x2D0, k); }
};

typedef struct It  { u8 pad00[4]; s16 f04; u8 pad06[2]; } It;
typedef struct Qry { u8 pad00[0x18]; } Qry;
typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct St  { u8 pad00[0x76]; s16 f76; } St;
typedef struct Itm { s16 f00; u8 pad02[6]; s32 f08; } Itm;

extern "C" {
extern void *D_004844A0;          /* gp - 0xCD0 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern St   *D_00484454;          /* gp - 0xD1C */

extern Ctx  *GetGameData_1fede0(void);
extern s32   UiEntryListGetCurrentData_28ec60(void *p);
extern Own  *PartyGetSlotChara_3c2fb0(s32 w, s32 k);
extern void  CharaAbilityViewCtor_3a8180(Qry *q, Own *o, s32 a, s32 b);
extern void IterInit_370170(It *, Qry *, int, int);
extern Itm  * IterSeek_36fff0(It *, s32, int, int);
extern Itm  *IterNext_370040(It *it);
extern void  UiSetTextFont_290a80(void *p, u16 id, s32 a, s32 b);
extern void  UiSetTextColor_290a40(void *p, u16 id, s32 rgba, s32 a);
extern void  UiSetTextStringPos_290b20(void *p, u16 id, s32 a, s32 b, s32 c, s32 d);
extern s32   normal_BtlChgPageGetMember_505f90(St *s);
}

extern "C" s32 normal_BtlChgMenuAbilityNamesRefresh_502e50(s32 base, s32 cnt, s32 mode)
{
    u16  id;
    It   it __attribute__((aligned(16)));
    Qry  q __attribute__((aligned(16)));
    Ctx *c;
    Own *o;
    Own *o2;
    Itm *p;
    s32  i;
    s32  st;
    s32  lim;
    u16  b16;

    if (UiEntryListGetCurrentData_28ec60(D_004844A0) == 0) {
        return 0;
    }
    st = D_00484454->f76;
    c = GetGameData_1fede0();
    if (c == 0) {
        return 0;
    }
    o2 = PartyGetSlotChara_3c2fb0(c->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
    o = o2;
    if (o2 == 0) {
        return 0;
    }
    CharaAbilityViewCtor_3a8180(&q, o2, 0, -1);
    IterInit_370170(&it, &q, 0, 0);
    lim = it.f04;
    if ((p = IterSeek_36fff0(&it, st, 0, 0)) != 0) {
        b16 = (u16)base;
        for (i = 0; i < cnt; i++) {
            id = (u16)(b16 + i * 3);
            UiSetTextFont_290a80(D_0048449C, id, 2, 0);
            if (mode != 0) {
                if ((st + i) < lim) {
                    UiSetTextStringPos_290b20(D_0048449C, id, 0, -1, -1, 0);
                }
            } else {
                if (((st + i) < lim) && (p != 0)) {
                    UiSetTextStringPos_290b20(D_0048449C, id, p->f08, -1, -1, 0);
                    UiSetTextColor_290a40(D_0048449C, id, 0xFF202020, 0);
                    if (o->owns(p->f00) != 0) {
                        UiSetTextColor_290a40(D_0048449C, id, 0xFF404040, 0);
                    }
                } else {
                    UiSetTextStringPos_290b20(D_0048449C, id, 0, -1, -1, 0);
                }
                p = IterNext_370040(&it);
            }
        }
    }
    return 1;
_x29:
    return 0;
}
