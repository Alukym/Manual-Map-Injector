
# Simple Manual Map Injector

- Supports ~~x86 and~~ x64 (Compiling depending the targets)
- Supports x64 exceptions (SEH) (only /EHa and /EHc)
- Supports multi-dll injection
- Release & Debug
- Removes PE Header and some sections (Configurable)
- Configurable DllMain params (default DLL_PROCESS_ATTACH)
- Add sections protections (Configurable)

## Devs

- Add **DISABLE_OUTPUT** definition if you want to disable injector.cpp output
- main.cpp is just an example but powerfull
- Hello World dlls added from https://github.com/carterjones/hello-world-dll for easy testing
