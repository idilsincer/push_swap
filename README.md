*This project has been created as part of the 42 curriculum by idsincer, otasar.*
# push_swap

## Description

push_swap sorts a list of integers with two stacks, `a` and `b`, and a small set of
operations (`sa sb ss pa pb ra rb rr rra rrb rrr`). The program prints a short list of
operations that sorts stack `a` in ascending order (smallest number on top).

The goal is to experience algorithmic complexity: the cost of an algorithm is the
**number of operations it prints**. The program contains four strategies and can choose
one from the **disorder** of the input (how far it is from being sorted):

| Flag | Algorithm | Class (in operations) |
|---|---|---|
| `--simple` | selection sort | O(n²) |
| `--medium` | chunk "butterfly" sort | O(n√n) |
| `--complex` | 3-way quicksort on 4 positions | O(n log n) |
| `--adaptive` (default) | picks one of the above from the disorder | see below |

## Instructions

### Compilation

```
make          # builds ./push_swap
make clean    # removes the object files
make fclean   # removes the object files and the program
make re       # rebuilds everything
```

### Usage

```
./push_swap 2 1 3 6 5 8                     # prints the operations, one per line
./push_swap --complex 5 4 3 2 1             # forces a strategy
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG
./push_swap --bench $ARG > /dev/null        # shows the metrics (stderr)
```

- The first number is the top of stack `a`. Each number is a separate argument.
- Flags: `--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`.
  If several strategy flags are given, the last one is used.
- No numbers, or numbers already sorted: nothing is printed.
- Errors print `Error` and a newline on stderr: an argument that is not an integer,
  a number outside the `int` range, a duplicate, an unknown flag.

`--bench` prints after sorting, on stderr:

```
[bench] disorder:  40.00%
[bench] strategy:  Adaptive / O(n√n)
[bench] total_ops:  9
[bench] sa:  0  sb:  0  ss:  0  pa:  2  pb:  2
[bench] ra:  4  rb:  0  rr:  0  rra:  1  rrb:  0  rrr:  0
```

## Algorithms

### Preparation

- Every number is replaced by its rank (0 = smallest, n - 1 = biggest). Only the order
  matters, and with ranks every algorithm knows exactly which value it is looking for.
- **Disorder** = number of pairs (i < j) with a[i] > a[j], divided by the number of pairs.
  It is computed once, before any operation (O(n²) comparisons: CPU time, not operations).

### Simple: selection sort, O(n²)

Bring the minimum of `a` to the top with `ra` or `rra` (the shorter way) and `pb` it,
until 3 numbers are left. Sort those 3 with at most 2 operations, then `pa` everything back.
`b` holds the ranks 0 .. b.size - 1, so the minimum of `a` is always `b.size`.

- Time: each minimum costs at most n/2 rotations + 1 push, so at most n²/2 + 2n operations.
- Space: the two stacks, O(n).
- Inputs of 5 numbers or less use this sort in every strategy (base case):
  at most 2 operations for 3 numbers, at most 10 for 5 numbers.

### Medium: chunk "butterfly", O(n√n)

Let R ≈ 1.4·√n. Phase 1: look at the top of `a`. If its rank is ≤ i + R, `pb` it
(and `rb` it if its rank is ≤ i, so small values go to the bottom of `b`), then i++.
Otherwise `ra`. Phase 2: bring the maximum of `b` (always `b.size - 1`) to the top the
shorter way and `pa` it, until `b` is empty.

- Phase 1: at any moment at least R values of `a` can be pushed, so each full turn of `a`
  pushes at least R values: at most n/R turns of at most n `ra`, about 0.7·n√n operations,
  plus at most 2n for `pb` and `rb`.
- Phase 2: every pushed value was ≤ i + R, so after t pushes at most R values smaller than
  t + R are still in `a`. Because of this the next maximum of `b` is always within about
  2R positions of the top (going the shorter way): each `pa` costs at most about 2R + 3
  operations, so O(n√n) in total.
- Space: O(n).
- Why 1.4·√n: a smaller window makes phase 1 longer, a bigger one makes phase 2 longer.
  We measured factors from 1.0 to 2.0 and 1.4 gave the fewest operations.

### Complex: 3-way quicksort on 4 positions, O(n log n)

A chunk of ranks lo..hi lies at one of 4 positions: top of `a`, bottom of `a`, top of `b`,
bottom of `b`. To sort a chunk, each of its elements is moved to one of the 3 other
positions, depending on its third (small, middle or big). One move needs at most 3 operations:

1. if the element is at a bottom, bring it to the top (`rra` / `rrb`),
2. if it must change stack, push it (`pb` / `pa`),
3. if its target is a bottom, send it there (`ra` / `rb`).

Then the big, middle and small thirds are sorted recursively. A sorted chunk always ends on
top of `a`, so the results pile up in the right order. Chunks of 1 or 2 elements are moved
straight to the top of `a` (plus one `sa` if needed).

- Time: on each level of the recursion every element is moved once (at most 3 operations),
  and a chunk shrinks to a third, so there are about log₃ n levels: about 3·n·log₃ n
  operations, O(n log n).
- Space: O(n) for the stacks and O(log n) for the recursion.

### Adaptive: thresholds

| Disorder | Strategy used | Bound |
|---|---|---|
| d < 0.2 | simple | O(n²) |
| 0.2 ≤ d < 0.5 | medium | O(n√n) |
| d ≥ 0.5 | complex | O(n log n) |

- We use the subject's thresholds, so each regime meets its required bound by construction.
  The comparison is done with integers: d < 0.2 ⇔ mistakes·5 < pairs,
  d < 0.5 ⇔ mistakes·2 < pairs.
- A random input has a disorder very close to 0.5 (about ±0.035 for 100 numbers, ±0.015
  for 500), so random inputs are sorted by medium or by complex. That is why both were
  chosen to stay under 700 (100 numbers) and 5500 (500 numbers) operations.
- Inputs of 5 numbers or less use the simple sort as a base case, like many sorting
  algorithms switch to a simpler method for small parts.

### Measured results (random inputs)

| | 100 numbers: average / worst | 500 numbers: average / worst |
|---|---|---|
| adaptive (default) | 623 / 681 | 4728 / 5188 |
| `--medium` | 574 / 613 | 5055 / 5225 |
| `--complex` | 675 / 682 | 4472 / 4488 |
| `--simple` | 1450 / 1711 | 32637 / 34455 |

## Contributions

- **idsincer**: project setup, stack structures (`push_swap.h`), stack operations
  (`s_operations.c`, `p_operations.c`, `r_operations.c`, `rr_operations.c`).
- **otasar**: argument parsing and errors, stack building, disorder, the four strategies and
  the adaptive choice, `--bench` (`sort.h`, `main.c`, `parse.c`, `stack.c`, `ops.c`,
  `bench.c`, `sort_simple_medium.c`, `sort_complex.c`), Makefile fixes, this README.

## Resources

- [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Selection sort](https://en.wikipedia.org/wiki/Selection_sort)
- [Quicksort](https://en.wikipedia.org/wiki/Quicksort) (multi-way partitioning)
- [Bucket sort](https://en.wikipedia.org/wiki/Bucket_sort) (the idea behind chunks)
- [Inversion](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))
  (the disorder is the number of inversions divided by the number of pairs)
- T. H. Cormen et al., *Introduction to Algorithms* (asymptotic notation, sorting)
- D. E. Knuth, *The Art of Computer Programming, Vol. 3: Sorting and Searching*

### AI usage

AI (Claude, by Anthropic) was used for these tasks:

- explaining the subject and comparing candidate algorithms with small simulations
  (operation counts on 100 and 500 random numbers),
- writing the code of `sort.h`, `main.c`, `parse.c`, `stack.c`, `ops.c`, `bench.c`,
  `sort_simple_medium.c` and `sort_complex.c`, fixing the `Makefile` and writing this README,
- writing the test scripts (random inputs, error cases, valgrind) used to check the program;
  they are not part of the submission.
