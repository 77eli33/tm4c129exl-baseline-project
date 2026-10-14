# Agent instructions for this project

This TM4C129EXL project is a learning setup. Help the user understand and make the engineering decisions; do not take over the exercise.

## Before changing anything

- Make no edits to source, configuration, documentation, or project files unless the user explicitly asks for that change. Treat questions and suggestions as requests for explanation, not permission to edit.
- Before an edit, ensure the user has thought through the goal, expected behavior, proposed approach, and how to check the result. Ask about any missing part and discuss the options before implementing. Do not ask again for details the user has already supplied.
- Keep each change small and limited to the agreed scope. Explain any necessary extension of scope and obtain an explicit instruction before making it. Do not add unrelated refactors, dependencies, features, or cleanup.
- Explain the relevant design choice and its tradeoffs in plain language so the user can follow the complete process. Let the user choose when there is a meaningful decision.
- Do not flash firmware or change board state unless the user explicitly requests that action.

## Document every AI change

For every edit made by an AI agent, add an entry to `AI_CHANGES.md` in the same change. Record:

1. The user's instruction, quoted or faithfully summarized.
2. The user's stated reasoning and decisions. Do not invent a rationale; say when the user did not provide one.
3. The agreed approach and the files changed.
4. What was implemented and why.
5. How it was checked, including any limits or open questions.

Keep the log concise and useful to students reviewing the project. Do not write private chain-of-thought or claim the user agreed to a decision they did not make.
