#include "types.h"

extern void func_4F19E0(const u8 *);
extern void func_4F6F00(const u8 *);
extern void func_4F6F50(const u8 *);
extern void func_4FAAC0(u8 *);
extern void func_506B70(const u8 *, s32);
extern void func_506C10(const u8 *);
extern void func_506D80(const u8 *);
extern void func_506DC0(const u8 *, u8 *);
extern void func_509040(s32, s32, s32);

extern s32 D_00481C5C;
extern u8 D_004BBC80[];
extern const u8 D_004BC250[];
extern const u8 D_00527020[];

void FieldHudInitOnce_204120(void)
{
    if (D_00481C5C == 0) {
        func_4F6F50(D_00527020);
        func_4F6F00(D_00527020);
        func_4F19E0(D_00527020);
        func_506DC0(D_004BC250, D_004BBC80);
        func_506D80(D_004BC250);
        func_506B70(D_004BC250, 0x59D9);
        func_506C10(D_004BC250);
        func_509040(1, 0, 1);
        func_4FAAC0(D_004BBC80);
        D_00481C5C = 1;
    }
    *(s8 *)0x5273CE = 1;
}
