
#pragma divbyzerocheck on
#include "types.h"

typedef struct Quad {
    s16 f00; s16 f02; s16 f04; s16 f06;
    s16 f08; s16 f0A; s16 f0C; s16 f0E;
    s32 f10; f32 f14; s32 f18; s32 f1C;
} Quad;

extern void *D_004831D4;
extern s16   D_00480730[3];
extern const s16 D_00463B10[3] ;
extern f32   D_0047FAF8;
extern f32   D_0047FAFC;
extern f32   D_0047FB00;
extern f32   D_004831DC;

typedef struct W {u8 pad[0x20];Quad *q;} W;
extern W *UiFindWidget_290460(void *,s32);

f32 SaveUiScrollBarLayoutMaybe_377830(s32 id, s32 a, s32 b, s32 c, s32 d)
{
    f32 fl[3];
    f32 pos[3];
    f32 fb;
    f32 p1;
    f32 p2;
    f32 v;
    f32 r;
    f32 *m;
    Quad *q;
    void *base;
    s32 n;
    s32 i;
    u8 *cp;
    u32 cn;
    s16 h0;
    s16 h1;
    s16 h2;
    s16 hv;

    base=D_004831D4;
    D_004831DC=0;
    if(base==0)return 0.0f;
    fb = (f32)a;
    fl[0] = D_0047FAF8;
    fl[1] = D_0047FAFC;
    fl[2] = D_0047FB00;
    cp = (u8 *)pos;
    cn = 12;
    if (cp != 0) {
        do {
            *cp = 0;
            cn--;
            cp++;
        } while (cn != 0);
    }

    {W *w=UiFindWidget_290460(base,id);if(w==0)return 0.0f;q=w->q;}
    if (q == NULL) {
        return 0.0f;
    }

    n = c - b;
    if (n < 0) {
        n = 0;
    }
    if (n == 0) {
        for (i = 0; i < 3; i++) {
            q[i].f00 = 0;
            q[i].f0C = 8;
            q[i].f04 = 8;
            hv = D_00463B10[i];
            q[i].f0E = hv;
            q[i].f06 = hv;
            q[i].f14 = 0.0f;
            q[i].f10 = 0;
        }
        h0 = D_00463B10[0];
        q[1].f06 = a - (h0 + D_00463B10[2]);
        q[0].f02 = 0;
        q[1].f02 = h0;
        q[2].f02 = h0 + q[1].f06;
        return 0.0f;
    }

    m = &fl[1];
    h2 = D_00463B10[2];
    h0 = D_00463B10[0];
    h1 = D_00463B10[1];
    v = (f32)((a - (h0 + h2)) / h1 - (n + 2));
    *m = v;
    if (v < 1.0f) {
        *m = 1.0f;
    }
    pos[0] = 0.0f;
    p1 = pos[0] + (f32)h0;
    pos[1] = p1;
    p2 = p1 + (f32)h1 * *m;
    pos[2] = p2;

    r = (fb - (p2 + (f32)h2)) / (f32)n;
    for (i = 0; i < 3; i++) {
        q->f00 = 0;
        q->f02 = (s16)pos[i];
        if (d != 0) {
            q->f0C = 0;
            q->f04 = 0;
            q->f0E = 0;
            q->f06 = 0;
        } else {
            q->f0C = 8;
            q->f04 = 8;
            hv = D_00463B10[i];
            q->f0E = hv;
            q->f06 = hv;
        }


        q->f10 = 0;
        q->f14 = fl[i];
        q++;
    }
    D_004831DC = r;
    return r;
}
