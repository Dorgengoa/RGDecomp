/* rg-missing: MainSinit_469180, MainSinit_469190 (retail MAIN 0x00469180 size 0x10,
 * 0x00469190 size 0x170)
 * why: the first two entries of MAIN's static-constructor table D_0046F9C0
 * (RunStaticCtors_100df0 from MainStaticInit_100580) are compiler __sinit
 * bodies that live as MIPS words inside the .rodata object D_00469140 (+0x40,
 * +0x50); the snapshot has no C for them (data2c symbolised the table words as
 * data pointers).  Ported from the retail words (disassembled from
 * D_00469140); the datareloc stage points the table at these names.
 * Checked: every callee/argument against config/main.symbols.txt and
 * game_protos.h; loop bounds 0x4918C0..0x491980 step 0x60 (2 MemStacks + the
 * third at 0x491980), 0x4927E0..0x494F60 step 0x4F0 (8 CameraRecs).
 * All 0x0049xxxx addresses are MAIN .bss (data2c_main_bss + (a - 0x481080)). */
#include "types.h"

extern unsigned char data2c_main_bss[];
#define BSS(a) ((void *)(data2c_main_bss + ((a) - 0x00481080u)))

void *VuMicrocodeTableInitMaybe_152830(void *);
void *MemStackCtor_14e030(void *);
void *GsPktCtorMaybe_13fb80(void *);
void CameraRecInit_156940(void *);
void LightStateInit_156b50(void *);
void *NameTableNodeCtor_15ae50(void *);
void PlaneShadowDescInit_156a70(void *);
void ShadowMapDescInit_156a00(void *);
void *NameTableCtorMaybe_15a560(void *);
void ConstructArray_100620(void *, void *, void *, unsigned int, unsigned int);
void *memset(void *, int, unsigned int);

/* lui a0,0x49; j 0x152830; addiu a0,a0,0x1280 */
void MainSinit_469180(void)
{
    VuMicrocodeTableInitMaybe_152830(BSS(0x00491280u));
}

void MainSinit_469190(void)
{
    u32 p;
    memset(BSS(0x00491880u), 0, 0x2C);
    for (p = 0x004918C0u; p < 0x00491980u; p += 0x60)
        MemStackCtor_14e030(BSS(p + 8));
    MemStackCtor_14e030(BSS(0x00491980u));
    GsPktCtorMaybe_13fb80(BSS(0x004919E0u));
    for (p = 0x004927E0u; p < 0x00494F60u; p += 0x4F0)
        CameraRecInit_156940(BSS(p));
    *(s32 *)BSS(0x00494F84u) = 0;
    *(s32 *)BSS(0x00494F80u) = -1;
    LightStateInit_156b50(BSS(0x00494F80u));
    *(s32 *)BSS(0x00495138u) = 0;
    *(s32 *)BSS(0x00495134u) = 0;
    NameTableNodeCtor_15ae50(BSS(0x00495180u));
    NameTableNodeCtor_15ae50(BSS(0x004951E8u));
    NameTableNodeCtor_15ae50(BSS(0x00495260u));
    PlaneShadowDescInit_156a70(BSS(0x00495150u));
    NameTableNodeCtor_15ae50(BSS(0x00495320u));
    ShadowMapDescInit_156a00(BSS(0x00495390u));
    NameTableNodeCtor_15ae50(BSS(0x00495488u));
    NameTableCtorMaybe_15a560(BSS(0x004955E0u));
    CameraRecInit_156940(BSS(0x004957E0u));
    ConstructArray_100620(BSS(0x00495CD0u), (void *)NameTableNodeCtor_15ae50, 0, 0x68, 2);
    ConstructArray_100620(BSS(0x00495DA0u), (void *)NameTableNodeCtor_15ae50, 0, 0x68, 2);
}
