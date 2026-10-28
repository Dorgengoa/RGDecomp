/* Retail traps integer division by zero itself (`bnez d; div; break 7`). */
#pragma divbyzerocheck on
#include "types.h"

/* The SB2 script bytecode interpreter.

   The instruction stream is a flat array of 12-byte {op, a, b} records and
   vm->pc points straight into it, so "advance" is one ++ at the bottom of the
   loop.  Dispatch is a 31-entry jump table; anything at or above 0x1F falls
   out of the switch and is simply skipped.

   Values live on an operand stack of 8-byte {type, value} slots:

       type 0  integer      type 2  code address (a label)
       type 1  float        type 3  slot reference (an lvalue)

   Every push bounds-checks and dies loudly on overflow, which is why
   "RUNTIME ERROR: %s" / "stack overflow" appears 90-odd times in one
   function -- the push helpers below are inlined at every site.  The
   arithmetic opcodes name themselves in their own error strings (_ADD,
   _SUB, _MUL, _DIV, _INVT, _SIN, _COS, _ITOF, _FTOI, _CMP), which is where
   the opcode numbering below was read off.

   Built as C++: every pop() result is a separate return temporary that is
   then COPIED into the destination (retail's per-site temps at 0x130..0x248
   plus the shared operand homes at 0x248/0x250/0x258); C RVOs the pop
   straight into the destination. */

/* The opcode set.  TEN OF THESE ARE RECOVERED, NOT INVENTED: the interpreter
   prints its own mnemonic when an operand has the wrong type, so the binary
   itself supplies _ADD, _SUB, _MUL, _DIV, _INVT, _ITOF, _FTOI, _CMP, _SIN and
   _COS -- see the error strings below.  The rest are named from what the
   handler does and are marked so. */
enum Opcode {
    OP_PUSHVAR   = 1  , /* inferred */
    OP_PUSHREF   = 2  , /* inferred */
    OP_PUSHIMM   = 3  , /* inferred */
    OP_DROP      = 4  , /* inferred */
    OP_STORE     = 5  , /* inferred */
    OP_ADD       = 6  , /* "_ADD" */
    OP_SUB       = 7  , /* "_SUB" */
    OP_MUL       = 8  , /* "_MUL" */
    OP_DIV       = 9  , /* "_DIV" */
    OP_MOD       = 10 , /* inferred */
    OP_INVT      = 11 , /* "_INVT" */
    OP_ITOF      = 12 , /* "_ITOF" */
    OP_FTOI      = 13 , /* "_FTOI" */
    OP_CMP       = 14 , /* "_CMP" */
    OP_RET       = 15 , /* inferred */
    OP_JMP       = 16 , /* inferred */
    OP_AND       = 17 , /* inferred */
    OP_OR        = 18 , /* inferred */
    OP_CALL      = 19 , /* inferred */
    OP_TRACE     = 20 , /* inferred */
    OP_NATIVE    = 21 , /* inferred */
    OP_YIELD     = 23 , /* inferred */
    OP_BITAND    = 24 , /* inferred */
    OP_BITOR     = 25 , /* inferred */
    OP_NOT       = 26 , /* inferred */
    OP_STOP      = 27 , /* inferred */
    OP_WAIT      = 28 , /* inferred */
    OP_SIN       = 29 , /* "_SIN" */
    OP_COS       = 30 , /* "_COS" */
};

/* The relation the compare opcode carries in its `a` operand.  Inferred from
   the six branch shapes, not named by the binary. */
enum CmpRel {
    CMP_EQ = 0x28,
    CMP_NE = 0x29,
    CMP_LT = 0x2A,
    CMP_LE = 0x2B,
    CMP_GT = 0x2C,
    CMP_GE = 0x2D
};

typedef struct Instr {
    s32 op;            /* +0x00 */
    s32 a;             /* +0x04 */
    s32 b;             /* +0x08 */
} Instr;

typedef struct Slot {
    s32 type;          /* +0x00 */
    union {
        s32 i;
        f32 f;
        u8 *p;
    } u;               /* +0x04 */
} Slot;

/* The same eight bytes, 8-aligned: copying one is a single ld/sd pair. */
typedef struct Slot8 {
    s32 type;
    s32 i;
} __attribute__((aligned(8))) Slot8;

typedef struct Entry {
    s32 code;          /* +0x00, offset into the code section */
    const char *name;  /* +0x04, what the error messages print */
    s32 slots;         /* +0x08, total stack slots */
    s32 args;          /* +0x0C, of which this many arrive filled */
} Entry;

/* A call frame is 12 bytes: the caller's pc, frame base and entry record. */
typedef struct Frame {
    Instr *pc;         /* +0x00 */
    u8 *frameBase;     /* +0x04 */
    Entry *entry;      /* +0x08 */
} Frame;

typedef s32 (*Native)(Slot *args, s32 argc);

typedef struct ScriptVm {
    s32 state;         /* +0x00 */
    s32 nativeCount;   /* +0x04 */
    Native *natives;   /* +0x08 */
    s32 stackSlots;    /* +0x0C */
    u8 *stack;         /* +0x10 */
    u8 *stackTop;      /* +0x14 */
    u8 *stackEnd;      /* +0x18 */
    u8 *globals;       /* +0x1C */
    s32 frameCount;    /* +0x20 */
    u8 *frames;        /* +0x24 */
    u8 *frameTop;      /* +0x28 */
    u8 *framesEnd;     /* +0x2C */
    u8 *frameBase;     /* +0x30 */
    Entry *entry;      /* +0x34 */
    Instr *pc;         /* +0x38 */
    s32 halted;        /* +0x3C */
    s32 suspend;       /* +0x40 */
    void *blob;        /* +0x44 */
    u8 *code;          /* +0x48 */
    s32 result;        /* +0x4C, what the outermost return latches */
    s32 steps;         /* +0x50 */
} ScriptVm;

typedef struct Console {
    u8 pad00[0x8];
    void *unk08;       /* +0x08 */
    void *out;         /* +0x0C */
} Console;

/* `const` keeps the console pointer off %gp_rel, and every string has to be
   declared as the external the reference names or the relocation points at
   mwcc's own @N label instead. */
extern "C" {
extern Console *const volatile D_00449858;
extern char D_00459230[];   /* "RUNTIME ERROR: %s"                       */
extern char D_00459248[];   /* "stack overflow"                          */
extern char D_00459260[];   /* "...: %s: operand is not integer"         */
extern char D_00459290[];   /* "...at _CMP: %s: operand is not number"   */
extern char D_004592D0[];   /* _ADD                                      */
extern char D_00459310[];   /* _SUB                                      */
extern char D_00459350[];   /* _MUL                                      */
extern char D_00459380[];   /* "Divide by 0"                             */
extern char D_00459390[];   /* _DIV                                      */
extern char D_004593C8[];   /* "Modulo by 0"                             */
extern char D_004593E0[];   /* _INVT                                     */
extern char D_00459420[];   /* _SIN                                      */
extern char D_00459460[];   /* _COS                                      */
extern char D_004594A0[];   /* the same "not integer", in Shift-JIS      */
extern char D_004594D0[];   /* _ITOF                                     */
extern char D_00459510[];   /* _FTOI                                     */

extern void Fprintf_12f9a0(void *out, const char *fmt, const char *what);
extern void Exit_12f4e0(s32 code);
extern void Fflush_12f590(void *out);
extern void memset(void *dst, s32 fill, s32 len);
extern f32 Cosf_128d30(f32 x);   /* cosf */
extern f32 Sinf_128fd0(f32 x);   /* sinf */
}

/* ---- the operand stack ------------------------------------------------- */

static inline void checkStack(ScriptVm *vm)
{
    if (vm->stackTop >= vm->stackEnd) {
        Fprintf_12f9a0(D_00449858->out, D_00459230, D_00459248);
        Exit_12f4e0(-1);
    }
}

/* Spelled through a named OLD-TOP local: retail keeps the old pointer live
   and reads -8/-4 off it. */
static inline Slot pop(ScriptVm *vm)
{
    u8 *top;

    top = vm->stackTop;
    vm->stackTop = top - 8;
    return *(Slot *)(top - 8);
}

/* A slot is true when either word is non-zero.  The reference keeps the pop
   temporary in its own 0x1F0-family home; the 8-aligned copy is retail's
   `ld`/`sd` into a second home that both words are then read back from. */
static inline u8 truthy(const Slot &v)
{
    Slot8 c __attribute__((aligned(16))) = *(Slot8 *)&v;

    return !(c.type == 0) || !(c.i == 0);
}

/* The `*(f32 *)&` read takes v's address: the shared `v` home (0x258) is then
   stored whole, as retail does in STORE and RET. */
static inline void pushSlot(ScriptVm *vm, Slot v)
{
    Slot *top;

    checkStack(vm);
    top = (Slot *)vm->stackTop;
    vm->stackTop = (u8 *)(top + 1);
    top->type = v.type;
    top->u.f = (*(f32 *)&v.u.f);
}

static inline void pushInt(ScriptVm *vm, s32 v)
{
    Slot *top;

    checkStack(vm);
    ((Slot *)vm->stackTop)->type = 0;
    top = (Slot *)vm->stackTop;
    vm->stackTop = (u8 *)(top + 1);
    top->u.i = v;
}

static inline void pushFloat(ScriptVm *vm, f32 v)
{
    Slot *top;

    checkStack(vm);
    ((Slot *)vm->stackTop)->type = 1;
    top = (Slot *)vm->stackTop;
    vm->stackTop = (u8 *)(top + 1);
    top->u.f = v;
}

static inline void pushCode(ScriptVm *vm, u8 *v)
{
    Slot *top;

    checkStack(vm);
    ((Slot *)vm->stackTop)->type = 2;
    top = (Slot *)vm->stackTop;
    vm->stackTop = (u8 *)(top + 1);
    top->u.p = v;
}

static inline void pushRef(ScriptVm *vm, Slot *v)
{
    Slot *top;

    checkStack(vm);
    ((Slot *)vm->stackTop)->type = 3;
    top = (Slot *)vm->stackTop;
    vm->stackTop = (u8 *)(top + 1);
    top->u.p = (u8 *)v;
}

/* The compare opcode pushes its result with the relation evaluated AFTER the
   overflow check, into a function-level variable (retail colours it after the
   stack-top loads).  Integer relations are evaluated before the type stamp,
   float ones after it. */
#define PUSH_INT_RESULT(vm, r, expr) {                  \
    Slot *top;                                          \
    checkStack(vm);                                     \
    r = (expr);                                         \
    ((Slot *)(vm)->stackTop)->type = 0;                 \
    top = (Slot *)(vm)->stackTop;                       \
    (vm)->stackTop = (u8 *)(top + 1);                   \
    top->u.i = r;                                       \
}

#define PUSH_FLOAT_RESULT(vm, r, expr) {                \
    Slot *top;                                          \
    checkStack(vm);                                     \
    ((Slot *)(vm)->stackTop)->type = 0;                 \
    r = (expr);                                         \
    top = (Slot *)(vm)->stackTop;                       \
    (vm)->stackTop = (u8 *)(top + 1);                   \
    top->u.i = r;                                       \
}

/* An index or a bitwise operand has to be an integer; the report names the
   routine the script is executing, not the opcode.  The entry pointer is an
   ARGUMENT evaluated after the pop (that is what gives retail's $a0/$a1
   colouring), the operand's address is taken so the by-value copy is
   materialised, and the error block is a cold block reached by goto. */
static inline s32 toInt(Slot v, Entry *e)
{
    s32 r;

    r = (*(s32 *)&v.u.i);
    if (v.type != 0) {
        goto bad;
    }
    return r;
bad:
    Fprintf_12f9a0(D_00449858->out, D_00459260, e->name);
    Exit_12f4e0(-1);
    r = 0;
    return r;
}

/* ---- the arithmetic opcodes --------------------------------------------
   Written as macros over the interpreter's own `a`/`b` (one shared pair of
   homes, 0x248/0x250, for every opcode).  The first type test reads `a`
   directly -- retail forwards the value it just copied -- and every later
   one goes through a volatile pointer, because retail reloads the type at
   each join.  The value words are read plainly and stay in registers. */
#define doAdd(vm, a, b) {                                               \
    volatile Slot *pa = &a;                                             \
    if (a.type == 0 && b.type == 0) {                                   \
        pushInt(vm, a.u.i + b.u.i);                                     \
    } else if (pa->type == 1 && b.type == 1) {                          \
        pushFloat(vm, a.u.f + b.u.f);                                   \
    } else if (pa->type == 0 && b.type == 1) {                          \
        pushFloat(vm, (f32)a.u.i + b.u.f);                              \
    } else if (pa->type == 1 && b.type == 0) {                          \
        pushFloat(vm, a.u.f + (f32)b.u.i);                              \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_004592D0, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

#define doSub(vm, a, b) {                                               \
    volatile Slot *pa = &a;                                             \
    if (a.type == 0 && b.type == 0) {                                   \
        pushInt(vm, a.u.i - b.u.i);                                     \
    } else if (pa->type == 1 && b.type == 1) {                          \
        pushFloat(vm, a.u.f - b.u.f);                                   \
    } else if (pa->type == 0 && b.type == 1) {                          \
        pushFloat(vm, (f32)a.u.i - b.u.f);                              \
    } else if (pa->type == 1 && b.type == 0) {                          \
        pushFloat(vm, a.u.f - (f32)b.u.i);                              \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_00459310, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

#define doMul(vm, a, b) {                                               \
    volatile Slot *pa = &a;                                             \
    if (a.type == 0 && b.type == 0) {                                   \
        pushInt(vm, a.u.i * b.u.i);                                     \
    } else if (pa->type == 1 && b.type == 1) {                          \
        pushFloat(vm, a.u.f * b.u.f);                                   \
    } else if (pa->type == 0 && b.type == 1) {                          \
        pushFloat(vm, (f32)a.u.i * b.u.f);                              \
    } else if (pa->type == 1 && b.type == 0) {                          \
        pushFloat(vm, a.u.f * (f32)b.u.i);                              \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_00459350, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

/* The divisor was already read into `d` for the divide-by-zero report, and
   retail keeps using that register. */
#define doDiv(vm, a, b, d) {                                            \
    volatile Slot *pa = &a;                                             \
    if (a.type == 0 && b.type == 0) {                                   \
        pushInt(vm, a.u.i / d);                                         \
    } else if (pa->type == 1 && b.type == 1) {                          \
        pushFloat(vm, a.u.f / b.u.f);                                   \
    } else if (pa->type == 0 && b.type == 1) {                          \
        pushFloat(vm, (f32)a.u.i / b.u.f);                              \
    } else if (pa->type == 1 && b.type == 0) {                          \
        pushFloat(vm, a.u.f / (f32)d);                                  \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_00459390, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

/* Integer operands are compared from registers (x, y); everything else is
   widened into the same pair of callee-saved floats and drops into ONE shared
   relation switch -- two inner jump tables, not four.  The mismatched-type
   report falls through into that switch rather than breaking out of it. */
#define doCmp(vm, a, b, x, y, r) {                                      \
    volatile Slot *pa = &a;                                             \
    f32 fb;                                                             \
    f32 fa;                                                             \
                                                                        \
    if (a.type == 0 && b.type == 0) {                                   \
        x = a.u.i;                                                      \
        y = b.u.i;                                                      \
        switch (vm->pc->a) {                                            \
        case CMP_EQ: PUSH_INT_RESULT(vm, r, y == x); break;             \
        case CMP_NE: PUSH_INT_RESULT(vm, r, y != x); break;             \
        case CMP_LT: PUSH_INT_RESULT(vm, r, x < y); break;              \
        case CMP_LE: PUSH_INT_RESULT(vm, r, x <= y); break;             \
        case CMP_GT: PUSH_INT_RESULT(vm, r, x > y); break;              \
        case CMP_GE: PUSH_INT_RESULT(vm, r, x >= y); break;             \
        }                                                               \
    } else {                                                            \
        if (pa->type == 1 && b.type == 1) {                             \
            fb = b.u.f;                                                 \
            fa = a.u.f;                                                 \
        } else if (pa->type == 0 && b.type == 1) {                      \
            fa = (f32)a.u.i;                                            \
            fb = b.u.f;                                                 \
        } else if (pa->type == 1 && b.type == 0) {                      \
            fb = (f32)b.u.i;                                            \
            fa = a.u.f;                                                 \
        } else {                                                        \
            Fprintf_12f9a0(D_00449858->out, D_00459290, vm->entry->name); \
            Exit_12f4e0(-1);                                           \
        }                                                               \
        switch (vm->pc->a) {                                            \
        case CMP_EQ: PUSH_FLOAT_RESULT(vm, r, fb == fa); break;         \
        case CMP_NE: PUSH_FLOAT_RESULT(vm, r, fb != fa); break;         \
        case CMP_LT: PUSH_FLOAT_RESULT(vm, r, fa < fb); break;          \
        case CMP_LE: PUSH_FLOAT_RESULT(vm, r, fa <= fb); break;         \
        case CMP_GT: PUSH_FLOAT_RESULT(vm, r, fa > fb); break;          \
        case CMP_GE: PUSH_FLOAT_RESULT(vm, r, fa >= fb); break;         \
        }                                                               \
    }                                                                   \
}

/* ---- the one-operand opcodes -------------------------------------------
   Over the shared `b` home.  Here the value word IS read through its
   address, which is what keeps `b` materialised for the binary opcodes. */
#define doInvt(vm, v) {                                                 \
    if (v.type == 0) {                                                  \
        pushInt(vm, -(*(s32 *)&v.u.i));                                 \
    } else if (v.type == 1) {                                           \
        pushFloat(vm, -(*(f32 *)&v.u.f));                               \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_004593E0, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

#define doSin(vm, v) {                                                  \
    if (v.type == 0) {                                                  \
        pushFloat(vm, Sinf_128fd0((f32)(*(s32 *)&v.u.i)));             \
    } else if (v.type == 1) {                                           \
        pushFloat(vm, Sinf_128fd0((*(f32 *)&v.u.f)));                  \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_00459420, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

#define doCos(vm, v) {                                                  \
    if (v.type == 0) {                                                  \
        pushFloat(vm, Cosf_128d30((f32)(*(s32 *)&v.u.i)));             \
    } else if (v.type == 1) {                                           \
        pushFloat(vm, Cosf_128d30((*(f32 *)&v.u.f)));                  \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_00459460, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

#define doItof(vm, v) {                                                 \
    if (v.type == 0) {                                                  \
        pushFloat(vm, (f32)(*(s32 *)&v.u.i));                           \
    } else if (v.type == 1) {                                           \
        pushFloat(vm, (*(f32 *)&v.u.f));                                \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_004594D0, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

#define doFtoi(vm, v) {                                                 \
    if (v.type == 0) {                                                  \
        pushInt(vm, (*(s32 *)&v.u.i));                                  \
    } else if (v.type == 1) {                                           \
        pushInt(vm, (s32)(*(f32 *)&v.u.f));                             \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_00459510, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

#define doNot(vm, v) {                                                  \
    if (v.type == 0) {                                                  \
        pushInt(vm, (u8)!((*(s32 *)&v.u.i) != 0));                      \
    } else {                                                            \
        Fprintf_12f9a0(D_00449858->out, D_004594A0, vm->entry->name);     \
        Exit_12f4e0(-1);                                               \
    }                                                                   \
}

/* Declaration order v, b, a puts the three shared operand homes at
   0x258 (v), 0x250 (b), 0x248 (a). */
/* Retail did not constant-propagate locals: OR's pushed 1 sits in `i`'s own
   (low-numbered) register, so it is coloured after the stack-top temps
   (li a1,1).  With propagation on, the 1 becomes a fresh last-made temp and
   takes v1. */
#pragma opt_propagation off
extern "C" void ScriptVmExec_173b00(ScriptVm *vm, Instr *start)
{
    Slot v __attribute__((aligned(16)));
    Slot b __attribute__((aligned(16)));
    Slot a __attribute__((aligned(16)));
    Instr *pc;
    s32 i;
    s32 x;
    s32 y;

    vm->pc = start;
    for (;;) {
        pc = vm->pc;
        switch (pc->op) {

        /* ---- 1: push the value of a variable -------------------------
           The operand descriptor is a bit mask, and the four "float"
           forms are the four plain ones shifted up by three: they stamp
           the slot's type before reading it.  Popping the subscript is
           a store into the vm, so everything after one reads vm->pc
           again rather than the cached instruction pointer.  A subscript
           used once is converted INSIDE the expression; one used twice
           is converted into `i` first (two different frame families). */
        case OP_PUSHVAR:
            switch (pc->b) {
            case 1:
                pushSlot(vm, ((Slot *)vm->frameBase)[pc->a]);
                break;
            case 0x40:
                pushSlot(vm, ((Slot *)vm->globals)[pc->a]);
                break;
            case 2:
                pushSlot(vm, ((Slot *)vm->frameBase + vm->pc->a)[toInt(pop(vm), vm->entry)]);
                break;
            case 4:
                pushSlot(vm, ((Slot *)((Slot *)vm->frameBase + vm->pc->a)->u.p)[toInt(pop(vm), vm->entry)]);
                break;
            case 8:
                ((Slot *)vm->frameBase + pc->a)->type = 1;
                pushSlot(vm, ((Slot *)vm->frameBase)[vm->pc->a]);
                break;
            case 0x200:
                ((Slot *)vm->globals + pc->a)->type = 1;
                pushSlot(vm, ((Slot *)vm->globals)[vm->pc->a]);
                break;
            case 0x10:
                i = toInt(pop(vm), vm->entry);
                ((Slot *)vm->frameBase + vm->pc->a)[i].type = 1;
                pushSlot(vm, ((Slot *)vm->frameBase + vm->pc->a)[i]);
                break;
            case 0x20:
                i = toInt(pop(vm), vm->entry);
                ((Slot *)((Slot *)vm->frameBase + vm->pc->a)->u.p)[i].type = 1;
                pushSlot(vm, ((Slot *)((Slot *)vm->frameBase + vm->pc->a)->u.p)[i]);
                break;
            }
            break;

        /* ---- 2: push a reference to a variable -----------------------
           Same descriptor bits as PUSHVAR, but the "float" forms do NOT
           stamp the type here: a reference is just an address. */
        case OP_PUSHREF:
            switch (pc->b) {
            case 1:
                pushRef(vm, (Slot *)vm->frameBase + pc->a);
                break;
            case 0x40:
                pushRef(vm, (Slot *)vm->globals + pc->a);
                break;
            case 2:
                pushRef(vm, (Slot *)vm->frameBase + vm->pc->a + toInt(pop(vm), vm->entry));
                break;
            case 4:
                pushRef(vm, (Slot *)((Slot *)vm->frameBase + vm->pc->a)->u.p + toInt(pop(vm), vm->entry));
                break;
            case 8:
                pushRef(vm, (Slot *)vm->frameBase + vm->pc->a);
                break;
            case 0x200:
                pushRef(vm, (Slot *)vm->globals + vm->pc->a);
                break;
            case 0x10:
                pushRef(vm, (Slot *)vm->frameBase + vm->pc->a + toInt(pop(vm), vm->entry));
                break;
            case 0x20:
                pushRef(vm, (Slot *)((Slot *)vm->frameBase + vm->pc->a)->u.p + toInt(pop(vm), vm->entry));
                break;
            }
            break;

        /* ---- 5: assign through a reference, leaving the value -------- */
        case OP_STORE:
            v = pop(vm);
            *(Slot *)pop(vm).u.p = v;
            pushSlot(vm, v);
            break;

        /* ---- 3: push an immediate ------------------------------------ */
        case OP_PUSHIMM:
            if (pc->a == 1) {
                pushInt(vm, pc->b);
            } else if (pc->a == 3) {
                pushCode(vm, vm->code + pc->b);
            } else if (pc->a == 2) {
                pushFloat(vm, *(f32 *)&pc->b);
            }
            break;

        /* ---- 4: drop ------------------------------------------------- */
        case OP_DROP:
            vm->stackTop -= 8;
            break;

        /* ---- 16: jump ------------------------------------------------ */
        case OP_JMP:
            if (vm->suspend == 0) {
                vm->pc = (Instr *)(vm->code + pc->a);
                continue;
            }
            break;

        /* ---- 18: short-circuit OR ------------------------------------ */
        case OP_OR:
            if (vm->suspend == 0) {
                if (truthy(pop(vm)) != 0) {
                    if (vm->pc->b != 0) {
                        /* open-coded pushInt so the 1 lives in `i` */
                        checkStack(vm);
                        ((Slot *)vm->stackTop)->type = 0;
                        i = 1;
                        {
                            Slot *top = (Slot *)vm->stackTop;
                            vm->stackTop = (u8 *)(top + 1);
                            top->u.i = i;
                        }
                    }
                    vm->pc = (Instr *)(vm->code + vm->pc->a);
                    continue;
                }
            }
            break;

        /* ---- 17: short-circuit AND ----------------------------------- */
        case OP_AND:
            if (vm->suspend == 0) {
                if (truthy(pop(vm)) == 0) {
                    if (vm->pc->b != 0) {
                        pushInt(vm, 0);
                    }
                    vm->pc = (Instr *)(vm->code + vm->pc->a);
                    continue;
                }
            }
            break;

        /* ---- 14: compare --------------------------------------------- */
        case OP_CMP:
            b = pop(vm);
            a = pop(vm);
            doCmp(vm, a, b, x, y, i);
            break;

        /* ---- 6, 7, 8: add, subtract, multiply ------------------------ */
        case OP_ADD:
            b = pop(vm);
            a = pop(vm);
            doAdd(vm, a, b);
            break;

        case OP_SUB:
            b = pop(vm);
            a = pop(vm);
            doSub(vm, a, b);
            break;

        case OP_MUL:
            b = pop(vm);
            a = pop(vm);
            doMul(vm, a, b);
            break;

        /* ---- 9: divide ----------------------------------------------- */
        case OP_DIV:
            b = pop(vm);
            y = b.u.i;
            if (y == 0) {
                Fprintf_12f9a0(D_00449858->out, D_00459230, D_00459380);
                Exit_12f4e0(-1);
            }
            a = pop(vm);
            doDiv(vm, a, b, y);
            break;

        /* ---- 10: modulo ---------------------------------------------- */
        case OP_MOD:
            y = toInt(pop(vm), vm->entry);
            if (y == 0) {
                Fprintf_12f9a0(D_00449858->out, D_00459230, D_004593C8);
                Exit_12f4e0(-1);
            }
            pushInt(vm, toInt(pop(vm), vm->entry) % y);
            break;

        /* ---- 24, 25: bitwise and, or --------------------------------- */
        case OP_BITAND:
            y = toInt(pop(vm), vm->entry);
            pushInt(vm, y & toInt(pop(vm), vm->entry));
            break;

        case OP_BITOR:
            y = toInt(pop(vm), vm->entry);
            pushInt(vm, y | toInt(pop(vm), vm->entry));
            break;

        /* ---- 11: negate ---------------------------------------------- */
        case OP_INVT:
            b = pop(vm);
            doInvt(vm, b);
            break;

        /* ---- 29, 30: sine, cosine ------------------------------------ */
        case OP_SIN:
            b = pop(vm);
            doSin(vm, b);
            break;

        case OP_COS:
            b = pop(vm);
            doCos(vm, b);
            break;

        /* ---- 26: logical not ----------------------------------------- */
        case OP_NOT:
            b = pop(vm);
            doNot(vm, b);
            break;

        /* ---- 12, 13: int to float, float to int ---------------------- */
        case OP_ITOF:
            b = pop(vm);
            doItof(vm, b);
            break;

        case OP_FTOI:
            b = pop(vm);
            doFtoi(vm, b);
            break;

        /* ---- 20: drop arguments and report --------------------------- */
        case OP_TRACE:
            vm->stackTop -= pc->a * 8;
            x = vm->pc->a;
            for (i = 0; i < x; i++) {
                Fflush_12f590(D_00449858->unk08);
            }
            break;

        /* ---- 21: call a native ---------------------------------------
           The slot under the arguments carries the table index; everything
           above it is the argument list. */
        case OP_NATIVE:
            vm->stackTop -= pc->a * 8;
            if (vm->suspend == 0) {
                i = ((Slot *)vm->stackTop)->u.i;
                x = vm->pc->a;
                if (i >= 0 && i < vm->nativeCount) {
                    /* named: the table base loads before the index scales */
                    Native f __attribute__((aligned(16))) = vm->natives[i];
                    if (f != 0) f((Slot *)vm->stackTop + 1, x - 1);
                }
            }
            break;

        /* ---- 27: stop ------------------------------------------------ */
        case OP_STOP:
            vm->halted = 1;
            vm->pc = 0;
            return;

        /* ---- 19: call ------------------------------------------------ */
        case OP_CALL: {
            Entry *e;

            e = (Entry *)(vm->code + pc->b);
            if (vm->frameTop >= vm->framesEnd) {
                Exit_12f4e0(-2);
            }
            ((Frame *)vm->frameTop)->pc = pc;
            ((Frame *)vm->frameTop)->entry = vm->entry;
            ((Frame *)vm->frameTop)->frameBase = vm->frameBase;
            vm->frameBase = vm->stackTop - e->args * 8;
            vm->stackTop = vm->frameBase + e->slots * 8;
            vm->entry = e;
            vm->frameTop += 0xC;
            memset(vm->frameBase + vm->entry->args * 8, 0,
                   (vm->entry->slots - vm->entry->args) * 8);
            checkStack(vm);
            x = e->code;
            vm->pc = (Instr *)(vm->code + x);
            vm->pc = vm->pc - 1;
            break;
        }

        /* ---- 15: return ----------------------------------------------
           With no frame left this is the outermost return: the value is
           latched into vm->result and the interpreter stops. */
        case OP_RET:
            v = pop(vm);
            if (vm->frameTop != vm->frames) {
                vm->stackTop = vm->frameBase;
                vm->frameTop -= 0xC;
                vm->frameBase = ((Frame *)vm->frameTop)->frameBase;
                vm->entry = ((Frame *)vm->frameTop)->entry;
                vm->pc = ((Frame *)vm->frameTop)->pc;
            } else {
                vm->result = (*(s32 *)&v.u.i);
                pushSlot(vm, v);
                vm->pc = 0;
                vm->halted = 1;
                return;
            }
            pushSlot(vm, v);
            break;

        /* ---- 23: yield ----------------------------------------------- */
        case OP_YIELD:
            if (vm->suspend == 0) {
                vm->pc = pc + 1;
                return;
            }
            break;

        /* ---- 28: wait ------------------------------------------------ */
        case OP_WAIT:
            vm->steps++;
            if (vm->suspend != 0) {
                vm->suspend = 0;
                vm->pc = vm->pc + 1;
                return;
            }
            break;
        }
        vm->pc = vm->pc + 1;
    }
}
