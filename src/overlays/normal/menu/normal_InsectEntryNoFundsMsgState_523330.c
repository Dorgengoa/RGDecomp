#include "types.h"
/* normal 0x00523330 -- optional 0x7532 push, then the 0x4B2570 text-device
 * open/close pair; the `sltiu $1,$2,2` tail is the two-value range test on
 * the open's result. */

extern const u8 D_005281C0[];
extern const u8 D_004B2570[];

extern s32 D_004849A8;            /* gp - 0x7C8 */

extern void func_28EA90(const u8 *w, s32 id, s32 a);
extern s32  func_28E170(const u8 *w, const u8 *p, s32 a, s32 b);
extern void func_28EC60(const u8 *w);
extern void func_28EDE0(void *w, s32 id, s32 a);

s32 normal_InsectEntryNoFundsMsgState_523330(void *a, s32 b)
{
    s32 r;

    if (b != 0) {
        func_28EA90(D_005281C0, 0x7532, 1);
    }
    r = func_28E170(D_005281C0, D_004B2570, 0, 0);
    func_28EC60(D_005281C0);
    if (r == 1 || r == 2) {
        func_28EDE0(&D_004849A8, 0x7536, 1);
    }
    return 1;
}
