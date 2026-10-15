#include "types.h"

#pragma opt_propagation off
#pragma opt_rotateloops off


/* MAIN MenuCaptureScreenTex_298810 -- called by MenuSysInitMaybe_297640.  Sets up a 0x100x0100 RGBA
   surface: builds the destination pointer once (stored to D_00482418, kept
   in $17 across every call), then blits with a constant 0x80 alpha.

   Readings:
     * `D_0048233C` is loaded ONCE into $16 and used five times -> named local.
     * `D_00482414` is written from the call result, tested and bitfield-poked
       through the LIVE result value, then RE-LOADED for the `0x50` store:
       the `sb 0x3C` invalidates the cached gp load, so the source reads the
       global by name each time.
     * `andi $3,$0,0x1` / `sll $6,$3,2` / `and ~4` / `or` is a BITFIELD INSERT
       of the value 0 at bit 2 -- mwcc does not fold the zero.
     * the three `daddu $x,$0,$0` addends are locals initialised to 0.

   FOUR MEASURED LEVERS, all needed together (see the pragmas above):
     1. `opt_propagation off` -- without it mwcc folds `r + q[i]` (r == 0) and
        drops three `addu`; with it the adds come back.  MEASURED: 12-arm sweep,
        the source axis alone cannot reach this (8 words short in every arm).
     2. `opt_rotateloops off` -- with rotation on, mwcc emits a DUPLICATED
        entry test (`slti`+`beqz`) per loop; retail jumps to the SHARED bottom
        test (`b .Lcond`).  Worth 2 words.  `for` vs `while` is INERT
        (identical object sha1), so the loop FORM is a measured null; the
        rotation KNOB is the whole lever.
     3. the three channel bytes are read into NAMED LOCALS before any store:
        `dst` and `q` are both `u8 *`, so a store through `dst` forces mwcc to
        RELOAD `q[1]`/`q[2]`; naming them hoists all three loads to the top.
        And their READ ORDER is `c1, c2, c0` -- the complete 6-permutation
        sweep of that order runs MATCH / 5 / 7 / 7 / 9 / 9 / 11, so it is a
        real gradient and `c0,c1,c2` is NOT the answer.
     4. `y = 0` is written BEFORE `r = g = bl = 0` and `y++` BEFORE
        `src += 0x800`; both are source ORDER showing through into the emitted
        order of the four `daddu $x,$0,$0` and the outer-loop tail.  4 words.
   Declaration order of c0/c1/c2 is INERT (5 arms, one object).  */

typedef struct Hnd98810 {
    u8 pad00[0x28];
    u8 *m28;                 /* +0x28 */
    s32 m2C;                 /* +0x2C */
} Hnd98810;

typedef struct Res98810 {
    u8 pad00[0x3C];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;               /* bit 2 of +0x3C */
    u8 f3 : 5;
    u8 pad3D[0x13];
    void *m50;               /* +0x50 */
} Res98810;

typedef struct Buf98810 {
    u8 d[0x70];
} Buf98810;

extern void *GetDrawCtx_15de80(void);
extern void MemStackAlign64_14d8e0(void *);
extern void *GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(void *, s32);
extern Res98810 *NameTableAddEntry_159b70(void *, s32, void *, s32, s32, s32, s32, s32,
                              s32, s32);
extern void MemStackAllocQw_14d950(void *, s32);
extern void NameTableNodeCtor_15ae50(Buf98810 *);
extern void DrawEnvGetFrameTexDesc_144cc0(void *, Buf98810 *);
extern void GsDownloadImage_140f20(void *, Buf98810 *, u8 *);

extern Hnd98810 *D_0048233C;
extern Res98810 *D_00482414;
extern void *D_00482418;
extern u8 D_00461240[];

void MenuCaptureScreenTex_298810(void)
{
    Buf98810 buf;
    void *v;
    u8 *dst;
    void *w;
    Hnd98810 *h;
    u8 *src;
    s32 r;
    s32 g;
    s32 bl;
    s32 x;
    s32 y;
    u8 *q;
    s32 c2;
    s32 c1;
    s32 c0;

    v = GetDrawCtx_15de80();
    h = D_0048233C;
    MemStackAlign64_14d8e0(h);
    dst = h->m28 + (h->m2C << 4);
    D_00482418 = dst;
    w = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(w, 0x32D);
    NameTableFreeGroup_158ac0(w, 0x32D);
    D_00482414 = NameTableAddEntry_159b70(w, 0x32D, D_00461240, 0, 0x100, 0x100, 0x20,
                              0, 0, 0);
    if (D_00482414 != 0) {
        D_00482414->f2 = 0;
        D_00482414->m50 = dst;
        MemStackAllocQw_14d950(h, 0x4001);
    }
    NameTableNodeCtor_15ae50(&buf);
    DrawEnvGetFrameTexDesc_144cc0(v, &buf);
    MemStackAlign64_14d8e0(h);
    src = h->m28 + (h->m2C << 4);
    GsDownloadImage_140f20(v, &buf, src);
    src = src + 0x35000;
    y = 0;
    r = 0;
    g = 0;
    bl = 0;
    while (y < 0x100) {
        q = src + 0x2FC;
        for (x = 0; x < 0x100; x++) {
            c1 = q[1];
            c2 = q[2];
            c0 = q[0];
            dst[0] = r + c0;
            dst[1] = g + c1;
            dst[2] = bl + c2;
            dst[3] = 0x80;
            q += 4;
            dst += 4;
        }
        y++;
        src += 0x800;
    }
}
