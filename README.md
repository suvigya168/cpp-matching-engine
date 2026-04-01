# cpp-matching-engine
A high-performance C++ simulation of a financial limit order book (LOB) utilizing price-time priority matching logic and STL containers.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
Overview :
This repository contains a terminal-based simulation of a financial matching engine. It replicates the core "Price-Time Priority" logic used by global stock exchanges to match buy and sell orders.

Technical Architecture ;
- Language: C++
- Concepts: Object-Oriented Programming (OOP), Encapsulation, STL Containers.
- Data Structures: std::vector for order storage and std::sort for priority management.


How it Works :
- Ingestion: Orders are created as objects with unique IDs, tickers, sides (Buy/Sell), prices, and quantities.

      Priority Sorting: >     * Bids (Buy): Sorted in descending order (highest price gets priority).

- Asks (Sell): Sorted in ascending order (lowest price gets priority).
- Execution: The engine matches a Buy order with a Sell order whenever the Buy Price >= Sell Price.
- Partial Fills: The system automatically handles orders where the matched quantity is less than the total order size, maintaining the remainder in the book.
  
