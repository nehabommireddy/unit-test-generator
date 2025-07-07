import os
from src.ollama_client import call_ollama
from src.utils import read_file, write_file

def run():
    os.makedirs("tests", exist_ok=True)

    for root, _, files in os.walk("input_code/controllers"):
        for file in files:
            if file.endswith(".cc") or file.endswith(".cpp"):
                filepath = os.path.join(root, file)
                cpp_code = read_file(filepath)
                yaml_instructions = read_file("instructions/test_prompt.yaml")
                prompt = f"{yaml_instructions}\n\n---\n\n{cpp_code}"

                print(f"📤 Sending {file} to LLM...")
                response = call_ollama(prompt)

                if not response.strip():
                    print(f"⚠️ No test generated for {file}")
                    continue

                test_file = os.path.join("tests", f"test_{file}")
                write_file(test_file, response)
                print(f"✅ Test written to {test_file}")

