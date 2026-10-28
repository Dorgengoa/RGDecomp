/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetMember_505fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Obj { u8 pad00[0x68]; s32 f68; } Obj;
extern s32 normal_BtlChgPageSetMember_505fa0(Obj *p, s32 v);
s32 normal_BtlChgPageSetMember_505fa0(Obj *p, s32 v) { p->f68 = v; return 1; }
