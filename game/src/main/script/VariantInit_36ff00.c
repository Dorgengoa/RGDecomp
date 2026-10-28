/* rgp:protos */
#define RGP_SELF_VariantInit_36ff00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *dst, s32 fill, s32 len);

typedef struct {
    u8 flag0 : 1;
    u8 unused : 7;
} Byte32Bits;

void VariantInit_36ff00(void *arg0) {
    *(s32 *)arg0 = 5;
    memset((u8 *)arg0 + 8, 0, 8);
    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    memset((u8 *)arg0 + 0x18, 0, 8);
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    memset((u8 *)arg0 + 0x28, 0, 8);
    *(s16 *)((u8 *)arg0 + 0x30) = 0;
    ((Byte32Bits *)((u8 *)arg0 + 0x32))->flag0 = 0;
}
