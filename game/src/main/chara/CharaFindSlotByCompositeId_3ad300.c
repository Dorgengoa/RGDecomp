/* rgp:protos */
#define RGP_SELF_CharaFindSlotByCompositeId_3ad300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct EFUN_003ad300 { u8 d[0x28]; };
struct PFUN_003ad300 { u8 pad000[0x308]; struct EFUN_003ad300 e[10]; };

/*rgp*/

struct EFUN_003ad300 *CharaFindSlotByCompositeId_3ad300(struct PFUN_003ad300 *p, s32 key)
{
    s32 i;
    struct EFUN_003ad300 *e;

    for (i = 0; i < 10; i++) {
        e = &p->e[i];
        if (e != 0) {
            if (key == EquipSlotGetAbilityCompositeId_3a0730(e)) {
                return e;
            }
        }
    }
    return 0;
}
