#include "types.h"

extern s32 strlen(const s8 *s);
extern s8 *strcpy(s8 *dst, const s8 *src);

typedef struct {
    u8 pad00[0x20];
    s32 enabled;  /* +0x20 */
    u8 pad24[4];
    u8 *base;     /* +0x28 */
    s32 pos;      /* +0x2c */
    u8 pad30[4];
    s32 capacity; /* +0x34 */
    u8 pad38[0x1c];
    s32 lock;     /* +0x54 */
} Ctx;

s8 *MemStackStrDup_14cff0(s8 *str, Ctx *ctx)
{
    u32 len;
    s32 chunks;
    s8 *result;

    if (str == 0 || ctx == 0) {
        return 0;
    }

    len = (u32)strlen(str) + 1;
    if ((len & 0xF) != 0) {
        chunks = (len >> 4) + 1;
    } else {
        chunks = len >> 4;
    }

    if (ctx->enabled != 0) {
        result = 0;
    } else if (chunks <= 0) {
        result = 0;
    } else {
        s32 oldpos = ctx->pos;
        s32 newpos = oldpos + chunks;

        if (ctx->capacity < newpos) {
            while (ctx->lock != 0) {
            }
            result = 0;
        } else {
            result = (s8 *)(ctx->base + (oldpos << 4));
            ctx->pos = newpos;
        }
    }

    if (result == 0) {
        return 0;
    }
    strcpy(result, str);
    return result;
}
