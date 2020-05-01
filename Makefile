all: my-cat my-sed my-uniq

my-cat: my-cat.c
	gcc -o my-cat my-cat.c -Wall -Werror

my-sed: my-sed.c
	gcc -o my-sed my-sed.c -Wall -Werror

my-uniq: my-uniq.c
	gcc -o my-uniq my-uniq.c -Wall -Werror

clean:
	rm my-cat my-sed my-uniq