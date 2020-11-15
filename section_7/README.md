# 7.1 The sushi bar problem
This problem was inspired by a problem proposed by Kenneth Reek^[1 Kenneth A. Reek. Design patterns for semaphores. In ACM SIGCSE, 2004]. Imagine a sushi bar with 5 seats. If you arrive while there is an empty seat, you can take a seat immediately. But if you arrive when all 5 seats are full, that means that all of them are dining together, and you will have to wait for the entire party
to leave before you sit down.

Puzzle: write code for customers entering and leaving the sushi bar that enforces these requirements.