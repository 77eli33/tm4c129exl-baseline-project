# Context for a chat assistant

Copy or attach this file when asking a chat assistant about this project. Also share the relevant source file and any build or debugger output for the specific question. A chat assistant cannot assume it can see the rest of the repository.

## Project facts

- This is a learning baseline for the **EK-TM4C129EXL** board, which has a **TM4C129ENCPDT** Cortex-M4 MCU.
- The example is bare-metal C. `src/main.c` contains startup code and blinks board LED **D2 on PN0**. It uses the reset clock and does not configure the PLL.
- `platformio.ini` pins the **TI TIVA 3.1.0** platform and a GNU Arm 10.3.1 toolchain. It uses PlatformIO's compatible TM4C129 LaunchPad board definition with the actual MCU name overridden.
- The board's on-board **TI-ICDI** probe is used for flashing and debugging through the **DEBUG USB** port.
- `linker.ld` defines flash and RAM. `.vscode/tasks.json` has build and upload tasks; `.vscode/launch.json` has the Cortex-Debug launch. The beginner setup and VS Code quick start are in `README.md`.

## Commands and expected behavior

Run commands from the project folder:

```sh
PLATFORMIO_CORE_DIR=$PWD/.pio-core pio run
PLATFORMIO_CORE_DIR=$PWD/.pio-core pio run -t upload
PLATFORMIO_CORE_DIR=$PWD/.pio-core pio run -e tm4c129exl_debug -t upload
```

The release environment is `tm4c129exl`; the debug environment is `tm4c129exl_debug`. A successful upload reports `Verified OK`, and D2 should blink afterward. In VS Code, **Debug on TM4C129EXL** builds and flashes the debug firmware and stops at `main`; F5 continues, F10 steps over, and F11 steps into. OpenOCD may print `SRST error` with this probe even when upload and debugging work. Judge success from the full command result and observed board behavior, not that message alone.

## How to help the student

This is a learning exercise. Explain the relevant concept and tradeoffs, then ask the student to describe the intended behavior, approach, and test. Help them reason through the whole change rather than providing a finished solution immediately. If they have already supplied these details, build on what they said instead of repeating questions.

Treat a question or suggestion as a request for discussion. **Only provide a concrete file edit or patch when the student explicitly asks for one.** Keep edits small and within the requested scope; discuss any needed scope change first. Never present a proposed edit as already applied. Do not suggest flashing the board as an accomplished step without the student's explicit instruction and a real result.

For each AI-assisted edit the student applies, help add an entry to `AI_CHANGES.md` with the student's instruction, their stated reasoning and decisions, the implementation, and the actual verification result. Do not invent the student's reasoning or claim a build or hardware test passed without seeing its output. If information is missing, say what to check next.

## Starting a chat

After sharing this file, the student can write:

> I am working on `[file or feature]`. My goal is `[expected behavior]`. I think the approach is `[my idea]`. I plan to verify it by `[test]`. Please discuss my reasoning and help me spot gaps. Do not provide a patch unless I ask for one.
