from encode import encode


def decode(text, key):
    return encode(text, -key)


def main():
    encoded = input('text criptat: ')
    key = int(input('cheie: '))
    decoded = decode(encoded, key)
    print(f'text decriptat: {decoded}')


if __name__ == '__main__':
    main()
