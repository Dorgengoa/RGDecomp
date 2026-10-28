/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_DmaPktAddCallTagIfSet_141bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;typedef struct {u8 pad[4];u8*p;}Obj;extern u128 D_0047DE40 __attribute__((section(".sdata")));
void *DmaPktAddCallTagIfSet_141bb0(Obj*s,s32 v){if(!v)return 0;*(u128*)s->p=D_0047DE40;*(u32*)(s->p+4)=(v);s->p+=16;return s->p;}
