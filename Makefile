objectfiles = main.o mainrc.o
app.exe : $(objectfiles)
	gcc -o app.exe $(objectfiles) -Wl,--subsystem,windows -lcomdlg32
main.o:
	gcc -o main.o -c main.c
mainrc.o:
	windres -i main.rc -o mainrc.o
.PHONY: clean
clean:
	del $(objectfiles)