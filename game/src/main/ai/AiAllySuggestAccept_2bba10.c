/* rgp:protos */
#define RGP_SELF_AiAllySuggestAccept_2bba10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s16 a, b; } P2;

void AiAllySuggestAccept_2bba10(void *arg0, void *arg1, s8 arg2) {
    if (arg1 == NULL || *(s16 *)((u8 *)arg0 + 0xAE) == 0x190) {
        return;
    }
    *(s16 *)((u8 *)arg0 + 0x130) = *(s16 *)((u8 *)arg1 + 0);
    *(P2 *)((u8 *)arg0 + 0x132) = *(P2 *)((u8 *)arg1 + 2);
    *(P2 *)((u8 *)arg0 + 0x136) = *(P2 *)((u8 *)arg1 + 6);
    *(s8 *)((u8 *)arg0 + 0x143) = arg2;
    *(u16 *)((u8 *)arg0 + 0xAC) = 0x1F4;
}
