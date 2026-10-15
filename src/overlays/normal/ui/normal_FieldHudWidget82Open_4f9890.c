#include "types.h"
/* normal 0x004F9890 -- open widget 0x82 only when func_1FEDE0's record says
 * mode 1.  The `beql` on the null test carries the shared `ld $31`. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x4A4 - 0x37A];
    s16 f4A4;
} Obj;

typedef struct Sub { u8 pad00[0x22]; s16 f22; } Sub;
typedef struct Rec { u8 pad00[0xC]; Sub *f0C; } Rec;

extern Rec *func_1FEDE0(void);
extern void func_291110(Obj *p, s32 id, s32 c, s32 d);
extern void func_290F60(Obj *p, s32 id, s32 c, s32 d);
extern void func_2907A0(Obj *p, s32 id, f32 x);

void normal_FieldHudWidget82Open_4f9890(Obj *p)
{
    Rec *r;

    if (p->f378 != 0) {
        r = func_1FEDE0();
        if (r == NULL) {
            return;
        }
        if (r->f0C->f22 == 1) {
            func_291110(p, 0x82, 1, 1);
            func_290F60(p, 0x82, 0x12, 0x5A);
            func_2907A0(p, 0x82, 1.0f);
            p->f4A4 = 1;
        }
    }
}
