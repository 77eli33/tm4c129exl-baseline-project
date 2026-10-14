# TM4C129EXL project baseline

A small bare-metal EK-TM4C129EXL project for copying into future work. It blinks user LED D2 on PN0. The firmware starts at the MCU's reset clock and does not configure the PLL. The Projects contains Toolchain setup and VSCode configuration as well as instructions for AI-Agents and Chatbots, tuning them to support learning progress.

## Download and set up

You do not need to know Git or have a GitHub account to use a public copy of this project:

1. On this GitHub repository page, click the green **Code** button above the file list, then **Download ZIP**. [GitHub's ZIP guide](https://docs.github.com/en/repositories/working-with-files/using-files/downloading-source-code-archives) shows the button.
2. Unzip the download. Keep the extracted folder together; do not open individual files from inside the ZIP.
3. Install [Visual Studio Code](https://code.visualstudio.com/download).
4. Install [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html). Follow its [installer instructions](https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html) and [shell-command setup](https://docs.platformio.org/en/latest/core/installation/shell-commands.html) so the `pio` command is available. In a VS Code terminal, run `pio --version` to check it. If VS Code says `pio` is not found, finish the shell-command setup, then restart VS Code.
5. In VS Code, choose **File → Open Folder…** and select the extracted folder containing `platformio.ini`. Install the recommended **Cortex-Debug** and **C/C++** extensions if VS Code offers them. You can also find both in the **Extensions** view.
6. Connect the board's **DEBUG** USB port to the computer. Continue with [Quick start in VS Code](#quick-start-in-vs-code).

The first build or debug launch downloads the pinned TI TIVA platform, GNU Arm compiler/GDB, and OpenOCD into `.pio-core`. This can take a few minutes. No separate board package download is needed.

**Want your own GitHub repository?** If you have a GitHub account, click **Use this template → Create a new repository** on this page, then download or clone **your new repository** and follow steps 3–6 above. This creates an independent project; the baseline is not set as its remote. [GitHub's template guide](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template) explains the choices.

The `platformio.ini` uses PlatformIO's compatible TM4C129 LaunchPad board definition and sets the actual EXL MCU to TM4C129ENCPDT. The `.vscode` configurations use `${workspaceFolder}` paths, so they work after copying the project folder. `.pio`, `.pio-core`, and `build` contain generated files and are excluded by `.gitignore`.

## Quick start in VS Code

| Goal | Action | Result |
| --- | --- | --- |
| Build | **Terminal → Run Task… → PIO: Build** | Compiles the release firmware. |
| Run on board | **Terminal → Run Task… → PIO: Run on board** | Builds, flashes, verifies, and resets. D2 blinks after the task finishes. |
| Start debugger | Open **Run and Debug** in the left sidebar, select **Debug on TM4C129EXL**, then press **F5** | Builds and flashes the debug firmware, connects via the on-board TI-ICDI probe, and pauses at `main`. |

While paused, click the gutter beside a source line to add or remove a breakpoint. Use the floating debug toolbar: **F5** continues, **F10** steps over one source line, **F11** steps into a function, and **Shift+F11** steps out. **Shift+F5** stops the session. The `delay()` function is separate so F10 can step over it. Select **Variables**, **Watch**, or **Call Stack** in the Run and Debug sidebar to inspect program state. Use the named launch configuration in the sidebar; the small **Debug C/C++ File** button in the editor is a different VS Code action.

The launch uses `.vscode/launch.json`; the build and flash tasks are in `.vscode/tasks.json`. `.vscode/c_cpp_properties.json` points the editor at the ARM compiler so IntelliSense treats MCU pointers as 32-bit.

## Using a chat assistant

If you use a chat interface that cannot read this repository, paste or attach [CHAT_CONTEXT.md](CHAT_CONTEXT.md) at the start of the conversation. It explains the board, toolchain, commands, and the learning approach for AI help. Also share the source file you are asking about and any relevant build or debugger output. The file includes a starter prompt you can adapt to describe your goal, proposed approach, and planned test.

The chat context asks assistants to discuss your reasoning first and provide a patch only when you explicitly request one. Review and apply any suggested edit yourself, then record AI-assisted changes in [AI_CHANGES.md](AI_CHANGES.md).

## Command line

Run from this project folder:

```sh
PLATFORMIO_CORE_DIR=$PWD/.pio-core pio run
PLATFORMIO_CORE_DIR=$PWD/.pio-core pio run -t upload
PLATFORMIO_CORE_DIR=$PWD/.pio-core pio run -e tm4c129exl_debug -t upload
```

For a manual GDB session, first run the debug upload command above so the ELF and OpenOCD package exist, then start OpenOCD in one terminal:

```sh
./.pio-core/packages/tool-openocd/bin/openocd -f board/ti_ek-tm4c1294xl.cfg
```

Connect from another terminal:

```sh
./.pio-core/packages/toolchain-gccarmnoneeabi/bin/arm-none-eabi-gdb .pio/build/tm4c129exl_debug/firmware.elf
(gdb) target extended-remote localhost:3333
(gdb) monitor reset halt
(gdb) tbreak main
(gdb) continue
```


