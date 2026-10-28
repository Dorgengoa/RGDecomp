/* SPDX-License-Identifier: CC0-1.0 */
/* Interpolated presentation, device side (nr_interp.h, docs/NATIVE-RENDER.md "Interpolated
 * presentation"): the retained frame as the device's own command list.
 *
 * A recorder wraps the backend (installed when interpolation is first switched on; until then
 * nothing changes).  While a log records, every command that draws is kept with copies of what
 * it points at: native draws (mesh and immediate: targets, state, constant rows, vertices,
 * the decoded texture's content key), target copies, loads and clears, target creations and
 * destructions.  Not kept: local-memory traffic (transfers, write-backs, CLUT loads, local copies,
 * read-backs): a replay never touches local memory, so the game's view of the device cannot
 * change.  Each target the log writes that existed before it gets a pre-image (a copy taken
 * just before the log's first write), so a replay starts from the target's state at the frame's
 * start (frames that blend over last frame's content draw the same image again).
 *
 * Replay: the current content of every pre-existing target the log wrote is saved (once per
 * dirty period), the pre-images put back, then the commands run on the real backend: textures by
 * their decoded key only (tex_cached_only), targets the log created replaced by temporary ones,
 * mesh draws with constant rows / bones from nr_ip_mesh_cb (interpolated); then the display
 * shows the in-between frame.  Restore: the saved content back (exact). */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <deque>
#include <map>
#include <unordered_map>
#include <vector>

#include "gpu_internal.h"
#include "nr_interp.h"

GpuBackend **gpu_ip_backend(gpu_renderer *r);

namespace {

enum CmdKind { C_DRAW, C_COPY, C_LOAD, C_CLEAR, C_CREATE, C_DESTROY, C_RESIZE, C_REINT };

struct Cmd {
    CmdKind k;
    GpuNrDraw g;                 /* C_DRAW (pointers re-pointed into the owned copies at replay) */
    int has_d;
    gpu_nr_draw d;
    std::vector<GpuImVtx> im;
    std::vector<uint32_t> runs;
    std::vector<uint32_t> rgba;
    uint32_t mesh_id;            /* the mesh record drawn (0: immediate / generated) */
    int rt[3];                   /* referenced targets (color, depth, tex / dst, src) */
    int srt[3];                  /* C_DRAW: the targets as frame-stable tokens (a target the log created: its creation ordinal) */
    uint32_t life[3];
    int a, b, c;                 /* C_COPY dx dy; C_CREATE depth w h; C_RESIZE w h */
    GpuRect r;
    uint32_t bp, bw;
    int psm;
    int img;                     /* C_LOAD: the target as the load left it (local memory may differ at replay) */
    GpuRect r2;                  /* C_REINT: the source rect (r: the destination's); bp bw psm the destination's */
    uint32_t bp2, bw2;
    int psm2;
};

struct Pre { int id; uint32_t life; int img; };

struct Slot {
    int rec;                     /* recorded (complete or recording) */
    int bad;                     /* something not replayable met */
    std::vector<Cmd> cmds;
    std::vector<Pre> pre;        /* pre-existing targets written, their pre-images */
    std::map<int, uint32_t> born;   /* targets created in the log: id -> life at creation */
    std::map<int, int> ord;      /* targets created in the log: id -> creation ordinal (current life) */
    int nborn = 0;
};

struct Stats {
    uint64_t draws, copies, loads, clears, creates, pre_images, pre_fail;
    uint64_t replays, replay_draws, replay_interp, replay_stale, replay_notex, replay_bad;
    uint64_t saves, restores, put_fail;
    uint64_t im_draws, im_paired, im_tris, im_tris_lerped, trimmed, zs_strips, zs_groups, zs_groups_all, zs_pose, zs_widened;
};

static uint32_t g_mesh_id;
static int dbg_on()
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_INTERP_DEBUG"); on = e && *e && e[0] != '0'; }
    return on;
}

class IpRec : public GpuBackend {
public:
    GpuBackend *in;
    std::vector<uint32_t> life;  /* per target id: creations + destructions */
    Slot slot[NR_IP_SLOTS];
    int cur = -1;                /* slot recording */
    int replaying = 0;
    std::vector<Pre> saved;      /* current content of targets a replay wrote (restore) */
    int dirty = 0;
    Stats st = {};

    explicit IpRec(GpuBackend *b) : in(b) { sync(); }
    ~IpRec() override;
    void sync()
    {
        n_decodes = in->n_decodes;
        n_decode_hits = in->n_decode_hits;
        n_nr_tex = in->n_nr_tex;
        n_nr_mesh = in->n_nr_mesh;
        n_nr_blend_approx = in->n_nr_blend_approx;
        n_nr_mesh_pre = in->n_nr_mesh_pre;
        n_rt_pool_hits = in->n_rt_pool_hits;
    }
    uint32_t life_of(int id) const { return id >= 0 && (size_t)id < life.size() ? life[(size_t)id] : 0; }
    void bump(int id)
    {
        if (id < 0) return;
        if ((size_t)id >= life.size()) life.resize((size_t)id + 1, 0);
        life[(size_t)id]++;
    }
    void free_slot(int i)
    {
        Slot &s = slot[i];
        for (Pre &p : s.pre)
            if (p.img >= 0) in->rt_destroy(p.img);
        for (Cmd &c : s.cmds)
            if (c.img >= 0) in->rt_destroy(c.img);
        s.pre.clear();
        s.cmds.clear();
        s.born.clear();
        s.ord.clear();
        s.nborn = 0;
        s.rec = 0;
        s.bad = 0;
    }
    /* a write to target id is coming: its pre-image first (pre-existing targets, once per log) */
    void writes(int id)
    {
        if (cur < 0 || replaying || id < 0) return;
        Slot &s = slot[cur];
        if (s.born.count(id)) return;
        for (const Pre &p : s.pre)
            if (p.id == id) return;
        Pre p;
        p.id = id;
        p.life = life_of(id);
        p.img = in->rt_clone(id);
        if (p.img < 0) { st.pre_fail++; s.bad = 1; }
        else st.pre_images++;
        s.pre.push_back(p);
    }
    Cmd &add(CmdKind k)
    {
        Slot &s = slot[cur];
        s.cmds.emplace_back();
        Cmd &c = s.cmds.back();
        c.k = k;
        c.has_d = 0;
        c.mesh_id = 0;
        c.rt[0] = c.rt[1] = c.rt[2] = -1;
        c.srt[0] = c.srt[1] = c.srt[2] = -1;
        c.life[0] = c.life[1] = c.life[2] = 0;
        c.img = -1;
        return c;
    }
    bool recording() const { return cur >= 0 && !replaying; }

    /* ---- the backend, forwarded ---- */
    const char *name() const override { return in->name(); }
    bool exact() const override { return in->exact(); }
    bool rov() const override { return in->rov(); }
    bool zrov() const override { return in->zrov(); }
    void mirror_upload(uint32_t off, uint32_t len, const uint8_t *src) override { in->mirror_upload(off, len, src); }
    void mirror_download(const uint32_t *runs, int nruns, uint8_t *vram) override { in->mirror_download(runs, nruns, vram); }
    bool can_merge() const override { return in->can_merge(); }
    void mirror_merge(uint32_t w0, uint32_t n, const uint32_t *dm) override { in->mirror_merge(w0, n, dm); }
    int rt_create(int depth, int w, int h) override
    {
        int id = in->rt_create(depth, w, h);
        if (id >= 0) {
            bump(id);
            if (recording()) {
                Cmd &c = add(C_CREATE);
                c.rt[0] = id;
                c.life[0] = life_of(id);
                c.a = depth; c.b = w; c.c = h;
                slot[cur].born[id] = life_of(id);
                slot[cur].ord[id] = slot[cur].nborn++;
                st.creates++;
            }
        }
        sync();
        return id;
    }
    void rt_resize(int id, int w, int h) override
    {
        if (recording()) {
            writes(id);
            Cmd &c = add(C_RESIZE);
            c.rt[0] = id;
            c.life[0] = life_of(id);
            c.a = w; c.b = h;
        }
        in->rt_resize(id, w, h);
    }
    void rt_destroy(int id) override
    {
        if (recording() && id >= 0) {
            Cmd &c = add(C_DESTROY);
            c.rt[0] = id;
            c.life[0] = life_of(id);
            slot[cur].ord.erase(id);
        }
        in->rt_destroy(id);
        bump(id);
    }
    void rt_clear(int id) override
    {
        if (recording()) {
            writes(id);
            Cmd &c = add(C_CLEAR);
            c.rt[0] = id;
            c.life[0] = life_of(id);
            st.clears++;
        }
        in->rt_clear(id);
    }
    void rt_load(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override
    {
        if (recording()) {
            writes(id);
            Cmd &c = add(C_LOAD);
            c.rt[0] = id;
            c.life[0] = life_of(id);
            c.bp = bp; c.bw = bw; c.psm = psm; c.r = r;
            st.loads++;
            in->rt_load(id, bp, bw, psm, r);
            /* the target after the load: the replay puts it back (local memory is not the same
             * then: the core makes it current from live targets before a load) */
            slot[cur].cmds.back().img = in->rt_clone(id);
            return;
        }
        in->rt_load(id, bp, bw, psm, r);
    }
    void rt_writeback(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) override { in->rt_writeback(id, bp, bw, psm, r); }
    bool rt_copy(int dst, int dx, int dy, int src, const GpuRect &sr) override
    {
        if (recording()) {
            writes(dst);
            writes(src);
            Cmd &c = add(C_COPY);
            c.rt[0] = dst; c.life[0] = life_of(dst);
            c.rt[1] = src; c.life[1] = life_of(src);
            c.a = dx; c.b = dy; c.r = sr;
            st.copies++;
        }
        return in->rt_copy(dst, dx, dy, src, sr);
    }
    bool rt_reinterpret(int dst, uint32_t dbp, uint32_t dbw, int dpsm, const GpuRect &dr, int src, uint32_t sbp, uint32_t sbw,
                        int spsm, const GpuRect &sr) override
    {
        if (recording()) {
            writes(dst);
            writes(src);
            Cmd &c = add(C_REINT);
            c.rt[0] = dst; c.life[0] = life_of(dst);
            c.rt[1] = src; c.life[1] = life_of(src);
            c.bp = dbp; c.bw = dbw; c.psm = dpsm; c.r = dr;
            c.bp2 = sbp; c.bw2 = sbw; c.psm2 = spsm; c.r2 = sr;
        }
        return in->rt_reinterpret(dst, dbp, dbw, dpsm, dr, src, sbp, sbw, spsm, sr);
    }
    int rt_read(int id, const GpuRect &r, uint32_t *out) override { return in->rt_read(id, r, out); }
    void set_clut(const GpuClutCB &c) override { in->set_clut(c); }
    void set_clut_part(const GpuClutCB &c, const uint8_t *own) override { in->set_clut_part(c, own); }
    bool clut_load_gpu(const uint32_t u[3][4]) override { return in->clut_load_gpu(u); }
    bool clut_read(GpuClutCB *out) override { return in->clut_read(out); }
    bool mem_copy(const uint32_t u[3][4]) override { return in->mem_copy(u); }
    bool mem_xfer_batch(const uint8_t *bytes, uint32_t nbytes, const uint32_t *desc, uint32_t ndesc, uint32_t npx) override
    {
        return in->mem_xfer_batch(bytes, nbytes, desc, ndesc, npx);
    }
    void draw(const GpuDraw &d) override
    {
        if (recording()) slot[cur].bad = 1;   /* (the GS-exact path: not in the native-only device) */
        in->draw(d);
    }
    void kick() override { in->kick(); sync(); }
    int snap_copy(const uint32_t *runs, int nruns) override { return in->snap_copy(runs, nruns); }
    const uint8_t *snap_map(int s) override { return in->snap_map(s); }
    void snap_unmap(int s) override { in->snap_unmap(s); }
    int disp_rt[2] = { -1, -1 };   /* the targets the last display read (circuits) */
    void note_display(const GpuDisplay &d)
    {
        for (int i = 0; i < 2; i++) disp_rt[i] = d.c[i].en ? d.c[i].rt : -1;
    }
    int display(const GpuDisplay &d, uint32_t *out) override
    {
        note_display(d);
        int rc = in->display(d, out);
        sync();
        return rc;
    }
    int display_post(const GpuDisplay &d, const GpuPost &p, uint32_t *out) override
    {
        note_display(d);
        int rc = in->display_post(d, p, out);
        sync();
        return rc;
    }
    void *shared_out() override { return in->shared_out(); }
    bool vk_present_device(gpu_vk_device *o) override { return in->vk_present_device(o); }
    void set_scale(int s) override
    {
        for (int i = 0; i < NR_IP_SLOTS; i++) free_slot(i);
        drop_saved();
        in->set_scale(s);
    }
    bool nr_draw(const GpuNrDraw &g) override
    {
        if (recording()) {
            /* pre-images of what the draw writes and reads (a target read may be gone at replay) */
            writes(g.color_rt);
            writes(g.depth_rt);
            writes(g.tex_rt);
            Cmd &c = add(C_DRAW);
            c.g = g;
            if (g.d) { c.d = *g.d; c.has_d = 1; }
            if (g.im && g.nim) c.im.assign(g.im, g.im + g.nim);
            if (g.runs && g.nruns > 0) c.runs.assign(g.runs, g.runs + 2 * g.nruns);
            if (g.dec_rgba) {
                size_t n = (size_t)(g.dec_rect.x1 - g.dec_rect.x0) * (size_t)(g.dec_rect.y1 - g.dec_rect.y0);
                c.rgba.assign(g.dec_rgba, g.dec_rgba + n);
            }
            c.mesh_id = g.im ? 0 : g_mesh_id;
            c.rt[0] = g.color_rt; c.life[0] = life_of(g.color_rt);
            c.rt[1] = g.depth_rt; c.life[1] = life_of(g.depth_rt);
            c.rt[2] = g.tex_rt; c.life[2] = life_of(g.tex_rt);
            for (int k = 0; k < 3; k++) {
                auto o = slot[cur].ord.find(c.rt[k]);
                c.srt[k] = o != slot[cur].ord.end() ? 0x40000000 + o->second : c.rt[k];
            }
            st.draws++;
        }
        bool ok = in->nr_draw(g);
        sync();
        return ok;
    }
    bool nr_tex_cached(const uint32_t *key, const GpuRect &rc) override { return in->nr_tex_cached(key, rc); }
    void nr_mesh_prewarm(const gpu_nr_mesh &m) override { in->nr_mesh_prewarm(m); }
    int rt_clone(int src) override { return in->rt_clone(src); }
    bool rt_put(int dst, int src) override { return in->rt_put(dst, src); }

    /* ---- interpolated presentation ---- */
    void drop_saved()
    {
        for (Pre &p : saved)
            if (p.img >= 0) in->rt_destroy(p.img);
        saved.clear();
        dirty = 0;
    }
    void restore()
    {
        if (!dirty) return;
        for (Pre &p : saved) {
            if (p.img < 0) continue;
            if (life_of(p.id) != p.life || !in->rt_put(p.id, p.img)) st.put_fail++;
            in->rt_destroy(p.img);
        }
        saved.clear();
        dirty = 0;
        st.restores++;
    }
    /* map a recorded target to the one the replay uses (-1 stays -1); false: stale */
    bool map_rt(const Slot &s, std::map<int, int> &tmp, int id, uint32_t lf, int *out)
    {
        if (id < 0) { *out = -1; return true; }
        auto t = tmp.find(id);
        if (t != tmp.end()) { *out = t->second; return true; }
        if (life_of(id) != lf) return false;
        (void)s;
        *out = id;
        return true;
    }
    /* the slots sl[0..n) (oldest first) run again in order; interp_at: the one whose mesh draws
     * are interpolated (-1: none) */
    int replay(const int *sl, int n, int interp_at, int prev, float alpha)
    {
        for (int i = 0; i < n; i++)
            if (!slot[sl[i]].rec || slot[sl[i]].bad) { st.replay_bad++; return -1; }
        /* the targets' current content, once per dirty period */
        for (int i = 0; i < n; i++)
            for (const Pre &p : slot[sl[i]].pre) {
                bool have = false;
                for (const Pre &q : saved)
                    if (q.id == p.id) have = true;
                if (have || p.img < 0) continue;
                if (life_of(p.id) != p.life) continue;   /* (destroyed since: nothing to keep) */
                Pre q;
                q.id = p.id;
                q.life = p.life;
                q.img = in->rt_clone(p.id);
                if (q.img < 0) { st.put_fail++; dirty = !saved.empty(); return -1; }
                saved.push_back(q);
                st.saves++;
            }
        dirty = 1;
        replaying = 1;
        std::map<int, int> tmp;   /* targets the slots created or that are gone -> temporary ones */
        /* every target at its state when the sequence began: the first pre-image of it in the
         * sequence (targets an earlier slot created are its temporaries, already right) */
        {
            std::vector<int> done;
            std::map<int, uint32_t> born;
            for (int i = 0; i < n; i++) {
                for (const Pre &p : slot[sl[i]].pre) {
                    bool skip = p.img < 0 || born.count(p.id);
                    for (int d : done)
                        if (d == p.id) skip = true;
                    if (skip) continue;
                    done.push_back(p.id);
                    if (life_of(p.id) != p.life) {
                        /* destroyed (or re-made) since: a temporary target from its pre-image */
                        int t = in->rt_clone(p.img);
                        if (t >= 0) tmp[p.id] = t;
                        else st.put_fail++;
                    } else if (!in->rt_put(p.id, p.img)) {
                        st.put_fail++;
                    }
                }
                for (auto &kv : slot[sl[i]].born) born[kv.first] = kv.second;
            }
        }
        for (int i = 0; i < n; i++) {
            /* after the interpolated frame only what reaches the displayed target matters (this
             * game: the copy of the frame into the display buffer at the next frame's start);
             * the rest of the later frames is drawn into targets the restore puts back anyway */
            size_t lim = slot[sl[i]].cmds.size();
            if (interp_at >= 0 && i > interp_at && trim_on() && (disp_rt[0] >= 0 || disp_rt[1] >= 0)) {
                lim = 0;
                for (size_t ci = 0; ci < slot[sl[i]].cmds.size(); ci++) {
                    const Cmd &c = slot[sl[i]].cmds[ci];
                    if (c.k != C_CREATE && c.k != C_DESTROY && c.rt[0] >= 0 && (c.rt[0] == disp_rt[0] || c.rt[0] == disp_rt[1]))
                        lim = ci + 1;
                }
                st.trimmed += slot[sl[i]].cmds.size() - lim;
            }
            replay_cmds(slot[sl[i]], tmp, i == interp_at,
                        i == interp_at && prev >= 0 && prev != sl[i] && slot[prev].rec && !slot[prev].bad ? &slot[prev] : NULL, alpha,
                        lim);
        }
        for (auto &kv : tmp) {
            in->rt_destroy(kv.second);
            bump(kv.second);
        }
        replaying = 0;
        in->kick();
        sync();
        st.replays++;
        return 0;
    }
    /* does what slot sl[0]'s mesh draws drew reach the displayed target by the end of the
     * sequence (through draws sampling a target and target copies)?  1 yes, 0 no, -1 unknown
     * (no display seen yet) */
    int flows(const int *sl, int n)
    {
        if (disp_rt[0] < 0 && disp_rt[1] < 0) return -1;
        std::map<int, int> t;
        for (int i = 0; i < n; i++)
            for (const Cmd &c : slot[sl[i]].cmds) {
                switch (c.k) {
                case C_DRAW:
                    if (c.rt[0] < 0) break;
                    if ((i == 0 && c.mesh_id) || (c.rt[2] >= 0 && t[c.rt[2]])) t[c.rt[0]] = 1;
                    break;
                case C_COPY:
                case C_REINT:
                    if (t[c.rt[1]]) t[c.rt[0]] = 1;
                    break;
                case C_CREATE:
                case C_DESTROY:
                    t[c.rt[0]] = 0;
                    break;
                default:
                    break;
                }
            }
        return (disp_rt[0] >= 0 && t[disp_rt[0]]) || (disp_rt[1] >= 0 && t[disp_rt[1]]) ? 1 : 0;
    }
    /* immediate draws of a frame paired with the previous frame's: the same state and vertex
     * count, in order (the k-th draw of a key with the k-th of the previous frame) */
    static int im_key_drop()
    {
        static int m = -1;   /* $RG_INTERP_IMKEY=bits (measurement): 1 no targets, 2 no texture key, 4 no vertex count */
        if (m < 0) { const char *e = getenv("RG_INTERP_IMKEY"); m = e && *e ? atoi(e) : 0; }
        return m;
    }
    static uint64_t im_key(const Cmd &c)
    {
        uint64_t h = 1469598103934665603ull;
        int drop = im_key_drop();
        auto mix = [&h](const void *p, size_t n) {
            const unsigned char *b = (const unsigned char *)p;
            for (size_t i = 0; i < n; i++) h = (h ^ b[i]) * 1099511628211ull;
        };
        const GpuNrDraw &g = c.g;
        if (!(drop & 1)) mix(&c.srt[0], sizeof c.srt);
        mix(&g.tme, sizeof g.tme);
        if (!(drop & 2)) mix(g.dec_key, sizeof g.dec_key);
        mix(&g.alpha_abcd, sizeof g.alpha_abcd);
        mix(&g.abe, sizeof g.abe);
        mix(&g.zfunc, sizeof g.zfunc);
        mix(&g.zwrite, sizeof g.zwrite);
        mix(&g.cmask, sizeof g.cmask);
        mix(&g.tex_snap, sizeof g.tex_snap);
        mix(&g.crov, sizeof g.crov);
        size_t nv = c.im.size(), nr = c.runs.size();
        if (!(drop & 4)) mix(&nv, sizeof nv);
        mix(&nr, sizeof nr);
        return h;
    }
    std::vector<int> pair_im(const Slot &s, const Slot &p)
    {
        std::vector<int> m(s.cmds.size(), -1);
        std::unordered_map<uint64_t, std::deque<int>> q;
        for (size_t i = 0; i < p.cmds.size(); i++)
            if (p.cmds[i].k == C_DRAW && !p.cmds[i].im.empty()) q[im_key(p.cmds[i])].push_back((int)i);
        for (size_t i = 0; i < s.cmds.size(); i++) {
            if (s.cmds[i].k != C_DRAW || s.cmds[i].im.empty()) continue;
            auto it = q.find(im_key(s.cmds[i]));
            if (it == q.end() || it->second.empty()) continue;
            m[i] = it->second.front();
            it->second.pop_front();
        }
        return m;
    }
    /* the triangles of a paired draw that moved (same texture coordinates, a bounded step on
     * screen) lerped from the previous frame's toward the recorded ones; the rest as recorded */
    std::vector<GpuImVtx> im_tmp;
    const GpuImVtx *im_lerp(const Cmd &c, const Cmd &pc, float alpha)
    {
        size_t n = c.im.size();
        float lim = 0.15f * (float)(c.g.vp_w > c.g.vp_h ? c.g.vp_w : c.g.vp_h);
        int changed = 0;
        im_tmp.assign(c.im.begin(), c.im.end());
        for (size_t t = 0; t + 2 < n; t += 3) {
            if (t + 2 >= pc.im.size()) break;
            const GpuImVtx *a = &pc.im[t], *b = &c.im[t];
            bool ok = true, moved = false;
            for (int k = 0; k < 3 && ok; k++) {
                if (memcmp(&a[k].s, &b[k].s, 3 * sizeof(float))) ok = false;
                float dx = b[k].x - a[k].x, dy = b[k].y - a[k].y;
                if (!(dx * dx + dy * dy <= lim * lim)) ok = false;
                if (dx != 0.0f || dy != 0.0f || a[k].z != b[k].z || a[k].rgba != b[k].rgba) moved = true;
            }
            st.im_tris++;
            if (!ok || !moved) continue;
            for (int k = 0; k < 3; k++) {
                GpuImVtx &o = im_tmp[t + (size_t)k];
                uint32_t rc = 0;
                o.x = a[k].x + (b[k].x - a[k].x) * alpha;
                o.y = a[k].y + (b[k].y - a[k].y) * alpha;
                o.z = (uint32_t)((double)a[k].z + ((double)b[k].z - (double)a[k].z) * alpha + 0.5);
                for (int j = 0; j < 32; j += 8) {
                    float ca = (float)((a[k].rgba >> j) & 0xFF), cb = (float)((b[k].rgba >> j) & 0xFF);
                    rc |= (uint32_t)(ca + (cb - ca) * alpha + 0.5f) << j;
                }
                o.rgba = rc;
            }
            st.im_tris_lerped++;
            changed = 1;
        }
        return changed ? im_tmp.data() : c.im.data();
    }
    static int trim_on()
    {
        static int t = -1;   /* $RG_INTERP_TRIM=0 (control): later frames replayed whole */
        if (t < 0) { const char *e = getenv("RG_INTERP_TRIM"); t = !(e && e[0] == '0'); }
        return t;
    }
    /* ---- composite placement and composite poses ($RG_INTERP_ZSCALE, default 4; nr_interp.c) ----
     * A strip group: the immediate draws that read a work target W into another target right
     * after mesh draws into W (the offscreen composite: a character part drawn into a work
     * buffer, copied into the frame by sprite strips cut for its screen box), until W is written
     * again.  The battle renderer draws each character through its own view of the work buffer,
     * so the groups of one key (W, destination, as frame-stable tokens) are one character: their
     * union rectangle is paired with the previous frame's of the same key, and every group of it
     * moves by the lerp of the two rectangles' centres: the character, drawn as recorded, travels
     * with the scene in one piece (per part, the parts' boxes change with the pose and drift
     * apart).  The parts' own constants cannot be interpolated: they also place each part in the
     * work buffer.
     * Composite poses (mode 4, default; docs/NATIVE-RENDER.md "Checkpoint 13"): one group is one
     * composite call (ModelDrawOffscreenCompositeMaybe_16aac0: an RGBA-0 clear of the call's box
     * in W, its parts, the copy strips); a group paired with the previous frame's draws its parts
     * with the bones interpolated (camera / object rows as recorded, so the part stays where the
     * frame put it in W), its copy moves by the pair's centres and is widened, with the clear, to
     * cover the pose between the two frames: nothing is cut (place_plan, zs_widen). */
    struct Grp {
        int key_w, key_f;
        float x0, y0, x1, y1;
        int vp;
        int clear;     /* the work target's clear before the parts (an untextured, unblended immediate draw), -1 none */
        int own;       /* the parts drawn into W since the last group feed this one (else it re-reads W: clear inherited) */
        int zs;        /* every part fed to it is a Z-scale composite mesh (nr_ip_zs_item; only in a pass) */
        uint64_t sig;  /* its parts' meshes (device mesh id, index count; order-free), 0 none: the call's identity across frames */
    };
    static int place_on()
    {
        int m = nr_ip_zs_mode();
        return m == 2 || m == 3 || m == 4;
    }
    /* cmd index -> group index (-1), and the groups; feed (optional): mesh draw cmd index -> the
     * group its part goes to (the first group reading its work target after it) */
    static void groups_of(const Slot &s, std::vector<int> &of, std::vector<Grp> &gs, std::vector<int> *feed = NULL)
    {
        of.assign(s.cmds.size(), -1);
        if (feed) feed->assign(s.cmds.size(), -1);
        gs.clear();
        std::map<int, int> lastw;   /* target id -> 1: last written by a mesh draw, 2 otherwise */
        std::map<int, int> open;    /* work target id -> its open group */
        std::map<int, std::vector<int>> pend;   /* target id -> mesh draws and clears into it since its last group */
        std::map<int, int> lastclear;           /* work target id -> the clear of its latest group with parts */
        auto wrote = [&](int id, int kind) {
            if (id < 0) return;
            lastw[id] = kind;
            open.erase(id);
        };
        for (size_t i = 0; i < s.cmds.size(); i++) {
            const Cmd &c = s.cmds[i];
            switch (c.k) {
            case C_DRAW:
                if (c.im.empty()) {
                    wrote(c.rt[0], c.mesh_id ? 1 : 2);
                    if (c.mesh_id && c.rt[0] >= 0) pend[c.rt[0]].push_back((int)i);
                    break;
                }
                if (c.rt[2] >= 0 && c.rt[2] != c.rt[0] && c.rt[0] >= 0) {
                    auto o = open.find(c.rt[2]);
                    int gi = -1;
                    if (o != open.end() && gs[(size_t)o->second].key_f == c.srt[0]) gi = o->second;
                    else if (lastw[c.rt[2]] == 1) {
                        Grp g;
                        g.key_w = c.srt[2];
                        g.key_f = c.srt[0];
                        g.x0 = g.y0 = 1e30f;
                        g.x1 = g.y1 = -1e30f;
                        g.vp = c.g.vp_w > c.g.vp_h ? c.g.vp_w : c.g.vp_h;
                        g.clear = -1;
                        g.own = 0;
                        g.zs = 0;
                        g.sig = 0;
                        gi = (int)gs.size();
                        /* the parts since W's last group, and the clear before the first of them */
                        std::vector<int> &pv = pend[c.rt[2]];
                        int clr = -1, meshes = 0, zsn = 0;
                        for (int idx : pv) {
                            const Cmd &m = s.cmds[(size_t)idx];
                            if (m.im.empty()) {
                                meshes++;
                                if (feed) (*feed)[(size_t)idx] = gi;
                                zsn += nr_ip_zs_item(m.mesh_id);
                                if (m.has_d) {
                                    uint64_t h = ((uint64_t)m.d.mesh.id << 32 | m.d.mesh.nidx) * 0x9E3779B97F4A7C15ull;
                                    g.sig += (h ^ (h >> 29)) | 1;   /* (a sum: the parts come in any order) */
                                }
                            } else if (!meshes)
                                clr = idx;   /* (the last one before the parts) */
                        }
                        g.zs = meshes && zsn == meshes;   /* (all its parts composites: not a screen grab) */
                        if (meshes) {
                            g.own = 1;
                            g.clear = clr;
                            lastclear[c.rt[2]] = clr;
                        } else {
                            auto lc = lastclear.find(c.rt[2]);
                            g.clear = lc != lastclear.end() ? lc->second : -1;
                        }
                        pv.clear();
                        gs.push_back(g);
                        open[c.rt[2]] = gi;
                    }
                    if (gi >= 0) {
                        Grp &g = gs[(size_t)gi];
                        for (const GpuImVtx &v : c.im) {
                            if (v.x < g.x0) g.x0 = v.x;
                            if (v.y < g.y0) g.y0 = v.y;
                            if (v.x > g.x1) g.x1 = v.x;
                            if (v.y > g.y1) g.y1 = v.y;
                        }
                        of[i] = gi;
                        lastw[c.rt[2]] = 1;   /* (W stays the part's until written again) */
                        lastw[c.rt[0]] = 2;
                        open.erase(c.rt[0]);
                        break;
                    }
                }
                wrote(c.rt[0], 2);
                /* an untextured, unblended immediate draw: a clear of the work buffer when parts follow */
                if (c.rt[0] >= 0 && !c.g.tme && !c.g.abe && c.rt[2] < 0) pend[c.rt[0]].push_back((int)i);
                break;
            case C_COPY:
            case C_LOAD:
            case C_CLEAR:
            case C_REINT:
            case C_RESIZE:
                wrote(c.rt[0], 2);
                pend.erase(c.rt[0]);
                lastclear.erase(c.rt[0]);
                break;
            case C_CREATE:
            case C_DESTROY:
                lastw.erase(c.rt[0]);
                open.erase(c.rt[0]);
                pend.erase(c.rt[0]);
                lastclear.erase(c.rt[0]);
                break;
            }
        }
    }
    /* per group of s: the shift its draws take at alpha (0 when unpaired or not plausible); pose
     * (mode 4): per group ex[4] = how far its copy strips (and, for the group owning the parts,
     * the work buffer's clear) are widened left / top / right / bottom, pose[g] = 1 when its parts
     * are interpolated (then no shift), 2 when it re-reads a work buffer whose parts are (drawn as
     * recorded), 0 placement as in mode 2 */
    struct Plan {
        std::vector<int> of, feed, clear_of;   /* cmd -> group (strips), cmd -> group (parts), cmd -> group (its clear) */
        std::vector<Grp> gs;
        std::vector<float> sh, ex, er;   /* er: (pose) the rectangle the group's copy covers, x0 y0 x1 y1 */
        std::vector<int> pose;
    };
    void place_plan(const Slot &s, const Slot &p, float alpha, Plan &pl)
    {
        std::vector<Grp> gp;
        std::vector<int> ofp;
        const int pose_mode = nr_ip_zs_mode() == 4;
        std::vector<Grp> &gs = pl.gs;
        groups_of(s, pl.of, gs, pose_mode ? &pl.feed : NULL);
        groups_of(p, ofp, gp);
        std::vector<float> &sh = pl.sh;
        sh.assign(gs.size() * 2, 0.0f);
        pl.ex.assign(gs.size() * 4, 0.0f);
        pl.er.assign(gs.size() * 4, 0.0f);
        pl.pose.assign(gs.size(), 0);
        pl.clear_of.assign(s.cmds.size(), -1);
        /* union rectangles per key */
        typedef std::pair<int, int> K;
        auto unite = [](std::map<K, Grp> &m, const Grp &g) {
            auto it = m.find(K(g.key_w, g.key_f));
            if (it == m.end()) { m[K(g.key_w, g.key_f)] = g; return; }
            Grp &u = it->second;
            if (g.x0 < u.x0) u.x0 = g.x0;
            if (g.y0 < u.y0) u.y0 = g.y0;
            if (g.x1 > u.x1) u.x1 = g.x1;
            if (g.y1 > u.y1) u.y1 = g.y1;
        };
        std::map<K, Grp> us, up;
        for (const Grp &g : gs) unite(us, g);
        for (const Grp &g : gp) unite(up, g);
        std::map<K, std::pair<float, float>> d;
        for (auto &kv : us) {
            auto it = up.find(kv.first);
            if (it == up.end()) continue;
            const Grp &a = it->second, &b = kv.second;
            float wa = a.x1 - a.x0, ha = a.y1 - a.y0, wb = b.x1 - b.x0, hb = b.y1 - b.y0;
            float dx = 0.5f * (a.x0 + a.x1 - b.x0 - b.x1), dy = 0.5f * (a.y0 + a.y1 - b.y0 - b.y1);
            float lim = 0.15f * (float)b.vp;
            /* (parts' boxes, not a screen pass; a similar box; a bounded step) */
            if (!(wb > 0 && hb > 0) || wb > 0.5f * (float)b.vp || hb > 0.5f * (float)b.vp) continue;
            if (wa > 1.5f * wb + 16.0f || wb > 1.5f * wa + 16.0f || ha > 1.5f * hb + 16.0f || hb > 1.5f * ha + 16.0f) continue;
            if (!(dx * dx + dy * dy <= lim * lim)) continue;
            d[kv.first] = std::make_pair(dx * (1.0f - alpha), dy * (1.0f - alpha));
        }
        /* pose, per group (one composite call: the clear of its work buffer, its parts, the copy
         * strips; several calls and several characters can share one work buffer key): it owns
         * parts that are all Z-scale meshes, its clear (RGBA 0, not a full-target clear) overlaps
         * its box, and it pairs with the previous frame's group of the key nearest in box (greedy:
         * the calls can come in another order) with a bounded step; why codes in the debug line:
         * 1 parts / clear, 2 clear not RGBA 0, 3 clear apart, 4 clear too large, 5-7 the pair.
         * Its copy is moved by the pair's centres (as placement) and widened, and its clear grown,
         * to the union of its box and the previous box moved onto it, + a margin (GS window
         * pixels: the work buffer and the frame share the window) */
        std::vector<int> gok(gs.size(), 0), gpair(gs.size(), -1), gwhy(gs.size(), 0), gks(gs.size(), 0), gkp(gs.size(), 0);
        std::vector<float> gsh(gs.size() * 2, 0.0f);
        std::vector<std::vector<float>> eg(gs.size());
        if (pose_mode) {
            std::map<K, std::vector<int>> ks, kp;
            for (size_t i = 0; i < gs.size(); i++) ks[K(gs[i].key_w, gs[i].key_f)].push_back((int)i);
            for (size_t i = 0; i < gp.size(); i++) kp[K(gp[i].key_w, gp[i].key_f)].push_back((int)i);
            const float m = 8.0f;
            /* each group with a previous frame's group, greedily by box distance (centre and size;
             * the calls can come in another order): first the groups drawing the same parts (part
             * signature, any work-buffer key: a character's view of the work buffer is a target the
             * frame creates, keyed by its creation ordinal, which shifts when another character's
             * view comes or goes), then the rest within their key ($RG_INTERP_ZSPAIR=0: by key only,
             * checkpoint 13) */
            static int bysig = -1;
            if (bysig < 0) { const char *e = getenv("RG_INTERP_ZSPAIR"); bysig = !(e && e[0] == '0'); }
            std::vector<int> gall(gs.size(), -1);
            {
                std::vector<std::pair<std::pair<int, float>, std::pair<int, int>>> cand;
                for (size_t i = 0; i < gs.size(); i++)
                    for (size_t j = 0; j < gp.size(); j++) {
                        const Grp &g = gs[i], &q = gp[j];
                        int tier;
                        if (bysig && g.sig && g.sig == q.sig && g.key_f == q.key_f) tier = 0;
                        else if (g.key_w == q.key_w && g.key_f == q.key_f) tier = 1;
                        else continue;
                        float c = fabsf(q.x0 - g.x0) + fabsf(q.x1 - g.x1) + fabsf(q.y0 - g.y0) + fabsf(q.y1 - g.y1);
                        cand.push_back(std::make_pair(std::make_pair(tier, c), std::make_pair((int)i, (int)j)));
                    }
                std::sort(cand.begin(), cand.end());
                std::vector<char> used(gp.size(), 0);
                for (auto &c : cand)
                    if (gall[(size_t)c.second.first] < 0 && !used[(size_t)c.second.second]) {
                        gall[(size_t)c.second.first] = c.second.second;
                        used[(size_t)c.second.second] = 1;
                    }
            }
            for (auto &kv : ks) {
                const std::vector<int> &vs = kv.second, &vq = kp[kv.first];
                std::vector<int> pair(vs.size(), -1);
                for (int v : vs) { gks[(size_t)v] = (int)vs.size(); gkp[(size_t)v] = (int)vq.size(); }   /* (debug: interp_groups.py) */
                for (size_t n = 0; n < vs.size(); n++) pair[n] = gall[(size_t)vs[n]];
                for (size_t n = 0; n < vs.size(); n++) {
                    if (pair[n] < 0) continue;
                    const Grp &g = gs[(size_t)vs[n]], &q = gp[(size_t)pair[n]];
                    gpair[(size_t)vs[n]] = pair[n];
                    if (!g.own || g.clear < 0 || !g.zs) { gwhy[(size_t)vs[n]] = 1; continue; }
                    float cx0 = 1e30f, cy0 = 1e30f, cx1 = -1e30f, cy1 = -1e30f;
                    int zero = 1;
                    for (const GpuImVtx &v : s.cmds[(size_t)g.clear].im) {
                        if (v.rgba) zero = 0;
                        cx0 = v.x < cx0 ? v.x : cx0; cx1 = v.x > cx1 ? v.x : cx1;
                        cy0 = v.y < cy0 ? v.y : cy0; cy1 = v.y > cy1 ? v.y : cy1;
                    }
                    if (!zero) { gwhy[(size_t)vs[n]] = 2; continue; }   /* (the composite clears to RGBA 0) */
                    if (!(cx1 > g.x0 && cx0 < g.x1 && cy1 > g.y0 && cy0 < g.y1)) { gwhy[(size_t)vs[n]] = 3; continue; }
                    if (cx1 - cx0 > 0.5f * (float)g.vp || cy1 - cy0 > 0.5f * (float)g.vp) { gwhy[(size_t)vs[n]] = 4; continue; }
                    float wa = q.x1 - q.x0, ha = q.y1 - q.y0, wb = g.x1 - g.x0, hb = g.y1 - g.y0;
                    float dx = 0.5f * (q.x0 + q.x1 - g.x0 - g.x1), dy = 0.5f * (q.y0 + q.y1 - g.y0 - g.y1);
                    float lim = 0.15f * (float)g.vp;
                    if (!(wb >= 0 && hb >= 0 && wa >= 0 && ha >= 0)) { gwhy[(size_t)vs[n]] = 5; continue; }
                    if (wa > 3.0f * wb + 64.0f || wb > 3.0f * wa + 64.0f || ha > 3.0f * hb + 64.0f || hb > 3.0f * ha + 64.0f) { gwhy[(size_t)vs[n]] = 6; continue; }
                    if (!(dx * dx + dy * dy <= lim * lim)) { gwhy[(size_t)vs[n]] = 7; continue; }
                    /* the parts stay where this frame drew them in the work buffer (their camera and
                     * object rows as recorded, the bones interpolated: nr_interp.c), the copy moves
                     * with the pair's centres as in placement; the pose then lies about within the
                     * union of this box and the previous one moved onto it */
                    float qx0 = q.x0 - dx, qy0 = q.y0 - dy, qx1 = q.x1 - dx, qy1 = q.y1 - dy;
                    std::vector<float> e(4);
                    e[0] = g.x0 - ((qx0 < g.x0 ? qx0 : g.x0) - m);
                    e[1] = g.y0 - ((qy0 < g.y0 ? qy0 : g.y0) - m);
                    e[2] = ((qx1 > g.x1 ? qx1 : g.x1) + m) - g.x1;
                    e[3] = ((qy1 > g.y1 ? qy1 : g.y1) + m) - g.y1;
                    gsh[2 * (size_t)vs[n]] = dx * (1.0f - alpha);
                    gsh[2 * (size_t)vs[n] + 1] = dy * (1.0f - alpha);
                    eg[(size_t)vs[n]] = e;
                    pl.er[4 * (size_t)vs[n] + 0] = g.x0 - e[0];
                    pl.er[4 * (size_t)vs[n] + 1] = g.y0 - e[1];
                    pl.er[4 * (size_t)vs[n] + 2] = g.x1 + e[2];
                    pl.er[4 * (size_t)vs[n] + 3] = g.y1 + e[3];
                    gok[(size_t)vs[n]] = 1;
                }
            }
        }
        for (size_t i = 0; i < gs.size(); i++) {
            K k(gs[i].key_w, gs[i].key_f);
            if (gok[i]) {
                const std::vector<float> &e = eg[i];
                for (int j = 0; j < 4; j++) pl.ex[4 * i + (size_t)j] = e[(size_t)j];
                pl.pose[i] = 1;
                sh[2 * i] = gsh[2 * i];
                sh[2 * i + 1] = gsh[2 * i + 1];
                pl.clear_of[(size_t)gs[i].clear] = (int)i;
                st.zs_pose++;
                continue;
            }
            if (pose_mode && gpair[i] >= 0) {
                /* (mode 4) a group drawn as recorded moves with its own pair, not the character's
                 * union: its neighbours are posed, not placed */
                const Grp &q = gp[(size_t)gpair[i]], &g = gs[i];
                float dx = 0.5f * (q.x0 + q.x1 - g.x0 - g.x1), dy = 0.5f * (q.y0 + q.y1 - g.y0 - g.y1);
                float lim = 0.15f * (float)g.vp;
                if (dx * dx + dy * dy <= lim * lim) {
                    sh[2 * i] = dx * (1.0f - alpha);
                    sh[2 * i + 1] = dy * (1.0f - alpha);
                    st.zs_groups++;
                }
                continue;
            }
            auto it = d.find(k);
            if (it == d.end()) continue;
            sh[2 * i] = it->second.first;
            sh[2 * i + 1] = it->second.second;
            st.zs_groups++;
        }
        if (pose_mode)
            /* a group re-reading a work buffer whose parts moved (e.g. the motion-blur copy): as
             * recorded, not shifted (the parts are where the interpolation put them) */
            for (size_t i = 0; i < gs.size(); i++) {
                if (gs[i].own || gs[i].clear < 0 || pl.pose[i]) continue;
                int owner = pl.clear_of[(size_t)gs[i].clear];
                if (owner >= 0 && pl.pose[(size_t)owner] == 1) {
                    pl.pose[i] = 2;
                    sh[2 * i] = sh[2 * i + 1] = 0.0f;
                }
            }
        st.zs_groups_all += gs.size();
        if (dbg_on()) {
            static int nd;
            for (size_t i = 0; i < gs.size() && nd < 4000000; i++, nd++)
                fprintf(stderr, "interp group %zu: key %d/%d box %.0f,%.0f-%.0f,%.0f own %d clear %d zs %d pose %d why %d pair %d ex %.0f %.0f %.0f %.0f sh %.1f %.1f ks %d kp %d\n", i,
                        gs[i].key_w, gs[i].key_f, gs[i].x0, gs[i].y0, gs[i].x1, gs[i].y1, gs[i].own, gs[i].clear, gs[i].zs, pl.pose[i], gwhy[i], gpair[i],
                        pl.ex[4 * i], pl.ex[4 * i + 1], pl.ex[4 * i + 2], pl.ex[4 * i + 3], sh[2 * i], sh[2 * i + 1], gks[i], gkp[i]);
        }
    }
    /* the draw's vertices on its outer edges moved out by ex (left, top, right, bottom), texture
     * coordinates along (the draw's own pixel -> texel mapping, from its extreme vertices): copy
     * strips cut for the recorded box cover the widened one; a clear (untextured) just grows */
    std::vector<GpuImVtx> ex_tmp;
    const GpuImVtx *zs_widen(const Cmd &c, const GpuImVtx *v, const float *ex)
    {
        size_t n = c.im.size();
        if (!n || (ex[0] <= 0.0f && ex[1] <= 0.0f && ex[2] <= 0.0f && ex[3] <= 0.0f)) return v;
        float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f;
        size_t ix0 = 0, iy0 = 0, ix1 = 0, iy1 = 0;
        for (size_t i = 0; i < n; i++) {
            if (v[i].x < x0) { x0 = v[i].x; ix0 = i; }
            if (v[i].x > x1) { x1 = v[i].x; ix1 = i; }
            if (v[i].y < y0) { y0 = v[i].y; iy0 = i; }
            if (v[i].y > y1) { y1 = v[i].y; iy1 = i; }
        }
        if (!(x1 > x0) || !(y1 > y0)) return v;
        float su = 0.0f, sv = 0.0f;   /* texels per pixel (u = s / q) */
        if (c.g.tme) {
            float qa = v[ix0].q != 0.0f ? v[ix0].q : 1.0f, qb = v[ix1].q != 0.0f ? v[ix1].q : 1.0f;
            float qc = v[iy0].q != 0.0f ? v[iy0].q : 1.0f, qd = v[iy1].q != 0.0f ? v[iy1].q : 1.0f;
            su = (v[ix1].s / qb - v[ix0].s / qa) / (x1 - x0);
            sv = (v[iy1].t / qd - v[iy0].t / qc) / (y1 - y0);
            if (!(su != 0.0f) || !(sv != 0.0f) || !std::isfinite(su) || !std::isfinite(sv)) return v;
        }
        ex_tmp.assign(v, v + n);
        for (GpuImVtx &o : ex_tmp) {
            float q = o.q != 0.0f ? o.q : 1.0f, dx = 0.0f, dy = 0.0f;
            if (o.x == x0) dx = -ex[0];
            else if (o.x == x1) dx = ex[2];
            if (o.y == y0) dy = -ex[1];
            else if (o.y == y1) dy = ex[3];
            o.x += dx;
            o.y += dy;
            if (c.g.tme) {
                o.s = (o.s / q + dx * su) * q;
                o.t = (o.t / q + dy * sv) * q;
            }
        }
        st.zs_widened++;
        return ex_tmp.data();
    }
    std::vector<GpuImVtx> zs_tmp;
    const GpuImVtx *zs_move(const Cmd &c, const GpuImVtx *v, float dx, float dy)
    {
        zs_tmp.assign(v, v + c.im.size());
        for (GpuImVtx &o : zs_tmp) { o.x += dx; o.y += dy; }
        return zs_tmp.data();
    }
    void replay_cmds(Slot &s, std::map<int, int> &tmp, int interp, const Slot *prev, float alpha, size_t lim)
    {
        std::vector<int> pm;
        Plan pl;
        if (prev) pm = pair_im(s, *prev);
        if (prev && place_on()) place_plan(s, *prev, alpha, pl);
        const std::vector<int> &zof = pl.of;
        const std::vector<float> &zsh = pl.sh;
        /* $RG_INTERP_ISOLATE=1 (measurement, tools/native/interp_pose.py): the interpolated frame's
         * composite characters alone: every other draw into the targets their strips copy into
         * writes no colour (depth as recorded) and those targets start cleared (the pose and
         * placement without the scene) */
        static int isolate = -1;
        if (isolate < 0) { const char *e = getenv("RG_INTERP_ISOLATE"); isolate = e && e[0] == '1'; }
        std::vector<int> iso_of;
        std::map<int, int> iso_dst;   /* destination target -> cleared yet */
        if (interp && isolate) {
            if (pl.of.empty()) {
                std::vector<Grp> ig;
                groups_of(s, iso_of, ig);
            } else
                iso_of = pl.of;
            for (size_t i = 0; i < s.cmds.size(); i++)
                if (iso_of[i] >= 0) iso_dst[s.cmds[i].rt[0]] = 0;
        }
        for (size_t ci = 0; ci < lim && ci < s.cmds.size(); ci++) {
            Cmd &c = s.cmds[ci];
            int a = -1, b = -1, t = -1;
            switch (c.k) {
            case C_CREATE: {
                auto old = tmp.find(c.rt[0]);
                if (old != tmp.end()) {   /* (a temporary for the id's earlier life) */
                    in->rt_destroy(old->second);
                    bump(old->second);
                    tmp.erase(old);
                }
                int id = in->rt_create(c.a, c.b, c.c);
                if (id >= 0) {
                    bump(id);
                    tmp[c.rt[0]] = id;
                }
                break;
            }
            case C_DESTROY: {
                auto it = tmp.find(c.rt[0]);
                if (it != tmp.end()) {
                    in->rt_destroy(it->second);
                    bump(it->second);
                    tmp.erase(it);
                }
                break;
            }
            case C_RESIZE:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && a >= 0) in->rt_resize(a, c.a, c.b);
                break;
            case C_CLEAR:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && a >= 0) in->rt_clear(a);
                break;
            case C_LOAD:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && a >= 0 && !(c.img >= 0 && in->rt_put(a, c.img)))
                    in->rt_load(a, c.bp, c.bw, c.psm, c.r);
                break;
            case C_REINT:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && map_rt(s, tmp, c.rt[1], c.life[1], &b) && a >= 0 && b >= 0)
                    in->rt_reinterpret(a, c.bp, c.bw, c.psm, c.r, b, c.bp2, c.bw2, c.psm2, c.r2);
                else
                    st.replay_stale++;
                break;
            case C_COPY:
                if (map_rt(s, tmp, c.rt[0], c.life[0], &a) && map_rt(s, tmp, c.rt[1], c.life[1], &b) && a >= 0 && b >= 0) {
                    in->rt_copy(a, c.a, c.b, b, c.r);
                } else
                    st.replay_stale++;
                break;
            case C_DRAW: {
                int iso_mask = 0;
                if (!iso_dst.empty()) {
                    auto it = iso_dst.find(c.rt[0]);
                    if (it != iso_dst.end()) {
                        int t0 = -1;
                        if (!it->second && map_rt(s, tmp, c.rt[0], c.life[0], &t0) && t0 >= 0) in->rt_clear(t0);
                        it->second = 1;
                        if (iso_of[ci] < 0) iso_mask = 1;   /* (depth still written: what hides the characters) */
                    }
                }
                if (!map_rt(s, tmp, c.rt[0], c.life[0], &a) || !map_rt(s, tmp, c.rt[1], c.life[1], &b) ||
                    !map_rt(s, tmp, c.rt[2], c.life[2], &t)) {
                    st.replay_stale++;
                    if (dbg_on() && st.replay_stale < 40)
                        fprintf(stderr, "interp replay: stale draw rt %d/%u %d/%u %d/%u now %u %u %u\n", c.rt[0], c.life[0], c.rt[1],
                                c.life[1], c.rt[2], c.life[2], life_of(c.rt[0]), life_of(c.rt[1]), life_of(c.rt[2]));
                    break;
                }
                GpuNrDraw g = c.g;
                gpu_nr_draw dd;
                g.color_rt = a;
                g.depth_rt = b;
                g.tex_rt = t;
                g.im = c.im.empty() ? NULL : c.im.data();
                {
                    /* a composite strip: moved with its group (not lerped) */
                    int zg = g.im && !zof.empty() ? zof[ci] : -1;
                    int zc = g.im && !pl.clear_of.empty() ? pl.clear_of[ci] : -1;
                    if (zg >= 0) {
                        float dx = zsh[2 * (size_t)zg], dy = zsh[2 * (size_t)zg + 1];
                        st.im_draws++;
                        if (pl.pose[(size_t)zg] == 1) g.im = zs_widen(c, g.im, &pl.ex[4 * (size_t)zg]);
                        if (dx != 0.0f || dy != 0.0f) { g.im = zs_move(c, g.im, dx, dy); st.zs_strips++; }
                    } else if (zc >= 0) {
                        /* the work buffer's clear before a composite's parts: over all its copy covers */
                        float b[4] = { 1e30f, 1e30f, -1e30f, -1e30f }, e[4];
                        const float *r = &pl.er[4 * (size_t)zc];
                        for (const GpuImVtx &v : c.im) {
                            b[0] = v.x < b[0] ? v.x : b[0]; b[1] = v.y < b[1] ? v.y : b[1];
                            b[2] = v.x > b[2] ? v.x : b[2]; b[3] = v.y > b[3] ? v.y : b[3];
                        }
                        e[0] = b[0] - (r[0] - 2.0f); e[1] = b[1] - (r[1] - 2.0f);
                        e[2] = (r[2] + 2.0f) - b[2]; e[3] = (r[3] + 2.0f) - b[3];
                        for (int j = 0; j < 4; j++)
                            if (!(e[j] > 0.0f)) e[j] = 0.0f;
                        st.im_draws++;
                        g.im = zs_widen(c, g.im, e);
                    } else if (prev && g.im) {
                        st.im_draws++;
                        if (pm[ci] >= 0) {
                            st.im_paired++;
                            g.im = im_lerp(c, prev->cmds[(size_t)pm[ci]], alpha);
                        }
                    }
                }
                g.runs = c.runs.empty() ? NULL : c.runs.data();
                g.dec_rgba = c.rgba.empty() ? NULL : c.rgba.data();
                g.d = c.has_d ? &c.d : NULL;
                if (iso_mask) g.cmask = 0;
                if (g.tme && g.tex_rt < 0 && !g.dec_rgba) g.tex_cached_only = 1;   /* by its content key */
                if (interp && c.mesh_id && c.has_d) {
                    dd = c.d;
                    /* (mode 4) a composite part moves only when its copy was widened */
                    nr_ip_zs_allow(!pl.feed.empty() && pl.feed[ci] >= 0 && pl.pose[(size_t)pl.feed[ci]] == 1);
                    if (nr_ip_mesh_cb(c.mesh_id, &dd)) {
                        if (dbg_on() > 0) {
                            static int nprint;
                            for (int k = 0; k < 24 && nprint < 60; k++) {
                                if (k == 11 || k == 23) continue;
                                float m = 0;
                                for (int j = 0; j < 4; j++) {
                                    float d = g.cb[k][j] - dd.cb[k][j];
                                    if (d < 0) d = -d;
                                    if (d > m) m = d;
                                }
                                if (m > 1e-3f) {
                                    nprint++;
                                    fprintf(stderr, "interp cb: mesh %u row %d recorded %g %g %g %g new %g %g %g %g\n", c.mesh_id, k,
                                            g.cb[k][0], g.cb[k][1], g.cb[k][2], g.cb[k][3], dd.cb[k][0], dd.cb[k][1], dd.cb[k][2],
                                            dd.cb[k][3]);
                                }
                            }
                        }
                        /* only the components the interpolated constants changed (the
                         * recorded source c.d vs the new dd): what the device derived at
                         * submit (row 10.z the depth format's largest Z, row 11 the
                         * viewport, 22-23 pixel state, 12-13 for target textures) stays */
                        for (int k = 0; k < 24; k++)
                            for (int j = 0; j < 4; j++)
                                if (memcmp(&c.d.cb[k][j], &dd.cb[k][j], 4)) g.cb[k][j] = dd.cb[k][j];
                        g.d = &dd;
                        st.replay_interp++;
                    }
                }
                {
                    static int nodraw = -1;   /* $RG_INTERP_NODRAW=1: control, the replay draws nothing */
                    if (nodraw < 0) { const char *e = getenv("RG_INTERP_NODRAW"); nodraw = e && e[0] == '1'; }
                    if (nodraw) break;
                }
                nr_ip_zs_allow(0);
                if (!in->nr_draw(g)) st.replay_notex++;
                st.replay_draws++;
                break;
            }
            }
        }
    }
};

/* the one recorder (one device per process); valid while the renderer's backend is it */
static IpRec *g_inst;
static gpu_renderer *g_inst_r;
static IpRec *rec_of(gpu_renderer *r)
{
    GpuBackend **b = r ? gpu_ip_backend(r) : NULL;
    return b && g_inst && r == g_inst_r && *b == (GpuBackend *)g_inst ? g_inst : NULL;
}

IpRec::~IpRec()
{
    for (int i = 0; i < NR_IP_SLOTS; i++) free_slot(i);
    drop_saved();
    delete in;
    if (g_inst == this) { g_inst = NULL; g_inst_r = NULL; }
}

} // namespace

extern "C" {

void gpu_ip_install(gpu_renderer *r)
{
    GpuBackend **b = r ? gpu_ip_backend(r) : NULL;
    if (!b || !*b || rec_of(r)) return;
    g_inst = new IpRec(*b);
    g_inst_r = r;
    *b = g_inst;
}

void gpu_ip_set_mesh(uint32_t id) { g_mesh_id = id; }

void gpu_ip_rec_slot(gpu_renderer *r, int s)
{
    IpRec *p = rec_of(r);
    if (!p) return;
    p->restore();
    if (s >= 0 && s < NR_IP_SLOTS) {
        p->free_slot(s);
        p->slot[s].rec = 1;
        p->cur = s;
    } else {
        p->cur = -1;
    }
}

void gpu_ip_slot_free(gpu_renderer *r, int s)
{
    IpRec *p = rec_of(r);
    if (!p || s < 0 || s >= NR_IP_SLOTS) return;
    if (p->cur == s) p->cur = -1;
    p->free_slot(s);
}

int gpu_ip_replay(gpu_renderer *r, const int *slots, int n, int interp_at, int prev, float alpha)
{
    IpRec *p = rec_of(r);
    if (!p || n <= 0 || n > NR_IP_SLOTS) return -1;
    for (int i = 0; i < n; i++)
        if (slots[i] < 0 || slots[i] >= NR_IP_SLOTS) return -1;
    if (prev >= NR_IP_SLOTS) prev = -1;
    return p->replay(slots, n, interp_at, prev, alpha);
}

void gpu_ip_restore(gpu_renderer *r)
{
    IpRec *p = rec_of(r);
    if (p) p->restore();
}

int gpu_ip_flows(gpu_renderer *r, const int *slots, int n)
{
    IpRec *p = rec_of(r);
    if (!p || n <= 0 || n > NR_IP_SLOTS) return -1;
    return p->flows(slots, n);
}

int gpu_ip_dirty(gpu_renderer *r)
{
    IpRec *p = rec_of(r);
    return p ? p->dirty : 0;
}

void gpu_ip_slot_info(gpu_renderer *r, int s, uint32_t out[4])
{
    IpRec *p = rec_of(r);
    out[0] = out[1] = out[2] = out[3] = 0;
    if (!p || s < 0 || s >= NR_IP_SLOTS) return;
    out[0] = (uint32_t)p->slot[s].cmds.size();
    out[1] = (uint32_t)p->slot[s].pre.size();
    out[2] = (uint32_t)p->slot[s].born.size();
    out[3] = (uint32_t)p->slot[s].bad;
}

void gpu_ip_dump(gpu_renderer *r, int si, FILE *f)
{
    IpRec *p = rec_of(r);
    if (!p || si < 0 || si >= NR_IP_SLOTS || !f) return;
    const Slot &s = p->slot[si];
    static const char *kn[] = { "draw", "copy", "load", "clear", "create", "destroy", "resize", "reint" };
    fprintf(f, "interp device log: %zu commands, %zu pre-images:", s.cmds.size(), s.pre.size());
    for (const Pre &q : s.pre) fprintf(f, " %d", q.id);
    fprintf(f, "\n");
    for (const Cmd &c : s.cmds) {
        fprintf(f, "  %-7s rt %d %d %d", kn[c.k], c.rt[0], c.rt[1], c.rt[2]);
        if (c.k == C_DRAW) {
            fprintf(f, " mesh %u im %zu tme %d tex_rt %d abe %d rt %dx%d", c.mesh_id, c.im.size(), c.g.tme, c.g.tex_rt, c.g.abe,
                    c.g.rt_w, c.g.rt_h);
            if (!c.im.empty()) {
                float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f, s0 = 1e30f, s1 = -1e30f;
                for (const GpuImVtx &v : c.im) {
                    x0 = v.x < x0 ? v.x : x0; x1 = v.x > x1 ? v.x : x1;
                    y0 = v.y < y0 ? v.y : y0; y1 = v.y > y1 ? v.y : y1;
                    s0 = v.s < s0 ? v.s : s0; s1 = v.s > s1 ? v.s : s1;
                }
                fprintf(f, " box %.1f,%.1f-%.1f,%.1f s %g-%g", x0, y0, x1, y1, s0, s1);
            }
        }
        else if (c.k == C_LOAD)
            fprintf(f, " bp %u bw %u psm %d rect %d,%d-%d,%d", c.bp, c.bw, c.psm, c.r.x0, c.r.y0, c.r.x1, c.r.y1);
        else if (c.k == C_COPY)
            fprintf(f, " to %d,%d from %d,%d-%d,%d", c.a, c.b, c.r.x0, c.r.y0, c.r.x1, c.r.y1);
        else if (c.k == C_CREATE)
            fprintf(f, " depth %d %dx%d", c.a, c.b, c.c);
        fprintf(f, "\n");
    }
}

void gpu_ip_stats(gpu_renderer *r, FILE *f)
{
    IpRec *p = rec_of(r);
    if (!p || !f) return;
    const Stats &s = p->st;
    fprintf(f, "interp device: recorded draws %llu, target copies %llu, loads %llu, clears %llu, targets created %llu, "
               "pre-images %llu (failed %llu); replays %llu (%llu draws, %llu interpolated, %llu stale, %llu without "
               "texture, %llu refused), saves %llu, restores %llu (copy failures %llu); immediate draws in passes %llu, "
               "paired %.1f %%, triangles lerped %llu of %llu; composite strip groups placed %llu of %llu (draws moved %llu), "
               "posed %llu (draws widened %llu); commands trimmed %llu\n",
            (unsigned long long)s.draws, (unsigned long long)s.copies, (unsigned long long)s.loads,
            (unsigned long long)s.clears, (unsigned long long)s.creates, (unsigned long long)s.pre_images,
            (unsigned long long)s.pre_fail, (unsigned long long)s.replays, (unsigned long long)s.replay_draws,
            (unsigned long long)s.replay_interp, (unsigned long long)s.replay_stale, (unsigned long long)s.replay_notex,
            (unsigned long long)s.replay_bad, (unsigned long long)s.saves, (unsigned long long)s.restores,
            (unsigned long long)s.put_fail, (unsigned long long)s.im_draws,
            s.im_draws ? 100.0 * (double)s.im_paired / (double)s.im_draws : 0.0, (unsigned long long)s.im_tris_lerped,
            (unsigned long long)s.im_tris, (unsigned long long)s.zs_groups, (unsigned long long)s.zs_groups_all,
            (unsigned long long)s.zs_strips, (unsigned long long)s.zs_pose, (unsigned long long)s.zs_widened,
            (unsigned long long)s.trimmed);
}

} /* extern "C" */

#else /* the default build (GS model): nothing recorded */

#include <stdint.h>
#include <stdio.h>

#include "nr_interp.h"

extern "C" {
void gpu_ip_install(struct gpu_renderer *r) { (void)r; }
void gpu_ip_set_mesh(uint32_t id) { (void)id; }
void gpu_ip_rec_slot(struct gpu_renderer *r, int s) { (void)r; (void)s; }
void gpu_ip_slot_free(struct gpu_renderer *r, int s) { (void)r; (void)s; }
int gpu_ip_replay(struct gpu_renderer *r, const int *slots, int n, int interp_at, int prev, float alpha) { (void)r; (void)slots; (void)n; (void)interp_at; (void)prev; (void)alpha; return -1; }
void gpu_ip_restore(struct gpu_renderer *r) { (void)r; }
int gpu_ip_dirty(struct gpu_renderer *r) { (void)r; return 0; }
int gpu_ip_flows(struct gpu_renderer *r, const int *slots, int n) { (void)r; (void)slots; (void)n; return -1; }
void gpu_ip_slot_info(struct gpu_renderer *r, int s, uint32_t out[4]) { (void)r; (void)s; out[0] = out[1] = out[2] = out[3] = 0; }
void gpu_ip_stats(struct gpu_renderer *r, FILE *f) { (void)r; (void)f; }
void gpu_ip_dump(struct gpu_renderer *r, int slot, FILE *f) { (void)r; (void)slot; (void)f; }
}

#endif /* RG_NATIVE_ONLY */
