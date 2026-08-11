# Umicom Platform

`umicom-platform` is the master integration workspace for the Umicom ecosystem.

It does not replace the Git history of Umicom Framework, Studio IDE, TMS, Bank,
UmiCoin, Umicom OS, AuthorEngine or other products. Those repositories remain
independent Git submodules. This repository records a tested combination of
their exact Git revisions and supplies platform-wide validation, build
orchestration, suite manifests and integration tests.

## First-stage commands

```powershell
git submodule sync --recursive
git submodule update --init --recursive

cmake --preset host-debug
cmake --build --preset host-debug
ctest --preset host-debug

.\build\host-debug\bin\umicom-platform.exe doctor
.\build\host-debug\bin\umicom-platform.exe status
.\build\host-debug\bin\umicom-platform.exe validate
.\build\host-debug\bin\umicom-platform.exe framework-audit
```

On Linux omit `.exe`.

The two website projects remain **planned** in Batch 15 and are not Git
submodules yet. A literal placeholder such as `<FOUNDATION-WEBSITE-URL>` must
not be typed into PowerShell because `<` is parsed as shell syntax.
