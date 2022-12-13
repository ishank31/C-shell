main: main.c display.c cd.c echo.c helpers.c input.c ls.c pwd.c history.c foreground.c background.c pinfo.c discover.c newredirection.c jobs.c sig.c fg.c signals.c bg.c
	gcc -o shell main.c display.c cd.c echo.c helpers.c input.c ls.c pwd.c history.c foreground.c background.c pinfo.c discover.c newredirection.c jobs.c sig.c fg.c signals.c bg.c

clean:
	rm shell