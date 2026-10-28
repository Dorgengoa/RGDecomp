/* rgp:protos */
#define RGP_SELF_normal_LeaderHudDeactivate_506d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506D70 -- clears the list's dirty flag and its row counter. */
typedef struct Obj { u8 pad00[0x5C]; s8 f5C; u8 pad5D[0xA6 - 0x5D]; s16 fA6; } Obj;
extern s32 normal_LeaderHudDeactivate_506d70(Obj *p);
s32 normal_LeaderHudDeactivate_506d70(Obj *p)
{
    p->f5C = 0;
    p->fA6 = 0;
    return 1;
}
