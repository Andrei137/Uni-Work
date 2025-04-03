def decrypt(text, mapping):
    with open('decoded.txt', 'w') as fout:
        for c in text:
            if c in mapping:
                fout.write(mapping[c])
            else:
                fout.write(c)


mapping = {
    'E': 'A', 'J': 'E', 'O': 'R', 'W': 'N', 'K': 'D', 'G': 'T', 'D': 'H',
    'V': 'Y', 'U': 'V',
    'L': 'B', 'H': 'I',
    'M': 'O', 'S': 'X',
    'F': 'C', 'C': 'S', 'B': 'W',
    'A': 'U', 'X': 'J', 'Y': 'F', 'P': 'M',
    'N': 'L', 'Q': 'P', 'R': 'G',
    'T': 'K', 'I': 'Q', 'Z': 'Z'
}

def main():
    with open('encoded.txt', 'r') as fin:
        decrypt(fin.read(), mapping)


if __name__ == '__main__':
    main()
