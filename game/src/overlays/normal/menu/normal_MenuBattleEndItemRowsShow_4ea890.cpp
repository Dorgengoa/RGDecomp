/* rgp:protos */
#line 1
/* === SESSION 71 (2026-09-21, SOLO): 511 bad -> MATCH.  Read end to end against
 * the listing; s31's statement-move installs had made the draft semantically
 * wrong.  Edits, each measured (build/wf-normal/s71/a1..a18.py):
 *  - `u = p2->f24;` moved BACK before its use in the -0xFF arm (s31 had put it
 *    after the `if (u != 0)` that reads it); it sits before `if (t != 0)` so
 *    retail's beqz delay slot gets the load.  Restored exact length.
 *  - `s32 *e = &normal_D_00527000[i];` -- retail keeps the element pointer in $30.
 *  - `w = 0x20; h = w; if (..) { w = 0x28; h = w; }` (h duplicated per arm).
 *  - `ofs = (f32)(n % 8);` BEFORE func_134A98 (retail holds it in $f20 across
 *    the call), `ofs = ofs * (f32) h;` after, and `#pragma
 *    opt_arithtransformation off` so the product is a TEMP ($f5), not $f20.
 *    Load-bearing: without it 3 bad; a bogus pragma name gives the same 3.
 *  - arm B: q42 after the o-> stores, id2 after the done block, the id3 call
 *    through a named `o`.
 *  - `if (n < 0 || n > 0x40) n = 0;` -- the `$at` compare (at-compare-class).
 *  - `h` declared before `n`/`w` (callee-saved permutation, 53 -> 33).
 *  - `o->f08 = (s16) cx;` NOT `(s16) (s32) cx`: the (s32) step makes the
 *    constant conversion LOOP-INVARIANT and mwcc hoists it to the function
 *    entry and spills it; the direct f32->s16 conversion is NOT hoisted.  This
 *    is what `opt_loop_invariants off` had been standing in for -- and that
 *    pragma is WRONG here, because retail DOES hoist the digit loop's `10`.
 *  - done block: `k = (u32) i * 42;` before `s`, `(f32) (s32) (k + 0xE)` at
 *    the store -- the chain starts first but the final value is created at the
 *    store, so s=$5 and the value=$4 as in retail.  16 -> MATCH.
 * Everything below predates this session. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_u_L400_T420_DEREF_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 558 words, 539 bad   after: 558 words, 517 bad   (retail 558 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_ofs_L268_T276_DEREF_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 561 words, ? bad   after: 558 words, 539 bad   (retail 558 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* !! PARKED, SEVEN WORDS SHORT (0x89c vs 0x8b8).  NOT under src/.
 * 2 scoring round trips + one 5-arm sweep; round 1 was ELEVEN short, so the
 * round-2 levers below are worth +4 words net and the sweep a further +10
 * against the arm it replaced.
 *
 * The residue is TWO recorded classes and nothing else:
 *
 * 1. [[normal-cse-cost-split]] -- 8 words, two sites.  At 0x004EABA0 and
 *    0x004EAF10 retail RECOMPUTES the whole `i * 42` chain
 *    (sll3/subu/sll2/subu/sll1) inside the `if (done == 0)` block for the
 *    `+0xE` operand, while $19 (ARM A) / $22 (ARM B) still hold `i * 42` and
 *    $16 / $21 hold `i * 42 + 0xC`.  mwcc value-numbers the inline `i * 42`
 *    onto the named local and derives `+0xE` with a single `addiu`, 4 words
 *    short per site.  Naming `q42 = i * 42` and `yy = q42 + 0xC` and leaving
 *    `i * 42 + 0xE` inline (the shape retail's registers imply) does NOT
 *    break the value numbering.  That file records this class as needing a
 *    scheduler-level result; it is not reachable from a spelling.
 *
 * 2. mwcc's C++ FRONT END folds `(s32)<float constant>`; the C front end does
 *    not.  Retail materialises 224.0f / 170.0f with `lui`+`mtc1` and converts
 *    at run time (`cvt.w.s`+`mfc1`), 4 words a site; every C++ spelling
 *    collapses to one `li` or one spilled `lq`.  FIVE ARMS, THREE DISTINCT
 *    OBJECTS:
 *      named f32 local  `cx = 224.0f; (s16)(s32)cx`  998f5b51  0x89c  *best*
 *      literal at the use `(s16)(s32)224.0f`         606131ea  0x874
 *      folded sum       `(s16)(s32)(112.0f+112.0f)`  606131ea  0x874  = above
 *      quotient         `(s16)(s32)(448.0f/2.0f)`    606131ea  0x874  = above
 *      volatile pin     `*(volatile f32*)&cx`        03f02f20  0x898
 *      `(f32)224` int-through-float                  998f5b51  INERT vs base
 *    => THE NAMED f32 LOCAL IS WORTH 10 WORDS over the literal here even
 *    though it does not close the site -- the literal lets mwcc fold AND
 *    sink; the named local at least keeps the value.  The plain-C precedent
 *    that DOES reach the run-time conversion is insect_InsectSeqExecSnailThrow_516a30
 *    (`fps = 30.0f; lim = (s32)fps / 2 - 5;`), a .c file.  This unit cannot
 *    be .c: 0x004EA918 is `lw $25,0x0($4) / lw $25,0x70($25) / jalr $25`.
 *
 * LEVERS THAT DID LAND THIS SESSION, each re-measured from disk:
 *  * `s32 lvl` not `s16 lvl` -- retail divides the `lh` result directly and
 *    widens s32->s64 with `dsll32/dsra32 ..,0` at the `sd`; an s16 local puts
 *    a `dsll32/dsra32 ..,0x10` pair at the DIVIDE instead.  2 words.
 *  * guard polarity on the 0..0x40 clamp: retail falls through into the
 *    `n >= 0x41` test and branch-likelies (`bltzl`) to the `n = 0` arm, so
 *    the source is `if (n >= 0) { if (n >= 0x41) n = 0; } else { n = 0; }`.
 *    The natural `if (n < 0) ... else if ...` costs a `b`+`move`.  1 word.
 *  * naming `n3 + 5` in a local instead of spelling it at both call sites.
 *
 * Everything structural is confirmed: the C++ class (vptr +0, slot 26 =
 * 0x70), `#pragma divbyzerocheck on` for the four `break 0,7` traps, the
 * dead digit-count loop that only the traps keep alive, the two 32-byte
 * record types copied member-by-member out of normal_D_00524D00/20/40, and the
 * `u8 done` flag that must be tested `== 0` to get retail's `andi 0xFF`.
 */
#pragma divbyzerocheck on
#pragma opt_arithtransformation off
#include "types.h"
/* normal 0x004EA890 -- 2,232 bytes, 558 instructions.  The town map's four
 * quest-marker slots: for each of normal_D_00527000[0..3] it either builds a live
 * marker (entry > 0) or the "cleared" placeholder (entry == -0xFF), and the
 * FIRST slot that builds anything also arms the pointer/arrow at m+0xAC.
 *
 * The `lw $25,0x0($4) / lw $25,0x70($25) / jalr $25` at 0x004EA918 is a C++
 * virtual, so this unit is .cpp.  vptr at +0, slot (0x70-8)/4 = 26.
 *
 * Four `break 0,7` traps (0x004EA950, 0x004EA974, 0x004EB0A8, 0x004EB0C0) so
 * the TU needs `#pragma divbyzerocheck on`; the digit-count loop at
 * 0x004EB090 computes nothing that is ever read, and only the divide traps
 * keep it alive.
 *
 * `sq $2,0xE0($29)` / `lq` around the calls is mwcc's ordinary caller-saved
 * spill of `i * 3`, not a 128-bit type.
 */

typedef struct Wdg {
    s16 f00; s16 f02; s16 f04; s16 f06; s16 f08; s16 f0A; s16 f0C; s16 f0E;
} Wdg;

typedef struct Pan {
    u8    pad00[0x04];
    u8    f04[0x1C];
    Wdg  *f20;
    void *f24;
    void *f28;
} Pan;

typedef struct Rec {
    s16 f00; s16 f02; s32 f04; u8 pad08[2]; u8 f0A; u8 pad0B; s32 f0C; s16 f10;
} Rec;

typedef struct Cd { u8 pad00[0x0C]; s32 f0C; u8 pad10[0x2C - 0x10]; s16 f2C; } Cd;

typedef struct Lv  { u8 pad000[0xF4];  s16 f0F4; } Lv;
typedef struct Nd  { u8 pad000[0x1C8]; Lv *f1C8; } Nd;
typedef struct Ct2 { u8 pad000[0x238]; Nd *f238; } Ct2;
typedef struct Ct  { u8 pad000[0x20];  Ct2 *f20; } Ct;

typedef struct RecA {
    s16 f00; s16 f02; u8 pad04[4]; s64 f08;
    s16 f10; s16 f12; s16 f14; s16 f16; s16 f18; s16 f1A; s16 f1C; s16 f1E;
} RecA;

typedef struct RecB {
    s16 f00; s16 f02; s16 f04; s16 f06; s16 f08; s16 f0A; s16 f0C; s16 f0E;
    f32 f10; f32 f14; s16 f18; s16 f1A; u16 f1C;
} RecB;

typedef struct Menu {
    u8   pad000[0x14];
    u8   f014[0x98];
    f32  f0AC;
    f32  f0B0;
    f32  f0B4;
    s16  f0B8;
    u8   pad0BA[0x104 - 0xBA];
    s16  f104;
    u8   pad106[0x108 - 0x106];
    u8  *f108;
} Menu;

class Db {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Cd * find(s16 id) { return VCM(Cd *, (void *, s16), 0x70, id); }     /* slot 26 -> vtable +0x70 */
};

typedef struct Hp { u8 pad00[0x08]; Db *f08; } Hp;
typedef struct Ho { u8 pad00[0x40]; Hp *f40; } Ho;

extern "C" {

extern s32  normal_D_00527000[];
extern s32  normal_D_005261C0[];
extern s32  normal_D_005261D0[];

extern s16  normal_D_00524D00[];
extern s16  normal_D_00524D02[];
extern s16  normal_D_00524D04[];
extern s16  normal_D_00524D06[];
extern s16  normal_D_00524D08[];
extern s16  normal_D_00524D0A[];
extern s16  normal_D_00524D0C[];
extern s16  normal_D_00524D0E[];
extern f32  normal_D_00524D10[];
extern f32  normal_D_00524D14[];
extern s16  normal_D_00524D18[];
extern s16  normal_D_00524D1A[];
extern u16  normal_D_00524D1C[];
extern s16  normal_D_00524D20[];
extern s16  normal_D_00524D22[];
extern s64  normal_D_00524D28[];
extern s16  normal_D_00524D30[];
extern s16  normal_D_00524D32[];
extern s16  normal_D_00524D34[];
extern s16  normal_D_00524D36[];
extern s16  normal_D_00524D38[];
extern s16  normal_D_00524D3A[];
extern s16  normal_D_00524D3C[];
extern s16  normal_D_00524D3E[];
extern s16  normal_D_00524D40[];
extern s16  normal_D_00524D42[];
extern s64  normal_D_00524D48[];
extern s16  normal_D_00524D50[];
extern s16  normal_D_00524D52[];
extern s16  normal_D_00524D54[];
extern s16  normal_D_00524D56[];
extern s16  normal_D_00524D58[];
extern s16  normal_D_00524D5A[];
extern s16  normal_D_00524D5C[];
extern s16  normal_D_00524D5E[];

extern void *D_004843E0;

extern Pan  *UiFindWidget_290460(void *a, u16 id);
extern Ho   *GetWorldDataMgr_1fedf0(void);
extern Ct   *GetGameData_1fede0(void);
extern void  UiIconGetSheetPos_288720(s32 a, s32 b, s16 *c, s16 *d);
extern void  strcpy(void *a, void *b);
extern void  UiSetWidgetPos_290f60(void *a, u16 id, s32 c, s32 d);
extern void  UiSetWidgetsVisibleById_291110(void *a, u16 id, s32 c, s32 d);
extern void  UiSetWidgetAlpha_2907a0(void *a, u16 id, f32 v);
extern void  UiFadeWidgetAlpha_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern void  SoundPlayScaledVolume_1b9520(void *a, s32 b, s32 c, f32 d);
extern void  memcpy(void *dst, const void *src, s32 n);

extern void normal_MenuBattleEndItemRowsShow_4ea890(Menu *m);

}

void normal_MenuBattleEndItemRowsShow_4ea890(Menu *m)
{
    s16   v1;
    s16   v2;
    RecB  rb __attribute__((aligned(16)));
    RecA  ra __attribute__((aligned(16)));
    RecA  rc __attribute__((aligned(16)));
    Pan  *p;
    Pan  *p2;
    Wdg  *o;
    Cd   *cd;
    Menu *s;
    Rec  *d;
    Ct   *c;
    Nd   *t;
    Lv   *y;
    void *u;
    s32  *e;
    s32   n3;
    s32   q42;
    s32   yy;
    s32   id3;
    s32   id;
    s32   id2;
    s32   h;
    s32   n;
    s32   w;
    s32   i;
    s32   dv;
    s32   k;
    s32   j;
    s32   lvl;
    u8    done;
    f32   ofs;
    f32   cx;
    f32   cy;

    done = 0;
    for (i = 0; i < 4; i++) {
        e = &normal_D_00527000[i];
        if (*e > 0) {
            n3 = i * 3;
            id = n3 + 3;
            p  = UiFindWidget_290460(m->f014, id);
            o  = p->f20;
            cd = GetWorldDataMgr_1fedf0()->f40->f08->find(*e);
            n  = (cd->f2C % 100) - 1;
            UiIconGetSheetPos_288720(cd->f2C / 1000, (cd->f2C % 1000) / 100, &v1, &v2);
            if (n < 0 || n > 0x40) {
                n = 0;
            }
            w = 0x20;
            h = w;
            if (cd->f2C == 0x8FD) {
                w = 0x28;
                h = w;
            }
            ofs = (f32) (n % 8);
            strcpy(&p->f04, normal_D_005261C0);
            d = (Rec *) (m->f108 + i * 32);
            d->f00 = 0;
            d->f02 = 0;
            d->f04 = cd->f0C;
            d->f0A = 2;
            d->f0C = 0xFF606060;
            d->f10 = -1;
            ofs = ofs * (f32) h;
            o->f08 = (s16) (s32) ((f32) v1 + ofs);
            o->f0A = (s16) (s32) ((f32) v2 + (f32) ((n / 8) % 8) * (f32) w);
            if (!((f32) v1 + ofs < 992.0f)) {
                h = h - 1;
            }
            o->f0C = h;
            o->f0E = w;
            o->f04 = 0x20;
            o->f06 = 0x26;
            q42 = i * 42;
            yy  = q42 + 0xC;
            UiSetWidgetPos_290f60(m->f014, id, 0xF, yy);
            UiSetWidgetsVisibleById_291110(m->f014, id, 1, 1);
            UiSetWidgetAlpha_2907a0(m->f014, id, 0.0f);
            if (done == 0) {
                UiFadeWidgetAlpha_290690(m->f014, id, 1.0f, 0.125f, -1.0f);
                k = (u32) i * 42;
                s = (Menu *) ((u8 *) m + i * 16);
                s->f0B0 = (f32) yy;
                s->f0AC = (f32) (s32) (k + 0xE);
                s->f0B4 = -6.0f;
                s->f0B8 = 1;
                if (m->f104 != 1) {
                    SoundPlayScaledVolume_1b9520(D_004843E0, 0x20, 0, 1.0f);
                }
                done = 1;
            }
            id2 = n3 + 4;
            p2  = UiFindWidget_290460(m->f014, id2);
            p2->f28 = m->f108 + i * 32;
            UiSetWidgetPos_290f60(m->f014, id2, 0x23, 2);
            UiSetWidgetsVisibleById_291110(m->f014, id2, 1, 1);
            UiSetWidgetAlpha_2907a0(m->f014, id2, 0.0f);
            rb.f00 = normal_D_00524D00[0];
            rb.f02 = normal_D_00524D02[0];
            rb.f04 = normal_D_00524D04[0];
            rb.f06 = normal_D_00524D06[0];
            rb.f08 = normal_D_00524D08[0];
            rb.f0A = normal_D_00524D0A[0];
            rb.f0C = normal_D_00524D0C[0];
            rb.f0E = normal_D_00524D0E[0];
            rb.f10 = normal_D_00524D10[0];
            rb.f14 = normal_D_00524D14[0];
            rb.f18 = normal_D_00524D18[0];
            rb.f1A = normal_D_00524D1A[0];
            rb.f1C = normal_D_00524D1C[0];
            if (p2->f20 != 0) {
                memcpy(p2->f20, &rb, 0x20);
            }
            ra.f00 = normal_D_00524D20[0];
            ra.f02 = normal_D_00524D22[0];
            ra.f08 = normal_D_00524D28[0];
            ra.f10 = normal_D_00524D30[0];
            ra.f12 = normal_D_00524D32[0];
            ra.f14 = normal_D_00524D34[0];
            ra.f16 = normal_D_00524D36[0];
            ra.f18 = normal_D_00524D38[0];
            ra.f1A = normal_D_00524D3A[0];
            ra.f1C = normal_D_00524D3C[0];
            ra.f1E = normal_D_00524D3E[0];
            u = p2->f24;
            if (u != 0) {
                memcpy(u, &ra, 0x20);
                *(s64 *) ((u8 *) u + 8) = e[4];
            }
            id3 = n3 + 5;
            UiSetWidgetPos_290f60(m->f014, id3, 0xF2, q42 + 0x35);
            o = UiFindWidget_290460(m->f014, id3)->f20;
            o->f04 = -1;
        } else if (*e == -0xFF) {
            *e = -0xFF;
            n3 = i * 3;
            id = n3 + 3;
            p  = UiFindWidget_290460(m->f014, id);
            o  = p->f20;
            strcpy(&p->f04, normal_D_005261D0);
            o->f00 = 0;
            o->f02 = 0;
            cx = 224.0f;
            cy = 170.0f;
            o->f08 = (s16) cx;
            o->f0A = (s16) cy;
            o->f0C = 0x1F;
            o->f0E = 0x1F;
            o->f04 = 0x20;
            o->f06 = 0x26;
            q42 = i * 42;
            yy  = q42 + 0xC;
            UiSetWidgetPos_290f60(m->f014, id, 0xF, yy);
            UiSetWidgetsVisibleById_291110(m->f014, id, 1, 1);
            UiSetWidgetAlpha_2907a0(m->f014, id, 0.0f);
            if (done == 0) {
                UiFadeWidgetAlpha_290690(m->f014, id, 1.0f, 0.125f, -1.0f);
                k = (u32) i * 42;
                s = (Menu *) ((u8 *) m + i * 16);
                s->f0B0 = (f32) yy;
                s->f0AC = (f32) (s32) (k + 0xE);
                s->f0B4 = -6.0f;
                s->f0B8 = 1;
                if (m->f104 != 1) {
                    SoundPlayScaledVolume_1b9520(D_004843E0, 0x20, 0, 1.0f);
                }
                done = 1;
            }
            id2 = n3 + 4;
            p2  = UiFindWidget_290460(m->f014, id2);
            p2->f28 = 0;
            UiSetWidgetPos_290f60(m->f014, id2, 0x23, 2);
            UiSetWidgetsVisibleById_291110(m->f014, id2, 1, 1);
            UiSetWidgetAlpha_2907a0(m->f014, id2, 0.0f);
            c = GetGameData_1fede0();
            if (c == 0) {
                return;
            }
            rc.f00 = normal_D_00524D40[0];
            rc.f02 = normal_D_00524D42[0];
            rc.f08 = normal_D_00524D48[0];
            rc.f10 = normal_D_00524D50[0];
            rc.f12 = normal_D_00524D52[0];
            rc.f14 = normal_D_00524D54[0];
            rc.f16 = normal_D_00524D56[0];
            rc.f18 = normal_D_00524D58[0];
            rc.f1A = normal_D_00524D5A[0];
            rc.f1C = normal_D_00524D5C[0];
            rc.f1E = normal_D_00524D5E[0];
            t = c->f20->f238;
            u = p2->f24;
            if (t != 0) {
                y = t->f1C8;
            } else {
                y = 0;
            }
            lvl = y->f0F4;
            if (u != 0) {
                rc.f08 = lvl;
                memcpy(u, &rc, 0x20);
            }
            dv = 1000;
            for (j = 3; j >= 0; j--) {
                if (lvl / dv != 0) {
                    break;
                }
                dv = dv / 10;
            }
            id3 = n3 + 5;
            UiSetWidgetPos_290f60(m->f014, id3, 0xF2, q42 + 0x35);
            o = UiFindWidget_290460(m->f014, id3)->f20;
            o->f04 = -1;
        }
    }
}
