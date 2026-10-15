#include "types.h"
/* normal 0x00521160 -- near-twin of normal_ShopMenuShutdown_50a630, different globals. */
extern const u8 D_004B2570[];
extern void normal_ThinkMenuResFree_5217b0(void);
extern void func_183960(const void *a);
extern void func_183940(const void *a);
extern void *func_206A40(void);
extern void func_42B650(void *a, s32 b);
extern s32 D_00484934;
extern u8  D_00480788;
extern u8  D_0048493C;
extern u8  D_00484938;
extern u8  D_00484940;

void normal_ThinkMenuShutdown_521160(void)
{
    normal_ThinkMenuResFree_5217b0();
    func_183960(D_004B2570);
    func_183940(D_004B2570);
    func_42B650(func_206A40(), 2);
    D_00484934 = 0;
    D_00480788 = 1;
    D_0048493C = 0;
    D_00484938 = 0;
    D_00484940 = 0;
}
