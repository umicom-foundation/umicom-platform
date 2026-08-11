# ADR-0005 — Canonical application repository layout

Status: Accepted

Every independently runnable Umicom application repository uses a root-level
`framework/` Git submodule and stores product source below
`applications/<product>/`.

Umicom OS is the first repository migrated after the platform decision. Other
products follow in controlled batches rather than mass-moving source at once.
