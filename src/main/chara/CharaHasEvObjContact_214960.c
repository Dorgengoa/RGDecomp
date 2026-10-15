#include "types.h"
typedef struct P214960 { u8 pad000[0xB5C]; s32 mB5C; s16 mB60; } P214960;
s32 CharaHasEvObjContact_214960(P214960 *p) { return !(p->mB60 < 0) && p->mB5C != 0; }
