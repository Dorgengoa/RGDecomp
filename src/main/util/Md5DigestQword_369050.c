#include "types.h"
#include "vec.h"

extern void Md5Digest_369090(void *, s32, s32);
extern void *memcpy(void *, const void *, u32);

u128 Md5DigestQword_369050(s32 arg0, s32 arg1) {
    u128 sp20;
    u128 sp10;

    Md5Digest_369090(&sp20, arg0, arg1);
    memcpy(&sp10, &sp20, 0x10);
    return sp10;
}
