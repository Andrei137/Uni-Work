def decode(text, key):
    range_text, range_key = range(len(text)), range(key)
    rail = [['' for _ in range_text] for _ in range_key]
    down = None
    row, col = 0, 0

    for i in range_text:
        if row == 0:
            down = True
        if row == key - 1:
            down = False
        rail[row][col] = '*'
        col += 1
        row += 1 if down else -1

    index = 0
    for i in range_key:
        for j in range_text:
            if rail[i][j] == '*' and index < len(text):
                rail[i][j] = text[index]
                index += 1

    result = []
    row, col = 0, 0
    for i in range_text:
        if row == 0:
            down = True
        if row == key - 1:
            down = False
        if (rail[row][col] != '*'):
            result.append(rail[row][col])
            col += 1
        row += 1 if down else -1
    return "".join(result)


def main():
    encoded = input('text criptat: ')
    key = int(input('cheie: '))
    decoded = decode(encoded, key)
    print(f'text decriptat: {decoded}')


if __name__ == '__main__':
    main()
