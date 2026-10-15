#include "types.h"

class Obj1f5060;

class Obj1f5060 {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual s16 *v26(s16 idx);
};

struct Root1f5060 {
    u8 pad00[0x60];
    void *m60;
};

struct Mid1f5060 {
    u8 pad00[0xC];
    class Obj1f5060 *m0C;
};

struct Rec1f5060 {
    u8 pad00[0x8];
    s16 *m08;
};

extern "C" struct Root1f5060 *GetWorldDataMgr_1fedf0(void);

extern "C" s32 PcDefGetCharaDataId_1f5060(s32 id)
{
    struct Rec1f5060 *r;

    r = (struct Rec1f5060 *)((struct Mid1f5060 *)GetWorldDataMgr_1fedf0()->m60)->m0C->v26((s16)id);
    if (r == 0) {
        return -1;
    }
    if (r->m08 == 0) {
        return -1;
    }
    return *r->m08;
}
