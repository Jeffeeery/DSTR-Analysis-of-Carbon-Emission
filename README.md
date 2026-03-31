# DSTR — Analysis of Carbon Emission

## About This Project
A C++ console application that analyses **carbon emissions** from residents across 3 Malaysian cities (City A, B, C).  
The project is built **twice** — once using a custom **Array** data structure, and once using a custom **Singly Linked List** — to compare their performance in sorting and searching.

> **No STL containers allowed.** All data structures are built from scratch.

- **Course:** CT077-3-2-DSTR (Data Structures)
- **Institution:** Asia Pacific University (APU)
- **Submission Deadline:** Week 10, Monday 5:00 PM

---

## Project Structure
```
Assignment1_2026/
├── shared/                    ← Shared across both programs
│   ├── resident.h             ← Resident struct definition        [BAN]
│   ├── csvloader.h/.cpp       ← CSV file reader/parser            [BAN]
│   └── analysis.h/.cpp        ← Emission analysis functions       [EV]
│
├── program1_array/            ← Array-based implementation
│   ├── arraylist.h            ← ResidentArray class               [BAN]
│   ├── array_sort.h/.cpp      ← Bubble Sort + Merge Sort          [WT]
│   ├── array_search.h/.cpp    ← Linear Search + Binary Search     [WK]
│   └── main_array.cpp         ← Main menu for Program 1           [ALL]
│
└── program2_linkedlist/       ← Linked List-based implementation
    ├── linkedlist.h           ← Node struct + ResidentList class   [BAN]
    ├── linkedlist_sort.h/.cpp ← Insertion Sort + Selection Sort   [WT]
    ├── linkedlist_search.h/.cpp ← Linear + Ordered Traversal      [WK]
    └── main_linkedlist.cpp    ← Main menu for Program 2           [ALL]
```

---

## How to Compile & Run

### Requirements
- C++ compiler (g++ recommended, C++11 or later)
- Dataset CSV files placed in the project root

### Program 1 — Array
```bash
g++ program1_array/main_array.cpp shared/csvloader.cpp shared/analysis.cpp -o program1
./program1
```

### Program 2 — Linked List
```bash
g++ program2_linkedlist/main_linkedlist.cpp shared/csvloader.cpp shared/analysis.cpp -o program2
./program2
```

---

## Carbon Emission Formula
```
Monthly Emission = Daily Distance × Emission Factor × Avg Days Per Month
```
Age groups are categorised as:
| Age Range | Group |
|-----------|-------|
| 6 – 17    | Children / Teens |
| 18 – 25   | Young Adults |
| 26 – 45   | Working Adults |
| 46 – 60   | Middle-Aged |
| 61 – 100  | Seniors |

---

## Work Distribution

### Member 1 [BAN] — Core Data Structures + CSV Loader + Age Group Categorization
- Define shared `Resident` struct (ID, age, transport, distance, emission, age group)
- Write CSV file reader/parser for all 3 datasets
- Build custom `ResidentArray` class (no `<vector>`)
- Build `ResidentList` Singly Linked List class (no `<list>`)
- Compute `monthlyEmission` and assign `ageGroup` on data load
- Bucket residents into 5 age groups: 6–17, 18–25, 26–45, 46–60, 61–100
- Find most preferred transport mode per age group
- Calculate total & average emissions per age group
- Display age group results in formatted console tables
- Write main menu skeleton for both programs

### Member 2 [EV] — Carbon Emission Analysis
- Apply formula: `Monthly Emission = Daily Distance × Emission Factor × Avg Days/Month`
- Calculate total emissions per dataset (City A, B, C)
- Calculate total emissions per transport mode
- Display all results as text-based console tables

### Member 3 [WT] — Sorting Experiments (Both Programs)
- Implement **Bubble Sort + Merge Sort** on Array
- Implement **Insertion Sort + Selection Sort** on Linked List
- Sort by: Age / Daily Distance / Monthly Carbon Emission
- Display sorted results in formatted console tables
- Compare sorting performance between Array and Linked List

### Member 4 [WK] — Searching Experiments (Both Programs)
- Array: **Linear Search** (unsorted) + **Binary Search** (sorted)
- Linked List: **Linear Search** (unsorted) + **Ordered Traversal Search** (sorted)
- Search by: age group / transport mode / distance threshold
- Display matching records in table + comparison count

### Member 5 [EEE] — Performance Analysis
- Record execution time for all sorting & searching operations (using `<chrono>`)
- Estimate memory usage for Array vs Linked List
- Discuss when each data structure performs better with justification

### All Members [ALL] — Insights & Recommendations
- Analyse findings across all 3 cities
- Suggest transport policies for city planners based on emission data
- Each member contributes findings from their own section

---

## File Type Reference
| Extension | Purpose |
|-----------|---------|
| `.h` (header) | Declares **what exists** — function signatures, class definitions, structs, enums |
| `.cpp` (source) | Defines **how it works** — the actual code and logic |

---

## Group Members
| Tag | Role |
|-----|------|
| [BAN] | Member 1 — Core Structures & CSV Loader |
| [EV]  | Member 2 — Carbon Emission Analysis |
| [WT]  | Member 3 — Sorting (Array + Linked List) |
| [WK]  | Member 4 — Searching (Array + Linked List) |
| [EEE] | Member 5 — Performance Analysis |

---

## Timeline
| Week | Tasks |
|------|-------|
| Week 6 | [BAN] completes `resident.h`, csvloader, ResidentArray, ResidentList. All others begin their modules. |
| Week 7 | [EV] finishes emission analysis. [WT] finishes sorting on both programs. [WK] starts searching. |
| Week 8 | [WK] finishes searching. [EEE] finishes performance analysis + recommendations. |
| Week 9 | Full integration — plug all modules into both main programs. Fix bugs together. |
| Week 9 (end) | Record video (max 30 min, each member ≤ 5 min). [EEE] finalises report. |
| **Week 10 Mon 5PM** | **Submit ZIP + MP4 + DOCX** |
