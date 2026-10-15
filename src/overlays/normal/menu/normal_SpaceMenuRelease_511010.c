#include "types.h"
/* normal 0x00511010 -- teardown/close of the 0x4B2570 sub-scene. */

extern u8    D_00480674;          /* gp - 0x4AFC */
extern s32   D_00480670;          /* gp - 0x4B00 */
extern void *D_004846B0;          /* gp - 0xAC0  */
extern s32   D_004846B4;          /* gp - 0xABC  */
extern s32   D_004846B8;          /* gp - 0xAB8  */
extern u8    D_004B2570[];

extern void  func_14D830(void *p);
extern void *func_1F59D0(void);
extern void  func_1CD340(void *p, s32 id);
extern void  func_183960(u8 *p);
extern void  func_183940(u8 *p);
extern void *func_206A40(void);
extern void  func_42B650(void *p, s32 a);

s32 normal_SpaceMenuRelease_511010(void)
{
    void *w;

    if (D_004846B8 != 0) {
        D_004846B8 = 0;
    }
    if (D_004846B4 != 0) {
        D_004846B4 = 0;
    }
    if (D_004846B0 != 0) {
        func_14D830(D_004846B0);
    }
    w = func_1F59D0();
    if (D_00480674 != 0 && D_00480670 != -1) {
        func_1CD340(w, D_00480670);
        D_00480674 = 0;
        D_00480670 = -1;
    }
    func_183960(D_004B2570);
    func_183940(D_004B2570);
    func_42B650(func_206A40(), 2);
    return 1;
}
