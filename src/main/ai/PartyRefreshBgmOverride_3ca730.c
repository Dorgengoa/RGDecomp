#include "types.h"
typedef struct { u8 pad[0x14]; s16 id; u8 flag:1; u8 rest:7; } Sub;
typedef struct { u8 pad[0xC]; s16 id; u8 padE[0x2C-0xE]; s16 out; u8 flag:1; u8 rest:7; u8 pad2F[0x36-0x2F]; s16 kind; } Obj;
extern s32 D_00483890;
extern Sub *WorldFindBgmEntry_3ed340(s32,s32);
s32 PartyRefreshBgmOverride_3ca730(Obj *o) { Sub *p;
 if(o->kind!=3)return 0;
 p=WorldFindBgmEntry_3ed340(D_00483890,o->id);
 if(p!=0) { o->out=p->id; o->flag=p->flag; } else { o->out=-1; o->flag=0; }
 return 1;
}
