#include "types.h"

typedef struct T_FUN_0018e090 T_FUN_0018e090;

typedef struct Obj_FUN_0018e090 {
    T_FUN_0018e090 *f00;
} Obj_FUN_0018e090;

extern T_FUN_0018e090 *MemStackNew_14e230(s32 n);
extern T_FUN_0018e090 *ListNodeCtor_18e1a0(T_FUN_0018e090 *m);
extern void ListLinkAtTail_18e110(T_FUN_0018e090 *a, T_FUN_0018e090 *b);

T_FUN_0018e090 *ListAppendNew_18e090(Obj_FUN_0018e090 *o, s32 flag)
{
    T_FUN_0018e090 *m;

    if (flag == 0) {
        return (T_FUN_0018e090 *)0;
    }
    m = MemStackNew_14e230(0x18);
    if (m != 0) {
        m = ListNodeCtor_18e1a0(m);
    }
    if (m == 0) {
        return (T_FUN_0018e090 *)0;
    }
    if (o->f00 == 0) {
        o->f00 = m;
    } else {
        ListLinkAtTail_18e110(o->f00, m);
    }
    return m;
}
