{
  description = "game";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            pkg-config
            sdl3
            sdl3-image
            sdl3-ttf
            clang
            cmake
          ];
          
          shellHook = ''
            echo "SDL3 development environment ready!"
          '';
        };
      }
    );
}
