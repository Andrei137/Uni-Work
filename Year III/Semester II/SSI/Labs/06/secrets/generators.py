import json
import string
import secrets
import inspect
import bcrypt


def generate_secure_password(length=10):
    if length < 10:
        raise ValueError("Password length must be at least 10 characters!")

    special_chars = ".!$@"
    all_chars = string.ascii_letters + string.digits + special_chars
    password_chars = [
        secrets.choice(string.ascii_uppercase),
        secrets.choice(string.ascii_lowercase),
        secrets.choice(string.digits),
        secrets.choice(special_chars)
    ]
    password_chars.extend(secrets.choice(all_chars) for _ in range(length - 4))
    secrets.SystemRandom().shuffle(password_chars)
    return ''.join(password_chars)


def generate_url_safe_token(length=32):
    return secrets.token_urlsafe(length * 6 // 8)


def generate_hex_token(length=32):
    return secrets.token_hex(length // 2)


def generate_binary_key(length=100):
    return "".join(format(byte, "08b") for byte in secrets.token_bytes(length))


def get_generators():
    return {
        name: func for name, func in inspect.getmembers(__import__(__name__))
        if callable(func) and name.startswith("generate_")
    }


def compare_securely(seq1, seq2):
    return secrets.compare_digest(seq1, seq2)


def store_password(password):
    return bcrypt.hashpw(password.encode("utf-8"), bcrypt.gensalt()).decode("utf-8")


def verify_password(stored_hash, password):
    return bcrypt.checkpw(password.encode("utf-8"), stored_hash.encode("utf-8"))


def main():
    password = "password"
    password_hash = store_password(password)
    output = {
        "generators": {
            name.replace("generate_", ""): generate() for name, generate in get_generators().items()
        },
        "compare": {
            "equal_passwords": compare_securely(password, password),
            "different_passwords": compare_securely(password, "pasword")
        },
        "store_password": {
            "value": password,
            "stored_value": password_hash,
            "verify": verify_password(password_hash, password)
        }
    }
    with open(f"output.json", "w") as fout:
        json.dump(output, fout, indent=2)


if __name__ == "__main__":
    main()
