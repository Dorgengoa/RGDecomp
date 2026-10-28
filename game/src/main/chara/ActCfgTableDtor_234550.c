/* rgp:protos */
#define RGP_SELF_ActCfgTableDtor_234550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Sub234550 { u8 pad000[0xC]; const u8 *vp; };

extern u8 D_00471420[];
extern u8 D_00471430[];
extern u8 D_00471440[];
extern u8 D_00471450[];
extern u8 D_00471460[];
extern u8 D_00471470[];
/*rgp*/
/*rgp*/

struct Obj234550 {
    u8 pad000[0x7C];
    struct Sub234550 s7C;
    struct Sub234550 s8C;
};

void *ActCfgTableDtor_234550(struct Obj234550 *o, s16 flag)
{
    if (o != 0) {
        if (&o->s8C != 0) {
            o->s8C.vp = D_00471420;
            DListClear_42ea80(&o->s8C);
            if (&o->s8C != 0) {
                o->s8C.vp = D_00471430;
                DListClear_42ea80(&o->s8C);
                if (&o->s8C != 0) {
                    o->s8C.vp = D_00471440;
                    DListClear_42ea80(&o->s8C);
                    if (&o->s8C != 0) {
                        DListClear_42ea80(&o->s8C);
                    }
                }
            }
        }
        if (&o->s7C != 0) {
            o->s7C.vp = D_00471450;
            DListClear_42ea80(&o->s7C);
            if (&o->s7C != 0) {
                o->s7C.vp = D_00471460;
                DListClear_42ea80(&o->s7C);
                if (&o->s7C != 0) {
                    o->s7C.vp = D_00471470;
                    DListClear_42ea80(&o->s7C);
                    if (&o->s7C != 0) {
                        DListClear_42ea80(&o->s7C);
                    }
                }
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
