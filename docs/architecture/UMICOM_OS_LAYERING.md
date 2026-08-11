# Umicom OS Layering

| Layer | Framework dependency | Reason |
|---|---:|---|
| Linux kernel | No | Kernel boot/recovery must not depend on application framework code. |
| Minimal base userland | No | Recovery and low-level administration remain available independently. |
| Umicom Framework runtime/SDK | It is the dependency | Shared application/runtime services begin here. |
| Umicom OS desktop shell | Yes | Reuses runtime, security, configuration, messaging and UI contracts. |
| Umicom system applications | Yes | Settings, launcher, control centre and development tools reuse Framework. |
| Bundled Umicom applications | Yes | Same rule as their standalone repositories. |

The normal desktop distribution therefore installs Framework as a core user-space
package, while rescue/minimal profiles may omit it.
