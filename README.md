# LzwOptimizingProject_BinaryTree

LzwOptimizing

We use a binary tree instead of a hash table to reduce memory overhead.

Encode structure:
```C++
typedef struct {
  char	rWord;
  int	rCode;		//represents the corresponding encoding of the character/string in the hash table
  int	rChild;		//initially -1, if there are children, it is the sequence number of the next one-dimensional array in the two-dimensional arra
}
```


Decode structure:
```C++
typedef struct {
  char	rWord;
  int	rParent = -2;
}
```
