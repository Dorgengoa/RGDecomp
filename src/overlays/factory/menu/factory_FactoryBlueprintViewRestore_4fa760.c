#include "types.h"

/* factory.bin overlay, 0x004FA760 -- widget setup for one dialog page.
 *
 * The object pointer is the PARAMETER and `o->f80` is spelled out at every one
 * of the twelve call sites: retail re-issues `lw $4, 0x80($16)` each time, and
 * mwcc's per-basic-block CSE reproduces that for free because every use is
 * separated by a call.  (`levers.d/factory-count-the-gp-loads.md`.)
 *
 * ★ `func_28F670`'s arguments 5 and 6 repeat arguments 3 and 4, so retail emits
 * `daddu $8, $6, $0` / `daddu $9, $7, $0` rather than fresh `addiu`s.  Write the
 * literals out plainly and let mwcc share them -- an argument that is not
 * materialised in its own instruction is not a missing one.
 */

typedef struct Page {
    u8    pad0[0x80];
    void *f80;
} Page;

extern void *D_00484A70;                        /* _gp - 0x700 */

extern void  func_28F670(void *w, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  func_291110(void *w, s32 id, s32 a, s32 b);
extern void  func_28F510(void *w, s32 id, s32 a, s32 b);
extern s32   func_28AA30(void *ctx, s32 id);

void factory_FactoryBlueprintViewRestore_4fa760(Page *o)
{
    func_28F670(o->f80, 0x3C, 0xA, 6, 0xA, 6, 0xC);
    func_28F670(o->f80, 0x3C, 0x196, 6, 8, 6, 0xD);
    func_28F670(o->f80, 0x3C, 0xA, 6, 0xA, 6, 0xE);
    func_290010(o->f80, 0x28, 1, -1);
    func_291110(o->f80, 0x29, 1, 1);
    func_291110(o->f80, 0x23, 1, 1);
    func_291110(o->f80, 0x40, 1, 1);
    func_291110(o->f80, 0x26, 1, 1);
    func_290010(o->f80, 0x3D, 1, -1);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 2), 2);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 3), 3);
    func_28F510(o->f80, 0x39, func_28AA30(D_00484A70, 4), 5);
}
