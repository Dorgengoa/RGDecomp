#include "types.h"

extern "C" s16 *AbilityListFindByDefId_3f5720(s32, s16);
class V70 {
public:
    virtual s32 v08();
    virtual s32 v0c();
    virtual s32 v10();
    virtual s32 v14();
    virtual s32 v18();
    virtual s32 v1c();
    virtual s32 v20();
    virtual s32 v24();
    virtual s32 v28();
    virtual s32 v2c();
    virtual s32 v30();
    virtual s32 v34();
    virtual s32 v38();
    virtual s32 v3c();
    virtual s32 v40();
    virtual s32 v44();
    virtual s32 v48();
    virtual s32 v4c();
    virtual s32 v50();
    virtual s32 v54();
    virtual s32 v58();
    virtual s32 v5c();
    virtual s32 v60();
    virtual s32 v64();
    virtual s32 v68();
    virtual s32 v6c();
    virtual s32 v70(s16);
};
class V5C {
public:
    virtual s32 v08();
    virtual s32 v0c();
    virtual s32 v10();
    virtual s32 v14();
    virtual s32 v18();
    virtual s32 v1c();
    virtual s32 v20();
    virtual s32 v24();
    virtual s32 v28();
    virtual s32 v2c();
    virtual s32 v30();
    virtual s32 v34();
    virtual s32 v38();
    virtual s32 v3c();
    virtual s32 v40();
    virtual s32 v44();
    virtual s32 v48();
    virtual s32 v4c();
    virtual s32 v50();
    virtual s32 v54();
    virtual s32 v58();
    virtual s32 v5c();
};
class A {
public:
    virtual s32 v08();
    virtual s32 v0c();
    virtual s32 v10();
    virtual s32 v14();
    virtual s32 v18();
    virtual s32 v1c();
    virtual s32 v20();
    virtual s32 v24();
    virtual s32 v28();
    virtual s32 v2c();
    virtual s32 v30();
    virtual s32 v34();
    virtual s32 v38();
    virtual s32 v3c();
    virtual s32 v40();
    virtual s32 v44();
    virtual s32 v48();
    virtual s32 v4c();
    virtual s32 v50();
    virtual s32 v54();
    virtual s32 v58();
    virtual s32 v5c();
    virtual s32 v60();
    virtual s32 v64();
    virtual s32 v68();
    virtual s32 v6c();
    virtual s32 v70();
    virtual s32 v74();
    virtual s32 v78();
    virtual V5C *v7c();
};
struct H44 { u8 pad[0xC]; V70 *mC; };
struct G { u8 pad[0x44]; H44 *m44; };
extern "C" G *D_0048374C;
class A2 : public A { public: s16 *m4; };

extern "C" s16 EquipSlotFindOwnerAbilityIdMaybe_39f6d0(A2 *arg0)
{
    s16 *p;
    s16 id;
    V5C *o;
    s32 r;

    if (D_0048374C == 0) return -1;
    p = arg0->m4;
    if (p == 0) return -1;
    id = *p;
    if (id < 0) return -1;
    o = arg0->v7c();
    if (o == 0) return -1;
    { s32 k = o->v5c(); r = D_0048374C->m44->mC->v70(k); }
    if (r == 0) return -1;
    p = AbilityListFindByDefId_3f5720(r, id);
    if (p != 0) return *p;
    return -1;
}
