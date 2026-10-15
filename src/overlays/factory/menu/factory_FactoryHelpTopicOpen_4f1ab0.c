#include "types.h"

typedef struct Rec {
    s16 f00;
    s16 f02;
} Rec;

typedef struct Meta {
    u8  pad00[0x16];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} Meta;

typedef struct Scr {
    u8    pad00[0x6A];
    u8    f6A;
    u8    pad6B[0x1];
    s32   f6C;
    s8    f70;
    s8    f71;
    u8    pad72[0x2];
    Rec  *f74;
    s32   f78;
    s32   f7C;
    s32   f80;
    u8    pad84[0x4];
    void *f88;
    void *f8C;
} Scr;

extern void *D_00484A30;                        /* _gp - 0x740 */
extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    D_0050CB20[];

extern void  func_1343B8(u8 *dst, u8 *fmt, void *s);
extern u8   *func_1347C0(void *s, s32 c);
extern void  func_14D830(void *p);
extern void  func_158AC0(s32 h, s32 k);
extern s32   func_15DE40(void);
extern void  func_1CD670(s32 h);
extern s32   func_1CD870(s32 h, u8 *p, s32 k);
extern s32   func_1F59D0(void);
extern void *func_28AA30(void *bank, s32 id);
extern Meta *func_28EA40(void *w, u32 id);
extern void  func_28EA90(void *w, u32 id, s32 a);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);

void factory_FactoryHelpTopicOpen_4f1ab0(Scr *o)
{
    u8   buf[0x20];
    u8  *p;
    u8  *q;
    u8  *r;
    Meta *m;
    s32  h;
    u32  n;
    s32  v;

    if (o->f7C == -1) {
        if (D_00484A30 != 0) {
            func_14D830(D_00484A30);
        }
        func_158AC0(func_15DE40(), 0x32E);
        h = func_1F59D0();
        o->f7C = -1;
        o->f80 = 0;
        m = func_28EA40(o->f8C, 0x8944);
        v = m->f16 + m->f1A;
        if (o->f6A == 0 && v >= 0xB) {
            v = v + 1;
        }
        o->f6C = v;
        q = func_28AA30(D_00484A70, o->f74[v].f00 + 0x2710);
        p = func_1347C0(q, 0xA);
        *p = 0;
        r = buf;
        n = 0x20;
        if (r != 0) {
            do {
                *r = 0;
                n--;
                r++;
            } while (n != 0);
        }
        func_1343B8(buf, D_0050CB20, q);
        *p = 0xA;
        o->f7C = func_1CD870(h, buf, 0);
        if (o->f7C != -1) {
            o->f78 = 0;
            o->f71 = 0;
            func_1CD670(h);
            func_290690(o->f88, 0x7C, 0.0f, -0.125f, -1.0f);
            func_28EA90(o->f8C, 0x894E, 0);
            o->f70 = 2;
        }
    }
}
