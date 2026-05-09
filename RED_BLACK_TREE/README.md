 # RED BLACK TREE (DSA Project)

📌 Overview :
--------------
This project implements a Red-Black Tree (RBT) in Data Structures using the C programming language.

A Red-Black Tree is a self-balancing Binary Search Tree (BST) in which every node contains an extra color attribute, either RED or BLACK.
The tree automatically maintains balance after insertion and deletion operations using rotations and recoloring techniques.
The balancing properties of the Red-Black Tree guarantee efficient performance for dynamic data operations such as insertion, deletion, and searching.


🚀 Features :
-------------- 
1. Insert Node
2. Delete Node
3. Search Node
4. Find Minimum
5. Find Maximum
6. Delete Minimum
7. Delete Maximum
8. Tree Printing
9. Red-Black Balancing

-------------------------------------------------------------------------------

📌 Red-Black Tree Properties :
------------------------------
1. Every node is either RED or BLACK.
2. Root node is always BLACK.
3. Red node cannot have a red child.
4. Every path from root to NULL has same black nodes.
5. NULL nodes are considered BLACK.

-------------------------------------------------------------------------------

🧠 Data Structure :
-------------------

typedef int data_t;

typedef struct tree
{
    data_t data;
    int color;

    struct tree *left;
    struct tree *right;

} tree_t;

-------------------------------------------------------------------------------

⚙️ Compilation :
----------------

Compile using:

    make

Run program:

    ./a.out

Clean files:

    make clean

-------------------------------------------------------------------------------

📖 Menu :
---------

1. Insert
2. Delete
3. Search
4. Find Minimum
5. Delete Minimum
6. Find Maximum
7. Delete Maximum
8. Print RB Tree

-------------------------------------------------------------------------------

📸 Example Tree :
------------------

                20(B)
              /       \
         2(R)          40(R)
        /    \        /     \
     1(B)  10(B)   30(B)   50(B)
             /                    \
          4(R)                   54(R)

(B) -> BLACK Node
(R) -> RED Node

-------------------------------------------------------------------------------

📄 Time Complexity :
---------------------

Insert          O(log n)
Delete          O(log n)
Search          O(log n)
Find Min/Max    O(log n)

-------------------------------------------------------------------------------

👨‍💻 Author :
-----------

Saiddivakar Busala

-------------------------------------------------------------------------------

📄 License :
-----------
This project is open-source and free to use for learning purposes.

