# ADR-0003 — Reusable GTK4 Implementations Belong in Umicom Framework

Status: Accepted

## Existing foundation

Umicom Framework already exposes toolkit-neutral `Umicom::ui` contracts and an
optional `Umicom::ui_gtk4` adapter. The current GTK4 target implements the
application shell, workbench, panes, editor, menus, toolbar, status,
notifications, theme, accessibility, selection, dialogs, clipboard and
declarative rendering.

## Decision

Expand this into the canonical reusable GTK4 component library for all Umicom
desktop applications and Umicom OS user-space.

The Framework should make reusable GTK4 implementations available for:

- application windows and shells
- header bars and application chrome
- menu and toolbar rendering
- status bars
- tab/document containers
- split panes and docking/pane hosts
- tree/list/table views
- forms, labels, buttons and entries
- dialogs and notifications
- settings/property editors
- search/filter controls
- command palette presentation
- progress/busy/error states
- accessibility helpers
- theme/CSS/resource management
- clipboard and selection
- file/folder chooser adapters
- reusable chart surfaces
- reusable media/browser hosts where appropriately abstracted

## Boundary

Do not wrap GTK merely to rename every GTK symbol. Framework components must
exist because they provide a stable Umicom contract, common behaviour,
accessibility, policy, testing or composition value.

A product may still use raw GTK4 privately inside its frontend for
product-specific widgets. Once a component is genuinely reused by two products,
it should normally move into the Framework GTK4 library.

## Public API rule

Toolkit-neutral Framework APIs contain no GTK types.

GTK-aware application frontend code may explicitly link `Umicom::ui_gtk4`.
