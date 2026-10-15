typedef unsigned int U;
typedef struct B { unsigned char flag:1; unsigned char length:7; } B;
typedef struct S { U flags; U size; char *data; } S;
extern void StringReplaceFill_1075d0(S *, U, U, U, char);
void StringResize_106e20(S *s, U size, char c) {
    U oldSize = (s->flags & 1) ? s->size : ((B *)s)->length;
    if (oldSize < size)
        StringReplaceFill_1075d0(s, oldSize, 0, size - oldSize, c);
    else
        StringReplaceFill_1075d0(s, size, oldSize - size, 0, 0);
}
