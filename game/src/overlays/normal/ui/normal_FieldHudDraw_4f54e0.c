/* rgp:protos */
#define RGP_SELF_normal_FieldHudDraw_4f54e0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* normal 0x004F54E0 -- the panel's play-time caption tick.  Re-arms the 0x28
 * widget, sweeps the 0x310-stride D_00484414 table, then either draws the
 * elapsed-time number (width chosen from its DIGIT COUNT) or, when the save
 * header says the clock is hidden, parks the 0x54 widget with func_290690.
 *
 * `%` gets a bare `div`, `/` gets the `bnez`/`break 0,7` pair; the middle
 * `div/mfhi` at 0x004F5608 is the modulo and is unchecked.  The `/ 60` MUST be
 * applied to the ternary INLINE -- writing `t = ternary; t = t / 60;` lets
 * mwcc fold `(x/60)/60` into `x/3600` and no restatement of the chain (eight
 * measured spellings, one identical object) recovers it.
 *
 * `s->f238` is read TWICE and retail RELOADS it (the flag `lbu` overwrites the
 * pointer's register).  mwcc's redundant-load elimination is TYPE-KEYED, so
 * reading the second site through a SECOND struct type of identical layout is
 * what suppresses the CSE; a `volatile` read of the same field is byte-for-byte
 * equivalent (same object sha1) and this spelling is the one without volatile. */

typedef struct Obj {
    u8  pad000[0x14];
    u8  f014[0x28 - 0x14];
    u8  f028[0x378 - 0x28];
    s16 f378;
    u8  pad37A[0x383 - 0x37A];
    u8  f383;
} Obj;

typedef struct T310 { u8 pad000[0x310]; } T310;
typedef struct Hdr  { u8 pad000[0x16C]; s32 f16C; u8 pad170[0x172 - 0x170];
                      u8 f172; } Hdr;
typedef struct Save { u8 pad000[0x238]; Hdr *f238; } Save;
typedef struct Save2 { u8 pad000[0x238]; Hdr *f238; } Save2;
typedef struct Root { u8 pad00[0x20]; Save *f20; } Root;

extern T310 *D_00484414;          /* gp - 0xD5C  */
extern f32   D_0047D828;          /* gp - 0x7948 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_FieldHudDraw_4f54e0(Obj *p);

void normal_FieldHudDraw_4f54e0(Obj *p)
{
    Root *r;
    Save *s;
    s32   n;
    s32   i;
    s32   t;
    s32   v;
    s32   d;
    u8    f;

    if (p->f378 == 0) {
        return;
    }
    UiSetWidgetsVisibleById_291110(p, 0x28, 0, 1);
    UiDrawWidgets_291910(p);
    UiSetWidgetsVisibleById_291110(p, 0x28, 1, 1);
    UiDrawWidgets_291910(p->f014);
    BattleSparkBurstDraw_382fd0(p->f028);
    if (p->f383 != 0) {
        normal_FieldHudRadarDraw_4f3720(p);
    }
    n = normal_FieldHudPartyRowCount_4f9c50();
    if (D_00484414 != 0) {
        for (i = 0; i < n; i++) {
            UiGlowSpriteListDraw_33bd20(&D_00484414[i]);
        }
    }
    r = ((Root *)GetGameData_1fede0());
    if (CharaSysStateGetChallengeKindMaybe_3a3800(r->f20) == 0) {
        return;
    }
    s = r->f20;
    f = (s->f238 != 0) ? (s->f238->f172 & 1) : 0;
    if (f != 0) {
        t = ((((Save2 *)s)->f238 != 0) ? ((Save2 *)s)->f238->f16C : 0) / 60;
        v = t % 60 + (t / 60) * 60;
        if (v >= 100) {
            d = 0;
        } else if (v >= 10) {
            d = 1;
        } else {
            d = 2;
        }
        UiSetWidgetPos_290f60(p, 0x54, d * 11 + 0xDF, 0x3C);
        UiSetWidgetSubItemValue_291250(p, 0x54, 0, v);
    } else {
        UiFadeWidgetAlpha_290690(p, 0x54, 0.0f, D_0047D828, -1.0f);
    }
}
