#include "types.h"
#undef NULL
#define NULL 0

typedef struct {
    s32 type;
    union {
        s32 i;
        f32 f;
    } v;
} Arg;

typedef void (*CmdFunc)(Arg *, s32);
typedef void (*DefFunc)(u16, Arg *, s32);

typedef struct {
    s32 unk0;
    CmdFunc exec;
} Cmd;

typedef struct {
    u8 pad0[0x404];
    DefFunc def;
    s32 active;
    s32 count;
    s32 *limit;
    u8 *start;
    u8 pad418[0x420 - 0x418];
    u8 *cur;
    s32 pc;
    Arg args[0x80];
    u8 quiet;
} VM;

extern "C" {
Cmd *CfgVmFindCmd_42f470(VM *, u16);
s32 CfgVmGetString_42f3d0(VM *, s32);
}

static inline s32 align4(s32 x) {
    return x + (4 - x % 4) % 4;
}

static inline s32 flag_bytes(s32 bits) {
    return bits / 8 + (bits % 8 > 0);
}

extern "C" u8 *CfgVmStep_42f6e0(VM *vm, s32 run) {
    u8 *op;
    s32 n;
    s32 *src;
    Arg *dst;
    Cmd *cmd;
    u8 *p;
    s32 c;
    u32 bits;
    s32 i;
    bool ok;
    u32 id;
    s32 off;


    if (vm->active == 0 || vm->count <= 0 || vm->limit == NULL) {
        return NULL;
    }
    if (vm->pc >= *vm->limit) {
        return NULL;
    }
    op = vm->cur;
    if (op == NULL) {
        vm->cur = vm->start;
    } else {
        c = op[2];
        off = align4(flag_bytes(c * 2) + 3);
        vm->cur = op + align4(off + c * 4);
    }
    op = vm->cur;
    if (op != NULL && run != 0) {
        id = *(u16 *)op;
        n = op[2];
        cmd = CfgVmFindCmd_42f470(vm, id);
        ok = false;
        if (cmd != NULL) {
            ok = true;
        } else if (vm->quiet == 0 && vm->def != NULL) {
            ok = true;
        }
        if (ok) {
            op = vm->cur;
            p = op + 3;
            src = (s32 *)(op + align4(flag_bytes(op[2] * 2) + 3));
            dst = vm->args;
            bits = 0;
            for (i = 0; i < n; i++) {
                if (i >= 0x80) {
                    break;
                }
                if (i % 4 == 0) {
                    if (i > 0) {
                        p++;
                    }
                    bits = *p;
                } else {
                    bits = (u8)(bits >> 2);
                }
                switch ((u8)bits & 3) {
                case 0:
                    dst->type = 0;
                    dst->v.i = CfgVmGetString_42f3d0(vm, *src);
                    break;
                case 1:
                    dst->type = 1;
                    dst->v.i = *src;
                    break;
                case 2:
                    dst->type = 2;
                    dst->v.f = *(f32 *)src;
                    break;
                default:
                    continue;
                }
                src++;
                dst++;
            }
            if (cmd != NULL) {
                cmd->exec(vm->args, n);
            } else {
                vm->def(id, vm->args, n);
            }
        }
    }
    vm->pc++;
    return vm->cur;
    return NULL;
}
