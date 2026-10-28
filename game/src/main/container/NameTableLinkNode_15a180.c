/* rgp:protos */
#define RGP_SELF_NameTableLinkNode_15a180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x30];
    u8 *bucket[0x6A];
    u8 **unk1D8;
    s32 unk1DC;
    s32 unk1E0;
} T15a180_arg0;

void NameTableLinkNode_15a180(T15a180_arg0 *arg0, s8 *arg1)
{
    u8 *n;
    u8 *q;
    u8 **b;
    s8 *p;
    u8 h;

    if (arg0->unk1E0 >= arg0->unk1DC) {
        n = NULL;
    } else {
        n = arg0->unk1D8[arg0->unk1E0++];
    }
    if (n != NULL) {
        *(s32 *)(n + 4) = 0;
        p = arg1 + 8;
        *(s8 **)(n + 0) = arg1;
        h = 0;
        while (*p != 0) {
            h = ((h << 8) + *p++) % 101;
        }
        b = (u8 **)((u8 *)arg0 + 0x30) + (h & 0xFF);
        q = *b;
        if (q == NULL) {
            *b = n;
        } else {
            while (q != NULL) {
                if (*(u8 **)(q + 4) == NULL) {
                    *(u8 **)(q + 4) = n;
                    break;
                }
                q = *(u8 **)(q + 4);
            }
        }
    }
}
