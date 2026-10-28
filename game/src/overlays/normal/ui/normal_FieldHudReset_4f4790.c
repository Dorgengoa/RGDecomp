/* rgp:protos */
#define RGP_SELF_normal_FieldHudReset_4f4790 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F4790 -- the 16-slot RESET over two parallel record arrays.
 * Each slot's destructor is beql-guarded on the array base being non-NULL:
 * stride 60 (((i<<4)-i)<<2) through normal_FieldHudEnemyRowInitMaybe_4f9d20, stride 28
 * (((i<<3)-i)<<2) through normal_FieldHudSlotRecClearRelated_4f9ce0.  The repeated `sll $2,$17,2`
 * and `sll $2,$17,1` are the branch-likely delay-slot copies of the index
 * scaling, not a CSE cost split.  Tail: the 0x398 sub-object is reset by
 * func_3A80E0 and the trailing pair goes -1 / 0. */

typedef struct RecA { u8 pad000[0x3C]; } RecA;   /* stride 60 */
typedef struct RecB { u8 pad000[0x1C]; } RecB;   /* stride 28 */

typedef struct Obj {
    u8    pad000[0x378];
    s16   f378;
    u8    pad37A[0x383 - 0x37A];
    u8    f383;
    u8    pad384[0x398 - 0x384];
    u8    f398[0x430 - 0x398];
    u8    f430;
    u8    pad431[0x434 - 0x431];
    RecA *f434;
    s32   f438[16];
    s16   f478;
    s16   f47A;
    s16   f47C[16];
    u8    pad49C[0x4A8 - 0x49C];
    s16   f4A8;
    u8    pad4AA[0x4AC - 0x4AA];
    s32   f4AC[16];
    RecB *f4EC;
    s32   f4F0;
    s32   f4F4;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudReset_4f4790(Obj *p)
{
    s32 i;

    p->f378 = 0;
    p->f4A8 = 0;
    for (i = 0; i < 16; i++) {
        if (p->f434 != NULL) {
            normal_FieldHudEnemyRowInitMaybe_4f9d20(&p->f434[i], i);
        }
        p->f4AC[i] = 0;
        if (p->f4EC != NULL) {
            normal_FieldHudSlotRecClearRelated_4f9ce0(&p->f4EC[i]);
        }
        p->f438[i] = 0;
        p->f47C[i] = 0;
    }
    p->f478 = 0;
    p->f430 = 0;
    p->f47A = 0;
    AiAllySuggestRecReset_3a80e0(&p->f398);
    p->f4F0 = -1;
    p->f4F4 = 0;
    p->f383 = 0;
}
