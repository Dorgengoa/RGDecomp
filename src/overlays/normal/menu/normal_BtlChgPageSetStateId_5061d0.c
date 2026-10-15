#include "types.h"
typedef struct Obj { u8 pad00[0x5C]; s32 f5C; } Obj;
extern s32 normal_BtlChgPageSetStateId_5061d0(Obj *p, s32 v);
s32 normal_BtlChgPageSetStateId_5061d0(Obj *p, s32 v) { p->f5C = v; return 1; }
