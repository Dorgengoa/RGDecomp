#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct {
    s16 id;
    s16 x;
    s16 y;
} Ent;

typedef struct {
    Ent e[11];
} Tbl;

typedef struct {
    u8 pad0[4];
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
} Spr;

typedef struct {
    u8 pad0[8];
    s64 x8;
} Val;

typedef struct {
    u8 pad0[0x20];
    Spr *x20;
    Val *x24;
} Win;

typedef struct {
    u8 pad0[0x2C];
    s16 x2C;
} Info;

extern Win *UiFindWidget_290460(s32, s32);
extern Info *CharaGetIconRecMaybe_3ae3e0(void *);
extern s16 D_00453890[];
extern s16 D_004538E0[];
extern s32 D_00482360;

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual s32 f();
};
void RevelationBoardSetCharaPortrait_349660(VC_0 *p)
{
    Tbl a;
    Tbl b;
    Win *w;
    Spr *s;
    Val *v;
    s16 id;
    s32 i;

    if (p == NULL) {
        return;
    }
    a = *(Tbl *)D_00453890;
    b = *(Tbl *)D_004538E0;
    w = UiFindWidget_290460(D_00482360, 0x4D);
    if (w != NULL && (s = w->x20) != NULL) {
            id = CharaGetIconRecMaybe_3ae3e0(p)->x2C;
            s->x8 = 0;
            s->xA = 0;
            for (i = 0; i < 10; i++) {
                if (id == a.e[i].id) {
                    s->x8 = a.e[i].x;
                    s->xA = a.e[i].y;
                }
            }
    }
    w = UiFindWidget_290460(D_00482360, 0x4C);
    if (w != NULL && (s = w->x20) != NULL) {
            id = CharaGetIconRecMaybe_3ae3e0(p)->x2C;
            s->x8 = 0;
            s->xA = 0;
            for (i = 0; i < 10; i++) {
                if (id == b.e[i].id) {
                    s->x8 = b.e[i].x;
                    s->xA = b.e[i].y;
                    s->xC = 0x36;
                    s->x4 = 0x36;
                    s->xE = 0x40;
                    s->x6 = 0x40;
                }
            }
    }
    w = UiFindWidget_290460(D_00482360, 0x4E);
    if (w != NULL && (v = w->x24) != NULL) {
        v->x8 = p->f();
    }
}

}
