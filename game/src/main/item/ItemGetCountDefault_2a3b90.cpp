/* rgp:protos */
#line 1
#include "types.h"
extern "C" s32 ItemPosInvalid_3d49a0(void *);
extern "C" u32 ItemGetCountDefault_2a3b90(void *rgp_a0)
{
    bool b = ((unsigned char)ItemPosInvalid_3d49a0((void *)rgp_a0));
    return (u8)(b ^ 1);
}
