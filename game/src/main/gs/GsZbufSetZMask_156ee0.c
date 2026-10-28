/* rgp:protos */
#define RGP_SELF_GsZbufSetZMask_156ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct {u8 pad[0x34];u8 flag:1;u8 other:7;}Obj;
void GsZbufSetZMask_156ee0(Obj*p,s32 v){switch(v){case 1:p->flag=1;break;case 0:default:p->flag=0;break;}}
