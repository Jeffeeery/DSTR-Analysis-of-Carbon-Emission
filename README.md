# DSTR-Analysis-of-Carbon-Emission

# Work Distribution
***Member 1 [BAN] — Core Data Structures + CSV Loader + Age Group Categorization

Define shared Resident struct (ID, age, transport, distance, emission, age group)
Write CSV file reader/parser for all 3 datasets
Build custom ResidentArray class (no <vector>)
Build ResidentList Singly Linked List class (no <list>)
Compute monthlyEmission and assign ageGroup on data load
Bucket residents into 5 age groups: 6–17, 18–25, 26–45, 46–60, 61–100
Find most preferred transport mode per age group
Calculate total & average emissions per age group
Display age group results in formatted console tables
Write main menu skeleton for both programs

***Member 2 [EV] — Carbon Emission Analysis
Apply formula: Monthly Emission = Daily Distance × Emission Factor × Avg Days/Month
Calculate total emissions per dataset (City A, B, C)
Calculate total emissions per transport mode
Display all results as text-based console tables

***Member 3 [WT] — Sorting Experiments (Both Programs)
Implement Bubble Sort + Merge Sort on Array
Implement Insertion Sort + Selection Sort on Linked List
Sort by: Age / Daily Distance / Monthly Carbon Emission
Display sorted results in formatted console tables
Compare sorting performance between Array and Linked List

***Member 4 [WK] — Searching Experiments (Both Programs)
Array: Linear Search (unsorted) + Binary Search (sorted)
Linked List: Linear Search (unsorted) + Ordered Traversal Search (sorted)
Search by: age group / transport mode / distance threshold
Display matching records in table + comparisons count

***Member 5 [EEE] — Performance Analysis
Record execution time for all sorting & searching operations
Estimate memory usage for Array vs Linked List
Discuss when each data structure performs better with justification

***[ALL] — Insights & Recommendations (everyone contributes)
Analyse findings across all 3 cities
Suggest transport policies for city planners based on emission data
Each member contributes findings from their own section

# File Type
.h (header)	  Declares what exists — function signatures, class definitions, structs, enums

.cpp (source)	Defines how it works — the actual code/logic

# Timeline
Week 6	Member 1 [BAN] completes resident.h, csvloader, array/LL classes. All others begin their modules.

Week 7	Member 2 [EV] & 3 [WT] finish sorting. Member 4 starts searching. Member 5 starts analysis.

Week 8	Member 4 [WK] finishes searching + timing. Member 5 [EEE] finishes analysis + recommendations.

Week 9	Full integration — plug all modules into both main programs. Fix bugs together.

Week 9 (end)	Record video (max 30 min, each member ≤5 min). Member 5 [EEE] finalizes report.

Week 10 Mon 5pm	Submit ZIP + MP4 + DOCX.
