def encode(text, key):
    range_text, range_key = range(len(text)), range(key)
    rail = [['' for _ in range_text] for _ in range_key]
    down = False
    row, col = 0, 0

    for i in range_text:
        if row in [0, key - 1]:
            down = not down
        rail[row][col] = text[i]
        col += 1
        row += 1 if down else -1

    result = []
    for i in range_key:
        for j in range_text:
            result.append(rail[i][j])
    return "".join(result)


def main():
    plain = input('text clar: ')
    key = int(input('cheie: '))
    encoded = encode(plain, key)
    print(f'text criptat: {encoded}')


if __name__ == '__main__':
    main()
