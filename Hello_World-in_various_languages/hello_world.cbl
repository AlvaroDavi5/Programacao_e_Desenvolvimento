*>  Hello World in COBOL

*>  run using commands:
*> cobc -free -x -o hello_world hello_world.cbl
*> ./hello_world


IDENTIFICATION DIVISION.
PROGRAM-ID. HELLO-WORLD.
AUTHOR. ALVARO.

PROCEDURE DIVISION.
	DISPLAY "Hello World!".
	STOP RUN.
