#include "types.h"
typedef struct Obj { u8 pad00[0x90]; s32 f90; } Obj;
extern s32 normal_LeaderHudSetField90Related_506940(Obj *p, s32 v);
s32 normal_LeaderHudSetField90Related_506940(Obj *p, s32 v) { p->f90 = v; return 0; }
