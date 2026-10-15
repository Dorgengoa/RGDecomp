#include "types.h"

typedef struct {
    u8 *buf;
    s32 x4;
    s32 pos;
} Reader;

typedef struct {
    s32 type;
    union {
        s32 i;
        f32 f;
        char *s;
    } v;
} Value;

extern void TextReaderPushValue_15f640(Reader *, Value);
extern s32 strlen(const char *);

s16 TextReaderReadBinaryArgs_15ef70(Reader *r)
{
    s8 types[0x400];
    Value val;
    s16 n;
    s32 i;
    s32 m;
    s32 len;

    n = *(s16 *)(r->buf + r->pos);
    r->pos += 2;
    if (n == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        switch (r->buf[r->pos++]) {
        case 1:
            types[i] = 1;
            break;
        case 2:
            types[i] = 2;
            break;
        case 3:
            types[i] = 0;
            break;
        }
    }
    m = r->pos % 4;
    if (m != 0) {
        r->pos += 4 - m;
    }
    for (i = 0; i < n; i++) {
        val.type = types[i];
        switch (val.type) {
        case 1:
            val.v.i = *(s32 *)(r->buf + r->pos);
            r->pos += 4;
            break;
        case 2:
            val.v.f = *(f32 *)(r->buf + r->pos);
            r->pos += 4;
            break;
        case 0:
            val.v.s = (char *)(r->buf + r->pos);
            len = strlen(val.v.s) + 1;
            m = len % 4;
            if (m != 0) {
                len += 4 - m;
            }
            r->pos += len;
            break;
        }
        TextReaderPushValue_15f640(r, val);
    }
    return n;
}
