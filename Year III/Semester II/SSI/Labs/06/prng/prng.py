import json
import inspect
from itertools import accumulate


def generate_values(seed, steps, func):
    return list(accumulate([seed] * steps, lambda acc, _: func(acc)))


def candidate1(seed):
    return seed ^ seed


def candidate2(seed):
    return int(seed + seed / 2)


def candidate3(seed):
    return seed >> 2


def random(seed, steps, candidate):
    return generate_values(seed, steps, candidate)


def get_candidates():
    return {
        name: func for name, func in inspect.getmembers(__import__(__name__))
        if callable(func) and name.startswith("candidate")
    }


def main():
    seed = int(input("Seed: "))
    steps = int(input("Steps: "))
    for name, candidate in get_candidates().items():
        output = {
            "seed": seed,
            "values": random(seed, steps, candidate)
        }
        with open(f"{name}.json", "w") as fout:
            json.dump(output, fout, indent=2)


if __name__ == "__main__":
    main()
