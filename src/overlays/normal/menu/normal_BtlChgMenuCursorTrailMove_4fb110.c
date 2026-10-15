/* MATCH -- byte-identical (session 19, lane r2d).  TWO levers, both needed:
 *  1. [[mwcc-float-literal-pool]] -- D_0047D278 and D_0047D950 are POOL
 *     LITERALS 0.8f and 0.035f.  These are exactly the two gp loads the park
 *     note named ("retail interleaves `lwc1 $f12,-0x7EF8` and
 *     `lwc1 $f13,-0x7820` among the callee-saved `sq`s and we rank both
 *     LAST").  Worth 8 words: 17 bad -> 9.
 *     NOTE 0x0047D950 sits ABOVE the 0x0047D7FF pool bound quoted in
 *     levers.d/mwcc-float-literal-pool.md, so that bound is a GUIDE, not a
 *     screen -- the working screen is "retail HOISTS the load" plus reading
 *     the word at the address.
 *  2. the (s32) result in its OWN named local, written back after the call:
 *     `s32 bi = (s32)(t + (f32)b); func_290F50(..., bi, ...); b = bi;`
 *     Worth the remaining 9 words (the 12.0f/0.5f GPR pair and the whole
 *     $f0/$f1/$f2 numbering).  6-arm sweep, 6 distinct objects: the operand
 *     swap, an `f32 fb` named local, a named 0.5f and a reused `t` destination
 *     are all live-but-equal at 9; the one-expression form is 1 word long.
 * Carries a `.lit4`; n_olink.py:375 retargets it.  Bare dv_osbuild reads 2 bad
 * -- the un-retargeted displacement, not a defect. */
#include "types.h"
/* normal 0x004FB110 -- a four-channel tint/param pass over the object in $4,
 * then a scalar recomputed from func_128FD0 and pushed to the same four
 * channels.  The four u16 ids at 0x004804C0..C6 are CONSECUTIVE but written as
 * four separate externs, per the "four lwc1/swc1 pairs are four globals, not a
 * block copy" rule -- a declared array would be a relocation change.
 * 0x41400000 is 12.0f, 0x3F000000 0.5f, 0x3E800000 0.25f, 0x3E000000 0.125f. */

extern u16 D_004804C0;
extern u16 D_004804C2;
extern u16 D_004804C4;
extern u16 D_004804C6;
extern f32 D_0047D5BC;
extern f32 D_0047DA4C;
extern f32 D_0047DA50;
extern f32 D_0047DA54;
extern f32 D_0047DA58;
extern f32 D_0047DA5C;
extern f32 D_0047DA60;
extern f32 D_00484440;
extern const u8 D_00527020[];

extern void func_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern void func_290F50(void *a, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void normal_FieldHudPanelTintUpdateMaybe_4f4c10(const void *a);
extern void func_28B630(f32 *p, f32 v);
extern f32  func_128FD0(f32 x);

s32 normal_BtlChgMenuCursorTrailMove_4fb110(void *a, s32 b, s32 c)
{
    f32 t;

    func_290690(a, D_004804C0, 0.8f, 0.035f, -1.0f);
    func_290690(a, D_004804C2, 0.5f, D_0047D5BC, -1.0f);
    func_290690(a, D_004804C4, 0.25f, D_0047DA4C, -1.0f);
    func_290690(a, D_004804C6, 0.125f, D_0047DA50, -1.0f);
    normal_FieldHudPanelTintUpdateMaybe_4f4c10(D_00527020);
    func_28B630(&D_00484440, D_0047DA54);
    /* The PRODUCT is its own statement: written inline mwcc contracts the
     * expression into adda.s/madd.s and retail has mul.s + add.s. */
    t = 12.0f * func_128FD0(D_00484440);
    {
        s32 bi = (s32)(t + (f32)b);
        func_290F50(a, D_004804C0, bi, c, 0, 0.5f);
        b = bi;
    }
    func_290F50(a, D_004804C2, b, c, 0, D_0047DA58);
    func_290F50(a, D_004804C4, b, c, 0, D_0047DA5C);
    func_290F50(a, D_004804C6, b, c, 0, D_0047DA60);
    return 0;
}
