/* rgp:protos */
#define RGP_SELF_CharaEffEntryClone_230260 1
#define RGP_SELF_REF 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 v[6]; } B24;
typedef struct { f32 x, y, z; } V3;
typedef struct { s16 a, b, c; } S6;
typedef struct Obj {
    B24 m0;
    B24 m18;
    V3 v30;
    V3 v3c;
    V3 v48;
    char *p54;
    char *p58;
    char *p5c;
    u16 f60;
    s16 f62;
    S6 s64;
    S6 s6a;
    S6 s70;
    S6 s76;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline u16 REF(S6 *d, S6 *s, s32 arg3, s32 arg2) {
    char *name = ((char *)ReadU32Bytes_302ec0(s));
    s16 save = s->c;
    char *r;
    d->c = -1;
    ClearU32Bytes_302f20(d);
    if (arg2 == 0) return 0;
    if (name != 0 && *name != 0) {
        r = ((char *)StrPoolIntern_302fd0(arg3, name, arg2));
        if (r == 0) return 0;
        StoreU32Bytes_302ef0(d, r);
    }
    d->c = save;
    return 1;
}

s32 CharaEffEntryClone_230260(Obj *dst, Obj *src, s32 arg2, s32 arg3) {
    char *r;
    CharaEffEntryInit_230760(dst);
    if (arg2 == 0 || arg3 == 0 || src == 0 || src->p54 == 0 || src->p58 == 0) {
        return 0;
    }
    dst->m0 = src->m0;
    dst->m18 = src->m18;
    dst->v30 = src->v30;
    dst->v3c = src->v3c;
    dst->v48 = src->v48;
    dst->p54 = src->p54;
    dst->p58 = src->p58;
    dst->p5c = src->p5c;
    dst->f60 = src->f60;
    dst->f62 = src->f62;
    dst->s64 = src->s64;
    dst->s6a = src->s6a;
    dst->s70 = src->s70;
    dst->s76 = src->s76;

    r = ((char *)StrPoolIntern_302fd0(arg3, src->p54, arg2));
    dst->p54 = r;
    if (r == 0) {
        return 0;
    }
    r = ((char *)TableFindByNameHashed_429540(*(char **)(*(char **)(*(char **)(((char *)GetGameData_1fede0()) + 8) + 0x5C) + 8), src->p58));
    if (r != 0) {
        dst->p58 = *(char **)(r + 8);
    } else {
        dst->p58 = ((char *)StrPoolIntern_302fd0(arg3, src->p58, arg2));
    }
    if (dst->p58 == 0) {
        return 0;
    }
    if (dst->f60 & 0x80) {
        if (!REF(&dst->s64, &src->s64, arg3, arg2)) return 0;
    }
    if (dst->f60 & 0x100) {
        if (!REF(&dst->s6a, &src->s6a, arg3, arg2)) return 0;
    }
    if (dst->f60 & 0x200) {
        if (!REF(&dst->s70, &src->s70, arg3, arg2)) return 0;
    }
    if (dst->f60 & 0x400) {
        if (!REF(&dst->s76, &src->s76, arg3, arg2)) return 0;
    }
    if (dst->f60 & 8) {
        r = ((char *)StrPoolIntern_302fd0(arg3, src->p5c, arg2));
        dst->p5c = r;
        if (r == 0) {
            return 0;
        }
    }
    return 1;
}
