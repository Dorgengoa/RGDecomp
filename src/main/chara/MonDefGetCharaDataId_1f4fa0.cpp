#include "types.h"

class Obj1f4fa0;

class Obj1f4fa0 {
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

struct Root1f4fa0 {
    u8 pad00[0x64];
    void *m64;
};

struct Mid1f4fa0 {
    u8 pad00[0xC];
    class Obj1f4fa0 *m0C;
};

struct Rec1f4fa0 {
    u8 pad00[0x20];
    s16 *m20;
};

extern "C" struct Root1f4fa0 *GetWorldDataMgr_1fedf0(void);

extern "C" s32 MonDefGetCharaDataId_1f4fa0(s32 id)
{
    struct Rec1f4fa0 *r;

    r = (struct Rec1f4fa0 *)((struct Mid1f4fa0 *)GetWorldDataMgr_1fedf0()->m64)->m0C->v26((s16)id);
    if (r == 0) {
        return -1;
    }
    if (r->m20 == 0) {
        return -1;
    }
    return *r->m20;
}
