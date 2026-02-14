# DRMO Security Checker

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![Language: C](https://img.shields.io/badge/language-C99-blue.svg)
![Status: In Development](https://img.shields.io/badge/status-in%20development-orange.svg)

A command-line security tool that validates PEXA property settlement files to detect fraud, data corruption, and formatting errors in real estate transactions.

---

## Purpose

When estate lawyers handle property settlements through PEXA (Property Exchange Australia's electronic platform), they receive digital settlement files containing critical transaction data—buyer/seller information, property details, financial amounts, and authority signatures. Manual verification of these files is time-consuming, error-prone, and leaves room for fraudulent manipulation.

**DRMO Security Checker** automates the validation process by programmatically analyzing settlement files for integrity violations, suspicious patterns, and compliance with PEXA formatting standards.

This tool helps legal professionals quickly identify:

- Tampered or corrupted files (via checksum verification)
- Amount discrepancies between sections
- Duplicate entries that may indicate fraud
- Malformed data structures that could cause processing errors

Unlike manual inspection, this tool provides systematic, repeatable validation with detailed error reporting—enabling lawyers to confidently proceed with settlements or flag issues for investigation.

---

## Features

- **File Format Validation** – Verifies settlement files conform to PEXA XML/CSV structure specifications
- **Checksum Verification** – Calculates and compares file checksums to detect tampering or corruption
- **Suspicious Pattern Detection** – Identifies anomalies like amount mismatches, duplicate transaction IDs, or unusual field values
- **Comprehensive Error Reporting** – Outputs detailed PASS/FAIL reports with line-by-line findings
- **Cross-Platform Support** – Runs on Windows, Linux, and macOS
- **Zero Dependencies** – Uses only standard C library (no external packages required)

---

## Technical Specifications

| Specification | Details |
| -------------- | --------- |
| **Language** | C (ANSI C99 standard) |
| **Compiler** | GCC 4.8+ or Clang 3.5+ |
| **Platform** | Cross-platform (Windows/Linux/macOS) |
| **Dependencies** | Standard C library only |
| **File Types** | PEXA XML and CSV settlement formats |

---

## Installation

### Clone the Repository

```bash
git clone https://github.com/andrefabre/drmo-security-checker.git
cd drmo-security-checker

```

## Compile the Program

**On Windows (MinGW/WSL):**

```bash
gcc -std=c99 -o build/drmo-checker src/main.c src/file_reader.c src/validator.c -Wall -Wextra
```

**On Linux/macOS:**

```bash
gcc -std=c99 -o build/drmo-checker src/main.c src/file_reader.c src/validator.c -Wall -Wextra
```

## Run the Executable

```bash
./build/drmo-checker tests/sample_settlement.xml
```

## Usage

Basic Command

```bash
./drmo-checker <filepath>
```

**Example:**

```bash
./drmo-checker settlement_20260212.xml
```

Expected Output

```bash
DRMO Security Checker v1.0
==========================
File: settlement_20260212.xml
Size: 45,231 bytes

[✓] Format validation: PASS
[✓] Checksum verification: PASS
[✗] Suspicious patterns detected:
    - Line 87: Purchase amount mismatch ($450,000 vs $455,000)
    - Line 142: Duplicate transaction ID (TXN-2026-00451)

RESULT: VALIDATION FAILED (2 issues detected)
```

Exit Codes

Code Meaning
0 File validation passed (no issues)
1 Validation failed (errors/suspicious patterns detected)
2 File read error (file not found, permissions, etc.)
3 Invalid command-line arguments

drmo-security-checker/
├── src/              # Source code (.c and .h files)
├── docs/             # Documentation and design notes
├── tests/            # Test files and sample PEXA settlement files
├── build/            # Compiled executables (gitignored)
├── README.md         # This file
├── .gitignore        # Git ignore rules
└── LICENSE           # MIT License

**Development Roadmap**
Phase Timeline Status

Phase 1: Repository setup, basic file I/O, README 🟡 IN PROGRESS
Phase 2: File format validation, header parsing ⚪ Pending
Phase 3: Checksum verification, data integrity checks ⚪ Pending
Phase 4: Suspicious pattern detection, error reporting ⚪ Pending
Phase 5: Testing, documentation, demo preparation ⚪ Pending
Target Completion: Q1 2026 (50 hours over 10 weeks)

**Educational Context**
This project is developed as part of Murdoch University's Bachelor of IT program, specifically applying concepts from:

ICT167 - Principles of Computer Science: Problem-solving methodologies, algorithm design
Foundations of Programming (Chapters 3-4):
Top-down design with functions
Selection structures (if/else, switch statements)
Modular programming principles

**Learning Objectives:**

Master C programming fundamentals (file I/O, string processing, memory management)
Apply security-first development practices
Build real-world tools addressing industry problems (legal tech/property settlements)
Practice software engineering workflows (version control, documentation, testing)

**Contributing**
This is an educational project, but feedback and suggestions are welcome! If you notice bugs or have ideas for improvements:

- Open an issue describing the problem/suggestion
- Fork the repository and create a feature branch
- Submit a pull request with clear descriptions of changes

**Author & License**
Author: Andre Fabre
GitHub: @andrefabre
LinkedIn: Andre Fabre
License: MIT License - see LICENSE file for details

**Acknowledgments**
Murdoch University for curriculum framework
PEXA for electronic settlement platform specifications
"Problem Solving and Program Design in C" (textbook) for foundational concepts
Last Updated: February 14, 2026
Version: 0.1.0 (Phase 1 - Initial Development)
