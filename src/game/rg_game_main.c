/* SPDX-License-Identifier: CC0-1.0
 * rg-game: the game executable's host entry (docs/LINK.md).
 *
 *   rg-game [--settings FILE] [--preset NAME] [--set id=value]...
 *           [--headless] [--fields N] [--data DIR] [--saves DIR] [--input SCRIPT]
 *           [--unthrottled] [--screenshot PNG] [--shot FIELD:PNG]...
 *           [--prompt-style playstation|xbox|nintendo|keyboard[@FIELD]]...
 *           [--mouse-motion FIRST-LAST:DX:DY]... [--look-record FILE]
 *           [--save-state FIELD:FILE]... [--state-note TEXT] [--load-state FILE]
 *
 * Save states (rg_game_ss.c, docs/TEST-FIXTURES.md): the whole running game
 * after a field, for this exact build; off unless asked for.
 *
 * Settings (docs/SETTINGS.md): the registry (core + input actions) is built
 * first and `--settings` / `--preset` / `--set` are consumed from argv; the
 * runtime takes throttle, audio, window mode and scale from it and the host
 * applies the rest live.  No settings file is loaded implicitly, so a run with
 * none of those flags uses the defaults; the program's own flags
 * (--unthrottled, --headless) are applied after the registry and win.
 * Scripted runs (--input) stay deterministic: the input script bypasses live
 * input and bindings, and headless forces throttle off; no setting reaches
 * guest state today (the gameplay options are P6 placeholders) except
 * a wide graphics.aspect, which sets the game's own WIDE flag and the
 * aspect the stage 1 overrides read (presentation state: projection and 2D
 * widths; docs/WIDESCREEN.md).  At 4:3 (Original)
 * the flag is never written.  prompts.style swaps the button-prompt texture
 * (presentation only, docs/PROMPTS.md); scripted and headless runs always show
 * PlayStation prompts (the original bytes, never written) unless
 * --prompt-style forces a style (verification screenshots).  The mouse camera
 * (input.mouse_look, docs/INPUT.md "Mouse camera implementation") reaches
 * guest state only through the look record latched once per game frame
 * (rg_game_look_latch, called from the MainLoop override) and consumed by the
 * camera overrides; a scripted run takes it from the script's "#!look" lines
 * only (plus --mouse-motion, the verification path), so every existing script
 * and the Original preset (mouse camera off) run exactly as before.
 *
 * Wires the services the runtime leaves to their owners, then boots the game:
 *   1. rg_movie_runtime_attach()        movie service (IPU hooks, docs/MOVIE.md)
 *   2. overlay service hook             rg_ovl_service_init(&rg_ovl_generated_registry)
 *                                       (registry bind + RG_OVL_DATA resolver, docs/OVERLAY.md)
 *   3. trace symbol table + RG_TRACE_*  (docs/TRACE-PORT.md; no-op unless RG_TRACE_OUT)
 *   4. rg_runtime_init / run            crt0 calls rg_game_entry -> Main_15e700
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include "rg_runtime.h"
#include "rg_settings.h"
#include "rg_aspect.h"
#include "rg_prompts.h"
#include "rg_input.h"
#include "host.h"
#include "movie_game.h"
#include "ovl.h"
#include "rg_trace.h"
#include "ps2k.h"
#include "rg_game_ss.h"

extern uint32_t D_004810C4[];
static uint64_t g_field_next;
static void rg_dump_spec(const char *spec_in, const char *tag, unsigned long long field);

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#if defined(_WIN64)
/* x64 (docs/X64-PLAN.md step 4): the crash report and the RG_BREAK / RG_WATCH tools
 * below name the i686 CONTEXT registers; on x64 they read the 64-bit ones.  Every
 * address of the x64 exe is below 2 GB, so the 32-bit report fields stay exact; stack
 * words are scanned 4 bytes at a time (a return address shows as its low word). */
#define Eip Rip
#define Esp Rsp
#define Ebp Rbp
#define Eax Rax
#define Ebx Rbx
#define Ecx Rcx
#define Edx Rdx
#define Esi Rsi
#define Edi Rdi
#endif
/* Crash report: the faulting EIP, the fault address, and every stack word that points into
 * the exe image (resolve with rg-game.map, written by the link: docs/LINK.md "Running";
 * tools/native/crashsym.py).  To stderr (headless bring-up runs) AND, because a double-clicked
 * play-test exe has no console, appended to rg-game-crash.txt beside the exe, with the
 * function names when the exe's link map sits beside it (<exe>.map; play-test builds copy
 * it) and a minidump rg-game-crash.dmp (dbghelp, a Windows system DLL, loaded only here).
 * RG_CRASH_LOG=FILE writes the text there instead; RG_CRASH_LOG=0 = stderr only
 * (docs/BRINGUP.md "Crash log"). */
static int rg_game_exe_dir_path(char *out, size_t n, const char *name);
static char g_crash_txt[8192];
static size_t g_crash_len;
static void crash_out(const char *fmt, ...)
{
    va_list ap;
    int k;
    if (g_crash_len >= sizeof g_crash_txt - 1) return;
    va_start(ap, fmt);
    k = vsnprintf(g_crash_txt + g_crash_len, sizeof g_crash_txt - g_crash_len, fmt, ap);
    va_end(ap);
    if (k > 0) g_crash_len += (size_t)k < sizeof g_crash_txt - g_crash_len ? (size_t)k : sizeof g_crash_txt - g_crash_len - 1;
}
/* name of the function holding image offset rva, from the link map beside the exe
 * (lines " 0001:xxxxxxxx  _name  VA  lib:obj"; VA - preferred base = rva) */
#define RG_CRASH_SYMS 48
static struct { uint32_t rva, best; char name[96]; } g_crash_sym[RG_CRASH_SYMS];
static int crash_symbolise(int n)
{
    char mp[1024], line[512];
    FILE *f;
    uint32_t pref = 0x400000;
    uint32_t text_end = 0;
    if (!GetModuleFileNameA(NULL, mp, sizeof mp - 4)) return 0;
    char *dot = strrchr(mp, '.');
    if (!dot) return 0;
    strcpy(dot, ".map");
    if (!(f = fopen(mp, "r"))) return 0;
    while (fgets(line, sizeof line, f)) {
        unsigned sec, off;
        char name[256];
        unsigned long long va;
        if (!strncmp(line, " Preferred load address is ", 27)) { pref = (uint32_t)strtoul(line + 27, NULL, 16); continue; }
        {   /* code section extent (" 0001:00000000 006730e2H .text  CODE"): words past it are data */
            unsigned so, sl;
            char nm[64];
            if (sscanf(line, " 0001:%x %xH %63s", &so, &sl, nm) == 3 && strstr(line, "CODE") && so + sl > text_end)
                text_end = so + sl;
        }
        if (sscanf(line, " %x:%x %255s %llx", &sec, &off, name, &va) != 4 || sec != 1 || va < pref) continue;
        uint32_t r = (uint32_t)(va - pref);
        for (int i = 0; i < n; i++)
            if (r <= g_crash_sym[i].rva && r >= g_crash_sym[i].best) {
                g_crash_sym[i].best = r;
                snprintf(g_crash_sym[i].name, sizeof g_crash_sym[i].name, "%s", name[0] == '_' ? name + 1 : name);
            }
    }
    fclose(f);
    for (int i = 0; i < n; i++)   /* not code: a data / heap word, no function name */
        if (text_end && g_crash_sym[i].rva >= 0x1000 + text_end) g_crash_sym[i].name[0] = 0;
    return 1;
}
static void crash_minidump(EXCEPTION_POINTERS *ep, const char *path)
{
    typedef BOOL (WINAPI *mdw_fn)(HANDLE, DWORD, HANDLE, int, void *, void *, void *);
    struct { DWORD tid; EXCEPTION_POINTERS *ep; BOOL client; } mei;   /* MINIDUMP_EXCEPTION_INFORMATION */
    HMODULE dh = LoadLibraryA("dbghelp.dll");
    mdw_fn mdw = dh ? (mdw_fn)(void *)GetProcAddress(dh, "MiniDumpWriteDump") : NULL;
    HANDLE h;
    if (!mdw) return;
    h = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return;
    mei.tid = GetCurrentThreadId();
    mei.ep = ep;
    mei.client = FALSE;
    /* MiniDumpWithIndirectlyReferencedMemory (0x40): threads, stacks and the memory the
     * stacks point at; a few MB, not the game heap */
    if (mdw(GetCurrentProcess(), GetCurrentProcessId(), h, 0x40, &mei, NULL, NULL))
        crash_out("  minidump: %s\n", path);
    CloseHandle(h);
}
static LONG WINAPI rg_game_crash(EXCEPTION_POINTERS *ep)
{
    static volatile LONG once;
    HMODULE m = GetModuleHandleA(NULL);
    uintptr_t base = (uintptr_t)m;
    IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(base + ((IMAGE_DOS_HEADER *)m)->e_lfanew);
    uintptr_t end = base + nt->OptionalHeader.SizeOfImage;
    EXCEPTION_RECORD *er = ep->ExceptionRecord;
    CONTEXT *c = ep->ContextRecord;
    const char *env = getenv("RG_CRASH_LOG");
    char path[1024], dmp[1024];
    int ns = 0;
    if (InterlockedExchange(&once, 1)) return EXCEPTION_CONTINUE_SEARCH;   /* a second thread / fault */
    g_crash_len = 0;
    crash_out("rg-game: EXCEPTION 0x%08lX at eip=0x%08lX (image base 0x%08lX, rva 0x%08lX)",
              (unsigned long)er->ExceptionCode, (unsigned long)c->Eip, (unsigned long)base,
              (unsigned long)(c->Eip - base));
    if (er->NumberParameters >= 2)
        crash_out(" %s 0x%08lX", er->ExceptionInformation[0] ? "write" : "read",
                  (unsigned long)er->ExceptionInformation[1]);
    crash_out("\n  eax=%08lX ebx=%08lX ecx=%08lX edx=%08lX esi=%08lX edi=%08lX ebp=%08lX esp=%08lX\n",
              (unsigned long)c->Eax, (unsigned long)c->Ebx, (unsigned long)c->Ecx, (unsigned long)c->Edx,
              (unsigned long)c->Esi, (unsigned long)c->Edi, (unsigned long)c->Ebp, (unsigned long)c->Esp);
    crash_out("  stack words in the image (rva):");
    g_crash_sym[ns++].rva = (uint32_t)(c->Eip - base);
    uint32_t *sp = (uint32_t *)(uintptr_t)c->Esp;
    int n = 0;
    for (int i = 0; i < 4096 && n < 40; i++) {
        MEMORY_BASIC_INFORMATION mi;
        if (((uintptr_t)(sp + i) & 0xFFF) == 0 || i == 0) {
            if (!VirtualQuery(sp + i, &mi, sizeof mi) || mi.State != MEM_COMMIT)
                break;
        }
        uintptr_t v = sp[i];
        if (v > base + 0x1000 && v < end) {
            crash_out(" %08lX", (unsigned long)(v - base));
            if (ns < RG_CRASH_SYMS) g_crash_sym[ns++].rva = (uint32_t)(v - base);
            n++;
        }
    }
    crash_out("\n");
    fputs(g_crash_txt, stderr);
    fflush(stderr);
    if (env && env[0] == '0' && !env[1]) return EXCEPTION_CONTINUE_SEARCH;
    /* the file copy: when, which exe, the game's field, then the same report + names */
    {
        SYSTEMTIME t;
        char exe[1024];
        GetLocalTime(&t);
        if (!GetModuleFileNameA(NULL, exe, sizeof exe)) exe[0] = 0;
        int have_map = crash_symbolise(ns);
        crash_out("  field %llu, game vbl %lu\n", (unsigned long long)g_field_next, (unsigned long)D_004810C4[0]);
        if (!have_map)
            crash_out("  (no link map beside the exe: name the rvas with tools/native/crashsym.py MAP)\n");
        for (int i = 0; i < ns && have_map; i++) {
            if (g_crash_sym[i].name[0])
                crash_out("    %s%08lX  %s + 0x%lX\n", i ? "" : "eip ", (unsigned long)g_crash_sym[i].rva,
                          g_crash_sym[i].name, (unsigned long)(g_crash_sym[i].rva - g_crash_sym[i].best));
            else
                crash_out("    %s%08lX  (not in the exe's code)\n", i ? "" : "eip ", (unsigned long)g_crash_sym[i].rva);
        }
        if (env && env[0]) snprintf(path, sizeof path, "%s", env);
        else if (!rg_game_exe_dir_path(path, sizeof path, "rg-game-crash.txt")) path[0] = 0;
        if (path[0]) {
            snprintf(dmp, sizeof dmp, "%s", path);
            char *dot = strrchr(dmp, '.');
            if (dot && !strchr(dot, '\\') && !strchr(dot, '/')) strcpy(dot, ".dmp");
            else strncat(dmp, ".dmp", sizeof dmp - strlen(dmp) - 1);
            crash_minidump(ep, dmp);
            FILE *f = fopen(path, "a");
            if (f) {
                fprintf(f, "==== %04u-%02u-%02u %02u:%02u:%02u  %s\n", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute,
                        t.wSecond, exe);
                fputs(g_crash_txt, f);
                fputs("\n", f);
                fclose(f);
                fprintf(stderr, "rg-game: crash report written to %s\n", path);
            }
        }
    }
    fflush(stderr);
    return EXCEPTION_CONTINUE_SEARCH;
}

/* A stack overflow never reaches the unhandled-exception filter (no stack
 * left to run it on); report it from a vectored handler, which Windows runs
 * on the guard-page reserve. */
/* RG_BREAK=RVA[,RVA..] (bring-up diagnostics, docs/BRINGUP.md): an in-process
 * logging breakpoint at each exe RVA (rg-game.map).  Each hit prints eax, the
 * first four stack words (cdecl arguments at a function entry), the return
 * address RVA and the current game vbl; execution continues (int3 + single
 * step re-arm).  RG_BREAK_MAX=N stops logging after N hits per site.
 * RG_BREAK_DUMP=N hex-dumps N bytes at [eax], or at stack word K with
 * RG_BREAK_DUMPARG=K (break on a call instruction: K=0 is the last pushed argument). */
#define RG_BRK_MAX 32
static struct { uint8_t *at; uint8_t orig; unsigned hits; unsigned total; } rg_brk[RG_BRK_MAX];
static int rg_brk_n, rg_brk_rearm = -1;
static unsigned rg_brk_limit = 200;
static unsigned rg_brk_dump;   /* RG_BREAK_DUMP=N: also hex-dump N bytes at [eax] */
static unsigned rg_brk_stack;  /* RG_BREAK_STACK=N: list image addresses in the first N stack words */
static unsigned rg_brk_from_vbl; /* RG_BREAK_FROM_VBL=V: log (and count) hits only from game vbl V */
static const char *rg_brk_spec;  /* RG_BREAK_SPEC=items: rg_dump_spec at every logged hit (SDUMP lines) */
static int rg_brk_dump_arg = -1; /* RG_BREAK_DUMPARG=K: dump at stack word K instead of eax
                                    (a call site's pushed argument, e.g. an out pointer) */
extern uint32_t D_004810C4[];
static void rg_brk_poke(uint8_t *at, uint8_t v)
{
    DWORD old;
    VirtualProtect(at, 1, PAGE_EXECUTE_READWRITE, &old);
    *at = v;
    VirtualProtect(at, 1, old, &old);
    FlushInstructionCache(GetCurrentProcess(), at, 1);
}
/* RG_WATCH=0xHOSTADDR: a hardware write breakpoint (DR0, 4 bytes) on the main
 * thread (the game's flows are its fibers); each write prints a WATCH line with
 * the writing instruction's RVA (rva.py / rg-game.map) and the new value.
 * RG_WATCH_MAX=N limits the lines (default 50).  Host addresses of game objects
 * are deterministic run to run (fixed heap), so a first run finds the address
 * (RG_STATUS_DUMP / RG_BREAK_SPEC pointer chains) and a second one watches it. */
static uintptr_t rg_watch_addr;
static unsigned rg_watch_hits, rg_watch_max = 50;
static HANDLE rg_watch_main;
static DWORD WINAPI rg_watch_setter(LPVOID unused)
{
    (void)unused;
    CONTEXT ctx;
    memset(&ctx, 0, sizeof ctx);
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    SuspendThread(rg_watch_main);
    GetThreadContext(rg_watch_main, &ctx);
    ctx.Dr0 = (DWORD)rg_watch_addr;
    ctx.Dr7 = (ctx.Dr7 & ~0x000F0003u) | 0x1u | (1u << 16) | (3u << 18);  /* L0, write, 4 bytes */
    SetThreadContext(rg_watch_main, &ctx);
    ResumeThread(rg_watch_main);
    return 0;
}
static void rg_watch_init(void)
{
    const char *w = getenv("RG_WATCH");
    if (!w || !*w)
        return;
    rg_watch_addr = (uintptr_t)strtoul(w, NULL, 0) & ~(uintptr_t)3;
    if (getenv("RG_WATCH_MAX"))
        rg_watch_max = (unsigned)strtoul(getenv("RG_WATCH_MAX"), NULL, 0);
    DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &rg_watch_main, 0, FALSE,
                    DUPLICATE_SAME_ACCESS);
    HANDLE t = CreateThread(NULL, 0, rg_watch_setter, NULL, 0, NULL);
    WaitForSingleObject(t, INFINITE);
    CloseHandle(t);
    fprintf(stderr, "rg-game: RG_WATCH 0x%08lX armed\n", (unsigned long)rg_watch_addr);
}
static void rg_brk_init(void)
{
    rg_watch_init();
    const char *e = getenv("RG_BREAK");
    if (!e || !*e)
        return;
    if (getenv("RG_BREAK_MAX"))
        rg_brk_limit = (unsigned)strtoul(getenv("RG_BREAK_MAX"), NULL, 0);
    if (getenv("RG_BREAK_DUMP"))
        rg_brk_dump = (unsigned)strtoul(getenv("RG_BREAK_DUMP"), NULL, 0);
    if (getenv("RG_BREAK_FROM_VBL"))
        rg_brk_from_vbl = (unsigned)strtoul(getenv("RG_BREAK_FROM_VBL"), NULL, 0);
    if (getenv("RG_BREAK_STACK"))
        rg_brk_stack = (unsigned)strtoul(getenv("RG_BREAK_STACK"), NULL, 0);
    if (getenv("RG_BREAK_DUMPARG"))
        rg_brk_dump_arg = (int)strtol(getenv("RG_BREAK_DUMPARG"), NULL, 0);
    rg_brk_spec = getenv("RG_BREAK_SPEC");
    uint8_t *base = (uint8_t *)GetModuleHandleA(NULL);
    char buf[512];
    strncpy(buf, e, sizeof buf - 1);
    buf[sizeof buf - 1] = 0;
    for (char *t = strtok(buf, ","); t && rg_brk_n < RG_BRK_MAX; t = strtok(NULL, ",")) {
        uint8_t *at = base + strtoul(t, NULL, 0);
        rg_brk[rg_brk_n].at = at;
        rg_brk[rg_brk_n].orig = *at;
        rg_brk_poke(at, 0xCC);
        rg_brk_n++;
    }
}
static LONG WINAPI rg_brk_handler(EXCEPTION_POINTERS *ep)
{
    CONTEXT *c = ep->ContextRecord;
    DWORD code = ep->ExceptionRecord->ExceptionCode;
    uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
    if (code == EXCEPTION_BREAKPOINT) {
        for (int i = 0; i < rg_brk_n; i++) {
            if ((uintptr_t)rg_brk[i].at != (uintptr_t)ep->ExceptionRecord->ExceptionAddress)
                continue;
            uint32_t *sp = (uint32_t *)(uintptr_t)c->Esp;
            rg_brk[i].total++;   /* every hit (RG_INPUT_KEY=frames counts site 0) */
            if (D_004810C4[0] < rg_brk_from_vbl) {
                rg_brk_poke(rg_brk[i].at, rg_brk[i].orig);
                c->Eip = (DWORD)(uintptr_t)rg_brk[i].at;
                c->EFlags |= 0x100;
                rg_brk_rearm = i;
                return EXCEPTION_CONTINUE_EXECUTION;
            }
            if (rg_brk[i].hits++ < rg_brk_limit)
                fprintf(stderr, "BRK rva=0x%08lX vbl=%u eax=%08lX ecx=%08lX edx_rva=%08lX args=%08X %08X %08X %08X "
                                "ret_rva=0x%08lX hit=%u\n",
                        (unsigned long)((uintptr_t)rg_brk[i].at - base), D_004810C4[0],
                        (unsigned long)c->Eax, (unsigned long)c->Ecx, (unsigned long)(c->Edx - base),
#if defined(_WIN64)
                        /* x64: args = the four argument registers (rcx rdx r8 r9, low 32 bits) */
                        (uint32_t)c->Rcx, (uint32_t)c->Rdx, (uint32_t)c->R8, (uint32_t)c->R9,
#else
                        sp[1], sp[2], sp[3], sp[4],
#endif
                        (unsigned long)(sp[0] - base), rg_brk[i].total);
            if (rg_brk[i].hits <= rg_brk_limit && rg_brk_stack) {
                /* RG_BREAK_STACK=N: every stack word in the first N that points into
                 * the image (a heuristic backtrace; resolve with rva.py) */
                const IMAGE_NT_HEADERS *nt =
                    (const IMAGE_NT_HEADERS *)(base + ((const IMAGE_DOS_HEADER *)base)->e_lfanew);
                uintptr_t lim = base + nt->OptionalHeader.SizeOfCode + nt->OptionalHeader.BaseOfCode;
                fprintf(stderr, "BRKSTACK");
                for (unsigned j = 0; j < rg_brk_stack; j++) {
                    if (IsBadReadPtr(&sp[j], 4))
                        break;
                    if (sp[j] >= base + nt->OptionalHeader.BaseOfCode && sp[j] < lim)
                        fprintf(stderr, " %u:%08lX", j, (unsigned long)(sp[j] - base));
                }
                fprintf(stderr, "\n");
            }
            if (rg_brk[i].hits <= rg_brk_limit && rg_brk_spec && *rg_brk_spec)
                rg_dump_spec(rg_brk_spec, "SDUMP", (unsigned long long)g_field_next);
#if defined(_WIN64)
            /* x64: RG_BREAK_DUMPARG=1..4 = the argument registers rcx rdx r8 r9 at a function entry */
            const DWORD64 x64_args[4] = {c->Rcx, c->Rdx, c->R8, c->R9};
            uintptr_t at = rg_brk_dump_arg >= 1 && rg_brk_dump_arg <= 4 ? (uintptr_t)x64_args[rg_brk_dump_arg - 1]
                         : rg_brk_dump_arg >= 0 ? (uintptr_t)sp[rg_brk_dump_arg] : (uintptr_t)c->Eax;
#else
            uintptr_t at = rg_brk_dump_arg >= 0 ? (uintptr_t)sp[rg_brk_dump_arg] : (uintptr_t)c->Eax;
#endif
            if (rg_brk[i].hits <= rg_brk_limit && rg_brk_dump && at >= 0x10000 &&
                !IsBadReadPtr((const void *)at, rg_brk_dump)) {
                const uint8_t *m = (const uint8_t *)at;
                fprintf(stderr, "BRKDUMP");
                for (unsigned j = 0; j < rg_brk_dump; j++)
                    fprintf(stderr, "%s%02x", (j % 4) ? "" : " ", m[j]);
                fprintf(stderr, "\n");
            }
            rg_brk_poke(rg_brk[i].at, rg_brk[i].orig);
            c->Eip = (DWORD)(uintptr_t)rg_brk[i].at;
            c->EFlags |= 0x100;          /* single-step, then re-arm */
            rg_brk_rearm = i;
            return EXCEPTION_CONTINUE_EXECUTION;
        }
    } else if (code == EXCEPTION_SINGLE_STEP && (c->Dr6 & 0xF)) {
        /* RG_WATCH data breakpoint (trap after the write) */
        uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
        if (rg_watch_hits++ < rg_watch_max)
            fprintf(stderr, "WATCH eip_rva=0x%08lX vbl=%u field=%llu value=%08X\n",
                    (unsigned long)(c->Eip - base), D_004810C4[0], (unsigned long long)g_field_next,
                    *(volatile uint32_t *)rg_watch_addr);
        c->Dr6 = 0;
        if (rg_brk_rearm >= 0) {   /* also the RG_BREAK single step */
            rg_brk_poke(rg_brk[rg_brk_rearm].at, 0xCC);
            rg_brk_rearm = -1;
        }
        return EXCEPTION_CONTINUE_EXECUTION;
    } else if (code == EXCEPTION_SINGLE_STEP && rg_brk_rearm >= 0) {
        rg_brk_poke(rg_brk[rg_brk_rearm].at, 0xCC);
        rg_brk_rearm = -1;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

/* RG_INPUT_KEY=frames: the input script is keyed by game frames instead of
 * VBlanks -- the number of hits of the first RG_BREAK site so far (put it on
 * GfxEndFrame_141c20: tools/parity/parity.py does, and its retail driver
 * indexes input.py's guest table by the same count), so a scripted press
 * reaches the same game frame on retail even when retail drops a frame. */
static uint32_t rg_game_frame_key(void *user, uint64_t kernel_vblank)
{
    (void)user;
    (void)kernel_vblank;
    return rg_brk_n ? rg_brk[0].total : 0;
}

static LONG WINAPI rg_game_stack_overflow(EXCEPTION_POINTERS *ep)
{
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW) {
        uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
        char msg[160];
        int n = wsprintfA(msg, "rg-game: STACK OVERFLOW at eip=0x%08lX (rva 0x%08lX) esp=0x%08lX\n",
                          (unsigned long)ep->ContextRecord->Eip,
                          (unsigned long)(ep->ContextRecord->Eip - base),
                          (unsigned long)ep->ContextRecord->Esp);
        DWORD w;
        WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)n, &w, NULL);
        ExitProcess(3);
    }
    if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && getenv("RG_VEH")) {
        /* RG_VEH=1: report first-chance faults too (when the unhandled
         * filter is never reached) */
        rg_game_crash(ep);
        ExitProcess(4);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
#endif

/* RG_STATUS_DUMP / RG_BREAK_SPEC item list (comma separated): one stderr line
 * "<TAG> field=F vbl=V OFFSET: hex.." per item.  Items:
 *   ADDR:SIZE            PS2 address through the trace address map
 *   rRVA:SIZE            host bytes at an exe RVA (rg-game.map)
 *   pRVA[/O1/O2..][+OFF]:SIZE  follow the host pointer stored at the exe RVA,
 *                        then further pointer hops *(q + Ok), then +OFF
 *   hADDR:SIZE           an absolute host address
 * (tools/parity/parity.py builds these from its field table; compare with
 * probe.py on retail).  A chain that meets NULL (or an unreadable pointer)
 * prints "<TAG> field=F vbl=V ITEM: NULL". */
static void rg_dump_spec(const char *spec_in, const char *tag, unsigned long long field)
{
    char spec[4096];
    strncpy(spec, spec_in, sizeof spec - 1);
    spec[sizeof spec - 1] = 0;
    char *next = spec;
    while (next && *next) {
        char *t = next;
        next = strchr(t, ',');
        if (next)
            *next++ = 0;
        int host = (*t == 'r' || *t == 'p' || *t == 'h');
        uint32_t a = (uint32_t)strtoul(t + host, NULL, 0), n = 4, bad = 0;
        const uint8_t *hb = NULL;
#ifdef _WIN32
        hb = (const uint8_t *)GetModuleHandleA(NULL);
#endif
        if (*t == 'h')
            hb = (const uint8_t *)0;
        if (*t == 'p' && hb) {
            char *plus = strchr(t, '+');
            uintptr_t q = *(const uint32_t *)(hb + a);
            for (char *sl = strchr(t, '/'); q && sl && (!plus || sl < plus); sl = strchr(sl + 1, '/')) {
                uintptr_t at = q + strtoul(sl + 1, NULL, 0);
#ifdef _WIN32
                if (IsBadReadPtr((const void *)at, 4)) {
                    q = 0;
                    break;
                }
#endif
                q = *(const uint32_t *)at;
            }
            hb = (const uint8_t *)q;
            a = plus ? (uint32_t)strtoul(plus + 1, NULL, 0) : 0;
            if (!q) {
                fprintf(stderr, "%s field=%llu vbl=%u %s: NULL\n", tag, field, D_004810C4[0], t);
                continue;
            }
        }
        char *c = strchr(t, ':');
        if (c)
            n = (uint32_t)strtoul(c + 1, NULL, 0);
#ifdef _WIN32
        if (host && IsBadReadPtr((const void *)((uintptr_t)hb + a), n ? n : 1)) {
            fprintf(stderr, "%s field=%llu vbl=%u %s: NULL\n", tag, field, D_004810C4[0], t);
            continue;
        }
#endif
        fprintf(stderr, "%s field=%llu vbl=%u %08X:", tag, field, D_004810C4[0], a);
        for (uint32_t i = 0; i < n && i < 0x4000; i++) {
            uint8_t b = 0;
            if (host) {
#ifdef _WIN32
                b = ((const uint8_t *)((uintptr_t)hb + a))[i];
#endif
            } else
                rg_trace_read(a + i, &b, 1, &bad);
            fprintf(stderr, "%s%02x", (i % 4) ? "" : " ", b);
        }
        fprintf(stderr, "\n");
    }
}

int Main_15e700(void);                        /* game/src/main/sys (MAIN 0x0015E700) */
void rg_crt_heap_bind(void *av, void *params);   /* src/crt/crt_heap.c */
unsigned rg_movie_g_frames_decoded(void);        /* src/movie/mv_game.c */
extern uint32_t D_00449868[];                     /* newlib malloc av_ (retail .data) */
extern uint32_t D_00449C70[];                     /* trim_threshold .. current_mallinfo */
void rg_ovl_service_init(void *user);            /* src/ps2/overlay/ovl_bind.c */
extern const rg_ovl_registry rg_ovl_generated_registry; /* ovl_registry_gen.c */

/* ---- widescreen stages 0/1 (docs/WIDESCREEN.md, src/settings/rg_aspect.h) ----
 * Between fields (no guest code runs): decide from graphics.aspect /
 * graphics.movie_aspect and the screen state, write the game's WIDE flag
 * (D_00481638, SetAspectMode_1c6a90's variable) only when the policy says so,
 * and give the host the canvas / frame shape for this field's present. */
extern int32_t D_00481638[];   /* aspect mode: 1 = WIDE (MAIN .bss) */
extern uint32_t D_0047E254[];  /* loaded overlay id (2 = TITLE, docs/OVERLAY.md) */
static rg_aspect_ctl g_aspect;
static rg_aspect_frame g_aspect_now = { -1, 4, 3, 4, 3 };

static void aspect_apply(const rg_settings *s)
{
    int mw = 0, mh = 0;
    rg_movie_g_size(&mw, &mh);
    rg_host *h = rg_runtime_host();
    /* graphics.aspect = auto: the window's shape (stage 1); headless (no
     * renderer) uses display.width x display.height */
    int ww = 0, wh = 0;
    if (h)
        rg_host_window_size(h, &ww, &wh);
    if ((ww <= 0 || wh <= 0) && s && rg_settings_find(s, "display.width") >= 0 &&
        rg_settings_find(s, "display.height") >= 0) {
        ww = rg_settings_get_int(s, "display.width");
        wh = rg_settings_get_int(s, "display.height");
    }
    rg_aspect_step_settings(&g_aspect, s, (int32_t)D_0047E254[0] == 2, mw > 0 && mh > 0, ww, wh,
                            &g_aspect_now);
    if (g_aspect_now.game_wide >= 0)
        D_00481638[0] = g_aspect_now.game_wide;
    /* the projection aspect / HUD x scale the stage 1 overrides read */
    rg_aspect_set_current(&g_aspect_now);
    if (h) {
        int an, ad, cn, cd;
        rg_host_get_aspect(h, &an, &ad, &cn, &cd);
        if (an != g_aspect_now.canvas_num || ad != g_aspect_now.canvas_den ||
            cn != g_aspect_now.content_num || cd != g_aspect_now.content_den)
            rg_host_set_aspect(h, g_aspect_now.canvas_num, g_aspect_now.canvas_den,
                               g_aspect_now.content_num, g_aspect_now.content_den);
    }
}

/* ---- button prompts (docs/PROMPTS.md "Implementation", src/settings/rg_prompts.h) ----
 * Between fields (no guest code runs): the wanted style (--prompt-style, else
 * rg_host_prompt_style: prompts.style + the device in use; PlayStation when
 * scripted or headless) and, for keyboard, the first key / mouse button bound
 * to each button's action.  rg_prompts_step copies the style's pixels + CLUT
 * over the gaiji2 image in D_004C3180 only when the style changes, so the
 * PlayStation style never writes guest memory. */
extern uint8_t D_004C3180[];    /* gaiji2.img (GaijiLoadImage_2705a0), <= 0x10800 bytes */
extern uint32_t D_0044E680[];   /* gaiji metric records {u16 code, s16 u, v, w, s8 h, dx, dy, pad} */
_Static_assert(RG_GAIJI_PLAYSTATION == RG_PROMPT_PLAYSTATION && RG_GAIJI_XBOX == RG_PROMPT_XBOX &&
               RG_GAIJI_NINTENDO == RG_PROMPT_NINTENDO && RG_GAIJI_KEYBOARD == RG_PROMPT_KEYBOARD,
               "prompt style order");
static rg_prompts_ctl g_prompts;
/* --prompt-style STYLE[@FIELD] (repeatable, FIELDs ascending): force STYLE from
 * FIELD on (default 1), whatever the setting and the scripted rule; a live
 * switch in a scripted run proves the swap re-uploads (docs/PROMPTS.md
 * "Implementation"). */
#define RG_MAX_PROMPT_FORCE 8
static struct { uint64_t from; int style; } g_prompts_sched[RG_MAX_PROMPT_FORCE];
static int g_prompts_nsched;
static int g_prompts_force = -1;   /* the forced style now, -1 = none */
static uint64_t g_field_next = 1;  /* the field about to run (declared above) */
static int g_prompts_ok = -1;      /* the ELF's button rects are the ones rg_prompts.c redraws */

static int prompts_rects_match(void)
{
    const uint8_t *t = (const uint8_t *)D_0044E680;
    int found = 0;
    for (int r = 0; r < 64; r++, t += 12) {
        uint16_t code = (uint16_t)(t[0] | t[1] << 8);
        if (!code)
            break;
        for (int b = 0; b < RG_GAIJI_BUTTONS; b++) {
            const rg_gaiji_rect *g = &rg_gaiji_button_rects[b];
            if (g->code != code)
                continue;
            int16_t u = (int16_t)(t[2] | t[3] << 8), v = (int16_t)(t[4] | t[5] << 8);
            int16_t w = (int16_t)(t[6] | t[7] << 8), h = (int8_t)t[8];
            if (u != g->u || v != g->v || w != g->w || h != g->h)
                return 0;
            found++;
        }
    }
    return found == RG_GAIJI_BUTTONS;
}

static void prompts_apply(const rg_settings *s)
{
    if (g_prompts_ok < 0) {
        g_prompts_ok = prompts_rects_match();
        if (!g_prompts_ok)
            fprintf(stderr, "rg-game: gaiji button rects differ from the US table; prompts stay PlayStation\n");
    }
    if (!g_prompts_ok)
        return;
    for (int i = 0; i < g_prompts_nsched; i++)
        if (g_field_next >= g_prompts_sched[i].from)
            g_prompts_force = g_prompts_sched[i].style;
    rg_host *h = rg_runtime_host();
    int want = g_prompts_force >= 0 ? g_prompts_force : h ? (int)rg_host_prompt_style(h) : 0;
    static const char *keys[RG_GAIJI_BUTTONS];
    static char kb[RG_GAIJI_BUTTONS][64];
    static uint64_t keys_gen = ~0ull;
    if (want == RG_GAIJI_KEYBOARD && s && rg_settings_generation(s) != keys_gen) {
        /* the bindings: rebuilt only when a setting changed (menu, file) */
        static rg_actions a;
        keys_gen = rg_settings_generation(s);
        rg_actions_from_settings(&a, s);
        for (int b = 0; b < RG_GAIJI_BUTTONS; b++) {
            keys[b] = NULL;
            int act = rg_action_from_id(rg_gaiji_button_action[b]);
            for (int i = 0; act >= 0 && i < a.nbind[act]; i++) {
                const rg_binding *bd = &a.bind[act][i];
                if (bd->kind == RG_BIND_KEY || bd->kind == RG_BIND_MOUSE) {
                    rg_binding_format(bd, kb[b], sizeof kb[b]);
                    keys[b] = kb[b];
                    break;
                }
            }
        }
    }
    if (rg_prompts_step(&g_prompts, D_004C3180, RG_GAIJI_IMG_MAX, want, keys) && getenv("RG_PROMPTS_LOG"))
        fprintf(stderr, "PROMPTS field=%llu style=%s writes=%u captures=%u\n",
                (unsigned long long)g_field_next, rg_prompt_style_name((rg_prompt_style)want), g_prompts.writes, g_prompts.captures);
}

/* ---- mouse camera (docs/INPUT.md "Mouse camera implementation") ----
 * rg_game_look_latch: called by the MainLoop override (overrides/src/main/sys/
 * MainLoop_1c2c10.c) right before each port-0 PadUpdate_1843a0, i.e. once per
 * game frame on a guest fiber: the host's look delta for this VBlank becomes
 * the frame's record, replacing the previous one (a record no camera took is
 * dropped, so nothing bursts after a menu or an event).  rg_game_look_take:
 * the camera overrides (CameraObjApplyInputMaybe_1619e0 for the orbit modes,
 * CameraFirstPersonUpdate_307f00) take it once; returns 0 when there is none.
 * Both are plain C entry points the override files declare themselves. */
extern uint32_t D_004810C4[];   /* game VBlank counter */
static rg_look g_look;          /* this frame's record */
static int g_look_full;
static uint64_t g_look_used;    /* field a camera last asked for look (0 = never) */
static int g_look_site;         /* that camera: 0 orbit, 1 first person */
static FILE *g_look_rec;        /* --look-record: "#!look" lines */
#define RG_MAX_MOUSE_MOTION 16
static struct { uint64_t first, last; float dx, dy; } g_mm[RG_MAX_MOUSE_MOTION];
static int g_nmm;
static int g_look_log = -1;

void rg_game_look_latch(void)
{
    rg_host *h = rg_runtime_host();
    rg_look l = { 0, 0 };
    if (h)
        rg_host_look_latch(h, D_004810C4[0], &l);
    g_look = l;
    g_look_full = l.yaw != 0 || l.pitch != 0;
    if (g_look_full && g_look_rec)
        fprintf(g_look_rec, "#!look %u %d %d\n", D_004810C4[0], (int)l.yaw, (int)l.pitch);
}

/* site: 0 orbit (modes 0 / 2 / 18), 1 first person (for RG_LOOK_LOG) */
int rg_game_look_take(int32_t *yaw, int32_t *pitch, int site)
{
    g_look_used = g_field_next;
    g_look_site = site;
    if (!g_look_full)
        return 0;
    g_look_full = 0;
    *yaw = g_look.yaw;
    *pitch = g_look.pitch;
    if (g_look_log < 0)
        g_look_log = getenv("RG_LOOK_LOG") != NULL;
    if (g_look_log)
        fprintf(stderr, "LOOK field=%llu vbl=%u site=%d yaw=%d pitch=%d\n",
                (unsigned long long)g_field_next, D_004810C4[0], site, (int)*yaw, (int)*pitch);
    return 1;
}

/* Before every field: the capture hint (a camera asked within the last 30
 * fields) and the --mouse-motion injection for this field. */
static void look_apply(void)
{
    rg_host *h = rg_runtime_host();
    if (!h)
        return;
    rg_host_set_look_active(h, g_look_used && g_field_next - g_look_used <= 30);
    /* the camera stick convention's hint (docs/INPUT.md "Camera stick convention"):
     * the camera that ran in the last 4 fields (it asks every game frame) */
    rg_host_set_camera_view(h, !(g_look_used && g_field_next - g_look_used <= 4) ? RG_CAMVIEW_NONE
                               : g_look_site ? RG_CAMVIEW_FIRST_PERSON : RG_CAMVIEW_ORBIT);
    for (int i = 0; i < g_nmm; i++)
        if (g_field_next >= g_mm[i].first && g_field_next <= g_mm[i].last)
            rg_host_look_inject(h, g_mm[i].dx, g_mm[i].dy);
}

/* --shot FIELD:PATH: the display at the end of FIELD as PATH (native, like
 * --screenshot) and PATH minus ".png" + "-view.png" (as presented: the
 * canvas aspect with the frame in its shape, rg_present_image). */
#define RG_MAX_SHOTS 32
static struct { uint64_t field; const char *path; } g_shots[RG_MAX_SHOTS];
static int g_nshots;

static void shot_write(uint64_t field)
{
    for (int i = 0; i < g_nshots; i++) {
        if (g_shots[i].field != field)
            continue;
        uint64_t hash = 0;
        uint32_t w = 0, h = 0;
        if (rg_runtime_screenshot(g_shots[i].path, &hash, &w, &h) != 0) {
            fprintf(stderr, "rg-game: --shot %llu: no display\n", (unsigned long long)field);
            continue;
        }
        const uint32_t *px = rg_runtime_read_display(&w, &h);
        char view[600];
        size_t n = strlen(g_shots[i].path);
        if (n > 4 && !strcmp(g_shots[i].path + n - 4, ".png"))
            n -= 4;
        snprintf(view, sizeof view, "%.*s-view.png", (int)n, g_shots[i].path);
        uint32_t vw = 0;
        int an = g_aspect_now.canvas_num, ad = g_aspect_now.canvas_den;
        size_t cap = (size_t)((uint64_t)h * (uint64_t)an / (uint64_t)ad + 2) * h;
        uint32_t *out = px ? (uint32_t *)malloc(cap * 4) : NULL;
        if (out && rg_present_image(px, w, h, g_aspect_now.canvas_num, g_aspect_now.canvas_den,
                                    g_aspect_now.content_num, g_aspect_now.content_den, out, cap,
                                    &vw) == 0)
            rg_png_write(view, out, vw, h);
        free(out);
        fprintf(stderr, "SHOT field=%llu %ux%u hash=%016llx canvas=%d:%d frame=%d:%d wide=%d %s\n",
                (unsigned long long)field, w, h, (unsigned long long)hash, g_aspect_now.canvas_num,
                g_aspect_now.canvas_den, g_aspect_now.content_num, g_aspect_now.content_den,
                (int)D_00481638[0], g_shots[i].path);
    }
}

/* crt0's weak default is replaced by this strong definition (RUNTIME.md "crt0") */
int rg_game_entry(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    return Main_15e700();
}

static void usage(void)
{
    fprintf(stderr, "usage: rg-game [--headless] [--fields N] [--data DIR] [--saves DIR] "
                    "[--input SCRIPT] [--unthrottled] [--screenshot PNG] [--shot FIELD:PNG]... "
                    "[--prompt-style playstation|xbox|nintendo|keyboard[@FIELD]]... "
                    "[--mouse-motion FIRST-LAST:DX:DY]... [--look-record FILE] "
                    "[--save-state FIELD:FILE]... [--state-note TEXT] [--load-state FILE]\n");
}

/* <exe dir>/<name>; 0 if the exe path is unknown */
static int rg_game_exe_dir_path(char *out, size_t n, const char *name)
{
#ifdef _WIN32
    DWORD len = GetModuleFileNameA(NULL, out, (DWORD)n);
    if (!len || len >= n) return 0;
#else
    ssize_t len = readlink("/proc/self/exe", out, n - 1);
    if (len <= 0) return 0;
    out[len] = 0;
#endif
    char *slash = strrchr(out, '/');
#ifdef _WIN32
    char *bs = strrchr(out, '\\');
    if (bs > slash) slash = bs;
#endif
    size_t dir = slash ? (size_t)(slash - out) + 1 : 0;
    size_t nl = strlen(name) + 1;
    if (dir + nl > n) return 0;
    memcpy(out + dir, name, nl);
    return 1;
}

/* <exe dir>/settings.ini; 0 if the exe path is unknown */
static int rg_game_default_settings_path(char *out, size_t n)
{
    return rg_game_exe_dir_path(out, n, "settings.ini");
}

/* no --data / $RG_DATA: <exe dir>/data when that folder exists (else the runtime's
 * "data"); no --saves / $RG_SAVES: <exe dir>/saves (mccard creates it on use).
 * Double-clicking the exe then works with no .bat (resume item 5). */
static void rg_game_default_dirs(rg_runtime_config *cfg)
{
    static char data[1024], saves[1024];
    struct stat st;
    if (!cfg->data_dir && !getenv("RG_DATA") && rg_game_exe_dir_path(data, sizeof data, "data") &&
        !stat(data, &st) && (st.st_mode & S_IFDIR))
        cfg->data_dir = data;
    if (!cfg->saves_dir && !getenv("RG_SAVES") && rg_game_exe_dir_path(saves, sizeof saves, "saves"))
        cfg->saves_dir = saves;
}

int main(int argc, char **argv)
{
    rg_runtime_config cfg;
    uint64_t fields = 0;
    const char *shot = NULL;
    int headless = 0, ssa = 0;
    rg_game_ss_early(argc, argv);   /* first: fixed-address state region (save states) */
    rg_runtime_default_config(&cfg);
#ifdef _WIN32
    SetUnhandledExceptionFilter(rg_game_crash);
    AddVectoredExceptionHandler(1, rg_game_stack_overflow);
    AddVectoredExceptionHandler(1, rg_brk_handler);
    rg_brk_init();
#endif
    /* settings registry (docs/SETTINGS.md "Using it from a program") */
    rg_settings *settings = rg_settings_create();
    const char *settings_path = NULL;
    {
        int errors = 0;
        rg_settings_register_core(settings);
        rg_actions_register_settings(settings);
        /* no --settings on a windowed run: keep settings in settings.ini beside the
         * exe (resume item 5), loaded first so --set/--preset still override it;
         * headless/test runs stay file-free */
        static char default_settings[1024];
        int want_default = 1;
        for (int i = 1; i < argc; i++)
            if (!strcmp(argv[i], "--headless") || !strcmp(argv[i], "--settings")) want_default = 0;
        if (want_default && rg_game_default_settings_path(default_settings, sizeof default_settings)) {
            if (rg_settings_load(settings, default_settings)) errors++;
            settings_path = default_settings;
        }
        int arg_errors = 0;
        const char *arg_path = NULL;
        argc = rg_settings_apply_args(settings, argc, argv, &arg_errors, &arg_path);
        errors += arg_errors;
        if (arg_path) settings_path = arg_path;
        if (errors) {
            fprintf(stderr, "rg-game: %d bad settings argument(s)\n", errors);
            rg_settings_destroy(settings);
            return 2;
        }
        rg_runtime_config_from_settings(&cfg, settings);
        cfg.settings_path = settings_path;
    }
    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
        const char *v = i + 1 < argc ? argv[i + 1] : NULL;
        if (!strcmp(a, "--headless")) headless = 1;
        else if (!strcmp(a, "--unthrottled")) cfg.throttle = 0;
        else if (!strcmp(a, "--fields") && v) { fields = strtoull(v, NULL, 0); i++; }
        else if (!strcmp(a, "--data") && v) { cfg.data_dir = v; i++; }
        else if (!strcmp(a, "--saves") && v) { cfg.saves_dir = v; i++; }
        else if (!strcmp(a, "--input") && v) { cfg.input_script = v; i++; }
        else if (!strcmp(a, "--screenshot") && v) { shot = v; i++; }
        else if (!strcmp(a, "--shot") && v && strchr(v, ':') && g_nshots < RG_MAX_SHOTS) {
            g_shots[g_nshots].field = strtoull(v, NULL, 0);
            g_shots[g_nshots].path = strchr(v, ':') + 1;
            g_nshots++;
            i++;
        }
        else if (!strcmp(a, "--prompt-style") && v && g_prompts_nsched < RG_MAX_PROMPT_FORCE) {
            const char *at = strchr(v, '@');
            size_t n = at ? (size_t)(at - v) : strlen(v);
            int st = -1;
            for (int k = 0; k < RG_PROMPT_COUNT; k++)
                if (strlen(rg_prompt_style_name((rg_prompt_style)k)) == n &&
                    !strncmp(v, rg_prompt_style_name((rg_prompt_style)k), n))
                    st = k;
            uint64_t from = at ? strtoull(at + 1, NULL, 0) : 1;
            if (st < 0 || (g_prompts_nsched && from <= g_prompts_sched[g_prompts_nsched - 1].from)) {
                usage();
                rg_settings_destroy(settings);
                return 2;
            }
            g_prompts_sched[g_prompts_nsched].from = from;
            g_prompts_sched[g_prompts_nsched++].style = st;
            i++;
        }
        else if (!strcmp(a, "--mouse-motion") && v && g_nmm < RG_MAX_MOUSE_MOTION) {
            /* FIRST-LAST:DX:DY: DX, DY counts of relative mouse motion in each of
             * fields FIRST..LAST, through the input.mouse_* settings (also in a
             * scripted run: verification of the mouse camera) */
            unsigned long long f0, f1;
            float dx, dy;
            if (sscanf(v, "%llu-%llu:%f:%f", &f0, &f1, &dx, &dy) != 4 || f1 < f0) {
                usage();
                rg_settings_destroy(settings);
                return 2;
            }
            g_mm[g_nmm].first = f0;
            g_mm[g_nmm].last = f1;
            g_mm[g_nmm].dx = dx;
            g_mm[g_nmm++].dy = dy;
            i++;
        }
        else if ((ssa = rg_game_ss_arg(a, v)) != 0) {
            if (ssa < 0) { usage(); rg_settings_destroy(settings); return 2; }
            i++;
        }
        else if (!strcmp(a, "--look-record") && v) {
            g_look_rec = fopen(v, "w");
            if (!g_look_rec) {
                fprintf(stderr, "rg-game: --look-record %s: cannot write\n", v);
                rg_settings_destroy(settings);
                return 2;
            }
            fprintf(g_look_rec, "#!look 1 0\n");
            i++;
        }
        else { usage(); rg_settings_destroy(settings); return 2; }
    }
    cfg.headless = headless;
    rg_game_default_dirs(&cfg);

    if (headless && !fields)
        fields = 600;
    cfg.title = "Rogue Galaxy";
    cfg.entry = rg_game_entry;
    /* the game's file layer reads data/ through the native file service
     * (overrides in src/main/file, docs/NATIVE-FS.md): no CDVD sector model or drive,
     * unless RG_CDVD_MODEL=1 asks for it (nothing in the game calls it then) */
    {
        const char *cm = getenv("RG_CDVD_MODEL");
        cfg.cdvd_model = (cm && *cm && *cm != '0') ? 1 : 0;
    }
    {
        /* RG_STACK_KB: host stack per guest thread (bring-up diagnostics) */
        const char *sk = getenv("RG_STACK_KB");
        if (sk && *sk)
            cfg.host_stack_size = (size_t)strtoul(sk, NULL, 0) << 10;
    }

    /* newlib malloc keeps its bins and parameters in MAIN .data (docs/BRINGUP.md "Heap") */
    rg_crt_heap_bind(D_00449868, D_00449C70);
    rg_movie_runtime_attach();
    rg_runtime_set_service_hook(rg_ovl_service_init, (void *)&rg_ovl_generated_registry);
    if (rg_trace_register_game_symtab() != 0)
        fprintf(stderr, "rg-game: trace symbol table rejected (tracing disabled)\n");
    else if (rg_trace_apply_env(&cfg) < 0)
        return 2;

#ifdef _WIN32
    {
        const char *ik = getenv("RG_INPUT_KEY");
        if (ik && !strcmp(ik, "frames"))
            cfg.game_vblank = rg_game_frame_key;
    }
#endif
    if (rg_game_ss_before_init() != 0) {
        rg_settings_destroy(settings);
        return 2;
    }
    if (rg_runtime_init(&cfg) != 0) {
        rg_settings_destroy(settings);
        return 1;
    }
    rg_settings_mark_applied(settings);
    int rc = 0;
    uint64_t first_field = 0;   /* --load-state: the state's field */
    {
        int lr = rg_game_ss_after_init(&first_field);
        if (lr == -2)
            _Exit(4);           /* bytes were written back: unusable */
        if (lr != 0) {
            rg_runtime_shutdown();
            rg_settings_destroy(settings);
            return 3;
        }
    }
    {
        /* RG_STATUS_EVERY=N: one stderr line of boot state every N fields
         * (bring-up: docs/BRINGUP.md; addresses: tools/trace/symbols.spec) */
        extern uint32_t D_0047E254[], D_0047E224[], D_004810C4[], D_004B51A0[], D_004B51E0[],
            D_00484164[], D_004803AC[], D_0048416C[];
        const char *se = getenv("RG_STATUS_EVERY");
        uint64_t every = se ? strtoull(se, NULL, 0) : 0;
        rg_aspect_ctl_init(&g_aspect);
        rg_prompts_init(&g_prompts);
        for (uint64_t k = first_field; !fields || k < fields; k++) {
            aspect_apply(settings);
            g_field_next = k + 1;
            prompts_apply(settings);
            look_apply();
            rc = rg_runtime_run_field();
            if (rc)
                break;
            if (g_nshots)
                shot_write(k + 1);
            if (rg_game_ss_saving())
                rg_game_ss_field_done(k + 1, cfg.input_script);
            if (getenv("RG_RAM_DUMP")) {
                /* RG_RAM_DUMP=FIELD:PATH[,FIELD:PATH..]: the 32 MB PS2 EE RAM
                 * image through the trace address map at the end of FIELD
                 * (compare with a PCSX2 savestate's eeMemory.bin; unmapped
                 * bytes read 0; pointers are host addresses on the port) */
                char spec[1024];
                strncpy(spec, getenv("RG_RAM_DUMP"), sizeof spec - 1);
                spec[sizeof spec - 1] = 0;
                for (char *t = strtok(spec, ","); t; t = strtok(NULL, ",")) {
                    char *c = strchr(t, ':');
                    if (!c || strtoull(t, NULL, 0) != k + 1)
                        continue;
                    FILE *f = fopen(c + 1, "wb");
                    static uint8_t page[4096];
                    for (uint32_t a = 0; f && a < 0x2000000u; a += sizeof page) {
                        uint32_t bad = 0;
                        memset(page, 0, sizeof page);
                        rg_trace_read(a, page, sizeof page, &bad);
                        fwrite(page, 1, sizeof page, f);
                    }
                    if (f)
                        fclose(f);
                    fprintf(stderr, "RAMDUMP field=%llu vbl=%u %s\n", (unsigned long long)(k + 1),
                            D_004810C4[0], c + 1);
                }
            }
            if (every && (k + 1) % every == 0 && getenv("RG_STATUS_THREADS")) {
                /* RG_STATUS_THREADS=1: every guest thread's state and the code
                 * address (exe RVA, rg-game.map) that last called a blocking
                 * kernel service (src/sce/kernel/eekernel.c) */
                extern uintptr_t rg_kernel_wait_caller[64];
                uintptr_t base = 0;
#ifdef _WIN32
                base = (uintptr_t)GetModuleHandleA(NULL);
#endif
                for (int t = 0; t < 64; t++) {
                    ps2k_thread_info ti;
                    if (ps2k_refer_thread_status(t, &ti, 0) < 0)
                        continue;
                    fprintf(stderr, "THREAD field=%llu tid=%d status=%d prio=%d wait=%d/%d "
                                    "caller_rva=0x%08lX\n",
                            (unsigned long long)(k + 1), t, (int)ti.status,
                            (int)ti.current_priority, (int)ti.wait_type, (int)ti.wait_id,
                            (unsigned long)(rg_kernel_wait_caller[t] ?
                                            rg_kernel_wait_caller[t] - base : 0));
                }
            }
            if (every && (k + 1) % every == 0 && getenv("RG_STATUS_DUMP"))
                rg_dump_spec(getenv("RG_STATUS_DUMP"), "DUMP", k + 1);
            if (every && (k + 1) % every == 0)
                fprintf(stderr,
                        "STATUS field=%llu vbl=%u ovl=%d sysmode=%d gamemode=%d/%d "
                        "title_ctr=%d menusel=%d menuopen=%d movie_frames=%u\n",
                        (unsigned long long)(k + 1), D_004810C4[0], (int)D_0047E254[0],
                        (int)D_0047E224[0], (int)D_004B51A0[0], (int)D_004B51E0[0],
                        (int)D_00484164[0], (int)(short)D_004803AC[0],
                        (int)(short)D_0048416C[0], rg_movie_g_frames_decoded());
        }
    }
    if (shot) {
        uint64_t h = 0;
        uint32_t w = 0, hh = 0;
        rg_runtime_screenshot(shot, &h, &w, &hh);
    }
    const rg_runtime_stats *st = rg_runtime_get_stats();
    printf("rg-game: fields=%llu vblank_start=%llu rc=%d\n", (unsigned long long)st->fields,
           (unsigned long long)st->vblank_start, rc);
    printf("rg-game: run_hash=%016llx\n", (unsigned long long)st->run_hash);
    fflush(stdout);
    rg_runtime_shutdown();
    rg_prompts_free(&g_prompts);
    if (g_look_rec)
        fclose(g_look_rec);
    rg_settings_destroy(settings);   /* after the runtime: the host holds it until shutdown */
    return rc > 1 ? rc : 0;
}
