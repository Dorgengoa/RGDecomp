#include "types.h"
typedef struct Obj { u8 pad00[0x70]; s8 f70; } Obj;
extern s32 normal_LeaderHudSetField70Related_506b40(Obj *p, s8 v);
s32 normal_LeaderHudSetField70Related_506b40(Obj *p, s8 v) { p->f70 = v; return 1; }
