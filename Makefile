all:
	cmake -S. -Bbuild
	ln -fs build/compile_commands.json .
	cmake --build build
