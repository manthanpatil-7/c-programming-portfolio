# C Programming Portfolio

## Manthan Sachin Patil

Computer Engineering (Minor in Biology) · Stony Brook University · Expected May 2029

[LinkedIn](https://www.linkedin.com/in/manthan-patil-76abb9395/) · [Email](mailto:manthansachin.patil@stonybrook.edu) · [GitHub profile](https://github.com/manthanpatil-7)

## About Me

I'm a Computer Engineering major with a Biology minor at Stony Brook
University, working at the intersection of systems-level programming and
machine learning for the life sciences.

My main independent project is **DisorderForge**, a research effort on
predicting intrinsically disordered protein regions using protein language
models (ESM-2, SaProt). It spans the full research stack — dataset
construction with homology-aware splits, ensemble architectures, LoRA
fine-tuning, and rigorous benchmarking against published CAID methods — and
I'm working toward publication-quality results.

Alongside that, I build a foundation in low-level engineering: small,
well-tested C programs (from pointer-level utilities to a persistent
command-line banking application), digital logic design (FSMs, timing
analysis, breadboard implementations with 74-series ICs), and clean,
modular code I can fully explain.

I'm seeking internship opportunities in software, machine learning, and
embedded systems — with a particular interest in computing applied to
biology.

## Technical Skills

- **Languages:** C, Python
- **ML / Scientific Computing:** PyTorch, protein language models (ESM-2,
  SaProt), LoRA fine-tuning, NumPy/Pandas, experiment tracking and
  benchmarking
- **Systems & Hardware:** Pointers and dynamic memory, file I/O and
  parsing, modular design with headers, data structures (stacks, queues),
  finite state machines, digital logic (K-maps, flip-flops, timing
  analysis), OrCAD/PSpice
- **Tools:** Git, GitHub, GitHub Actions, GCC, VS Code, Linux, LaTeX,
  Google Colab (GPU workflows)

## Currently

- 🔬 Closing the CAID3 NOX gap in DisorderForge (structure-aware pLMs,
  gradient boosting on engineered features)
- ⚙️ Deepening C and data structures fundamentals
- 🧬 Exploring where computer engineering meets molecular biology

## Featured Projects

### 1. Taylor Series Approximator

Approximates `1/(1-x)` with a configurable number of series terms and
reports the error against the exact value, validating the convergence domain
before computing.

- **Skills demonstrated:** loops, floating-point math, input validation
- **Source and details:** [`01-early-program/`](01-early-program/)

### 2. Pointer Toolkit

A self-testing collection of pointer-based array utilities — in-place
reversal, min/max via output pointers, pointer-arithmetic traversal — plus a
dynamic-memory demo with disciplined `malloc`/`free` ownership.

- **Skills demonstrated:** pointers, dynamic memory, defensive programming,
  built-in expected/actual testing
- **Source and details:** [`02-midcourse-program/`](02-midcourse-program/)

### 3. BroBank

A command-line banking application with a persistent balance, dated
transaction logging, strict validation (including overdraft protection), and
a sorted session statement — organized as modular C behind a single header
interface.

- **Skills demonstrated:** modular design, file persistence, pointer-based
  APIs, sorting, input validation
- **Source and details:** [`03-brobank/`](03-brobank/)

## What I Learned

This course took me from single-file programs built on loops and
conditionals to modular C applications with header interfaces, file
persistence, and pointer-based APIs. The biggest shift was learning to treat
every input and pointer as untrusted — validating domains before computing,
checking every `fopen` and `malloc`, and keeping ownership of allocated
memory explicit. Rebuilding BroBank week after week showed me how a design
survives change: logic placed behind a clean interface was easy to extend,
while logic left in `main()` was not. Next, I want to go deeper into data
structures — stacks, queues, and graph traversal — and apply them in larger
projects.

## Repository Guide

Each project folder contains:

- source code written by me;
- a short project description;
- clear compile and run instructions;
- a sample input/output when useful; and
- a brief explanation of design choices and testing.

A module diagram of BroBank is in [`diagrams/`](diagrams/).

## Acknowledgments

All programs in this portfolio were developed as coursework for ESE 124
(Programming Fundamentals) at Stony Brook University. Consistent with the
course's AI policy, Claude (Anthropic) provided limited assistance with
logic checks and code review during development.
