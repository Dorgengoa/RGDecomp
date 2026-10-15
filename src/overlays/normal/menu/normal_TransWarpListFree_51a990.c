#include "types.h"
/* normal 0x0051A990 -- clears the shop's pending-confirm word. */
extern void *D_00484870;          /* gp - 0x900 */
extern void normal_TransWarpListFree_51a990(void);
void normal_TransWarpListFree_51a990(void)
{
    D_00484870 = 0;
}
