/* rgp:protos */
#define RGP_SELF_EventObjMgrDtor_2d1d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Sub_2d1d80 { u8 pad000[0xC]; const u8 *vp; };

extern u8 D_00471548[];
extern u8 D_00471558[];
extern u8 D_00471568[];
extern u8 D_00471578[];
extern u8 D_00471588[];
extern u8 D_00471598[];
extern u8 D_004715A8[];
extern u8 D_004715B8[];
extern u8 D_004715C8[];
extern u8 D_004715D8[];
extern u8 D_004715E8[];
extern u8 D_004715F8[];
extern u8 D_00471608[];
extern u8 D_00471618[];
extern u8 D_00471628[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj_2d1d80 {
    struct Sub_2d1d80 s00;
    struct Sub_2d1d80 s10;
    struct Sub_2d1d80 s20;
    struct Sub_2d1d80 s30;
    struct Sub_2d1d80 s40;
    u8 m50[0x10];
};

void *EventObjMgrDtor_2d1d80(struct Obj_2d1d80 *o, s16 flag)
{
    if (o != 0) {
        DestroyArray_1005b0(&o->m50, (void *)EvObjListDtor_2d1ff0, 0x10, 0x10);
        if (&o->s40 != 0) {
            o->s40.vp = D_00471628;
            DListClear_42ea80(&o->s40);
            if (&o->s40 != 0) {
                o->s40.vp = D_00471618;
                DListClear_42ea80(&o->s40);
                if (&o->s40 != 0) {
                    o->s40.vp = D_00471608;
                    DListClear_42ea80(&o->s40);
                    if (&o->s40 != 0) {
                        DListClear_42ea80(&o->s40);
                    }
                }
            }
        }
        if (&o->s30 != 0) {
            o->s30.vp = D_004715F8;
            DListClear_42ea80(&o->s30);
            if (&o->s30 != 0) {
                o->s30.vp = D_004715E8;
                DListClear_42ea80(&o->s30);
                if (&o->s30 != 0) {
                    o->s30.vp = D_004715D8;
                    DListClear_42ea80(&o->s30);
                    if (&o->s30 != 0) {
                        DListClear_42ea80(&o->s30);
                    }
                }
            }
        }
        if (&o->s20 != 0) {
            o->s20.vp = D_004715C8;
            DListClear_42ea80(&o->s20);
            if (&o->s20 != 0) {
                o->s20.vp = D_004715B8;
                DListClear_42ea80(&o->s20);
                if (&o->s20 != 0) {
                    o->s20.vp = D_004715A8;
                    DListClear_42ea80(&o->s20);
                    if (&o->s20 != 0) {
                        DListClear_42ea80(&o->s20);
                    }
                }
            }
        }
        if (&o->s10 != 0) {
            o->s10.vp = D_00471598;
            DListClear_42ea80(&o->s10);
            if (&o->s10 != 0) {
                o->s10.vp = D_00471588;
                DListClear_42ea80(&o->s10);
                if (&o->s10 != 0) {
                    o->s10.vp = D_00471578;
                    DListClear_42ea80(&o->s10);
                    if (&o->s10 != 0) {
                        DListClear_42ea80(&o->s10);
                    }
                }
            }
        }
        if (o != 0) {
            o->s00.vp = D_00471568;
            DListClear_42ea80(o);
            if (o != 0) {
                o->s00.vp = D_00471558;
                DListClear_42ea80(o);
                if (o != 0) {
                    o->s00.vp = D_00471548;
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
