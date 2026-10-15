#include "types.h"
/* normal 0x00518370 -- teardown list, `return 0`. */

extern void *D_00484788;          /* gp - 0x9E8  */
extern void *D_004802A4;          /* gp - 0x4ECC */

extern void  func_28B160(void *w, s32 a);
extern void  func_28B550(void *w, void *a, s32 b, s32 c);
extern void *func_1F59D0(void);
extern void  func_1CD670(void *a);

s32 normal_TransMenuResRequest_518370(void)
{
    func_28B160(D_00484788, 1);
    func_28B550(D_00484788, D_004802A4, 0, 0);
    func_1CD670(func_1F59D0());
    return 0;
}
