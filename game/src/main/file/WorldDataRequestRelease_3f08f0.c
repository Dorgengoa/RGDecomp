/* rgp:protos */
#define RGP_SELF_WorldDataRequestRelease_3f08f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
typedef struct {s16 a,b,c; s16 pad; s32 h;} P;
s32 WorldDataRequestRelease_3f08f0(u8 *self) { P *p=*(P **)(self+0x28); s32 g;
if(p==0)return 0;
g=((s32)GetLoaderMgr_1f59d0()); if(g==0)return 0;
if(p->h>=0)LoaderReleaseById_1cd340(g,p->h);
p->h=-1;p->c=0;p->b=0;p->a=-1;return 1;}
