# ADR-0006 — Suite and Inter-Application Runtime

Status: Accepted

## Decision

Umicom applications remain independently buildable and launchable repositories.

A suite is a composition manifest containing **required members** and
**optional members**. Required members must be available for a suite to be
launchable. Optional members may be absent without invalidating the suite.

Cross-application behaviour uses Umicom Framework Integration Fabric contracts,
typed commands/events/queries, public capabilities, explicit sessions and
bounded discovery. Applications must not access another product's private
headers, process memory or database tables.

## Runtime layers

```text
Suite manifest
    ↓
Platform suite planner
    ↓
Framework application discovery / registry
    ↓
Framework capability/dependency resolver
    ↓
Integration Fabric route + envelope + dispatcher
    ↓
Application public service/capability
```

## Current Batch 18 boundary

Batch 18 plans suite readiness and builds the reusable Framework runtime.
Starting/stopping real product processes remains an explicit later step after
product executable conventions are standardised.
