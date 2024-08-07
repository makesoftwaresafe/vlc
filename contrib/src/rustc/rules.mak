# rustc+cargo installation via rustup

RUST_VERSION=1.79.0

ifdef BUILD_RUST
PKGS_TOOLS += rustc

ifdef HAVE_CROSS_COMPILE
PKGS_TOOLS += rustc-cross
PKGS_ALL += rustc-cross
endif

ifneq ($(call system_tool_version, rustup --version, cat),)
RUSTUP = $(RUST_ENV) rustup
else
RUSTUP = . $(CARGO_HOME)/env && \
         $(RUST_ENV) rustup
endif

ifeq ($(call system_tool_matches_min, echo 'fn main() {}' | rustc --target=$(RUST_HOST) --emit=dep-info - -o /dev/null 2>/dev/null && rustc --version,$(RUST_VERSION_MIN)),)
PKGS_FOUND += rustc
ifndef HAVE_CROSS_COMPILE
RUST_ENV=
endif
else
DEPS_rustc = rustup $(DEPS_rustup)
endif
ifeq ($(call system_tool_matches_min, echo 'fn main() {}' | rustc --target=$(RUST_TARGET) --emit=dep-info - -o /dev/null 2>/dev/null && rustc --version,$(RUST_VERSION_MIN)),)
PKGS_FOUND += rustc-cross
ifdef HAVE_CROSS_COMPILE
RUST_ENV=
endif
endif

endif

DEPS_rustc-cross = rustc $(DEPS_rustc) rustup $(DEPS_rustup)

.sum-rustc:
	touch $@

.sum-rustc-cross:
	touch $@

.rustc:
	+$(RUSTUP) set profile minimal
	+$(RUSTUP) default $(RUST_VERSION)
	touch $@

.rustc-cross:
	+$(RUSTUP) set profile minimal
	+$(RUSTUP) default $(RUST_VERSION)
	+$(RUSTUP) target add --toolchain $(RUST_VERSION) $(RUST_TARGET)
	touch $@
