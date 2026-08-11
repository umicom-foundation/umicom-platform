# ADR-0002 — Umicom OS Depends on Umicom Framework in User Space

Status: Accepted

## Decision

Umicom OS is layered.

The Linux kernel, boot chain and minimal base userland **must not** depend on
Umicom Framework. They must remain capable of booting, recovery and basic system
administration even when Umicom Framework is absent or damaged.

The Umicom OS user-space platform **does** depend on Umicom Framework. The
desktop shell, settings applications, application launcher, system dashboards,
developer tooling and bundled Umicom products consume normal Framework public
contracts.

## Rationale

This gives Umicom OS the reuse benefits of the same runtime, messaging,
configuration, security, UI, diagnostics and application services used by
Studio, Trader, TMS and Bank without placing application-framework code inside
the kernel.

## Layering

```text
Linux kernel / boot
        ↓
minimal base userland
        ↓
Umicom Framework runtime and SDK
        ↓
Umicom OS shell and system applications
        ↓
Studio / Trader / TMS / Bank / Media / other products
```

## Consequence

A recovery image can boot without Umicom Framework. A normal Umicom desktop
session requires the Framework packages selected by the OS profile.
