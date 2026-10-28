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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xE8); }
};
void RevelationBoardSetCharaPortrait_349660(VC_0 *p)
{
    Tbl a __attribute__((aligned(16)));
    Tbl b __attribute__((aligned(16)));
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
