#include "types.h"
/* normal 0x004FA870 -- the 0x47 prompt line.  Walks the D_005263A0 id table
 * until its -1 sentinel looking for a live func_3C8370 hit; the hit flips the
 * gp state byte 0x44E to 2 and selects the second string / second placement.
 * The two label buffers are then bound into the 0x533E record and the widget is
 * moved to the D_00526390 / D_00526392 pair for the chosen state.
 *
 * C++ virtual: `lw $25,0x60($25)` -> slot (0x60-8)/4 = 22.
 * `daddiu $19,$0,1` for the flag is the C++ `bool` spelling -- every integer
 * width gives `addiu` (levers.d/jalr-is-cpp-virtual).
 * `andi $17,$2,0xFF` on the index is a `u8` counter. */
class Ent {
public:
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual s32 s022();
};

typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct St   { u8 pad000[0x44E]; s16 f44E; } St;
typedef struct Hold { u8 pad00[0x20]; void *f20; } Hold;
typedef struct Rec  { u8 pad00[4]; void *f04; u8 pad08[0x14 - 8]; void *f14; } Rec;

extern const u8  D_00527820[];
extern       u8  D_00527860[64];
extern       u8  D_005278A0[64];
extern const u8  D_005263B0[];
extern const s32 D_005263A0[];
extern const s16 D_00526390[];
extern const s16 D_00526392[];

extern "C" {
extern St   *D_00484454;          /* gp - 0xD1C  */
extern s16   D_004804DC;          /* gp - 0x4C94 */
extern void *D_00481BBC;          /* gp - 0x35B4 */

extern Ctx        *func_1FEDE0(void);
extern Ent        *func_3C8370(s32 w, s32 a, s32 b, s32 c, s32 d, s32 e);
extern Hold       *func_290460(const u8 *p, u16 id);
extern Ent        *func_3C2420(s32 w, s32 i);
extern void       *func_206A40(void);
extern Rec        *func_42C270(void *o, s32 id);
extern void       *func_42C3A0(void *o, s32 id);
extern const void *func_28AA30(void *p, s32 id);
extern void        func_1343B8(void *d, const void *f, ...);
extern void        func_28F300(const u8 *p, u16 id, s32 c, s32 d);
extern void        func_290F60(const u8 *p, u16 id, s32 x, s32 y);
}

extern "C" void normal_BtlChgMenuLeaderDownNoticeMaybe_4fa870(void)
{
    Ctx  *c;
    s32   i;
    bool  flag;
    Ent  *e;
    Hold *h;
    void *o;
    Rec  *r;
    s32   v;

    flag = false;
    i = 0;
    c = func_1FEDE0();
    if (c == 0) {
        return;
    }
    D_00484454->f44E = 1;
    while ((v = D_005263A0[(u8)i]) != -1) {
        if (func_3C8370(c->f18, v, 0, -1, 0, 0) != 0) {
            D_00484454->f44E = 2;
            flag = true;
            break;
        }
        i = (u8)(i + 1);
    }
    h = func_290460(D_00527820, 0x47);
    if (h != 0) {
        e = func_3C2420(c->f18, D_004804DC);
        o = func_206A40();
        r = func_42C270(o, 0x533E);
        h->f20 = func_42C3A0(o, flag + 0x5244);
        if (e != 0) {
            func_1343B8(D_00527860, func_28AA30(D_00481BBC, 0x32), e->s022());
            if (flag) {
                func_1343B8(D_005278A0, D_005263B0, func_28AA30(D_00481BBC, 0x33));
                func_28F300(D_00527820, 0x47, 0xCA, 0);
                func_28F300(D_00527820, 0x47, 0xCA, 1);
            } else {
                func_1343B8(D_005278A0, D_005263B0, func_28AA30(D_00481BBC, 0x34));
                func_28F300(D_00527820, 0x47, 0xA6, 0);
                func_28F300(D_00527820, 0x47, 0xA6, 1);
            }
        }
        r->f04 = D_00527860;
        r->f14 = D_005278A0;
    }
    func_290F60(D_00527820, 0x47, D_00526390[flag * 2], D_00526392[flag * 2]);
}
