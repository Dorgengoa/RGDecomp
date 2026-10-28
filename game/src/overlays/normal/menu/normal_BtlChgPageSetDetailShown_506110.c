/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetDetailShown_506110 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x70]; s8 f70; } Obj;
extern s32 normal_BtlChgPageSetDetailShown_506110(Obj *p, s8 v);
s32 normal_BtlChgPageSetDetailShown_506110(Obj *p, s8 v) { p->f70 = v; return 0; }
