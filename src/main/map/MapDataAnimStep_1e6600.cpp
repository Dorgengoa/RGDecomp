#include "types.h"

struct B_001e6600 {
    u8 pad[0x68];
};

struct C_001e6600 : public B_001e6600 {
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
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28(s32);
    virtual void v29(f32);
};

struct T_001e6600 {
    u8 pad[0x2C];
    s32 f2C;
};

extern "C" s32 MapDataIsLoadedOrUnloading_1e7980(T_001e6600 *);
extern "C" C_001e6600 *MapDataGetModel_1e7810(T_001e6600 *);

extern "C" void MapDataAnimStep_1e6600(T_001e6600 *p, f32 v)
{
    C_001e6600 *c;

    if (MapDataIsLoadedOrUnloading_1e7980(p) == 0) return;
    p->f2C = p->f2C & ~0x10;
    c = MapDataGetModel_1e7810(p);
    if (c == 0) return;
    c->v28(0);
    c->v29(v);
}
