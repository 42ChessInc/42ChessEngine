# Aleph

Aleph is a work-in-progress chess engine written in C, designed to run on Linux. It is being developed with the eventual goal of becoming a fully UCI-compatible engine.

The project is currently in the early stages of development, focusing on implementing core chess logic and search algorithms.

-----

## Features

  * Bitboard representation for a fast and efficient board state
  * Alpha-Beta search algorithm
  * Material counting
  * Piece-square tables for positional evaluation

-----

## Building from Source

To build the engine, clone the repository and use the provided Makefile:

```bash
# Build the engine
make aleph
```

-----

## Usage

The engine currently works by taking a single FEN string as a command-line argument and processing that position.

```bash
./aleph "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
```

-----

## Dependencies

To build and run Aleph, you will need:

  * `gcc` (or any standard C compiler)
  * `make`

-----

## Contributing

Contributions are welcome.

  * Feel free to open an issue or submit a pull request.
  * You can also contact me via the links on my GitHub profile.
