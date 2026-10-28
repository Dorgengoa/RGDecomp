/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetAbilityReq_5052f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005052F0 -- stores the popup's two callback words, returns 0. */
typedef struct Obj { u8 pad000[0x444]; s32 f444; s32 f448; } Obj;
extern s32 normal_BtlChgPageSetAbilityReq_5052f0(Obj *p, s32 a, s32 b);
s32 normal_BtlChgPageSetAbilityReq_5052f0(Obj *p, s32 a, s32 b)
{
    p->f444 = a;
    p->f448 = b;
    return 0;
}
