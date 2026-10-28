/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00506FE0 -- the party-average gauge refresh.  Walks the s16 id list
 * normal_D_00525A10 until its -1 sentinel, sums each member's slot-58 and slot-72
 * values, and drives widget 0xF's bar from the ratio.
 *
 * `lw $25,0($x) / lw $25,K($25) / jalr $25` is a C++ VIRTUAL call, so this TU
 * is .cpp: slot = (K - 8) / 4, i.e. 0xF0 -> 58 and 0x128 -> 72.
 * `dsll32/dsra32 ..,16` off the `lh` is the explicit `(s16)` cast at the call. */
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s058() { return VCM0(s32, 0xF0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s072(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }
};

typedef struct It   { u8 pad00[8]; } It;
typedef struct Ctx  { u8 pad00[0x1C]; void *f1C; } Ctx;
typedef struct Bar  { u8 pad00[4]; s16 f04; } Bar;
typedef struct Hold { u8 pad00[0x20]; Bar *f20; } Hold;

extern "C" s16 normal_D_00525A10[64];

extern "C" {
extern void *D_00484564;          /* gp - 0xC0C */
extern u8    D_00484570;          /* gp - 0xC00 */

extern Ctx  *GetGameData_1fede0(void);
extern void IterInit_370170(It *, void *, int, int);
extern void IterSeek_36fff0(It *, s32, int, int);
extern Ent  * IterGetCurrent_36ff80(It *, int, int, int);
extern Hold *UiFindWidget_290460(void *p, u16 id);
extern void  UiSetWidgetVisible_290010(void *p, u16 id, s32 c, s32 d);
}

extern "C" void normal_LeaderHudBossGaugeUpdate_506fe0(void)
{
    It    it __attribute__((aligned(16)));
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
    c = GetGameData_1fede0();
    IterInit_370170(&it, c->f1C, 0, 0);
    sum = 0;
    cnt = 0;
    i = 0;
    while ((k = normal_D_00525A10[i]) >= 0) {
        IterSeek_36fff0(&it, (s16)k, 0, 0);
        e = IterGetCurrent_36ff80(&it, 0, 0, 0);
        sum += e->s058();
        cnt += e->s072(1);
        i++;
    }
    r = (f32)sum / (f32)cnt;
    h = UiFindWidget_290460(D_00484564, 0xF);
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
            UiSetWidgetVisible_290010(D_00484564, 0xF, 0, -1);
        }
    }
}
