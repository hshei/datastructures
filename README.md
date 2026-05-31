# Data Structures Library
A small C data structures library, other data structures will be added as time goes.
- Vector: a dynamic array with multiple functionalities.

All the data structures will have a separate test file on the `/test` folder, in which you can run using `./build/desired_test`


## Build

```sh
cd '/Users/hassansheikh/Desktop/C/Data Structures'
make
```

This produces:
- `build/Vector.o`
- `build/libdatastructures.a`
- `build/vector_test`

## Run tests

```sh
./build/vector_test
```

## Use as a library

Compile once and link into your program:

```sh
cc -Wall -Wextra -std=c11 -Iinclude -c src/Vector.c -o build/Vector.o
ar rcs build/libdatastructures.a build/Vector.o
cc -Wall -Wextra -std=c11 -Iinclude main.c -Lbuild -ldatastructures -o main
```

Use `#include "datastructures.h"` in your own code.

## Publish to GitHub

1. Initialize a Git repository:
   ```sh
git init
   git add .
   git commit -m "Initial vector library"
   ```
2. Create a GitHub repo and push:
   ```sh
gh repo create <username>/vector-lib --public --source=. --remote=origin
   git push -u origin main
   ```

If you do not have the GitHub CLI, create the repo in the GitHub web UI and push with:

```sh
git remote add origin https://github.com/<username>/<repo>.git
git branch -M main
git push -u origin main
```
