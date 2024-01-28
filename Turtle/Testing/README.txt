Main Commands:
make run_parsetest: Run parse script and assert test, with report format.


Project: Turtle
Project Timeline: 13th December 2023 -> 29th January 2024 (with extension)
Expected: 2 weeks (however took approximately 5 weeks)
Difficulty Reflection in comparison to past assignments: 10/10 (hardest so far - however with steepest learning curve)

General Testing Beginning Methadology (23/12/23):
When implementing testing, I thought I would first learn about the difference between
whitebox testing and blackbox, and then split testing for the parser and interpreter 
by two seperate files. 
For the parser, I set my white-box testing to be running through the provided .ttl files,
creating more .ttl for testing edge cases.
For blackbox, I wanted to test the recursive nature of the code, which was the most important thing.
As well as using strcpy to input instructions into the structure and running it through the program, I also had made
assert tests for making sure it failed.

Predictions:
I believe this project will take longer than the expected 2 weeks for myself having only programming experience built on this course,
however important to keep showing up in labs to ask questions and explore solutions collaboratively, as well as exploring solutions independantly 
-> ask for feedback in labs.

Parser Completion: 13/12/23 -> 23/12/23
Interp Completion: 12/01/23 -> 28/01/24

End of Project writeup (28/01/24)

-----------------------------------------------------PARSER----------------------------------------------------------------------------
Results/Reflection:
Through the process of testing the interpreter, I had only considered assert tests to be the main method of testing.
BUG: Difficulty in black-box testing (inner works of program). I found that testing for exit(EXIT_FAILURE) was difficult with assert tests. To combat, I had researched the use of 
testing for different "verbosity levels," a term I had come across refering to how much information the program outputs.
As I had only considered assert tests, the unit test included something like so:

void test_functionUnderTest() {
    int result = functionUnderTest(1);
    assert(result == ERROR_CODE);
}

BUG ENCOUNTER: I found that there was difficulty in testing different levels of "verbosity"
- ie the function became complicated due to the recursive nature and the result feeding back to
FAILURE/SUCCESS when coming back to runprogram function.
BUG FIX: To overcome, I had taken Dr.Campbell's advice on using a bash script. As I had already written out assert testing success, 
I thought of saving time and only test functions with EXIT_FAILURE. I had formatted using sleep so that it became easier for the user
to see the different tests with a pause inbetween and make more readable.

OVERALL: I had lots of enjoyment researching different ways of testing, which had been encourtered through failure. This failure I now found
was necessary, however next time it would be important to research testing from the beginning, as well as planning through code.
As I struggle with misorganisation with ADHD, it would be good for me to create a planning script, of asking questions like:
	-What is the program doing?
	-How can I implement + is this the best way of implementing? Feedback after.
	-NEXT TIME: How can I test? Is assert test the best way of testing? Could using a bash script be easier and more effective?
Tailoring a structure for planning these questions would be highly effective for myself having difficulty with planning as I go along,
however also saves lots of time. Exploring new methods of testing was done through lots of stack overflow research, however significant progress was 
made when looking at previous github projects that had different methods for testing (example later spoken about in Interpreter), and running them to 
understand how they work. However must say learning curve only increased as I was incredibly reflective with the Parser. I kept a bug log (not included as very small bugs and long file),
and made an end of day reflection for each major bug found.


-----------------------------------------------------INTERPRETER----------------------------------------------------------------------------


Interp: #endif BUG 


Testing Parser:
For the parser, I split by

Parsing Test:
White-box Testing:
-Testing Input/Output 
-Therefore running through TTLs provided
-Wrote new to include more edge cases
	-perhaps more ttl that will parse but doesnt interpret?

Black-box Testing:
-Testing I/O, but also internal testing
-Bash script to check error messaging
-assert testing each function for recursive nature
