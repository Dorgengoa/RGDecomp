/* rg-override: replaces game/src/main/file/SaveModeDispatch_375df0.cpp sha256 a56e82e248aeac4ca9153435f07b57d07399c9fe1bae4cbb26fe30dd6705e712
 * why: the only pointer-to-member-function call in the corpus.  mwcc's PMF
 *      is 12 bytes {this delta, vtable offset (-1 = not virtual), function};
 *      D_00463840 is a table of them (StaticInitSaveSys_46d9f0 copies the
 *      constants from D_0047F9F8..), and retail calls PtmfScall_100e70 (an
 *      excluded asm unit) with $25 = &D_00463840[idx * 12].  clang's MSVC-ABI
 *      PMF for this class is a 4-byte function pointer, so `arg0->*tab[idx]`
 *      indexed the table with the wrong stride and called word 0 (a null
 *      delta) -> EIP 0 at the title's memory-card check (docs/BRINGUP.md).
 *      Spelled as PtmfScall does it. */
#include "types.h"

class C375 {
public:
    u8 pad0[0x4DC];
    s32 m4DC;
    s32 m4E0;
};

extern "C" {
extern u8 D_00463840[];
extern void McSetErrorResult_375890(C375 *, s32);
extern void SaveSetMode_375a10(C375 *, s32);
extern void abort(void);

/* PtmfScall_100e70: $4 += delta; virtual (vtbl >= 0): fn = *(*(this + fn) + vtbl) */
static s32 rg_ptmf_scall(C375 *self, const u8 *pmf)
{
    const s32 *e = (const s32 *)pmf;
    u8 *t = (u8 *)self + e[0];
    void *fn;
    if (e[1] < 0) {
        fn = (void *)(u32)e[2];
    } else {
        abort(); /* virtual PMF: no table in the corpus uses one */
        fn = 0;
    }
    return ((s32(*)(void *))fn)(t);
}

s32 SaveModeDispatch_375df0(C375 *arg0) {
    s32 idx;
    s32 t;
    s32 r;

    idx = arg0->m4DC;
    r = 0;
    if (idx >= 0) {
        t = rg_ptmf_scall(arg0, D_00463840 + idx * 12);
        if (t == 1) {
            arg0->m4E0 = 0;
            SaveSetMode_375a10(arg0, 1);
        } else if (t != 0) {
            McSetErrorResult_375890(arg0, t);
        }
    }
    if (idx != arg0->m4DC) {
        r = 1;
    }
    return r;
}
}
