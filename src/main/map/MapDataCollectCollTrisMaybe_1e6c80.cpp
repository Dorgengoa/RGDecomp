#include "types.h"

class OBase {
public:
    u8 pad000[0x68];
};

class O : public OBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
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
    virtual s32 v22(void *p, void *d, s32 n);
};

typedef struct Rec {
    u8  pad000[0x54];
    s32 m54;
    u8  pad058[0x8];
} Rec;

extern "C" O *MapDataGetModel_1e7810(void);
extern "C" s32 MapDataGetId_1e7bd0(void *a);

extern "C" s32 MapDataCollectCollTrisMaybe_1e6c80(void *a, Rec *p, s32 n, void *d)
{
    O  *o;
    s32 cnt;
    s32 i;

    if (p == 0 || n <= 0) {
        return 0;
    }
    o = MapDataGetModel_1e7810();
    if (o == 0) {
        return 0;
    }
    cnt = o->v22(p, d, n);
    for (i = 0; i < cnt; i++) {
        p->m54 = MapDataGetId_1e7bd0(a);
        p++;
    }
    return cnt;
}
