import json
from collections import Counter


def analysis(text):
    letter_counts = Counter(''.join(filter(lambda c: c.isalpha(), text.upper())))
    total_letters = sum(letter_counts.values())
    return {letter: count / total_letters for letter, count in letter_counts.items()}


with open('encoded.txt') as fin:
    with open('frequencies.json', 'w') as fout:
        frequencies = {letter: f"{freq:.2%}" for letter, freq in sorted(analysis(fin.read()).items(), key=lambda x: x[1], reverse=True)}
        json.dump(frequencies, fout, indent=2)
