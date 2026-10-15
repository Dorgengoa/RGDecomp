#include "types.h"
/* normal 0x00506FE0 -- the party-average gauge refresh.  Walks the s16 id list
 * D_00525A10 until its -1 sentinel, sums each member's slot-58 and slot-72
 * values, and drives widget 0xF's bar from the ratio.
 *
 * `lw $25,0($x) / lw $25,K($25) / jalr $25` is a C++ VIRTUAL call, so this TU
 * is .cpp: slot = (K - 8) / 4, i.e. 0xF0 -> 58 and 0x128 -> 72.
 * `dsll32/dsra32 ..,16` off the `lh` is the explicit `(s16)` cast at the call. */
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
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual s32 s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual s32 s072(s32 a);
};

typedef struct It   { u8 pad00[8]; } It;
typedef struct Ctx  { u8 pad00[0x1C]; void *f1C; } Ctx;
typedef struct Bar  { u8 pad00[4]; s16 f04; } Bar;
typedef struct Hold { u8 pad00[0x20]; Bar *f20; } Hold;

extern s16 D_00525A10[64];

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern u8    D_00484570;          /* gp - 0xC00 */

extern Ctx  *func_1FEDE0(void);
extern void  func_370170(It *it, void *src);
extern void  func_36FFF0(It *it, s32 k);
extern Ent  *func_36FF80(It *it);
extern Hold *func_290460(void *p, u16 id);
extern void  func_290010(void *p, u16 id, s32 c, s32 d);
}

extern "C" void normal_LeaderHudBossGaugeUpdate_506fe0(void)
{
    It    it;
    Ctx  *c;
    Ent  *e;
    Hold *h;
    Bar  *b;
    s32   sum;
    s32   cnt;
    s32   i;
    s32   k;
    s32   v;
    f32   r;

    if (D_00484570 == 0) {
        return;
    }
    c = func_1FEDE0();
    func_370170(&it, c->f1C);
    sum = 0;
    cnt = 0;
    i = 0;
    while ((k = D_00525A10[i]) >= 0) {
        func_36FFF0(&it, (s16)k);
        e = func_36FF80(&it);
        sum += e->s058();
        cnt += e->s072(1);
        i++;
    }
    r = (f32)sum / (f32)cnt;
    h = func_290460(D_00484564, 0xF);
    if (h != 0) {
        b = h->f20;
        if (b != 0) {
            if (r > 0.0f) {
                v = (s32)(170.0f * r);
                b->f04 = v;
                if ((s16)v <= 0) {
                    b->f04 = 1;
                }
            }
        }
        if (r <= 0.0f) {
            func_290010(D_00484564, 0xF, 0, -1);
        }
    }
}
