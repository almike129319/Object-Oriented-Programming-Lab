# Object-Oriented Programming Lab

This repository contains a collection of C++ projects developed as part of an Object-Oriented Programming Lab course. Each lab demonstrates various OOP principles, data structures, and algorithms through practical applications.

## Project Overview

This project showcases a range of object-oriented programming concepts, including:

-   **Classes and Objects:** Fundamental building blocks for encapsulating data and behavior.
-   **Inheritance and Polymorphism:** Demonstrating code reusability and flexible design through base and derived classes, virtual functions, and operator overloading.
-   **Templates:** Implementing generic programming for type-independent data structures and algorithms.
-   **Data Structures:** Practical applications of vectors, maps, unordered maps, and custom data structures like min-heaps and priority queues.
-   **Algorithms:** Implementation of various algorithms such as sorting (merge sort, quick sort, custom comparators, topological sort), graph traversal (BFS, DFS for cycle detection and SCCs), dynamic programming (for LIS, Hamiltonian paths, maximum profit scheduling, and max hype paths), divide and conquer (for closest pair, polynomial multiplication, inversion counting, matrix exponentiation), and number theory algorithms (sieve, divisor calculations).
-   **Operator Overloading:** Enhancing readability and expressiveness of code for custom types.

The labs are designed to solve specific problems, ranging from simulating complex systems to optimizing resource allocation and pathfinding.
Each lab diectory contains cpp code and problem-statement doc for better understanding of problem
### Lab 1: Library Management System

-   **Description:** A system to manage books and members, allowing for adding books, registering members, borrowing, and returning books.
-   **Key OOP Concepts:** Multiple constructors, utility methods for interactions.

### Lab 2: Graph Datastructure Implementation

-   **Description:** Implements a `Graph` class with overloaded operators for graph union (`+`), intersection (`-`), and complement (`!`). It also supports adding/removing edges, checking reachability (BFS), and printing the graph.
-   **Key OOP Concepts:** Operator overloading, graph representation (adjacency list/matrix).
-   **Key Algorithms:**
    -   Breadth-First Search (BFS) for reachability checks.

### Lab 3: Avenger Battle Simulation

-   **Description:** Simulates battles between Avengers. It includes `QNS` (Quantum Nano Suit) class with attributes like power, durability, energy, and heat, and overloaded operators for various interactions. The `avengers` class uses `QNS` for suits, enabling attacks, suit upgrades, and repairs. The `Battle` class manages heroes, enemies, and battle logs.
-   **Key OOP Concepts:** Class composition, complex object interactions, state management.

### Lab 4: Number Theory & Utilities

-   **Description:** This lab provides utility classes for various mathematical operations. `currency_sorter` sorts a vector of serial numbers using Quick Sort. `fibinocci_generator` calculates the nth Fibonacci number using matrix exponentiation. `prime_calculator` uses a segmented sieve to find primes within a range or their sum. `number_analyser` (inheriting from `prime_calculator`) checks if a number is square-free, counts its divisors, and calculates the sum of its divisors.
-   **Key OOP Concepts:** Functors (`currency_sorter`), inheritance (`number_analyser`), mathematical algorithms (Quick Sort, Matrix Exponentiation, Sieve of Eratosthenes, Number Theory properties).
-   **Key Algorithms:**
    -   Quick Sort
    -   Matrix Exponentiation (for Fibonacci series)
    -   Segmented Sieve of Eratosthenes
    -   Divisor Counting and Summation

### Lab 5: Divide and Conquer (Closest Pair of Points, Inversions)

-   **Description:** Contains classes `Comparator`, `tupple4`, `quantumboard`, and `ICF_players`. It implements functionalities such as sorting rows of a 2D board (using a custom `Comparator` and merge sort), counting inversions in a linear representation of the board using divide and conquer, and finding the closest pair of points among players' coordinates.
-   **Key OOP Concepts:** Custom comparators, divide and conquer paradigm, geometric algorithms.
-   **Key Algorithms:**
    -   Merge Sort
    -   Divide and Conquer (for Closest Pair)
    -   Inversion Counting

### Lab 6: Graph Algorithms

-   **Description:** This lab defines a base `graph_algorithm` class and derived classes for specific graph problems: `is_cycle` (detects cycles using DFS), `indep_comp` (finds strongly connected components using Kosaraju's algorithm and builds a condensed graph), `valid_order` (performs topological sort using Kahn's algorithm with a priority queue), and `max_hype` (calculates the maximum hype score path in the condensed graph using dynamic programming). It demonstrates polymorphism for different graph algorithms and their respective query and print methods.
-   **Key OOP Concepts:** Polymorphism, inheritance, graph algorithms, custom comparators.
-   **Key Algorithms:**
    -   Depth-First Search (DFS) for cycle detection
    -   Kosaraju's Algorithm for Strongly Connected Components (SCCs)
    -   Kahn's Algorithm for Topological Sort
    -   Dynamic Programming on Directed Acyclic Graphs (DAGs)

### Lab 7: Polynomial Operations (using Templates)

-   **Description:** Implements operations on polynomials using C++ templates to support different data types (integers, floats, complex numbers, and strings). It includes classes for `Complex` numbers, `polynomial` with overloaded multiplication, and `polymul`, `evaluation`, and `poly_dif` for multiplication, evaluation, and differentiation of polynomials respectively
-   **Key OOP Concepts:** Templates, operator overloading for mathematical operations, complex number arithmetic.
-   **Key Algorithms:**
    -   Karastuba's multiplication (for Polynomial Multiplication)

### Lab 8: Castle Traversal

-   **Description:** Implements a shortest path algorithm (Dijkstra's-like) within a "castle" represented as a graph of "rooms" and "connections." It utilizes a custom `min_heap` template class to manage priorities. The `tup3` class is used to store distance, node pointer, and level information for the priority queue. The `castle` class handles graph creation and the shortest path calculation with a specific condition on the path's "level" (length).
-   **Key OOP Concepts:** Custom data structures (min-heap), template classes.
-   **Key Algorithms:**
    -   Dijkstra's Shortest Path Algorithm (or a variant)

### Lab 9: Card-Game(LIS, Greedy)

-   **Description:** Involves a card game where cards have different geometric shapes (triangle, square, rectangle) and areas. It uses polymorphism with a base `card` class and derived classes. The `card_organiser` class manages a collection of these cards, implementing logic to find the longest increasing subsequence (LIS) based on the area of the cards using a variation of patience sorting. It also handles input/output of card objects using overloaded stream operators.
-   **Key OOP Concepts:** Polymorphism, virtual functions, abstract base classes, operator overloading for I/O.
-   **Key Algorithms:**
    -   Longest Increasing Subsequence (LIS) using  dynamic programming approach
 
### Lab 10: Kingdom Management

-   **Description:** Models a kingdom with a hierarchy of "sentinels" (military personnel). It uses a base `sentinel` class and derived classes (`senapati`, `dandanayaka`, `chaturangini`) with different ranks and corresponding logic for `count_high_ranked`. A `comp` functor defines a custom sorting order for sentinels based on rank and ID. The `kingdom` class manages these sentinels, including their interconnections as a graph, and calculates the minimum number of active sentinels required to monitor all roads (likely a minimum vertex cover problem solved using DFS). It also supports sorting sentinels and querying the number of higher-ranked sentinels than a given sentinel.
-   **Key OOP Concepts:** Inheritance hierarchy, custom functors, graph traversal, minimum vertex cover (or similar graph optimization problem).
-   **Key Algorithms:**
    - Min-Vertex Cover for trees using dynamic programming based approach

### Lab 11: Island Traversals

-   **Description:** Defines an `Island` base class with derived classes for `Rectangle`, `Triangle`, and `Circle` shapes. Each island has an ID, center coordinates, and a "radius" (maximum distance from the center to any point on the island). The lab calculates if islands overlap. The `Group_of_islands` class builds an adjacency list based on overlapping islands and then uses dynamic programming with bitmasking to find the longest path that visits each island at most once (likely a Hamiltonian path or longest simple path problem variation). It outputs "YES" if all islands can be visited and "NO" otherwise, along with the length of the longest path and the path itself.
-   **Key OOP Concepts:** Polymorphism for geometric shapes, spatial relationships, graph representation.
-   **Key Algorithms:**
    -   Dynamic Programming with Bitmasking (for Hamiltonian Path / Traveling Salesperson Problem variant)

### Lab 12: Event Management

-   **Description:** Implements an event management system using polymorphism. A base `Event` class has derived classes `Concert`, `TheaterShow`, and `Wedding`, each with its own profit calculation logic. The `EventOrganiser` class reads multiple events, sorts them by start time, and then uses dynamic programming to find the maximum total profit from a non-overlapping schedule of events. It employs a `Comparator` functor for sorting and `lower_bound` for efficient searching of compatible events.
-   **Key OOP Concepts:** Polymorphism for different event types, profit calculation logic, greedy algorithms/dynamic programming (weighted interval scheduling).
-   **Key Algorithms:**
    -   Dynamic Programming (for Weighted Interval Scheduling)
    -   Sorting (using custom comparator)
    -   Binary Search (`std::lower_bound`)
