# ♟️ Chess Engine WASM Demo

Welcome to the open WebAssembly chess engine demo! This project compiles a custom chess engine written in C into WebAssembly, letting users play right in their browser—no install, no server required.

**Live Demo:**  
[▶️ Play in your browser on GitHub Pages!](https://Shab00.github.io)  

---

## 🚀 Features

- ⚡ **Native-speed C engine** running in your browser with WebAssembly (WASM)
- ♟️ **Interactive chessboard UI** (powered by [cm-chessboard](https://github.com/shaack/cm-chessboard))
- 🍃 **Clean, modern minimal UI**
- 🏁 **No backend/server required**—just static files via GitHub Pages
- 🎯 **Open-source & portable**—run it, fork it, modify it
- (Planned) **Adaptive search**, PGN/FEN import/export, and more

---

## 🖥️ How it Works

- The core engine is written in C ([see `src/`](src/)) and compiled to WebAssembly using [Emscripten](https://emscripten.org/).
- The web UI is standard HTML + JS, using a drag-and-drop chessboard and engine-to-JS glue code.
- Everything runs **100% in your browser** for maximum portability and privacy.

---

## 📦 Directory Structure

```
chess-engine-wasm/
  src/           # C source code of the chess engine
  docs/          # GitHub Pages files (index.html, engine.js, engine.wasm, assets...)
  README.md
```

---

## 🛠️ Local Setup & Build Instructions

**1. Clone the repo**
```sh
git clone https://github.com/Shab00/chess-engine-wasm.git
cd chess-engine-wasm
```

**2. Install Emscripten ([official guide](https://emscripten.org/docs/getting_started/downloads.html))**

**3. Build the engine as WASM:**
```sh
cd src
emcc engine.c -o ../docs/engine.js -s WASM=1 -s "EXPORTED_FUNCTIONS=['_engine_set_fen','_engine_get_bestmove', ...]" -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
```
- Adjust filenames/EXPORTED_FUNCTIONS as needed for your API.

**4. Serve locally (for quick testing):**
```sh
cd docs
python3 -m http.server
```
Visit [http://localhost:8000/index.html](http://localhost:8000/index.html)

---

## 🌍 Deploying with GitHub Pages

- Push new commits to the main branch.
- Ensure the `docs/` folder has your latest `index.html`, `engine.js`, and `engine.wasm`.
- The site will be public soon at:  
  `https://<your-username>.github.io/chess-engine-wasm/`

---

## ✨ Future Plans

- Smarter move generation, adaptive search depth
- UCI import/export, PGN logs and analysis
- Stronger evaluation & training self-play
- Theme switching, more mobile-friendly UI

---

## 🤝 Contributing

Contributions, feature requests, and bug reports are welcome—open an issue or PR!

---

## 📜 License

This project is licensed under the MIT License.  
See the [LICENSE](LICENSE) file for details.

---

## 🙌 Acknowledgments

- [cm-chessboard](https://github.com/shaack/cm-chessboard) for the sleek JS chessboard
- [Emscripten](https://emscripten.org/) for awesome WASM compiler tech
- [Stockfish authors](https://stockfishchess.org/) and the open chess dev community for inspiration

---

*Made by [Shab00](https://github.com/Shab00).
