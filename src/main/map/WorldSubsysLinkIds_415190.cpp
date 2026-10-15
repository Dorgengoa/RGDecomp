#include "types.h"

class Obj415190 {
public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void vf25();
    virtual void *call(void *a);
};

struct It415190 {
    u8 b[8];
};

struct E415190 {
    u8 pad00[0x4];
    void *m04;
};

struct T415190 {
    u8 pad00[0x1C];
    class Obj415190 *m2C;
};

struct P415190 {
    u8 pad00[0x34];
    struct T415190 *m34;
};

extern "C" void IterInit_370170(struct It415190 *it, void *arg);
extern "C" struct E415190 *IterNext_370040(struct It415190 *it);

extern "C" s32 WorldSubsysLinkIds_415190(u8 *p4, struct P415190 *p5)
{
    struct It415190 it;
    struct E415190 *e;
    u8 *arg;

    if (p5 == 0) {
        return 0;
    }
    arg = p4;
    if (p4 != 0) {
        arg += 0x88;
    }
    IterInit_370170(&it, arg);
    while ((e = IterNext_370040(&it)) != 0) {
        e->m04 = p5->m34->m2C->call(e->m04);
    }
    return 1;
}
