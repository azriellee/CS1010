# Question 1: Selection (15 marks)
--------------------------------------

Sorting a list of item so that they are in order (e.g., 
in non- decreasing order) is a fundamental problem in 
computing.

In this question, you are asked to implement a sorting
algorithm called _selection sort_.  The idea behind
selection sort is simple, and we will illustrate with
the sequence `15 23 16 4 42 8`.  To sort an array with n
values in non-decreasing order, selection sort first finds
the maximum value, then moves it into its proper place,
that is, the last position.  This move is achieved by
swapping the value currently in the last position with
the maximum value.  For instance, for `15 23 16 4 42 8`,
`42` is the maximum value and `8` wrongly occupies the
position reserved for the maximum value.  After the first
step, the array becomes `15 23 16 4 8 42`.

We now focus on sorting the first n-1 values in the array
(since the maximum is now in place).  To do this, we
find the second largest value and move it to the second
last position.  The array becomes `15 8 16 4 23 48` after
this second step.

The algorithm continues, moving the third largest value
into place, the fourth largest value into place, etc.,
until the array is sorted.  The table below shows the
evolution of the array.

|Step| Array            | Remarks                           
|----|------------------|-----------------------------------
| 0  | 15 23 16 4 42 8  | Input Array                       
| 1  | 15 23 16 4 8 42  | Swap 42 and 8                     
| 2  | 15 8 16 4 23 42  | Swap 23 and 8                     
| 3  | 15 8 4 16 23 42  | Swap 16 and 4                     
| 4  | 4 8 15 16 23 42  | Swap 15 and 4                     
| 5  | 4 8 15 16 23 42  | 8 already be in position
| 6  | 4 8 15 16 23 42  | 4 must already be in position       

Write a program `selection` that, reads the following,
from the standard input,

- n, the number of integers to sort (n <= 1000)
- followed by n integers

into an array, and prints, to the standard output, n - 1 
lines, each line showing the array after moving the
largest or the next largest element into position.

You can assume that the input list of n integers to be
sorted are unique -- i.e., no repetition.

### Sample Run
```
ooiwt@pe119:~/as04-skeleton$ ./selectionsort
6 15 23 16 4 42 8
15 23 16 4 8 42
15 8 16 4 23 42
15 8 4 16 23 42
4 8 15 16 23 42
4 8 15 16 23 42
ooiwt@pe119:~/as04-skeleton$ ./selectionsort
3 0 4 8
0 4 8
0 4 8
ooiwt@pe119:~/as04-skeleton$ ./selectionsort
5 1 3 5 4 2
1 3 2 4 5
1 3 2 4 5
1 2 3 4 5
1 2 3 4 5
```

# Question 2: Mastermind (15 marks)
-----------------------------------

Many childhood games from the 70s and 80s are gaining
attention again lately.  One of such childhood games 
that requires strong logical thinking to play is the 
game of Mastermind.

Mastermind is a board game played by two players, a
_coder_ and a _codebreaker_.  The coder creates a code
that consists of four color pegs, chosen from pegs of
six different colors (cyan, green, red, blue, purple,
orange).  Repetition of the same colors is allowed.
The codebreaker's task is to guess the colors of the 
pegs and the order their appears in the code.

The game proceeds in rounds.  In each round, the
codebreaker tries to guess the code by specifying the
colors and the order of the colors.  The coder then
provides feedback to the codebreaker, with two smaller
pegs of black and white color.  A black color peg is
placed if the codebreaker guesses correctly a peg in both
position and color.  A white color peg is placed if the
codebreaker guesses correctly a peg in color but not in
the position.  Based on the feedback, the codebreaker
guesses again in the next round.  The codebreaker wins if
he guesses correctly every color in the correct order.
In the board game version of this game, the coder wins
if the codebreaker failed to guess correctly after some
agreed-upon number of guesses.  In our version, however,
the game continues until the codebreaker guesses correctly.

Write a program called `mastermind` that simulates the
Mastermind game.  The program first reads in the code
from the standard inputs.  We denote the colors with
a number, `1`, `2`, `3`, `4`, `5`, `6`.  Hence, the code 
is represented with 4 numbers, e.g., `1 3 5 4`.  

The program then reads in a sequence of guesses, each is
4 single-digit number ranged from 1 to 6.  For each guess,
the program prints out two numbers, the first is the number
of pegs that are correct in both position and color.
The second is the number of pegs that are correct in
color but not position.  Note that we do not double count,
so the total of these two numbers is at most 4.

For example,  if the code is `5 3 6 4` and the guess is
`4 6 3 2`, the program prints `0 3`.  Since none of the
guesses is correct in both color and position.  The three
colors `3`, `4`, `6`, however, appear in the code, albeit
in a different position.  Suppose the guess is `3 3 3 3`,
the program prints `1 0`.  The third `3` is the guess that
appears in the correct position and correct color.  There
is no other `3` in the code, so the second number is 0.
This example illustrates that we do not double count.
We do not match the other `3`s in the guess to the `3`
in the code, once the `3` in the code has been matched.

The program terminates when the guess is the same as
the code.

## Sample Run
-------------
```
ooiwt@pe119:~/as04-skeleton$ ./mastermind
5 3 6 4
4 6 3 2
0 3
3 3 3 3
1 0
4 4 4 4
1 0
6 6 3 3
0 2
5 3 5 4
4 0
ooiwt@pe119:~/as04-skeleton$ ./mastermind
1 1 1 5
4 6 3 2
0 0
5 3 6 4
0 1
6 6 6 1
0 1
1 6 6 1
1 1
5 1 5 1
1 2
1 5 1 5
3 0
1 1 1 5
4 0
```
