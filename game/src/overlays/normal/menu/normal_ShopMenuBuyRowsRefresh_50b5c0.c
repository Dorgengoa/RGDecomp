/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyRowsRefresh_50b5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* WARNING PARKED at FOUR WORDS of 289 -- NOT in config/ocunits/normal.txt.
 * RIGHT LENGTH; every call, branch kind and gap is exact.  The residue is one
 * four-instruction ROTATION in the case-1 hp==0 arm: retail is
 *   lwc1 $f12,gp / sw $3,0xC($16) / lw $4,gp / lui $2,0x3F800000
 * and mwcc gives
 *   sw $3,0xC($16) / lui $2,0x3F800000 / lwc1 $f12,gp / lw $4,gp
 * i.e. retail hoists the gp float read ABOVE the aliasing store and sinks the
 * 1.0f materialisation below the argument load.
 * Fourteen spellings, five builds, all four bad: the float read inline / in a
 * named local placed before, between and after the store and the id cast /
 * declared first of all locals / the 1.0f in its own named local in four
 * positions / the u16 cast as a local versus inline at both sites / `volatile`
 * on the stored field and on both fields of Fld.  Two of them are 8 and 9 bad
 * and the rest are exactly these four words.
 * ⚠ This is the recorded "a store through a pointer blocks a later gp load's
 * hoist" lever pointed the OTHER WAY -- there the fix was to write the read
 * before the store, and here that is measurably WORSE (8 words).
 *
 * normal 0x0050B5C0 -- rebuilds the eight-slot equip/ability row for page
 * `page`: one 0x27+i item widget and one 0x21/0x22/0x23 icon per row, filled
 * from normal_D_00527D30[page + i].
 *
 * `normal_ShopMenuBuyRowIconsRefresh_50dae0` is called with `$5 = 0` and `$4` NEVER WRITTEN, so the
 * first argument is this function's own parameter riding through -- writing
 * `normal_ShopMenuBuyRowIconsRefresh_50dae0(0)` against a one-argument prototype costs a `daddu
 * $4,$0,$0` retail does not have.
 * `$30` is `&normal_D_00527D30[page]` hoisted out of the loop, which is a POINTER
 * LOCAL in the source: `normal_D_00527D30[page + i]` would scale the sum inside.
 * func_28F710 takes ELEVEN arguments -- eight in $4..$11 and three in 8-byte
 * stack slots from sp+0 (EABI), and mwcc shares the constants between
 * arguments 5/9 and 6/10, which is why only two `addiu`s feed three `sd`s.
 * `daddiu $22,$0,1` for the flag plus a bare test is the u8-flag spelling.
 * The dispatch's `beql` delay slots carry the CASE BODY's first instruction,
 * not the next guard's constant, so it is a switch; retail tests 3/2/1 and the
 * bodies lie 1/2/3, which is source order `case 1, case 2, case 3`. */

typedef struct Item {
    u8  pad00[8];
    s64 f08;
    u8  pad10[0x16 - 0x10];
    s16 f16;
    s16 f18;
    u8  pad1A[0x28 - 0x1A];
    s64 f28;
    u8  pad30[0x36 - 0x30];
    s16 f36;
    s16 f38;
} Item;

typedef struct Fld  { u8 pad00[4]; s32 f04; u8 pad08[4]; u32 f0C; } Fld;
typedef struct Kind { u8 pad00[6]; u8 f06; } Kind;
typedef struct Ent  { u8 pad00[4]; Kind *f04; } Ent;
typedef struct Ctx  { u8 pad00[0x18]; void *f18; } Ctx;

extern void *D_004845C8;          /* gp - 0xBA8 */
extern s16   D_0048463C;          /* gp - 0xB34 */
extern f32   D_0047D288;          /* gp - 0x7EE8 */
extern Ent  *normal_D_00527D30[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyRowsRefresh_50b5c0(s32 page)
{
    Ent **p;
    u8    flag;
    s32   hp;
    s32   i;
    Ent  *e;
    s32   id;
    Item *it;
    Fld  *fd;

    D_0048463C = 0;
    normal_ShopMenuBuyRowIconsRefresh_50dae0(page, 0);
    p = &normal_D_00527D30[page];
    for (i = 0; i < 8; i++) {
        id = (u16)(i + 0x27);
        UiSetSpriteSizeUvSize_28f670(D_004845C8, id, 0, 0, 0, 0, 0);
        UiSetSpriteSizeUvSize_28f670(D_004845C8, id, 0, 0, 0, 0, 1);
        UiSetSpriteSizeUvSize_28f670(D_004845C8, 0x23, 0, 0, 0, 0, i);
        UiSetSpriteFlags_290bd0(D_004845C8, 0x23, (long long)(0x200), -1, i, 0);
        it = ((Item *)UiGetWidgetSubItem_28f2b0(D_004845C8, id, 0));
        if (it == 0) {
            return 0;
        }
        it->f38 = 0;
        it->f36 = 0;
        it->f18 = 0;
        it->f16 = 0;
        fd = ((Fld *)UiGetWidgetText_28f620(D_004845C8, id, 0));
        if (fd == 0) {
            return 0;
        }
        fd->f04 = 0;
        fd->f0C = 0xFF303030;
        UiSetSpriteSizeUvSize_28f670(D_004845C8, 0x21, 0, 0, 0, 0, i);
        e = p[i];
        if (e != 0) {
            fd->f04 = ShopRowGetItemName_3ce930(e);
            hp = ((short)ShopRowGetStock_3ce860(e));
            UiSetWidgetColor_2905b0(D_004845C8, id, 1.0f, 1.0f, 1.0f, 1.0f);
            flag = 1;
            switch (((short)ShopRowGetMode_3ce680(e))) {
            case 1:
                if (hp == 0) {
                    fd->f0C = 0xFF202020;
                    UiSetWidgetColor_2905b0(D_004845C8, (u16)id, 0.6f, 0.6f,
                                0.6f, 1.0f);
                    UiSetSpritePosSizeUv_28f710(D_004845C8, (u16)id, 0xEF, i * 0x1C + 0x2A, 0x30,
                                0x10, 0xCC, 0x40, 0x30, 0x10, 0);
                } else {
                    it->f36 = 0xC;
                    it->f38 = 0x10;
                    it->f28 = ShopRowGetPrice_3ce6e0(e);
                    UiSetSpriteSizeUvSize_28f670(D_004845C8, id, 0xC, 0x10, 0xC, 0x10, 1);
                    if (hp == 0x64) {
                        UiSetSpritePosSizeUv_28f710(D_004845C8, id, 0xFA, i * 0x1C + 0x2A,
                                    0x1A, 0x10, 0xCC, 0x30, 0x1A, 0x10, 0);
                    } else {
                        it->f16 = 0xC;
                        it->f18 = 0x10;
                        it->f08 = hp;
                    }
                }
                break;
            case 2:
                UiSetSpriteUv_28f970(D_004845C8, 0x21, 0, 0xEC, i);
                UiSetSpriteSizeUvSize_28f670(D_004845C8, 0x21, 0x88, 0x14, 0x88, 0x14, i);
                flag = 0;
                break;
            case 3:
                UiSetSpriteUv_28f970(D_004845C8, 0x21, 0, 0xD8, i);
                UiSetSpriteSizeUvSize_28f670(D_004845C8, 0x21, 0x88, 0x14, 0x88, 0x14, i);
                flag = 0;
                break;
            }
            if (flag && (e->f04->f06 & 1)) {
                UiSetSpriteSizeUvSize_28f670(D_004845C8, 0x23, 0x1C, 0x18, 0x1C, 0x18, i);
                if (InvHasItemInCategory_3c7f40(((Ctx *)GetGameData_1fede0())->f18, 0x40FB, 0xA, 0) != 0) {
                    UiSetSpriteFlags_290bd0(D_004845C8, 0x23, (long long)(0x200), 1, i, 0);
                } else {
                    if (hp == 0x64) {
                        UiSetSpriteSizeUvSize_28f670(D_004845C8, id, 0, 0, 0, 0, 0);
                    }
                    it->f18 = 0;
                    it->f16 = 0;
                }
            }
        } else {
            UiSetSpriteX_28fcd0(D_004845C8, 0x22, -1, i);
        }
    }
    return 1;
}
