# Framework GTK4 Component Roadmap

## Already represented by `Umicom::ui_gtk4`

- adapter bootstrap
- application shell
- workbench
- panes
- editor
- menus
- toolbar
- status
- notifications
- theme
- accessibility
- selection
- dialogs
- clipboard
- declarative renderer

## Expand as reusable component families

- windows and header bars
- labels, buttons, entries and form fields
- source/text views
- list/tree/column views
- tab/document hosts
- split panes and scrolled surfaces
- popovers/context menus
- command palette and search bar
- settings/property editors
- progress/busy/error states
- file/folder chooser adapters
- reusable chart surface
- reusable browser/media hosts where the abstraction remains product-neutral

## Rule

Framework must not become a mechanical mirror of every GTK symbol. A Framework
GTK component is justified when it supplies shared Umicom behaviour, stable
contracts, composition, accessibility, policy, testing or reuse across products.
