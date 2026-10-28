/* rgp:protos */
#define RGP_SELF_PartyMenuCursorGet_3c0760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj003c0760 {
    u8 pad0[0x28A];
    s16 arr28A[0x20];
    u8 pad2CA[0x4C28 - 0x2CA];
    s16 arr4C28[0x30];
} Obj003c0760;

s16 PartyMenuCursorGet_3c0760(Obj003c0760 *arg0, s32 idx)
{
    if (idx >= 0 && idx < 0x20) {
        return arg0->arr28A[idx];
    }
    if (idx >= 0x20 && idx < 0x30) {
        return arg0->arr4C28[idx];
    }
    return -1;
}
