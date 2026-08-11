# Umicom Platform

`umicom-platform` is the master integration workspace for the Umicom ecosystem.

Each major product remains an independent Git repository. The platform pins exact
submodule revisions, validates compatibility, plans workspace operations and
coordinates cross-project build, test and release work.

## Stage 2 native workspace commands

```powershell
$platform = ".\build\host-debug\bin\umicom-platform.exe"

& $platform workspace status
& $platform workspace graph
& $platform workspace sync --pinned --plan
& $platform workspace framework-audit
& $platform workspace lock-plan
& $platform workspace build-plan
& $platform workspace test-plan
& $platform workspace codeguard-plan
& $platform workspace os-ui
```

The first mutating workspace operation is deliberately narrow:

```powershell
& $platform workspace sync --pinned --apply
```

It performs only:

```text
git submodule sync --recursive
git submodule update --init --recursive
```

It does not switch branches, commit, push or move submodules to newer remote
branches.

## Umicom OS and Framework

The Linux kernel and base Linux userland do not depend on Umicom Framework.

The **Umicom OS user-space platform does depend on Umicom Framework**. This
includes the Umicom desktop shell, settings applications, launcher, system
management UI, developer environment and bundled Umicom applications.

The Framework is also the canonical home for reusable toolkit-neutral UI
contracts and the reusable GTK4 adapter/component implementation. Product-only
widgets remain in the product until a second real consumer proves they are
reusable.


## Suite and Integration Fabric commands

Batch 18 promotes suite manifests from planned membership lists to explicit
required/optional composition contracts.

```powershell
$platform = ".\build\host-debug\bin\umicom-platform.exe"

& $platform workspace suite list
& $platform workspace suite show umicom.suite.studio
& $platform workspace suite plan umicom.suite.studio
& $platform workspace suite validate umicom.suite.financial
& $platform workspace integration-graph
```

An unavailable **required** member blocks suite readiness. An unavailable
**optional** member is reported as `SKIP` and produces a degraded-but-usable
suite plan. No command in Batch 18 launches or stops real product processes.
