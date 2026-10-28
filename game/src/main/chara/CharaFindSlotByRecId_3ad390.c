/* rgp:protos */
#define RGP_SELF_CharaFindSlotByRecId_3ad390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct EFUN_003ad390 { u8 d[0x28]; };
struct PFUN_003ad390 { u8 pad000[0x308]; struct EFUN_003ad390 e[10]; };

/*rgp*/

struct EFUN_003ad390 *CharaFindSlotByRecId_3ad390(struct PFUN_003ad390 *p, s32 key)
{
    s32 i;
    struct EFUN_003ad390 *e;

    for (i = 0; i < 10; i++) {
        e = &p->e[i];
        if (e != 0) {
            if (key == EquipSlotGetRecId_3a0760(e)) {
                return e;
            }
        }
    }
    return 0;
}
