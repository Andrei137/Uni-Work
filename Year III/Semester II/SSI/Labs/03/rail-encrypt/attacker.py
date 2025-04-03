import json
from decode import decode


def brute(encoded):
    all_decoded = {f'{key:02}': decode(encoded, key) for key in range(2, len(encoded))}
    with open('decoded.json', 'w') as fout:
        json.dump(all_decoded, fout, indent=2)


def main():
    encoded = input('text criptat: ')
    brute(encoded)


if __name__ == '__main__':
    main()
