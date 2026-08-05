# Changelog

## [v4.0.0-beta2](https://github.com/redasm-dev/redasm/releases/tag/v4.0.0-beta2) - 2026-08-05

### GUI
- Loaded types are now visible in a dedicated dialog.
- Implemented patching and general editing in UI.
- Detect Tiling WMs on Linux in Debug builds and lock main window's size.
- Improved cursor movement behavior in listing and graph views.
- Added load file from command line support.
- Added `SELECT_ALL` action, reworked Edit menu.
- Added `Reanalyze` action.
- Added `UNDEFINE`, `CODE`, `DATA` and `Create function` menu actions.
- Adjusted rendering mode ordering.
- Updated welcome page.
- Cleaned UI.
- Smoother UX.
- Bumped QHexView to v5.1.3.
- **Fixed**: Missing CTRL+Enter in comments dialog ([#8](https://github.com/redasm-dev/bugs/issues/8)).
- **Fixed**: Don't show reference dialog when no xrefs are available, log instead.
- **Fixed**: Don't use native dialogs for `QFileDialog::getExistingDirectory`.
- **Fixed**: `LoaderDialog` premature deallocation when `RD_ACCEPT_FAIL_WRITE` happens.
- **Fixed**: Debug builds when ASAN or LSAN are not enabled.
- **Fixed**: `SplitWidget` stability (dangling pointers) and better UX.
- **Fixed**: Missing highlighting in `EXPERIMENTAL` flagged analyzers.
- **Fixed**: Detach some actions from `QMainWindow`.
- **Fixed**: Don't store `RDFunction` in `FunctionsModel`.
- **Fixed**: Autojump on EP only after first analysis.
- **Fixed**: Give detached dialogs a valid size.
- **Fixed**: Stale `RDGraph` in `GraphView` after mutations.
- **Fixed**: Manual addressing.

### Core
- Implemented `rd_version_parse` API.
- Implemented `rd_patch_instruction` API.
- Implemented `rd_make_code` API.
- Implemented `rd_get_flags` API.
- Implemented `rd_encode_instruction` and `rd_encode_instruction_to` APIs.
- Implemented `rd_typedef_is_builtin` API.
- Implemented `RDLexer` type.
- Implemented `RDScratchBuffer` type.
- Implemented general byte level edit and patching capabilities.
- Added `bool`, `function`, `isize` and `usize` builtin types.
- Added `rol` and `ror` API set.
- Added `rd_read_str` API.
- Added `rd_resolve_name` API.
- Added `PLACEHOLDER` confidence level.
- Added `RECONCILE` step in worker.
- Notify reconciling to core peers.
- Improved `RDFunction` creation, handling and internal storage.
- Improved `noret` detection and propagation.
- Reworked logging APIs.
- Reworked `RDType` and `RDTypeDef` for future proofing and stability.
- Implemented Encoding APIs.
- Renderer now uses grouping instead of character matching.
- Redesigned hex dump behavior and alignment.
- Functions with unknown return type and/or arguments are now allowed.
- Expanded surface APIs.
- Prefer system-wide `miniz` if available.
- **BREAKING**: Reworked internal `FLAGS` layout.
- **BREAKING**: Removed `int_size` field in `RDProcessorPlugin`.
- **BREAKING**: Removed `unit` field in `RDSegment`.
- **BREAKING**: Simplified and cleaned up SQLite schema.
- **BREAKING**: Removed RDListing type, rendering is now direct.
- **BREAKING**: Projects now validate against core version.
- **Fixed**: Crash in binary loader ([#4](https://github.com/redasm-dev/bugs/issues/4)).
- **Fixed**: `USER` confidence in `rd_i_set_type`.
- **Fixed**: Restore `min_string` on project load.
- **Fixed**: Autorenamer confidence propagation.
- **Fixed**: Analyzer plugins sorting.
- **Fixed**: Ignore empty comments.
- **Fixed**: String detection.

### Loaders
- PE loader now handles Load Config Directory.
- Implemented Rich Header parsing and classification for PE files.
- Improved PE classification logic.
- **Fixed**: MZ loader now respects x86 decode/emulate hooks.

### Processors
- Implemented x86 encoder.
- Improved x86 logging.
- **Fixed**: x86 instruction `hlt` now propagates 'noret'.

### Analyzers
- Implemented MSVC RTTI plugin (experimental).
- Moved VB decompiler from PE loader to "compiler" analyzer plugin.

### KB
- **BREAKING**: Reworked and simplified definition format.
- Reorganized VB types and dependencies.
- Added PE_LOADER_CONFIG_DIRECTORY struct.
- Added MSVC RTTI types.

### Workspace
- Lowered CMake requirements to 3.20.
- Updated unit tests, stricter requirements.
- Added GCC 11 support.

## [v4.0.0-beta1](https://github.com/redasm-dev/redasm/releases/tag/v4.0.0-beta1) - 2026-06-23
See [GitHub Releases page](https://github.com/redasm-dev/redasm/releases/tag/v4.0.0-beta1)
