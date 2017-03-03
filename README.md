# Bob
###### A distant relative of Eliza - so we think.

Bob is a chatbot built using very similar principles to that of ELIZA (Weizenbaum J., 1966 [1]).

# Building Bob

To build bob, use the provided cmake file (you will need cmake installed):

```
mkdir build
cd build
cmake .. && make
```

You should, assuming this did not fail, then be able to run bob with:

```
./bob
```

# References
[1] - Weizenbaum, J., 1966. ELIZA—a computer program for the study of natural language communication between man and machine. Communications of the ACM, 9(1), pp.36-45.
