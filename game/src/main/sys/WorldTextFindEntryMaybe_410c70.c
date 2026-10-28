/* rgp:protos */
#define RGP_SELF_WorldTextFindEntryMaybe_410c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    u8 pad[6];
} E;

typedef struct {
    u8 pad0[0x7C];
    s16 count;
    u8 pad7e[0x8C - 0x7E];
    E *table;
} O;

E *WorldTextFindEntryMaybe_410c70(O *o, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 j;
    s32 i;
    E *p;

    if (o->table == NULL || o->count <= 0) {
        return NULL;
    }
    for (j = 0; j < 2; j++) {
        for (i = 0; i < o->count; i++) {
            p = &o->table[i];
            if (p == NULL) {
                break;
            }
            if (j == 0) {
                if (p->x2 == a1 && p->x4 == a2 && p->x6 == a3) {
                    return p;
                }
            } else if (j == 1 && p->x2 == a1 && p->x4 == 0 && p->x6 == 0 && p->x8 == a4) {
                return p;
            }
        }
    }
    return NULL;
}
