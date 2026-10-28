/* rgp:protos */
#define RGP_SELF_TextEntryCommit_4348b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad00[0x30];
    char name[0xB0];
    s16 mode;
} Obj;

typedef struct Ctx {
    u8 pad00[0x24];
    s32 h;
} Ctx;

typedef struct Q {
    u8 pad[0xB0];
} Q;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(char *, const char *);
u32 strlen(const char *);
extern s16 D_00484128;

#pragma opt_lifetimes off
void TextEntryCommit_4348b0(Obj *obj) {
    char *z;
    char buf[0xAE] __attribute__((aligned(16)));
    Q q __attribute__((aligned(16)));
    Ctx *ctx;
    char *dst;
    char *p;
    u32 n;
    s32 i;
    s32 c;

    ctx = ((Ctx *)GetGameData_1fede0());
    dst = ((char *)RecordGetNameSlot_430580(ctx->h, 0));
    z = buf;
    n = 0xAE;
    if (z != 0) {
        do {
            *z = 0;
            n--;
            z++;
        } while (n != 0);
    }
    strcpy(buf, obj->name);
    p = &buf[0xAD];
    for (i = 0; i < 0xAE; p--, i++) {
        c = *p;
        if (c == '*' || c == ' ') {
            *p = 0;
        } else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            goto done;
        }
    }
done:
    if (obj->mode == 0) {
        TextEntryGetString_435640(obj, &q);
        if (InsectTeamCodeDecode_431570(ctx->h, &q, dst) != 0) {
            D_00484128 = 2;
            TextEntrySetState_434410(obj, 0x6D63, 0);
        } else {
            TextEntrySetState_434410(obj, 0x6D6A, 0);
        }
    } else if (obj->mode == 2) {
        if (strlen(buf) != 0) {
            if (dst != 0) {
                strcpy(dst, buf);
                D_00484128 = 2;
                TextEntrySetState_434410(obj, 0x6D63, 0);
            }
        } else {
            TextEntrySetState_434410(obj, 0x6D6A, 0);
        }
    } else if (obj->mode == 3) {
        if (strlen(buf) != 0) {
            if (dst != 0) {
                strcpy(dst + 9, buf);
                D_00484128 = 2;
                TextEntrySetState_434410(obj, 0x6D63, 0);
            }
        } else {
            TextEntrySetState_434410(obj, 0x6D6A, 0);
        }
    } else if (obj->mode == 1) {
        if (strlen(buf) != 0) {
            D_00484128 = 2;
            strcpy(obj->name, buf);
            TextEntrySetState_434410(obj, 0x6D63, 0);
        } else {
            TextEntrySetState_434410(obj, 0x6D6A, 0);
        }
    }
}
