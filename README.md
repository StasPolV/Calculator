# Qt Calculator

🇷🇺 [Читать на русском](README.ru.md)

A desktop calculator built with C++20 and Qt6 (Widgets), featuring a custom expression parser, calculation history, and a configurable UI. Built with an MVC architecture.

## Features

- Standard operations: `+ - * /`, parentheses, unary minus
- Extra functions: `x²`, `√x`, `1/x`
- Calculation history (reuse past results)
- Adjustable result precision
- Light / dark theme, saved between sessions
- Expression errors are caught and shown to the user
- Unit tests for the parser (GoogleTest)

## Build

**Requirements:** C++20 compiler, CMake ≥ 3.28, Qt6 (Core, Widgets)

```bash
git clone <repo_url>
cd <project_folder>
cmake -S . -B build -DCMAKE_PREFIX_PATH=<path_to_Qt6>
cmake --build build -j
```

Run the `Calculator` executable from the `build` folder.

To skip building tests (no internet / faster build): add `-DBUILD_TESTING=OFF`.

## Roadmap

1. More operations
2. Mode switching (engineering mode, etc.)
3. Fix existing parser bugs (e.g. empty expression when pressing `x²` on an empty field, multiple `+` in a row)
4. Functions graphing support
