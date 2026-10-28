/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetField74Related_506b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x74]; s32 f74; } Obj;
extern s32 normal_LeaderHudSetField74Related_506b60(Obj *p, s32 v);
s32 normal_LeaderHudSetField74Related_506b60(Obj *p, s32 v) { p->f74 = v; return 1; }
