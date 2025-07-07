from src.utils import run_command, read_file, write_file
from src.ollama_client import call_ollama

def run():
    compile_cmd = (
        "g++ -fprofile-arcs -ftest-coverage input_code/main.cpp tests/test_main_refined.cpp "
        "-lgtest -lgtest_main -pthread -o run_tests"
    )
    run_command(compile_cmd)
    run_command("./run_tests")
    run_command("gcov input_code/main.cpp > coverage_reports/coverage.txt")

    coverage = read_file("coverage_reports/coverage.txt")
    prompt = f"Improve test coverage based on this gcov report:\n\n{coverage}"
    improved_tests = call_ollama(prompt)
    write_file("tests/test_main_refined.cpp", improved_tests)
