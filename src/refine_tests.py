from src.ollama_client import call_ollama
from src.utils import read_file, write_file
import os

def run():
    if not os.path.exists("tests/test_main.cpp"):
        print("❌ Error: 'tests/test_main.cpp' does not exist. Cannot refine tests.")
        return

    raw_tests = read_file("tests/test_main.cpp")
    refine_prompt = (
        "Refine the following unit tests:\n"
        "- Remove duplicate tests\n"
        "- Add missing includes\n"
        "- Ensure proper formatting and structure\n"
    )
    refined = call_ollama(f"{refine_prompt}\n\n---\n\n{raw_tests}")
    write_file("tests/test_main_refined.cpp", refined)
    print("✅ Refined tests written to 'tests/test_main_refined.cpp'")