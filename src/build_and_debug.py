from src.utils import run_command, read_file, write_file, log_error
from src.ollama_client import call_ollama

def run():
    cmd = "g++ -std=c++17 input_code/main.cpp tests/test_main_refined.cpp -lgtest -lgtest_main -pthread -o run_tests"
    code, out, err = run_command(cmd)

    if code != 0:
        log_error(err)
        test_code = read_file("tests/test_main_refined.cpp")
        prompt = f"Fix build errors in the following code:\n\nError Log:\n{err}\n\nCode:\n{test_code}"
        fixed_code = call_ollama(prompt)
        write_file("tests/test_main_refined.cpp", fixed_code)
        print("Build failed, sent to LLM for fix.")
    else:
        print("Build successful.")
        run_command("./run_tests")