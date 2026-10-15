#include "types.h"

typedef struct A { u8 pad00[0x14]; } A;
typedef struct B { u8 pad00[0x68]; } B;

typedef struct Ctx {
    u8  pad00[0xCC];
    A  *fCC;
    s32 fD0;
    B  *fD4;
    s32 fD8;
} Ctx;

extern void *func_2D9040(void);
extern void *func_2E1550(void *p);
extern void *func_201A90(void);
extern void *func_1E49B0(void *p, s32 id, s32 a);
extern void *func_1E7810(void *p);
extern void  func_188FE0(void *p);
extern void  func_188FF0(void *p, void *w);
extern void  func_14D830(void *w);
extern void  factory_FactoryBeltTileGroupBuildObjs_4ff1e0(A *a, void *w);
extern void  factory_FactoryPartGroupBuildObjs_4fead0(B *b, void *w);
extern void  factory_FactoryFloorClearAll_501150(Ctx *c);

void factory_FactoryBuildModels_503d30(Ctx *c)
{
    void *p;
    void *t;
    void *q;
    void *w;
    A    *a;
    s32   i;
    B    *b;
    s32   j;

    func_2E1550(func_2D9040());
    q = func_201A90();
    p = 0;
    t = func_1E49B0(q, 0x2EE0, 0);
    if (t != 0) {
        p = func_1E7810(t);
    }
    if (p != 0) {
        func_188FE0(p);
    }
    w = (u8 *)c + 0x304;
    func_14D830(w);
    a = c->fCC;
    if (a != 0) {
        for (i = 0; i < c->fD0; i++, a++) {
            factory_FactoryBeltTileGroupBuildObjs_4ff1e0(a, w);
        }
    }
    b = c->fD4;
    if (b != 0) {
        for (j = 0; j < c->fD8; j++, b++) {
            factory_FactoryPartGroupBuildObjs_4fead0(b, w);
        }
    }
    if (p != 0) {
        func_188FF0(p, w);
    }
    factory_FactoryFloorClearAll_501150(c);
}
