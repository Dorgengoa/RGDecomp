#pragma optimization_level 3
#include "types.h"

class Streambuf {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual s32 overflow(s32);
    u8 pad4[0x10];
    u8 *pnext;
    u8 *pend;

    s32 sputc(char c) {
        if (pnext < pend) {
            char *p = (char *)pnext++;
            *p = c;
            return (u8)*p;
        }
        return overflow((u8)c);
    }
};

struct OutIt {
    Streambuf *sb;
    OutIt &operator*() { return *this; }
    OutIt &operator++(int) { return *this; }
    OutIt &operator=(char c) {
        if (sb != 0 && sb->sputc(c) == -1) {
            sb = 0;
        }
        return *this;
    }
};

struct IosBase {
    u8 pad0[0x30];
    s64 width;
    u16 flags;
};

extern "C" void NumPutPadOutput_1a4610(OutIt *ret, Streambuf *sb, IosBase &str, char fill, const char *prefix, s32 plen, const char *digits, s32 dlen) {
    s32 pad;
    s32 i;
    s32 j;
    s32 k;
    u16 adj;
    OutIt out;

    out.sb = sb;

    pad = 0;
    if ((s64)(plen + dlen) < str.width) {
        pad = str.width - (plen + dlen);
    }
    adj = str.flags & 0xB0;
    if (adj != 0x20 && adj != 0x10) {
        for (i = 0; i < pad; i++) {
            *out++ = fill;
        }
    }
    for (i = 0; i < plen; i++) {
        char c = *prefix++;
        *out++ = c;
    }
    if (adj == 0x10) {
        for (j = 0; j < pad; j++) {
            *out++ = fill;
        }
    }
    for (j = 0; j < dlen; j++) {
        char c = *digits++;
        *out++ = c;
    }
    if (adj == 0x20) {
        for (k = 0; k < pad; k++) {
            *out++ = fill;
        }
    }
    str.width = 0;
    *ret = out;
}
