#include "types.h"

/* factory.bin overlay, 0x004F16B0 -- shut the factory module down: drop the
 * live job handle, mute the HUD loop, and reset the two panels plus the
 * message window to their idle state.
 * 296 bytes, 70 instructions, 2 conditional branches, 14 calls -- the
 * branch-light LIST band, the same shape as factory_FUN_004EFD30.
 *
 * * `lw $3, 0x7C($4)` / `beq $3, $2` with $2 = -1 branches PAST the two
 * calls, so retail FALLS THROUGH into them: the body is the source's
 * `if (o->f7C != -1)` arm, not an early return.
 *
 * * Retail RE-READS `lw $5, 0x7C($16)` AFTER the jal, so func_1F59D0()'s
 * result is a NAMED LOCAL and the field read is a separate statement's
 * argument; nested as `func_1CD340(func_1F59D0(), o->f7C)` mwcc evaluates the
 * field first, CSEs it with the guard's load and burns a second callee-saved
 * register holding `o` -- 2 words long and 8 wrong.
 *
 * * The second guard is factory_FUN_004EC090's block verbatim -- `lw $4`
 * before the `beqz` and a bare `nop` in the `jal`'s delay slot -- so the
 * global is spelled at BOTH places and is not hoisted into a local.
 *
 * * D_00484A30 (_gp - 0x740) and D_004807E8 (_gp - 0x4988) are both inside
 * the small-data window (_gp = 0x00485170) and stay plain 4-byte externs.
 *
 * * The tail's three constants are `lui` + `mtc1` INLINE, not pool loads:
 * their low halves are zero (main pass 34 section 7), so they are written as
 * plain literals 1.0f / 0.125f / -1.0f -- the same triple every other
 * func_290690 site in this overlay passes.
 */

typedef struct Mod {
    u8    pad00[0x70];
    u8    f70;
    u8    pad71[0xB];
    s32   f7C;
    s32   f80;
    u8    pad84[0x4];
    void *f88;
    void *f8C;
} Mod;

extern void *D_00484A30;                        /* _gp - 0x740  */
extern void *D_004807E8;                        /* _gp - 0x4988 */

extern void  func_14D830(void *p);
extern s32   func_15DE40(void);
extern void  func_158AC0(s32 h, s32 id);
extern void  func_1CD340(s32 h, s32 k);
extern s32   func_1F59D0(void);
extern void  func_28EA90(void *ctx, s32 id, s32 a);
extern void  func_290010(void *w, u16 id, s32 a, s32 b);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void  func_2907A0(void *w, s32 id, f32 t);
extern void  func_290AC0(void *w, s32 id, s32 a);

void factory_FactoryHelpPageClose_4f16b0(Mod *o)
{
    s32 h;

    if (o->f7C != -1) {
        h = func_1F59D0();
        func_1CD340(h, o->f7C);
    }
    o->f7C = -1;
    o->f80 = 0;
    if (D_00484A30 != 0) {
        func_14D830(D_00484A30);
    }
    func_158AC0(func_15DE40(), 0x32E);
    func_290010(o->f88, 0x84, 0, -1);
    func_290010(o->f88, 0x85, 0, -1);
    func_290AC0(o->f88, 0x84, 0);
    func_290AC0(o->f88, 0x85, 0);
    func_290010(D_004807E8, 0x96, 0, -1);
    func_28EA90(o->f8C, 0x8944, 0);
    o->f70 = 0;
    func_2907A0(o->f88, 0x84, 0.0f);
    func_2907A0(o->f88, 0x85, 0.0f);
    func_290690(o->f88, 0x7C, 1.0f, 0.125f, -1.0f);
}
