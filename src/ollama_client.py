import requests

def call_ollama(prompt: str, model: str = "llama3") -> str:
    response = requests.post(
        "http://localhost:11434/api/generate",
        json={"model": model, "prompt": prompt, "stream": False}
    )

    if response.status_code != 200:
        raise RuntimeError(f"Ollama API error: {response.status_code} - {response.text}")

    return response.json().get("response", "")