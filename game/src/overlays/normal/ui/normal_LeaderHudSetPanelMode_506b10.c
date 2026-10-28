/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetPanelMode_506b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x72]; s8 f72; } Obj;
extern s32 normal_LeaderHudSetPanelMode_506b10(Obj *p, s8 v);
s32 normal_LeaderHudSetPanelMode_506b10(Obj *p, s8 v) { p->f72 = v; return 1; }
