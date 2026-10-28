/* rgp:protos */
#define RGP_SELF_PadBindingsUpdate_15fcd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    s32 val;
    s32 key;
} Ent;

typedef struct {
    f32 val;
    s32 type;
} FEnt;

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    Ent ent[0x80];
    FEnt fent[0x20];
} Obj;

void PadBindingsUpdate_15fcd0(Obj *arg0, s32 arg1)
{
    s32 i;
    Ent *e;
    FEnt *f;
    s32 id;
    s32 key;

    arg0->f0 = PadGetAnalogRXNorm_183c30(arg1);
    arg0->f4 = PadGetAnalogRYNorm_183b90(arg1);
    arg0->f8 = PadGetAnalogLXNorm_183af0(arg1);
    arg0->fC = PadGetAnalogLYNorm_183a50(arg1);
    for (i = 0; i < 0x80; i++) {
        e = &arg0->ent[i];
        if (e->key != 0) {
            id = e->key & 0xFFFF;
            switch (e->key & 0xF0000) {
            case 0x0:
                e->val = PadIsHeld_183a20(arg1, id);
                break;
            case 0x10000:
                e->val = PadIsTriggered_1839f0(arg1, id);
                break;
            case 0x20000:
                e->val = PadIsReleased_1839c0(arg1, id);
                break;
            }
        }
    }
    for (i = 0; i < 0x20; i++) {
        f = &arg0->fent[i];
        switch (f->type) {
        case 1:
            f->val = arg0->f8;
            break;
        case 2:
            f->val = arg0->fC;
            break;
        case 3:
            f->val = arg0->f0;
            break;
        case 4:
            f->val = arg0->f4;
            break;
        case 0:
            break;
        }
    }
}
