#include "types.h"

extern void TexAnimKeyInit_164080(void *);
extern void ConstructArray_100620(void *, void *, void *, s32, s32);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern u8 D_00495E70[];
extern u8 D_00495FB0[];
extern u8 D_0049B100[];
extern u8 D_0049D0B0[];
extern u8 D_004811D0;
extern s32 D_00481310;
extern void CdDirTableCtor_183780(void);
extern void CdDirTableDtor_183720(void);
extern void CdDirTablesDtor_183700(void);
extern void FileSlotCtor_1836d0(void);
extern void TexPairCtor_18fb70(void);

void StaticInitTexAnimeCfg_4693a0(void) {
    TexAnimKeyInit_164080(D_00495E70);
}

void func_004693B0(void) {
    ConstructArray_100620(D_00495FB0, CdDirTableCtor_183780, CdDirTableDtor_183720, 0xC, 2);
    RegisterGlobalObject_100dc0(0, CdDirTablesDtor_183700, &D_004811D0);
    ConstructArray_100620(D_0049B100, FileSlotCtor_1836d0, 0, 0x7C, 0xC);
}

void func_00469420(void) {
    ConstructArray_100620(D_0049D0B0, TexPairCtor_18fb70, 0, 0x5C, 8);
}

void func_00469440(void) {
    D_00481310 = 0;
}
