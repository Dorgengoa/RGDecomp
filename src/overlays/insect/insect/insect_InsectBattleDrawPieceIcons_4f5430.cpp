#include "types.h"
/* insect 0x004F5430 -- C++ virtual dispatch, vptr at +0xC0, slot 0xA4 =
 * virtual #39 (8 + 4*39).  Same class as insect_InsectBattleCamInit_4f3390 /
 * insect_InsectBattleDrawHpBars_4f5bd0 / insect_InsectBattleCamApplyTarget_4f32b0.  [[jalr-is-cpp-virtual]]
 */

class VE {
public:
    u8 pad000[0xC0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32();
    virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38();
    virtual void s39(void *p);          /* slot 0xA4 */
};

struct E {
    u8 pad000[0x38];
    s8 f038;
    u8 pad039[0x4F - 0x39];
    s8 f04F;
    u8 pad050[0x71 - 0x50];
    s8 f071;
};

struct EL2 {
    u8 pad000[0x994];
};

struct O {
    u8   pad000[0xC4];
    s32  f0C4;
    s32  f0C8;
    u8   pad0CC[0x874 - 0xCC];
    VE  *f874;
    u8   pad878[0x35F8 - 0x878];
    EL2  arr[2];                        /* +0x35F8, stride 0x994 */
    u8   pad4920[0x5D94 - 0x4920];
    s8   f5D94;
};

struct Vec {
    f32 f[4];
};

struct SP {
    s32 f[4];
};

extern f32 D_0047D354;
extern f32 D_0047D278;
extern f32 D_0047D480;

extern "C" void  func_1418C0(void *h, s32 id, f32 t);
extern "C" void *func_141B00(void *h);
extern "C" void  func_141A20(void *h);
extern "C" void  func_1ADEC0(void *x, s32 k, Vec *v);
extern "C" void  func_1CBD00(Vec *d, Vec *a, Vec *b);
extern "C" void  func_1CBB80(Vec *d, Vec *a);
extern "C" void  func_1CBCA0(Vec *d, Vec *a, f32 t);
extern "C" void  func_1CBDC0(Vec *d, Vec *a, Vec *b);
extern "C" s32   func_15D160(SP *p, Vec *v);
extern "C" s32   func_15D4A0(Vec *v);
extern "C" void  func_13E500(void *h, s32 a);
extern "C" void  func_13E4F0(void *h, s32 a);
extern "C" void  func_13E4C0(void *h, s32 a, s32 b);
extern "C" void  func_13E4D0(void *h, s32 a);
extern "C" void  func_13E460(void *h, s32 a);
extern "C" void  func_13E3B0(void *h, s32 a);
extern "C" void  func_13E2F0(void *h, s32 a);
extern "C" void  func_13E3D0(void *h, s32 a);
extern "C" void  func_13E390(void *h, s32 a);
extern "C" void  func_13E450(void *h, s32 a);
extern "C" void  func_13E430(void *h, s32 a);
extern "C" void  func_13E400(void *h, s32 a);
extern "C" void  func_13E3E0(void *h, s32 a);
extern "C" void  func_13F730(void *h, s32 a);
extern "C" void  func_13EC00(void *h, s32 a);
extern "C" void  func_13EE40(void *h, s32 a, s32 b, s32 c, s32 d);
extern "C" void  func_13ED60(void *h, s32 a, s32 b);
extern "C" void  func_13EF10(void *h, s32 x, s32 y, s32 z);
extern "C" void  func_13F5B0(void *h);
extern "C" E    *insect_InsectTeamGetPiece_5138d0(EL2 *b, s32 i);
extern "C" s32   insect_InsectPieceTestStatus_513280(E *e, s32 k);
extern "C" s32   insect_InsectPieceIsKing_514b00(E *e);
extern "C" s32   insect_InsectPieceIsInPlay_5149e0(E *e);
extern "C" s32   insect_InsectBattleTestFlag_50da40(O *o, s32 k);
extern "C" void *insect_InsectBattleGetPieceModel_50df60(O *o, E *e);

/* ix18e LEVER (from insect_InsectBattleDrawMarkerModels_4f4a30): the count must be COPIED into a
 * local declared AFTER the pointer and assigned BEFORE it. */
static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c;

    c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

extern "C" void insect_InsectBattleDrawPieceIcons_4f5430(O *o, void *h0)
{
    Vec v1;
    Vec v2;
    SP  p1;
    Vec b1;
    Vec b2;
    SP  p2;
    Vec vb;
    Vec va;
    Vec c1;
    Vec c2;
    void *h;
    s8  c;
    s32 i;
    s32 j;
    E *e;
    s32 k;
    s32 k2;
    EL2 *bp;
    void *x;
    s32 flag;
    s16 w;
    s32 xA;
    s32 xB;
    s32 yA;
    s32 yB;
    s32 z1;
    s32 n;
    s32 X0;
    s32 X1;
    s32 Y0;
    s32 Y1;
    s32 z2;
    s16 r;
    s16 s;
    s16 t;
    s16 u;

    c = o->f5D94;
    func_1418C0(h0, 0x29E, 1.0f);
    h = func_141B00(h0);
    func_13E500(h, 1);
    func_13E4F0(h, 1);
    func_13E4C0(h, 6, 0);
    func_13E4D0(h, 1);
    func_13E460(h, 0);
    func_13E3B0(h, 1);
    func_13E2F0(h, 0);
    func_13E3D0(h, 1);
    func_13E390(h, 0);
    func_13E460(h, 1);
    func_13E450(h, 2);
    func_13E430(h, 0);
    func_13E400(h, 1);
    func_13E3E0(h, 1);
    func_13F730(h, 6);
    for (i = 0; i < 2; i++) {
        bp = &o->arr[i];
        for (j = 0; j < 5; j++) {
            if (bp != 0) {
                e = insect_InsectTeamGetPiece_5138d0(bp, j);
                if (e != 0) {
                    if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                        clr(&v1, 0x10);
                        clr(&v2, 0x10);
                        x = insect_InsectBattleGetPieceModel_50df60(o, e);
                        if (x != 0) {
                            func_1ADEC0(x, 0, &v1);
                            for (k2 = 0; k2 < 3; k2++) {
                                v2.f[k2] = v1.f[k2];
                            }
                            v1.f[1] = v1.f[1] + D_0047D354;
                            if (insect_InsectPieceIsKing_514b00(e) != 0) {
                                v1.f[1] = v1.f[1] + D_0047D278;
                            }
                            if (e->f038 == 0x10) {
                                v1.f[1] = v1.f[1] + 0.5f;
                                v2.f[1] = v2.f[1] + 0.5f;
                            }
                            v2.f[1] = v2.f[1] + D_0047D480;
                        }
                        if (insect_InsectBattleTestFlag_50da40(o, 0x2F) != 0) {
                            flag = 0;
                            if (insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                                if (func_15D160(&p1, &v1) != 0) {
                                    w = 0x40;
                                    xA = p1.f[0] - 0xA0;
                                    yA = p1.f[1] - 0x1E0;
                                    xB = p1.f[0] + 0xA0;
                                    yB = p1.f[1] - 0xA0;
                                    z1 = p1.f[2];
                                    if (c > 0) {
                                        if (insect_InsectPieceTestStatus_513280(e, 3) != 0) {
                                            flag = 1;
                                            w = 0x54;
                                        }
                                    }
                                    if (insect_InsectPieceTestStatus_513280(e, 0x1C) != 0) {
                                        flag = 1;
                                    }
                                    if (flag != 0) {
                                        clr(&b1, 0x10);
                                        b1.f[0] = (f32)xA;
                                        b1.f[1] = (f32)yA;
                                        b1.f[2] = (f32)p1.f[2];
                                        clr(&b2, 0x10);
                                        b2.f[0] = (f32)xB;
                                        b2.f[1] = (f32)yB;
                                        b2.f[2] = (f32)p1.f[2];
                                        if (func_15D4A0(&b1) == 0) {
                                            continue;
                                        }
                                        if (func_15D4A0(&b2) == 0) {
                                            continue;
                                        }
                                        func_13EC00(h, o->f0C4);
                                        func_13EE40(h, 0x80, 0x80, 0x80, 0x80);
                                        func_13ED60(h, w, 0x20);
                                        func_13EF10(h, xA, yA, z1);
                                        func_13ED60(h, w + 0x14, 0x34);
                                        func_13EF10(h, xB, yB, z1);
                                    }
                                }
                            }
                        }
                        if (insect_InsectBattleTestFlag_50da40(o, 0x30) != 0) {
                            n = e->f04F;
                            if (n > 0) {
                                o->f874->s39(&vb);
                                func_1CBD00(&va, &vb, &v2);
                                func_1CBB80(&va, &va);
                                func_1CBCA0(&va, &va, 2.0f);
                                func_1CBDC0(&v2, &v2, &va);
                                if (func_15D160(&p2, &v2) != 0) {
                                    for (k = 0; k < n; k++) {
                                        X0 = p2.f[0] - 0x110 + k * 192;
                                        X1 = p2.f[0] - 0x70 + k * 192;
                                        Y0 = p2.f[1] - 0xD0;
                                        Y1 = p2.f[1] - 0x30;
                                        z2 = p2.f[2];
                                        clr(&c1, 0x10);
                                        c1.f[0] = (f32)X0;
                                        c1.f[1] = (f32)Y0;
                                        c1.f[2] = (f32)p2.f[2];
                                        clr(&c2, 0x10);
                                        c2.f[0] = (f32)X1;
                                        c2.f[1] = (f32)Y1;
                                        c2.f[2] = (f32)p2.f[2];
                                        u = 0xA;
                                        r = 0x5E;
                                        s = 0xF6;
                                        t = 0xA;
                                        if (e->f071 == 1) {
                                            r += 0xA;
                                        }
                                        if (insect_InsectPieceTestStatus_513280(e, 0x20) != 0) {
                                            X0 = p2.f[0] - 0xF0;
                                            X1 = p2.f[0] + 0xF0;
                                            Y0 = p2.f[1] - 0x130;
                                            Y1 = p2.f[1] - 0x50;
                                            t = 0xE;
                                            r = 0;
                                            u = 0x1E;
                                            s = 0;
                                            if (e->f071 == 1) {
                                                s = 0x1E;
                                            }
                                            n = 0;
                                        }
                                        if (func_15D4A0(&c1) == 0) {
                                            continue;
                                        }
                                        if (func_15D4A0(&c2) == 0) {
                                            continue;
                                        }
                                        func_13EC00(h, o->f0C8);
                                        func_13EE40(h, 0x80, 0x80, 0x80, 0x80);
                                        func_13ED60(h, s, r);
                                        func_13EF10(h, X0, Y0, z2);
                                        func_13ED60(h, s + u, r + t);
                                        func_13EF10(h, X1, Y1, z2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    func_13F5B0(h);
    func_141A20(h0);
}
