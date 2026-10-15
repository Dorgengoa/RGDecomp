#include "types.h"
extern s32 PartyCountMembers_3c2010(void*,s32,s32);
typedef struct{u8 pad[0x190];s16 a[3];s16 b[7];} Obj;
s32 PartyGetSlotId_3c3120(Obj*p,s32 i){if(i<0||i>=10)return -1;{s32 t=PartyCountMembers_3c2010(p,1,1);if(i<t)return p->a[i];if(i<t+7)return p->b[i-t];return -1;}}
