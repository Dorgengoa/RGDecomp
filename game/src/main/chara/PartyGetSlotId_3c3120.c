/* rgp:protos */
#define RGP_SELF_PartyGetSlotId_3c3120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
typedef struct{u8 pad[0x190];s16 a[3];s16 b[7];} Obj;
s32 PartyGetSlotId_3c3120(Obj*p,s32 i){if(i<0||i>=10)return -1;{s32 t=PartyCountMembers_3c2010(p,1,1);if(i<t)return p->a[i];if(i<t+7)return p->b[i-t];return -1;}}
