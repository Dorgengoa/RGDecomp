#include "types.h"

typedef struct B28 { u8 pad[0x28]; } B28;
typedef struct A4 { u8 pad[4]; } A4;

typedef struct S {
    s32 id;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 fpad : 5;
    A4 a[2];
    u8 mD;
    u8 mE;
    u8 mF;
    B28 b[30];
    s8 c[6];
    u8 m4C6;
    u8 m4C7;
    s16 m4C8;
    s16 m4CA;
} S;

extern void RecordStateSaveSlotInitMaybe_4324a0(A4 *);
extern void InsectTeamMemberInit_4325b0(B28 *);


void RecordPayloadInitKind1E_432370(S *s)
{
    B28 *p;
    s32 i;
    s8 *q;
    A4 *pa;
    u8 v = 0;

    s->id = 0x12E;
    s->f0 = v;
    s->f1 = v;
    s->f2 = v;
    pa = s->a;
    RecordStateSaveSlotInitMaybe_4324a0(pa);
    RecordStateSaveSlotInitMaybe_4324a0(pa + 1);
    s->mD = 0;
    s->mE = 0;
    p = s->b;
    i = 0;
    do {
        InsectTeamMemberInit_4325b0(p);
        i++;
        p++;
    } while (i < 30);
    q = s->c;
    i = 0;
    do {
        i++;
        *q = -1;
        q++;
    } while (i < 6);
    s->m4C6 = 0;
    s->m4C6 = 1;
    s->m4C8 = 0;
    s->m4CA = 0;
}
