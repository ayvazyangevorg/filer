# filer

filer is a small terminal utility for locating and reporting
application-related files on Debian-based systems.

It scans the filesystem, matches paths by name or pattern, classifies
results, and aggregates disk usage. The primary use case is identifying
residual files left behind after manual installation or incomplete
package removal.

The program is written in C/C++ and designed to be simple, predictable,
and dependency-light.

------------------------------------------------------------------------

## Purpose

Package managers remove files they install. They do not remove:

-   Manually extracted archives
-   Configuration files outside package ownership
-   Cache directories
-   User-local data
-   Build artifacts
-   Leftover directories created by applications

filer exists to locate those artifacts and report their total footprint.

It does not modify or delete anything.

------------------------------------------------------------------------

## Features

-   Recursive filesystem scan
-   Name and pattern-based matching
-   File size aggregation
-   Basic classification (config, cache, binary, other)
-   Deterministic terminal output
-   No runtime dependencies beyond standard system libraries

------------------------------------------------------------------------

## Non-Goals

-   No GUI
-   No background daemon
-   No database indexing
-   No package manager integration
-   No automatic deletion

filer reports. The user decides.

------------------------------------------------------------------------

## Build

Requirements:

-   CMake
-   g++
-   Debian-based system (for packaging)

Build locally:

    mkdir build
    cd build
    cmake ..
    make

Binary will be located at:

    build/filer

------------------------------------------------------------------------

## Install (Debian Package)

If building with Debian packaging:

    debuild -us -uc
    sudo dpkg -i ../filer_0.1.0-1_amd64.deb

After installation:

    filer <pattern>

------------------------------------------------------------------------

## Usage

Basic usage:

    filer viber

Pattern example:

    filer "*.txt"

The program outputs:

-   Matching file paths
-   Individual file sizes
-   Total matched files
-   Total aggregated size

------------------------------------------------------------------------

## Design

src/ main.cpp scanner.cpp matcher.cpp classifier.cpp aggregator.cpp

-   scanner: filesystem traversal
-   matcher: pattern filtering
-   classifier: file categorization
-   aggregator: size computation and totals
-   main: CLI coordination

The implementation favors correctness and clarity over premature
optimization.

------------------------------------------------------------------------

## Security

-   No elevated privileges required
-   No filesystem modification
-   No network communication
-   No telemetry

The tool performs read-only traversal.

------------------------------------------------------------------------

## License

Add your chosen license here (GPLv2, GPLv3, MIT, etc.).

------------------------------------------------------------------------

## Status

Early-stage but functional. Designed for extension.
