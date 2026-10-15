#include "types.h"

typedef struct Sub {
    u8  pad000[0x30];
    s16 f030;
    u8  pad032[0x15C];
    s16 f18E;
} Sub;

typedef struct Ev {
    u8   pad00[0x18];
    Sub *f18;
} Ev;

typedef struct Pl {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Pl;

extern u8    D_00526710[0x10];
extern u8    D_00527F10[0x10];

extern f32   D_00480700;   /* gp - 0x4A70 */
extern f32   D_00480704;   /* gp - 0x4A6C */
extern f32   D_00480708;   /* gp - 0x4A68 */
extern f32   D_0048070C;   /* gp - 0x4A64 */
extern void *D_004846E8;   /* gp - 0xA88  */
extern void *D_004846EC;   /* gp - 0xA84  */
extern void *D_004846F0;   /* gp - 0xA80  */
extern void *D_004846F4;   /* gp - 0xA7C  */
extern void *D_004846F8;   /* gp - 0xA78  */
extern s8    D_0048472C;   /* gp - 0xA44  */
extern s16   D_0048474C;   /* gp - 0xA24  */
extern f32   D_00484758;   /* gp - 0xA18  */

extern void  func_1418C0(void *p, s16 n, f32 t);
extern s32   func_1451D0(void *p);
extern s32   func_1451E0(void *p);
extern s16  *func_159FB0(void *p, void *s, s32 n);
extern void *func_15DE40(void);
extern void *func_15DE80(void);
extern void  func_177540(void *p);
extern void *func_1DCB50(s32 n);
extern void  func_1E2820(void *p, f32 *v, f32 t);
extern void  func_1E49B0(void *p, s16 n, s32 *out);
extern void *func_1FDB50(void);
extern Ev   *func_1FEDE0(void);
extern Pl   *func_201A70(void);
extern void *func_201A90(void);
extern void *func_233B50(void *p, s16 n);
extern void  func_2388A0(void *p, f32 *v);
extern void  func_291910(void *w);
extern void  func_3242B0(void *p, f32 *x, f32 *y, s32 n);
extern void  normal_TransMenuMinimapMarkersDrawMaybe_5174d0(void *p, s32 x, s32 y, s16 *s, f32 t);

void normal_TransMenuDraw_5163a0(void)
{
    s32   n;
    f32   pos[2];
    f32   v[4];
    void *p;
    Ev   *e;
    void *r;
    void *t;
    void *q;
    s16  *s;
    s32   w;
    s32   h;
    Pl   *pl;

    if (D_0048474C != 0) {
        func_291910(D_004846EC);
        p = func_201A90();
        if (p != 0) {
            e = func_1FEDE0();
            n = 0;
            func_1E49B0(p, e->f18->f030, &n);
            if (n != 0) {
                r = func_1DCB50(n);
                pl = func_201A70();
                if (pl != 0) {
                    r = pl->f510;
                    if (pl->f514 != 0) {
                        r = pl->f514;
                    }
                }
                if (r != 0) {
                    v[0] = D_00480700;
                    v[1] = D_00480704;
                    v[2] = D_00480708;
                    v[3] = D_0048070C;
                    t = func_233B50(func_1FDB50(), e->f18->f18E);
                    if (t != 0) {
                        func_2388A0(t, v);
                    }
                    if (D_0048472C != 0) {
                        func_1E2820(p, v, 0.0f);
                        q = func_15DE80();
                        s = func_159FB0(func_15DE40(), D_00526710, 0x32D);
                        if (s != 0) {
                            func_1418C0(q, *s, 1.0f);
                        }
                        func_3242B0(r, &pos[0], &pos[1], 1);
                        w = func_1451E0(q);
                        h = func_1451D0(q);
                        normal_TransMenuMinimapMarkersDrawMaybe_5174d0(q, (s32)((f32)(w / 2) - pos[0]),
                                            (s32)((f32)(h / 2) - pos[1]), s, D_00484758);
                    }
                }
            }
        }
        func_291910(D_004846E8);
        func_291910(D_004846F0);
        func_291910(D_004846F4);
        func_291910(D_004846F8);
        func_177540(D_00527F10);
    }
}
