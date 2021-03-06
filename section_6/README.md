# 6.1 The search-insert-delete problem

This one is from Andrews’s Concurrent Programming<sup>[1](#1)</sup>.

Three kinds of threads share access to a singly-linked list: searchers, inserters and deleters. Searchers merely examine the list; hence they can execute concurrently with each other. Inserters add new items to the end of the list; insertions must be mutually exclusive to preclude two inserters from inserting new items at about the same time. However, one insert can proceed in parallel with any number of searches. Finally, deleters remove items from anywhere in the list. At most one deleter process can access the list at a time, and deletion must also be mutually exclusive with searches and insertions.

Puzzle: write code for searchers, inserters and deleters that enforces this kind of three-way categorical mutual exclusion.

<br/><br/>
<a name="1">1</a>: Gregory R. Andrews. Concurrent Programming: Principles and Practice. Addison-Wesley, 1991. <br/>
