#include "types.h"
typedef struct Obj { u8 pad00[0x71]; s8 f71; } Obj;
extern s32 normal_BtlChgPageSetCommand_505da0(Obj *p, s8 v);
s32 normal_BtlChgPageSetCommand_505da0(Obj *p, s8 v) { p->f71 = v; return 1; }
