# Wind Tunnel Lift Coefficient Interpolator

A C++ command-line program that estimates the coefficient of lift for a given
angle of attack by linearly interpolating wind tunnel test data.

## Project Description

Wind tunnel testing produces discrete measurements of lift coefficient at
specific angles of attack. This program takes that raw data, sorts it if
needed, and uses **linear interpolation** to estimate the lift coefficient at
any angle of attack that falls within the tested range — even if that exact
angle was never measured.

## Features

- **Data loading** — reads angle of attack / coefficient of lift pairs from a
  plain-text data file
- **Automatic sorting** — detects if the input data is out of order and
  sorts it (angle ascending) using selection sort before interpolating
- **Linear interpolation** — computes the lift coefficient for any angle
  within the bounds of the dataset, returning an exact match directly when
  the angle was already tested
- **Bounds checking** — rejects angles outside the tested range with an
  error message instead of extrapolating
- **Interactive queries** — after the first result, the user can keep
  querying additional angles until they choose to stop

## Technologies Used

- **Language:** C++
- **Libraries:** C++ Standard Library (`<iostream>`, `<fstream>`, `<vector>`)
- **Data format:** plain-text `.dat` files (`angle coefficient` pairs, one
  per line)

## Files

| File | Description |
|------|-------------|
| `main.cpp` | Program source: data loading, sort check/sort, and interpolation logic |
| `tunnel1.dat` | Sample wind tunnel data, already sorted by angle |
| `tunnel2.dat` | Sample wind tunnel data, out of order (exercises the sorting path) |

## How It Works

1. The data file path is passed in as a command-line argument.
2. `readData` loads the angle/coefficient pairs into two parallel vectors.
3. `isOrdered` checks whether the angles are sorted ascending.
4. If not, `reorder` sorts both vectors together (selection sort) so the
   angle-to-coefficient mapping stays correct.
5. `interpolation` takes a user-supplied angle:
   - Returns the exact coefficient if the angle matches a tested point.
   - Otherwise finds the two nearest bracketing points and linearly
     interpolates between them.
   - Exits with an error if the angle is outside the tested range.
6. The program loops, letting the user query as many angles as they'd like.

## Build & Run

```bash
g++ -o interpolator main.cpp
./interpolator tunnel1.dat
```

Example session:

```
$ ./interpolator tunnel1.dat
5
0.4500
Yes
10
0.7920
no
```

(Enter an angle, get the interpolated coefficient, then type `yes`/`y` to
query another angle or anything else to stop.)

## Sample Data Format

Each line in a `.dat` file is an angle of attack followed by its measured
coefficient of lift:

```
-4.0 -0.182
-2.0 -0.056
0.0 0.097
...
```

`tunnel2.dat` contains the same kind of data but shuffled out of order, to
demonstrate the program's automatic sorting step.
