/* rgp:protos */
#define RGP_SELF_normal_TransWarpListAlloc_51a9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051A9A0 -- allocates the shop's 0xC00 work buffer. */
extern void *D_00484870;          /* gp - 0x900 */
/*rgp*/
extern void normal_TransWarpListAlloc_51a9a0(void *heap);
void normal_TransWarpListAlloc_51a9a0(void *heap)
{
    D_00484870 = MemStackNew_14e1b0(0xC00, heap);
}
