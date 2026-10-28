/* rgp:protos */
#define RGP_SELF_SoundStreamDtor_1bfc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 DeleteSema(s32);
/*rgp*/

struct Obj_FUN_001bfc30 {
    u8 pad000[0x10];
    s32 m10;
    u8 pad014[0x2C];
    s32 m40;
    u8 pad044[0x38];
    s32 m7C;
};

void *SoundStreamDtor_1bfc30(struct Obj_FUN_001bfc30 *o, s16 flag)
{
    void *p;

    if (o != 0) {
        p = (u8 *)o + 0x7C;
        if (p != 0) {
            if (o->m7C > 0) {
                DeleteSema(*(volatile s32 *)&o->m7C);
            }
            o->m7C = -1;
        }
        if (o != 0) {
            p = (u8 *)o + 0x40;
            if (p != 0) {
                if (o->m40 > 0) {
                    DeleteSema(*(volatile s32 *)&o->m40);
                }
                o->m40 = -1;
            }
            p = (u8 *)o + 0x4;
            if (p != 0) {
                if (p != 0) {
                    p = (u8 *)o + 0x10;
                    if (p != 0) {
                        if (o->m10 > 0) {
                            DeleteSema(*(volatile s32 *)&o->m10);
                        }
                        o->m10 = -1;
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
