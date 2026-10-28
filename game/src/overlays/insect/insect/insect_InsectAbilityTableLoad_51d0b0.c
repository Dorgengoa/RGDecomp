/* rgp:protos */
#define RGP_SELF_insect_InsectAbilityTableLoad_51d0b0 1
#include "port/game_protos.h"
#line 1
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

extern u8   insect_D_005244F0[];
extern char insect_D_005253F8[];

/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  strcpy(Ctx *a, const char *t);
extern u32   strlen(const char *t);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectAbilityTableLoad_51d0b0(Ctx *a, s32 b, s32 c, void *h)
{
    RecVm vm __attribute__((aligned(16)));

    insect_InsectAbilityTableClear_51d1d0(a);
    if (h != 0) {
        MemStackGetFree_1c6d50(h);
        MemStackGetUsed_1c6cf0(h);
        MemStackGetSize_1c6c80(h);
        MemStackHeapAlloc_14db10(h, 2, 0, 0x40);
        MemStackHeapInit_14dee0(a, MemStackAllocQw_14d950(h, 0xC0), 0xC0);
        if (strlen(insect_D_005253F8) < 0x10) {
            strcpy(a, insect_D_005253F8);
        }
        MemStackHeapReinit_14de90(a);
        MemStackReturnToOwnerMaybe_14dad0(h);
        CfgVmReset_42fc10(&vm);
        CfgVmRegisterCmds_42fb00(&vm, insect_D_005244F0);
        CfgVmLoad_42fac0(&vm, b, c);
        D_00485170 = a;
        CfgVmRun_42fa20(&vm);
        D_00485170 = 0;
        a->m64 = 0;
        a->m68 = 0;
    }
}
