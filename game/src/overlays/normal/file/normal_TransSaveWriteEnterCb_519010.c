/* rgp:protos */
#define RGP_SELF_normal_TransSaveWriteEnterCb_519010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519010 -- `sh $0, -0x958($28) / jr $31 / addiu $2, $0, 0x1`.
 * The return constant lands in the `jr`'s delay slot after the gp store.
 * One of the 55 unnamed functions. */
extern s16 D_00484818;

s32 normal_TransSaveWriteEnterCb_519010(void)
{
    D_00484818 = 0;
    return 1;
}
