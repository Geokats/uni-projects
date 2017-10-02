--- Katso's Go Machine ---


=== Compilation Instructions ===

Use the makefile included, with the "make" command.


Alternatively, use the "gcc -c <filename>" command on the following files:

*go.c
*administrative.c
*inout.c
*setup.c
*play.c

And then the "gcc -o go go.o administrative.o inout.o setup.o play.o" command.
The header files must be in the same directory as the source files.

=== Command Line Arguments  ===

You can run the program with the following arguments:

* "-seed <seednumber>" to manually chose the seed for the random number generator.
  If no seed is given the program will use 1 as the seed.

* "-superko" to include checking the moves for the superko rule.
  If not given then the program will only check for ko.

=== GTP Commands Implemented ===

*protocol_verion
*name
*version
*known_command
*list_commands
*quit
*boardsize
*clear_board
*fixed_handicap
*komi
*showboard
*play
*genmove
*undo
*final_score
