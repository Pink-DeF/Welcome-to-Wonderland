{
  description = "game";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    #flake-utils.lib.eachDefaultSystem (system:
      let
        system = "x86_64-linux";
        #pkgs = nixpkgs.legacyPackages.${system};
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.${system}.default = pkgs.mkShell {
          packages = with pkgs; [
            pkg-config
            sdl3
	          sdl3-image
	    clang
            cmake
          ];
	  
          shellHook = ''
            echo "SDL3 development environment ready!"
          '';
        };
      };
    #);
}
