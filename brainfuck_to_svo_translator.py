script = ""  # your brainfuck code here

bf_to_svo = {
    '+': 'сво',
    '-': 'гойда',
    '.': 'zov',
    '>': 'перемога',
    '<': 'потужно',
    '[': 'хрюко',
    ']': 'стяг',
}


def brainfuck_to_svolang(bf_code):
    result = []
    i = 0
    while i < len(bf_code):
        c = bf_code[i]
        if c in bf_to_svo:
            result.append(bf_to_svo[c])
        i += 1
    return ''.join(result)


print(brainfuck_to_svolang(script))
