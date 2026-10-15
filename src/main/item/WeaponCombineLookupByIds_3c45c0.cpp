#include "types.h"
class Obj { public:
virtual void v8();
virtual void v12();
virtual void v16();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v32();
virtual void v36();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v52();
virtual void v56();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v72();
virtual void v76();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v92();
virtual void v96();
virtual void v100();
virtual void v104();
virtual void v108();
virtual s32 get(s64);
};
extern "C" {
extern u8 *D_00483894;
s32 WeaponCombineLookup_3c4280(s32,s32,s32,s32,s32,s32,s32,s32,s64,s64,s64,s64);
void WeaponCombineLookupByIds_3c45c0(s32 a,s64 b,s32 c,s64 d,s32 e,s32 f,s32 g,s32 h,s32 i,s32 j,s32 k,s32 l){
 s32 x;
 Obj *p;
 p=*(Obj **)(*(u8 **)(D_00483894+0x40)+8);
 x=p->get((s64)(s16)b);
 p=*(Obj **)(*(u8 **)(D_00483894+0x40)+8);
 WeaponCombineLookup_3c4280(a,x,c,p->get((s64)(s16)d),e,f,g,h,(s64)i,(s64)j,(s64)k,(s64)l);
}
}
