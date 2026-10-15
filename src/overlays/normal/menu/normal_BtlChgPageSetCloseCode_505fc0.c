#include "types.h"
typedef struct Obj { u8 pad00[0x72]; s8 f72; } Obj;
extern s32 normal_BtlChgPageSetCloseCode_505fc0(Obj *p, s8 v);
s32 normal_BtlChgPageSetCloseCode_505fc0(Obj *p, s8 v) { p->f72 = v; return 1; }
