#include "types.h"
/* insect 0x0051D0B0 -- 276 B / 69 words.  SEED of the func_134A98 loader
 * family (grep -l 'func_134A98' over the insect listings).
 *
 * The family guard, transcribed from the already-matching
 * insect_InsectBattleHelpStep_50a9f0.c, is verbatim:
 *
 *     if (func_134BB0(NAME) < 0x10) { func_134A98(obj, NAME); }
 *
 * with `extern u32 func_134BB0(const char *)` -- the UNSIGNED return is what
 * makes the compare a `sltiu $1,$2,0x10`, and the `beql` past the call is the
 * if-body fall-through.  The object handed to func_134A98 is whatever the
 * NEXT call also takes, because retail parks it in the beql delay slot.
 *
 * The 0x830-byte local is the func_42Fxxx script VM frame already settled by
 * insect_InsectLiveTalkTableLoad_523540.c (RecVm raw[0x830]); the ctor/bind/arm/run quartet and
 * the "publish the context pointer through the gp global across the run call
 * only" idiom are copied from that unit.  D_00485170 is _gp+0x0 and is a
 * Ctx * (settled by insect_InsectAbilityTableCmdNextRecord_51c900.c). */

typedef struct Ctx {
    u8  pad00[0x58];
    s32 m58;                    /* +0x58 */
    u8  pad5C[0x64 - 0x5C];
    s32 m64;                    /* +0x64 */
    s32 m68;                    /* +0x68 */
} Ctx;

typedef struct RecVm { u8 raw[0x830]; } RecVm;

extern Ctx *D_00485170;

extern const u8   D_005244F0[];
extern const char D_005253F8[];

extern void  insect_InsectAbilityTableClear_51d1d0(Ctx *a);

extern void  func_1C6D50(void *h);
extern void  func_1C6CF0(void *h);
extern void  func_1C6C80(void *h);
extern s32   func_14DB10(void *h, s32 b, s32 c, s32 d);
extern void *func_14D950(void *h, s32 n);
extern void  func_14DEE0(Ctx *a, void *p, s32 n);
extern void  func_14DE90(Ctx *a);
extern void  func_14DAD0(void *h);
extern void  func_134A98(Ctx *a, const char *t);
extern u32   func_134BB0(const char *t);
extern void  func_42FC10(RecVm *vm);
extern void  func_42FB00(RecVm *vm, const u8 *cmds);
extern void  func_42FAC0(RecVm *vm, s32 b, s32 c);
extern void  func_42FA20(RecVm *vm);

void insect_InsectAbilityTableLoad_51d0b0(Ctx *a, s32 b, s32 c, void *h)
{
    RecVm vm;

    insect_InsectAbilityTableClear_51d1d0(a);
    if (h != 0) {
        func_1C6D50(h);
        func_1C6CF0(h);
        func_1C6C80(h);
        func_14DB10(h, 2, 0, 0x40);
        func_14DEE0(a, func_14D950(h, 0xC0), 0xC0);
        if (func_134BB0(D_005253F8) < 0x10) {
            func_134A98(a, D_005253F8);
        }
        func_14DE90(a);
        func_14DAD0(h);
        func_42FC10(&vm);
        func_42FB00(&vm, D_005244F0);
        func_42FAC0(&vm, b, c);
        D_00485170 = a;
        func_42FA20(&vm);
        D_00485170 = 0;
        a->m64 = 0;
        a->m68 = 0;
    }
}
