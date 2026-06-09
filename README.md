# Chess Engine WASM Demo

A browser-based chess engine demo that connects a custom C chess engine to a web UI using WebAssembly.

This project is focused on getting a local end-to-end chess engine demo working in the browser: board rendering, WASM loading, JavaScript/WASM integration, and engine-driven board updates.

---

## Overview

The core chess engine is written in C and compiled to WebAssembly using Emscripten. The browser UI is built with HTML, JavaScript, and [`cm-chessboard`](https://github.com/shaack/cm-chessboard), allowing the engine to run locally in the browser without a backend server.

The current demo already supports:

- rendering the chessboard in the browser
- loading the WebAssembly engine successfully
- calling engine functions from JavaScript
- syncing the board from engine FEN
- making player moves from the UI
- requesting the engine’s best move
- resetting or starting a new game locally

---

## Current Status

This project is currently at the **local integration milestone** stage.

### What works now

- local board rendering with `cm-chessboard`
- white-side move input from the browser UI
- WebAssembly engine startup with no runtime load errors
- JavaScript ↔ WASM engine communication
- FEN display and board refresh from engine state
- local controls for:
  - **New Game**
  - **Play Best Move**
  - **Reset to Start**
  - **Clear Log**

### Current limitations

- legal move validation still needs tightening in the engine
- the current demo is focused on local integration rather than a polished final game experience
- GitHub Pages deployment and a more direct “user plays White against engine” flow are planned next

---

## How It Works

- The chess engine is written in C.
- The engine is compiled to WebAssembly with Emscripten.
- The browser loads `engine.js` and `engine.wasm`.
- The UI sends moves from JavaScript to the engine.
- The engine returns updated board state as FEN.
- The board redraws from that FEN in the browser.

Everything runs locally in the browser, with no backend required for the current demo.

---

## Project Structure

```text
chess-engine-wasm/
  src/           # C source code for the chess engine
  docs/          # browser demo files (index.html, engine.js, engine.wasm, assets...)
  README.md
```

---

## Running Locally

From the `docs/` directory, start a simple local server:

```bash
python3 -m http.server
```

Then open:

```text
http://localhost:8000/
```

If you are serving from the project root instead, open the correct `/docs` path for your local setup.

---

## Building the WASM Engine

The engine is compiled from the C source using Emscripten.

Example build approach:

```bash
cd src
emcc engine.c -o ../docs/engine.js -s WASM=1
```

Depending on your engine wrapper, you may also need to export the functions used by the browser UI, such as:

- `wasm_engine_new_game`
- `wasm_engine_get_fen`
- `wasm_engine_make_move`
- `wasm_engine_get_bestmove`
- `wasm_engine_set_fen`

Adjust the exact build command and exported functions to match your implementation.

---

## Controls

The current demo includes:

- **New Game** — starts a fresh game in the engine and refreshes the board
- **Play Best Move** — asks the engine for the current best move and plays it
- **Reset to Start** — resets the engine and board to the starting position
- **Clear Log** — clears the log panel

---

## Screenshot

![Local chess engine demo](./docs/Chess_Engine_WASM_Demo_Screenshot.png)

---

## Next Steps

Planned next steps include:

- deploy the browser demo to GitHub Pages
- make the user play White while the engine responds automatically
- improve move legality handling
- continue polishing the UI and developer documentation

---

## Acknowledgements

🌸 Credit and thanks to the tools and communities that helped make this possible:

- [`cm-chessboard`](https://github.com/shaack/cm-chessboard) for the browser chessboard UI
- [Emscripten](https://emscripten.org/) for the C → WebAssembly toolchain
- the wider open-source chess programming community for ideas, references, and inspiration

---

## Contributing

Contributions, suggestions, and bug reports are welcome. Feel free to open an issue or submit a pull request.

---

## License

Add your license details here once confirmed.
