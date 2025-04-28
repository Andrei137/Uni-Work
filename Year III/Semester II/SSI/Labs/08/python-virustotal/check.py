import os
import sys
import json
import hashlib
import requests
from dotenv import load_dotenv


def calculate_sha256(file_path):
    sha256_hash = hashlib.sha256()
    with open(file_path, "rb") as f:
        for byte_block in iter(lambda: f.read(4096), b""):
            sha256_hash.update(byte_block)
    return sha256_hash.hexdigest()


def check_virustotal(api_key, file_hash):
    url = f"https://www.virustotal.com/api/v3/files/{file_hash}"
    headers = {
        "x-apikey": api_key
    }

    try:
        result = requests.get(url, headers=headers).json()
        if "data" in result and "attributes" in result["data"]:
            with open("result.json", "w") as fout:
                json.dump(result["data"], fout, indent=4)
            print(f"Detections: {result['data']['attributes']['last_analysis_stats']}")

    except requests.exceptions.RequestException as e:
        print(f"VirusTotal error: {e}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <file_path>")
        return

    try:
        load_dotenv()
        file_path = sys.argv[1]
        api_key = os.getenv("VIRUS_TOTAL_API_KEY")
        check_virustotal(api_key, calculate_sha256(file_path))
    except Exception as e:
        print(f"Error {e}")


if __name__ == "__main__":
    main()
