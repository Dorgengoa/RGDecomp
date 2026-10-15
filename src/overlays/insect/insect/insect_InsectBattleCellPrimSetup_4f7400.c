#include "types.h"
/* insect 0x004F7400 -- 292 bytes, 73 instructions.
 * Resets a widget then re-applies the bits of the mask; -1 means "leave
 * everything reset".  The first parameter is unused. */

extern void func_13E2F0(void *p, s32 k);
extern void func_13E3B0(void *p, s32 k);
extern void func_13E3D0(void *p, s32 k);
extern void func_13E3E0(void *p, s32 k);
extern void func_13E400(void *p, s32 k);
extern void func_13E430(void *p, s32 k);
extern void func_13E450(void *p, s32 k);
extern void func_13E460(void *p, s32 k);
extern void func_13E4C0(void *p, s32 k, s32 m);
extern void func_13E4D0(void *p, s32 k);
extern void func_13E4F0(void *p, s32 k);
extern void func_13E500(void *p, s32 k);

void insect_InsectBattleCellPrimSetup_4f7400(void *a, void *p, s32 mask)
{
    if (p != 0) {
        func_13E500(p, 1);
        func_13E4F0(p, 1);
        func_13E4D0(p, 1);
        func_13E4C0(p, 6, 0);
        func_13E2F0(p, 1);
        func_13E3B0(p, 1);
        func_13E460(p, 1);
        func_13E450(p, 2);
        func_13E430(p, 0);
        func_13E400(p, 1);
        func_13E3E0(p, 1);
        if (mask != -1) {
            if (mask & 1) {
                func_13E500(p, 0);
            }
            if (mask & 2) {
                func_13E4F0(p, 2);
            }
            if (mask & 4) {
                func_13E3D0(p, 0);
            }
            if (mask & 8) {
                func_13E3E0(p, 0);
            }
        }
    }
}
