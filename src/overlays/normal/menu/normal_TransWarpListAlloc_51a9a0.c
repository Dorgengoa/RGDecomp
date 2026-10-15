#include "types.h"
/* normal 0x0051A9A0 -- allocates the shop's 0xC00 work buffer. */
extern void *D_00484870;          /* gp - 0x900 */
extern void *func_14E1B0(s32 size, void *heap);
extern void normal_TransWarpListAlloc_51a9a0(void *heap);
void normal_TransWarpListAlloc_51a9a0(void *heap)
{
    D_00484870 = func_14E1B0(0xC00, heap);
}
