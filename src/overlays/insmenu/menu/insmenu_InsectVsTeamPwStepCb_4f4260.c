#include "types.h"

/* insmenu 0x004F4260 (352 bytes, 88 instructions, 13 calls) -- the map's other
 * cancel path, a near-twin of insmenu_InsectVsTeamInfoStepCb_4f43f0.  Same four-term
 * short-circuit chain against 0x20 then 0x10, same `func_2F6660` guard written
 * as a single condition (not an early return) so the shared epilogue keeps its
 * predecessors and the branch into it stays LIKELY.
 *
 * Both arms end with `D_00484360 = 0;` sunk into the `func_28EA90` delay slot.
 */

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern u8 D_00484360;       /* gp - 0xE10 */

extern s32  func_2F6660(void);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_37B490(s32 a);
extern void func_28EA90(const void *a, s32 b, s32 c);

s32 insmenu_InsectVsTeamPwStepCb_4f4260(void)
{
    if (func_2F6660() == 0) {
        if ((func_1839F0(D_004B2570, 0x20) != 0) ||
            ((func_2882C0() != 0) && (func_1839F0(D_004B27E0, 0x20) != 0))) {
            func_291110(D_004FA180, 0x9CA7, 0, 1);
            func_291110(D_004FA180, 0x9CAA, 1, 1);
            func_291110(D_004FA180, 0x88CC, 1, 1);
            func_291110(D_004FA180, 0x88E0, 1, 1);
            func_291110(D_004FA180, 0x88F4, 1, 1);
            func_37B490(0x890D);
            D_00484360 = 0;
            func_28EA90(D_004FA1A0, 0x88BD, 0);
        } else if ((func_1839F0(D_004B2570, 0x10) != 0) ||
                   ((func_2882C0() != 0) && (func_1839F0(D_004B27E0, 0x10) != 0))) {
            D_00484360 = 0;
            func_28EA90(D_004FA1A0, 0x88C0, 0);
        }
    }
    return 1;
}
