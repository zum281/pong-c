pong: pong.c
	clang $< -I$(RAYLIB) $(RAYLIB)/libraylib.a -framework IOKit -framework Cocoa -framework OpenGL -framework QuartzCore -o $@
