/* rgp:protos */
#define RGP_SELF_EffRandParamParse_19a3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern s32 strcmp(s32, void *);
extern u8 D_0045A050[], D_0045A058[];
struct Obj0 {s32 m00; f32 m04,m08;};
void EffRandParamParse_19a3d0(struct Obj0 *p0,s32 p1,f32 fa0,f32 fa1) {s32 x,r;
if (p1 == 0) x=0; else if (strcmp(p1,D_0045A050)==0) x=1; else if (strcmp(p1,D_0045A058)==0) x=2; else x=0;
p0->m00=x;p0->m04=fa0;p0->m08=fa1;
}
