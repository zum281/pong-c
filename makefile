
pong: pong.c
	clang $< -I./include ./lib/libraylib.a -framework IOKit -framework Cocoa -framework OpenGL -framework QuartzCore -o $@
