# ADR-0004 — Workspace Orchestrator Safety

Status: Accepted

The native workspace orchestrator follows plan-before-mutation.

Pinned sync may be applied directly because it only restores Git submodules to
the revisions already recorded by the parent repositories.

Remote revision changes, lock updates, repository migration, commits, pushes and
deletions require an explicit plan and a separate user action.

The orchestrator never silently commits or pushes.
