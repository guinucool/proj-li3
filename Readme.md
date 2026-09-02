# RideShare Analytics Engine in C

A command-line analytics engine written in C for processing and querying
ride-sharing data.

The application imports users, drivers, and rides from CSV files into custom
in-memory data structures. It provides nine analytical queries and supports
both an interactive interface and automated batch execution.

## Features

- CSV parsing and data validation
- Interactive command-line interface
- Batch execution from a command file
- Nine analytical queries
- Custom dynamic hash maps and linked lists
- Indexes organized by user, driver, city, and date
- Pagination for query results
- Performance-testing executable
- Explicit memory management and cleanup

## Project structure

```text
.
├── Readme.md
└── trabalho-pratico/
    ├── includes/
    │   ├── io/             # Parsing and user-interface headers
    │   ├── structs/        # Data-structure headers
    │   ├── queries.h
    │   └── utils.h
    ├── src/
    │   ├── io/             # Parser, interpreter, pagination, and UI
    │   ├── queries/        # Implementations of queries 1–9
    │   ├── structs/        # Users, drivers, rides, maps, lists, and dates
    │   ├── main.c
    │   ├── test.c
    │   └── utils.c
    ├── Resultados/         # Batch-query output
    ├── Makefile
    ├── relatorio-fase1.pdf
    └── relatorio-fase2.pdf
```

## Requirements

To compile the project, you need:

- GCC or another compatible C compiler
- GNU Make
- A Unix-like environment such as Linux, macOS, or WSL

## Building

Clone the repository and enter the project directory:

```bash
git clone https://github.com/guinucool/rideshare-analytics-um.git
cd rideshare-analytics-um/trabalho-pratico
make
```

This creates two executables:

- `programa-principal` — main interactive and batch application
- `programa-testes` — test and performance executable

## Dataset

The application expects a directory containing these files:

```text
dataset/
├── users.csv
├── drivers.csv
└── rides.csv
```

The three files are loaded automatically when the application starts.

The dataset is not included in this repository.

## Usage

### Interactive mode

Run the program without arguments:

```bash
./programa-principal
```

The application asks for the path to the dataset:

```text
Caminho até ao dataset: /path/to/dataset
```

After loading the files, it displays an interactive menu from which the
available queries can be executed.

### Batch mode

Provide the dataset directory and a text file containing the queries:

```bash
./programa-principal /path/to/dataset commands.txt
```

Each command in the input file is interpreted and executed in order. The
generated results are written to the `Resultados/` directory.

### Tests

Run the test executable with:

```bash
./programa-testes
```

## Available queries

The engine implements nine queries covering operations such as:

- Looking up user or driver profiles
- Ranking drivers and users
- Calculating average prices and trip distances
- Filtering rides by city and date interval
- Comparing driver activity using demographic criteria
- Selecting and ordering rides within a date range

See [`includes/queries.h`](trabalho-pratico/includes/queries.h) and
[`src/queries/`](trabalho-pratico/src/queries/) for the interfaces and
implementations.

## Implementation

The program does not rely on an external database. CSV records are parsed and
stored in purpose-built data structures, including:

- Dynamic hash maps
- Linked lists
- Date-based maps
- City indexes
- User, driver, and ride abstractions

A global structure owns the indexes required by the query engine and releases
their allocated memory before the program exits.

## Cleaning the build

Remove generated object files and executables with:

```bash
make clean
```

## Documentation

The original project reports are available in:

- [`relatorio-fase1.pdf`](trabalho-pratico/relatorio-fase1.pdf)
- [`relatorio-fase2.pdf`](trabalho-pratico/relatorio-fase2.pdf)

## Academic context

This project was developed for the **Laboratórios de Informática III (LI3)**
course. Its main goals were to apply modular C programming, data abstraction,
efficient data structures, dataset validation, query processing, and
performance analysis.

## License

No license is currently specified. Unless a license is added, the source code
remains protected by standard copyright rules.
