


For firefox you need to set dom.workers.modules.enabled to true
But there are still some issues ...

Borrowing from several projects:
MIDI code Copyright (C) 2016, Len Shustek from synth_Playtune and adapted to CMSIS-Stream

Music example (example1) from https://glicol.org
and totally rewritten to use CMSIS Stream

CMSIS Stream now support a callback mode but this
example has not been updated to use callback yet
(So for wasm it is a less efficient implementation).
