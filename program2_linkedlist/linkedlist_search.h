// Member 4 - [WK]
// program2_linkedlist/linkedlist_search.h - Search declarations for Linked List program

#ifndef LINKEDLIST_SEARCH_H
#define LINKEDLIST_SEARCH_H

#include "linkedlist.h"
#include "../program1_array/array_search.h"  // reuse SearchCriteria, SearchResult

// Linear Search on unsorted linked list
SearchResult linearSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword);

// Ordered Traversal Search on sorted linked list
// Stops early when traversal passes the target range
SearchResult orderedSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword);

// Print matched residents from linked list as a formatted table
void printSearchResultsLL(const ResidentList& list, const SearchResult& result,
                          SearchCriteria criteria, const char* keyword);

// Print performance comparison: Linear vs Ordered Traversal
void printSearchComparisonLL(const SearchResult& linear, const SearchResult& ordered);

#endif // LINKEDLIST_SEARCH_H
