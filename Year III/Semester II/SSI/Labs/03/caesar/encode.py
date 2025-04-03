def shift_with(key):
    def shift_char(ch):
        if not ch.isalpha():
            return ch
        start = 'a' if ch.islower() else 'A'
        return chr((ord(ch) - ord(start) + key) % 26 + ord(start))
    return shift_char


def encode(text, key):
    return "".join(map(shift_with(key), text))


def main():
    plain = input('text clar: ')
    key = int(input('cheie: '))
    encoded = encode(plain, key)
    print(f'text criptat: {encoded}')


if __name__ == '__main__':
    main()
