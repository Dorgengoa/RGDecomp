/* rgp:protos */
#define RGP_SELF_ActionMgrDtor_1fdd80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct SubF { u8 pad000[0xC]; const u8 *vp; };

extern u8 D_004712F0[];
extern u8 D_00471300[];
extern u8 D_00471310[];
extern u8 D_00471320[];
extern u8 D_00471330[];
extern u8 D_00471340[];
extern u8 D_00471350[];
extern u8 D_00471360[];
extern u8 D_00471370[];
/*rgp*/
/*rgp*/

struct ObjFDD80 {
    struct SubF s00;
    struct SubF s10;
    struct SubF s20;
};

void *ActionMgrDtor_1fdd80(struct ObjFDD80 *o, s16 flag)
{
    if (o != 0) {
        if (&o->s20 != 0) {
            o->s20.vp = D_004712F0;
            DListClear_42ea80(&o->s20);
            if (&o->s20 != 0) {
                o->s20.vp = D_00471300;
                DListClear_42ea80(&o->s20);
                if (&o->s20 != 0) {
                    o->s20.vp = D_00471310;
                    DListClear_42ea80(&o->s20);
                    if (&o->s20 != 0) {
                        DListClear_42ea80(&o->s20);
                    }
                }
            }
        }
        if (&o->s10 != 0) {
            o->s10.vp = D_00471320;
            DListClear_42ea80(&o->s10);
            if (&o->s10 != 0) {
                o->s10.vp = D_00471330;
                DListClear_42ea80(&o->s10);
                if (&o->s10 != 0) {
                    o->s10.vp = D_00471340;
                    DListClear_42ea80(&o->s10);
                    if (&o->s10 != 0) {
                        DListClear_42ea80(&o->s10);
                    }
                }
            }
        }
        if (o != 0) {
            o->s00.vp = D_00471350;
            DListClear_42ea80(o);
            if (o != 0) {
                o->s00.vp = D_00471360;
                DListClear_42ea80(o);
                if (o != 0) {
                    o->s00.vp = D_00471370;
                    DListClear_42ea80(o);
                    if (o != 0) {
                        DListClear_42ea80(o);
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
