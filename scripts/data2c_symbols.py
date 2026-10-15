"""Configured extra entry points; names follow address-based renames."""
def entries(cfg, current):
    result = {}
    for text, item in cfg.get('function_entries', {}).items():
        address = int(text, 0)
        owner = int(item['owner_address'], 0)
        if address != owner + item['offset']:
            raise ValueError('entry offset mismatch: ' + text)
        name = item['symbol']
        # rename.py replaces exact identifier tokens. Renaming an owning unit
        # does NOT rename its foo_e1 exports. Preserve their actual names;
        # an explicit alias rename updates symbol/renames by its own address.
        if owner not in current:
            raise ValueError('entry owner missing from current symbols: ' + text)
        name = cfg['renames'].get(text, name)
        result[address] = name
    return result


def verify_entries(cfg, current, root):
    """Reject moved/missing exports using the actual compiler objects."""
    from data2c_elf import ELF
    cache = {}
    names = entries(cfg, current)
    for text, item in cfg.get('function_entries', {}).items():
        owner_address = int(item['owner_address'], 0)
        owner = current[owner_address]
        if owner not in cache:
            elf = ELF(root / 'build/obj' / (owner + '.o'))
            cur, found = owner_address, {}
            cap = 16
            while cap > 4 and owner_address % cap:
                cap //= 2
            for index, sec in enumerate(elf.sections):
                if sec['name'] != '.text':
                    continue
                align = min(sec['align'] or 1, cap)
                cur = (cur + align - 1) & ~(align - 1)
                for sym in elf.symbols:
                    if sym['section'] == index and sym['bind'] == 1 and sym['type'] == 2:
                        found[sym['name']] = cur + sym['value']
                cur += sec['size']
            cache[owner] = found
        name = names[int(text, 0)]
        if cache[owner].get(name) != int(text, 0):
            raise ValueError('configured callable export missing or moved: ' + name)
    return {names[int(a, 0)]: int(a, 0) for a in cfg.get('function_entries', {})}


def external_addresses(cfg, root):
    """Verify imported addresses against their own address domain."""
    import data2c
    result = {}
    overlay_tables = {}
    assembly = None
    for name, item in cfg.get('external_symbols', {}).items():
        address = int(item['address'], 0)
        domain = item['domain']
        if domain == 'main_assembly':
            if assembly is None:
                assembly = {}
                pending = []
                for line in (root / 'asm/main.s').read_text().splitlines():
                    label = data2c.LABEL.match(line)
                    if label:
                        pending.append(label[1])
                    row = data2c.ROW.match(line)
                    if row:
                        for label in pending:
                            assembly[label] = int(row[2], 16)
                        pending = []
            if assembly.get(name) != address:
                raise ValueError('missing exact MAIN assembler entry: ' + name)
        elif domain.startswith('overlay:'):
            overlay = domain.split(':')[1]
            if overlay not in ('normal', 'insect', 'factory', 'title', 'insmenu'):
                raise ValueError('unknown overlay identity')
            if overlay not in overlay_tables:
                overlay_tables[overlay] = {m[1]: int(m[2], 16)
                    for line in (root / ('config/' + overlay + '.symbols.txt')).read_text().splitlines()
                    if (m := data2c.SYMBOL.match(line))}
            if overlay_tables[overlay].get(name) != address:
                raise ValueError('overlay symbol moved or missing: ' + name)
        elif domain == 'overlay_load_arena':
            if address != 0x4e9e80 or item['kind'] != 'data':
                raise ValueError('invalid shared overlay arena address')
        else:
            raise ValueError('unsupported external symbol domain: ' + domain)
        result[name] = address
    return result
