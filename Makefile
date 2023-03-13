all:
	go build sudokugen.go && ./sudokugen
	gcc -o main main.c -l pthread

clean:
	rm *.o main sudokugen
