{
  description = "game";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    sdl3pp = {
      url = "github:talesm/SDL3pp";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, flake-utils, sdl3pp }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        
        sdl3pp-package = pkgs.stdenv.mkDerivation {
          pname = "sdl3pp";
          version = "0.1.0";
          src = sdl3pp;

          # Просто копируем заголовочные файлы
          installPhase = ''
            mkdir -p $out/include
            cp -r include/* $out/include/
          '';

          # Не требуется сборка
          dontBuild = true;
          dontConfigure = true;
        };
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            pkg-config
            sdl3
            sdl3-image
            clang
            cmake
            sdl3pp-package
          ];
          
          shellHook = ''
            echo "SDL3 development environment ready!"
            echo "SDL3pp included from: ${sdl3pp}"
          '';
        };

        packages.default = sdl3pp-package;
      }
    );
}