make:
	@gcc -o main vstring.c arrlist.c md5.c main.c -l crypto 

clean:
	@rm main
	