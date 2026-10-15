#include "types.h"
typedef struct Obj { u8 pad00[0x74]; s32 f74; } Obj;
extern s32 normal_LeaderHudGetField74Related_506b50(Obj *p);
s32 normal_LeaderHudGetField74Related_506b50(Obj *p) { return p->f74; }
