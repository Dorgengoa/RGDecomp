#include "types.h"

typedef struct Info {
    u32 flags;
    s32 a[5];
    char name[16];
} Info;

typedef struct Big {
    u8 pad[0x60];
    Info info;
} Big;

char *SlotGetInt_15f720(s64 *);
s32 VariantGetInt_15f780(s64 *);
s32 strcmp(const char *, const char *);
char *strcpy(char *, const char *);
u32 strlen(const char *);
char *strncpy(char *, const char *, u32);

extern char D_00459C70[0x400];
extern char D_00459C78[0x400];
extern char D_00459C80[0x400];
extern char D_00459C88[0x400];
extern char D_00459C90[0x400];
extern char D_00459CA0[0x400];
extern Big *D_004812DC;

s32 MapCfgFuncEventData_18a830(s64 *args, s32 argc) {
    char *s;
    u32 flags;
    Info *p;
    char *nm;

    if (D_004812DC == 0) {
        return 0;
    }
    s = SlotGetInt_15f720(args++);
    flags = 0;
    p = &D_004812DC->info;
    p->a[0] = VariantGetInt_15f780(args++);
    p->a[1] = VariantGetInt_15f780(args++);
    p->a[2] = VariantGetInt_15f780(args++);
    p->a[3] = VariantGetInt_15f780(args++);
    p->a[4] = VariantGetInt_15f780(args++);
    if (s != 0) {
        if (strcmp(s, D_00459C70) == 0) {
            flags = 0x10A;
        } else if (strcmp(s, D_00459C78) == 0) {
            flags = 0x11A;
        } else if (strcmp(s, D_00459C80) == 0) {
            flags = 0x20;
        } else if (strcmp(s, D_00459C88) == 0) {
            flags = 0x40;
        } else if (strcmp(s, D_00459C90) == 0) {
            flags = 0x8A;
        } else if (strcmp(s, D_00459CA0) == 0) {
            flags = 0x202;
            p->a[0] = 1;
        }
    }
    p->flags = flags;
    if (argc >= 7) {
        nm = SlotGetInt_15f720(args++);
        if (nm != 0) {
            if (strlen(nm) >= 16) {
                strncpy(p->name, nm, 15);
                p->name[15] = 0;
            } else {
                strcpy(p->name, nm);
            }
        }
    }
    if (argc >= 8) {
        if (VariantGetInt_15f780(args++) != 0) {
            p->flags |= 2;
        }
    }
    if (argc >= 9) {
        if (VariantGetInt_15f780(args++) != 0) {
            p->flags |= 4;
        }
    }
    if (argc >= 10) {
        if (VariantGetInt_15f780(args++) != 0) {
            p->flags |= 0x100;
        } else {
            p->flags &= ~0x100;
        }
    }
    return 1;
}
