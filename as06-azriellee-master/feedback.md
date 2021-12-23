# CS1010 Assignment 6
## Feedback for azriellee
### contact
- Your `contact` fails to pass 1 of the test cases. For this question, there is a -1 penalty for each failed test.
- Your `contact` is buggy when malloc/calloc fails. For this question, there is a -1 penalty if there is more than one bug when memory allocation fails (either you did not check for NULL or you did not return a non-zero value).
- `clang` and `clang-tidy` are happy with your `contact.c`. No warnings are generated. :confetti_ball:
### social
The tutor has marked your code. You can find [the comments from your tutor here](https://www.github.com/nus-cs1010-2122-s1/as06-azriellee/commit/aa9e2e22b4aa3580da554ba86ade3fe66c40d134). Marks awarded by tutor (before deduction by bots):

Output from the bot (including possible auto-deduction):
- `clang` and `clang-tidy` generate 1 (non-documentation-related) warnings for `social.c`. There is a -1 penalty per warning.
- Your `social` is buggy when malloc/calloc fails. For this question, there is a -1 penalty if there is more than one bug when memory allocation fails (either you did not check for NULL or you did not return a non-zero value).

| Criteria | Max | Marks from Tutor | Marks After Bots Deduction) |
| ----------|-----|-----------|---|
| Correctness | 12 | 10 | 8 |
| Style | 1 | 1 | 1 |
| Efficiency | 0 | 0 | 0 |
| Documentation | 2 | 2 | 2 |
| **TOTAL** | 15 | **13** | **11**|
### life
- Your `life` passes all test cases. :thumbsup:
- No bug is detected when malloc/calloc fails (the bot's detection is not exhaustive though).
- `clang` and `clang-tidy` generate 1 (documentation-related) warnings for `life.c`. There is a -1 penalty per warning.
## Summary
| Question | Marks |
|----------|-------|
| contact | 9 |
| social | 11 |
| life | 14 |
