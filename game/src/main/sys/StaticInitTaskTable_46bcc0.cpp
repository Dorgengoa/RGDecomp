/* rgp:protos */
#line 1
#include "types.h"
class Obj { public: u8 pad[0x2C]; VC_VPTR_MEMBER; int init() { return VCM0(int, 0x8); } };
extern "C" {
extern s32 D_004821A4,D_00482198,D_004821B4,D_004821A8;
extern u8 D_004D8AA0[],D_004713E0[];
extern u8 D_004DAE60[0x100];
extern void *D_004DAE8C[0x100];
void RegisterGlobalObject_100dc0(void *,void *,void *);
void IosBaseInitCtor_102bd0(void *), WIosBaseInitCtor_103110(void *);
void IosBaseInitDtor_102ee0(),WIosBaseInitDtor_103420(),DebugTaskItemCtor_288440();
void ConstructArray_100620(void *,void *,s32,s32,s32);
int StaticInitTaskTable_46bcc0(){ int rgp_v0;
 IosBaseInitCtor_102bd0(&D_004821A4);
 RegisterGlobalObject_100dc0(&D_004821A4,(void *)IosBaseInitDtor_102ee0,&D_00482198);
 WIosBaseInitCtor_103110(&D_004821B4);
 RegisterGlobalObject_100dc0(&D_004821B4,(void *)WIosBaseInitDtor_103420,&D_004821A8);
 ConstructArray_100620(D_004D8AA0,(void *)DebugTaskItemCtor_288440,0,0x34,0xB0);
 D_004DAE8C[0]=D_004713E0;
 rgp_v0 = ((Obj *)D_004DAE60)->init();
return rgp_v0; }
}
