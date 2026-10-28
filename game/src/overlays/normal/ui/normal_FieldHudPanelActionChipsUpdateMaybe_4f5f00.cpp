/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x004F5F00 -- retargets the two "recommended action" chips shown on
 * each party row of the field menu.  For every live member it walks the
 * normal_D_005262A0 action table asking the member (virtual slot 101) which entries
 * it can perform, keeps at most two ids in `sel`, and then either seeds the
 * row's chip, leaves a matching one alone, or rotates to the other candidate
 * once the row's stickiness counter reaches 0x14 frames.
 *
 * `lw $25,0($16) / lw $25,0x19C($25) / jalr $25` -> C++ virtual, vptr 0,
 * slot (0x19C-8)/4 = 101.
 * `daddiu $6,$0,1` for the "already selected" flag is a C++ `bool`.
 * The `dsll32/dsra32 ..,16` pairs are s32 locals with explicit `(s16)` casts,
 * not s16 locals -- an s16 local is a measured null on this image. */

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 has(s32 k) { return VCM(s32, (void *, s32), 0x19C, k); }                       /* slot 101 -> vtable +0x19C */
};

typedef struct Act  { s16 f00; s16 f02; } Act;
typedef struct Chip { u8 pad000[0x354]; s16 f00; s16 f02; } Chip;
typedef struct Row  { s16 f00; s16 f02; } Row;
typedef struct Win  { u8 pad000[0x354]; Row chip[8]; } Win;
typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;

extern "C" Act normal_D_005262A0[];

extern "C" s16 D_004804A0;            /* gp - 0x4CD0 */
extern "C" s16 D_004804A2;            /* gp - 0x4CCE */

extern "C" {

extern Root *GetGameData_1fede0(void);
extern void  UiSetSpriteUvRect_28f9d0(Win *w, u16 id, s16 a, s32 b, s32 c, s32 d, s32 e);
extern void  UiSetSpriteSize_28fc30(Win *w, u16 id, s32 a, s32 b, s32 c);
extern void  UiSetWidgetVisible_290010(Win *w, u16 id, s32 a, s32 b);
extern Ent  *PartyGetSlotChara_3c2fb0(s32 w, s32 k);
extern s32 normal_FieldHudPartyRowCount_4f9c50(void);

}

extern "C" void normal_FieldHudPanelActionChipsUpdateMaybe_4f5f00(Win *p)
{
    s16   sel[2];
    s32   i;
    s32   j;
    s32   cnt;
    Ent  *e;
    Root *t;
    s32   n;
    s32   v;
    s32   q;
    u16   id;
    u16   id2;
    s16  *cur;
    Chip *c;
    s16  *pn;
    bool  found;

    t = GetGameData_1fede0();
    if (t == 0) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50();
    for (i = 0; i < n; i++) {
        e = PartyGetSlotChara_3c2fb0(t->f18, i);
        if (e == 0) {
            continue;
        }
        j = 0;
        cnt = 0;
        sel[0] = D_004804A0;
        sel[1] = D_004804A2;
        while ((v = normal_D_005262A0[(s16)j].f00) > 0) {
            if (e->has(v) != 0) {
                sel[(s16)cnt] = (s16)j;
                cnt = (s16)(cnt + 1);
                if (cnt >= 2) {
                    break;
                }
            }
            j = (s16)(j + 1);
        }
        id = (u16)(i + 0x1E);
        UiSetWidgetVisible_290010(p, id, 1, -1);
        if ((s16)cnt == 0) {
            p->chip[i].f00 = 0;
            p->chip[i].f02 = -1;
            UiSetWidgetVisible_290010(p, id, 0, -1);
        } else if ((s16)cnt > 0) {
            cur = &p->chip[i].f02;
            if (p->chip[i].f02 == -1) {
                *cur = sel[0];
            } else {
                found = false;
                for (q = 0; q < 2; q++) {
                    if (p->chip[i].f02 == sel[q]) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    c = (Chip *)((s32)p + (u32)i * 4);
                    pn = &c->f00;
                    c->f00 = (s16)(c->f00 + 1);
                    if ((s16)c->f00 >= 0x14) {
                        if ((s16)cnt >= 2) {
                            *cur = sel[q ^ 1];
                        } else {
                            *cur = sel[0];
                        }
                        *pn = 0;
                    }
                } else {
                    ((Chip *)((u8 *)p + (u32)i * 4))->f00 = 0;
                    *cur = sel[0];
                }
            }
            id2 = (u16)(i + 0x21);
            UiSetSpriteSize_28fc30(p, id2, 0x12, 0x12, 0);
            UiSetSpriteUvRect_28f9d0(p, id2, normal_D_005262A0[*cur].f02, 0x9E, 0x12, 0x12, 0);
            UiSetWidgetVisible_290010(p, id2, 1, -1);
        }
    }
}
