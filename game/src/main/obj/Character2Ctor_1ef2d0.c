/* rgp:protos */
#define RGP_SELF_Character2Ctor_1ef2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern u8 D_00470FB0[],D_00470F50[];
/*rgp*//*rgp*//*rgp*//*rgp*//*rgp*//*rgp*//*rgp*//*rgp*//*rgp*/
u8*Character2Ctor_1ef2d0(u8*p, int rgp_a1, int rgp_a2, int rgp_a3){u8*q;ModelObjCtor_1ef500(p, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);*(void**)(p+0x1b0)=D_00470FB0;ModelObjExParamBlockCtorMaybe_1ef490(p+0x4f0);ModelObjExMemberCtorZero3Related_1ef470(p+0x548);q=p+0x558;do{ModelObjExMemberCtorTrivialRelated_1ef460(q);q+=4;}while(q<p+0x568);MotionEventListCtor_1ef430(p+0x568);MotionEventSeHandlerCtor_1ef400(p+0x570);MotionEventFootSeHandlerCtor_1ef3d0(p+0x578);MotionEventTexAnimeHandlerCtor_1ef3a0(p+0x580);MotionEventEffectHandlerCtor_1ef370(p+0x588);*(void**)(p+0x1b0)=D_00470F50;return p;}
