#include "types.h"
/* insect 0x004F5BD0 -- C++ virtual dispatch, vptr at +0xC0, slot 0xA4 =
 * virtual #39 (8 + 4*39).  Same class as insect_InsectBattleCamInit_4f3390 /
 * insect_InsectBattleCamApplyTarget_4f32b0 / insect_InsectBattleCamApplyEye_4f3320.  [[jalr-is-cpp-virtual]]
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
    u8 pad039[0x71 - 0x39];
    s8 f071;
};

struct EL2 {
    u8 pad000[0x994];
};

struct O {
    u8   pad000[0xCC];
    s32  f0CC;
    u8   pad0D0[0x874 - 0xD0];
    VE  *f874;
    u8   pad878[0x35F8 - 0x878];
    EL2  arr[2];                        /* +0x35F8, stride 0x994 */
    u8   pad4920[0x4960 - 0x4920];
    s32  f4960;
};

struct Vec {
    s32 f00;
    f32 f04;
    s32 f08;
    s32 f0C;
};

struct SP {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
};

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
extern "C" void  func_13E500(void *h, s32 a);
extern "C" void  func_13E4F0(void *h, s32 a);
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
extern "C" f32   insect_InsectPieceGetHpRatio_512e70(E *e);
extern "C" s32   insect_InsectPieceTestStatus_513280(E *e, s32 k);
extern "C" void *insect_InsectBattleGetPieceModel_50df60(O *o, E *e);
extern "C" void  insect_InsectBoardFindPiece_4ee190(s32 *q, E *e, s32 *a, s32 *b);

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

extern "C" void insect_InsectBattleDrawHpBars_4f5bd0(O *o, void *h0)
{
    s32 sp13C;
    s32 sp138;
    Vec v;
    Vec b2;
    Vec a;
    SP  p;
    s32 *q;
    s32 i;
    s32 j;
    EL2 *bp;
    E *e;
    void *x;
    void *h;
    f32 fv;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 z;
    s32 m;

    q = &o->f4960;
    func_1418C0(h0, 0x29E, 1.0f);
    for (i = 0; i < 2; i++) {
        bp = &o->arr[i];
        for (j = 0; j < 5; j++) {
            e = insect_InsectTeamGetPiece_5138d0(bp, j);
            if (e != 0) {
                fv = insect_InsectPieceGetHpRatio_512e70(e);
                if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                    clr(&v, 0x10);
                    x = insect_InsectBattleGetPieceModel_50df60(o, e);
                    if (x != 0) {
                        func_1ADEC0(x, 0, &v);
                        if (e->f038 == 0x10) {
                            v.f04 = v.f04 + 0.5f;
                        }
                        v.f04 = v.f04 + D_0047D480;
                        o->f874->s39(&b2);
                        func_1CBD00(&a, &b2, &v);
                        func_1CBB80(&a, &a);
                        func_1CBCA0(&a, &a, 2.0f);
                        func_1CBDC0(&v, &v, &a);
                        if (func_15D160(&p, &v) != 0) {
                            insect_InsectBoardFindPiece_4ee190(q, e, &sp13C, &sp138);
                            h = func_141B00(h0);
                            if (h == 0) {
                                return;
                            }
                            func_13E500(h, 1);
                            func_13E4F0(h, 1);
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
                            x1 = p.x + 0x100;
                            x0 = p.x - 0x100;
                            y0 = p.y - 0x30;
                            y1 = p.y + 0x30;
                            z = p.z;
                            fv = (f32)(512.0f * fv);
                            func_13EC00(h, o->f0CC);
                            func_13EE40(h, 0x80, 0x80, 0x80, 0x80);
                            func_13ED60(h, 0x15D, 0xBD);
                            func_13EF10(h, x0 - 0x10, y0 - 0x10, z);
                            func_13ED60(h, 0x17E, 0xC4);
                            func_13EF10(h, x1 + 0x10, y1 + 0x10, z);
                            m = e->f071 * 12 + 0xEA;
                            func_13EE40(h, 0x80, 0x80, 0x80, 0x80);
                            func_13ED60(h, 0x156, m);
                            func_13EF10(h, x0 + 0x20, y0 + 0x20, z);
                            func_13ED60(h, 0x172, m + 2);
                            func_13EF10(h, (s32)((f32)x0 + fv) - 0x10, y1 - 0x10, z);
                            func_13F5B0(h);
                            func_141A20(h0);
                        }
                    }
                }
            }
        }
    }
}
