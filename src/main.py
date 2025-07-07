import os
import sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from src import generate_tests, refine_tests, build_and_debug, analyze_coverage

if __name__ == "__main__":
    print("🚀 Running generate_tests...")
    generate_tests.run()

    if os.path.exists("tests/test_main.cpp"):
        print("🧪 Running refine_tests...")
        refine_tests.run()

        print("🔧 Building and debugging...")
        build_and_debug.run()

        print("📊 Analyzing coverage...")
        analyze_coverage.run()
    else:
        print("❌ Error: 'tests/test_main.cpp' was not created. Exiting.")