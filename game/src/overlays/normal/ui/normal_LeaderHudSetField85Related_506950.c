/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetField85Related_506950 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x85]; s8 f85; } Obj;
extern s32 normal_LeaderHudSetField85Related_506950(Obj *p, s8 v);
s32 normal_LeaderHudSetField85Related_506950(Obj *p, s8 v) { p->f85 = v; return 1; }
