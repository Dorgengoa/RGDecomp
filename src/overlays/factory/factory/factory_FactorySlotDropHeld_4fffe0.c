#include "types.h"

/* factory.bin overlay, 0x004FFFE0 -- commit the piece the player is dragging:
 * take a free block, copy the staging block into it, register its ghost and,
 * when there is a ghost to key, record the grid coordinates.
 * 264 bytes, 68 instructions, 3 conditional branches, 6 calls.
 *
 * * `(s32)x` is spelled at THREE sites and retail recomputes `cvt.w.s` at each
 * one -- naming it in a local would hoist it into a callee-saved FPR and lose
 * two words.  ÃƒÆ’Ã‚Â¢Ãƒâ€¦Ã‚Â¡Ãƒâ€šÃ‚Â  objdump renders `cvt.w.s` as `trunc.w.s` and the reference
 * listing as a bare `.word`; the ENCODING 0x46000024 is identical and
 * `f_odiff` reporting it as a mismatch is the recorded false alarm.
 *
 * * `D_0045B080` is hoisted into `$f22` across both calls by -O4; it is spelled
 * once, where it is used.
 */

typedef struct Blk {
    u8  pad00[0x8];
    s16 f08;
    s16 f0A;
    s16 f0C;
    u8  pad0E[0x32];
} Blk;                                          /* 0x40 */

typedef struct Panel {
    u8  pad000[0x1F0];
    Blk f1F0;
    u8  f230;
} Panel;

extern f32 D_0045B080[];

extern Blk *factory_FactorySlotFindFree_503630(Panel *o);
extern f32  factory_FactoryGridCellCenterX_503760(Panel *o, s32 i);
extern s32  factory_FactoryMarkerAddFromSaved_4ea130(void *h, f32 x, f32 y, f32 z);
extern void func_1319A8(void *dst, const void *src, s32 n);

s32 factory_FactorySlotDropHeld_4fffe0(Panel *o, void *h, f32 x, f32 y)
{
    Blk *b;
    f32  gx;
    f32  k;
    f32  gy;

    if (o->f230 == 0) {
        return 0;
    }
    o->f230 = 0;
    b = factory_FactorySlotFindFree_503630(o);
    if (b == 0) {
        return 0;
    }
    gx = factory_FactoryGridCellCenterX_503760(o, (s32)x);
    k = D_0045B080[0];
    gy = factory_FactoryGridCellCenterX_503760(o, (s32)y);
    func_1319A8(b, &o->f1F0, 0x40);
    b->f08 = factory_FactoryMarkerAddFromSaved_4ea130(h, gx, k, gy);
    if (h != 0) {
        b->f0A = x;
        b->f0C = y;
    }
    return 1;
}
