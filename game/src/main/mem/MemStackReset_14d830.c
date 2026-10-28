/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_MemStackReset_14d830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void MemStackReset_14d830(void *arg0) {
    u8 c = *(u32 *)((u8 *)arg0 + 0x28) != 0;
    if (c == 0) {
        *(s32 *)((u8 *)arg0 + 0x2C) = 0;
        *(s32 *)((u8 *)arg0 + 0x30) = -1;
        *(s32 *)((u8 *)arg0 + 0x3C) = 0;
        *(s32 *)((u8 *)arg0 + 0x20) = 0;
        return;
    }
    if (*(s32 *)((u8 *)arg0 + 0x24) > 0) {
        while ((*(s32 *)((u8 *)arg0 + 0x54) != 0) && (rg_spin_halt(0x0014D86C), 1)) {
        }
    }
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = -1;
    *(s32 *)((u8 *)arg0 + 0x3C) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    MemStackResetChildren_14d170((void *)arg0);
}
