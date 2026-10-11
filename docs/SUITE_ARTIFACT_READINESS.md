# Suite executable-artifact readiness (read-only)

## Why this feature exists

Umicom Platform already supplies `workspace suite list`, `show`, `plan` and
`validate`. These check project manifests and directory availability, and
have to remain backward compatible. A present source directory, however, does
not prove an application was built or can be started. The artifact command adds a **second,
stricter gate**. It is intentionally not a new process launcher.

The canonical cross-application orchestrator belongs to **Umicom Platform**.
The reusable service lifecycle, messaging, permissions and application UI
remain owned by **Umicom Framework**, while business rules live in their
application modules. Neither a native kernel nor OS recovery depends on the
full Framework.

## Run the suite gate

From the `umicom-platform` repository root, after building the native Platform
tool and the selected Umicom applications:

```powershell
Set-Location "C:\umicom\umicom-platform"
$platform = ".\build\host-debug\bin\umicom-platform.exe"
$binaryRoot = "C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin"
& $platform workspace suite artifacts umicom.suite.studio --bin-dir $binaryRoot
& $platform workspace suite artifacts umicom.suite.financial --bin-dir $binaryRoot
```

A Linux build can choose `--target linux`. An explicit cross-build inspection
can choose `--target windows` even from another host; it is a *file-format*
inspection, not evidence that the image can execute on that host.

To use a separately reviewed filename list:

```powershell
& $platform workspace suite artifacts umicom.suite.studio `
    --bin-dir $binaryRoot `
    --catalogue ".\manifests\suites\executable_targets.txt" `
    --target windows
```

The native tool returns **0** if every required project is enabled, has an
existing source directory and has a regular, plausibly formatted executable
image. Missing optional members produce `READY-DEGRADED`. Missing or unmapped
required members produce **2 / BLOCKED**. Malformed catalogues are rejected,
not partially applied. Unsupported or missing image formats fail closed.

This does **not** perform ABI negotiation, cryptographic verification, startup,
service health, end-to-end actions or IPC. Further development must add those
independent proof stages before production suite launch can be declared ready.

## Catalogue format

`manifests/suites/executable_targets.txt` uses three whitespace-separated
fields: project ID, Windows filename, Linux filename. It supports comment
lines beginning with `#` and a `-` placeholder for an unverified target.
Product IDs must match `manifests/projects/*.json`; filenames must be plain
basenames with no directory separators, drive prefixes, shell symbols or
traversal. The directory itself comes only from `--bin-dir`.

**Do not substitute an unrelated executable as proof of readiness**.
Record a filename only after checking the application's actual CMake target,
installed manifest or packaged runnable product. The initial catalogue
intentionally covers only Studio, Trader, Bank and TMS. The current Platform
suite manifests include LLM and Umicoin as required members, so such suites
should report `BLOCKED` until their packaging contracts and repository pins are
reconciled. That is a feature of honest reporting, not a regression.

## Validation and ownership

- C23 implementation: `src/workspace/suite_artifacts.c`
- Public contract: `include/umicom/platform/workspace/suite_artifacts.h`
- Native command integration: `src/workspace/suite_command.c`
- Contract and negative-case tests: `tests/test_suite_artifacts.c`
- Original suite planning remains unchanged.
- No deletion or replacement of legacy functions; credits and comments retained.
- No automatic `git`, package install, provider connection or process startup.

## Next independent milestone

Use the artifact report to construct a real **application launch plan** that
performs version/ABI checks, permission policy, working-directory independence,
process supervision, health/readiness handshakes and deterministic teardown.
That follow-on work must use existing Framework runtime and Integration Fabric
contracts, not duplicate them in Platform.
