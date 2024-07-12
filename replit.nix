{ pkgs }: {
	deps = [
   pkgs.nano
		pkgs.clang
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
		pkgs.raylib
		pkgs.gtk3
	];
}