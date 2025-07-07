# C++ Unit Test Generator

This project automates unit test generation for a Drogon-based C++ RESTful API using a locally hosted LLM (via [Ollama](https://ollama.com/)). It supports:

- Test generation from real C++ controller source code
- Refinement of tests (deduplication, formatting, includes)
- Build + debug with Google Test
- Test coverage analysis using `gcovr` or `lcov`

---

## How It Works

1. **Generate Initial Tests**  
   Parses all `*.cpp`/`*.cc` files in `input_code/controllers/` and prompts the LLM to generate corresponding Google Test unit tests.

2. **Refine Tests**  
   Removes duplicates, adds necessary includes, formats test code, and standardizes structure.

3. **Build & Debug**  
   Compiles test files using `g++` or `cmake`. If the build fails, error logs are sent back to the LLM for suggested fixes.

4. **Analyze Coverage**  
   Uses `gcovr` to compute line/function coverage. Outputs reports in text or HTML.

---
## Unit Test Coverage
![image](https://github.com/user-attachments/assets/16a0da2e-eb5b-42f1-8ab2-cb1cc4c1e6e0)

## Approach
1. LLM-Powered Test Generation
Each .cpp file is paired with a YAML instruction file (test_prompt.yaml) containing Drogon-specific rules and formatting expectations. These prompts are sent to Ollama's local LLM instance.

2. Iterative Refinement
Generated tests are refined using a second LLM pass to improve structure, ensure headers are present, and remove redundant logic.

3. Build + Debug Feedback Loop
If the build fails, error logs and source code are sent back to the LLM to request inline fixes. This allows auto-correction for missing includes or type mismatches.

4. Test Coverage Loop
After build success, test coverage is measured. Low-coverage results are used to guide further test generation prompts.
