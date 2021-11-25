# Ocean's Anti-11 (Hard)

The problem statement for this one is simple: How many binary strings of length n exist which don't contain some substring b.

To come up with the solution to this problem, I leveraged how I had solved the easier version of this problem (https://open.kattis.com/problems/anti11), in which the substring is fixed to be "11". For that problem, I imagined building the string of length n by starting with a string of length 1 and incrementally lengthning one bit at a time. During this process, we can keep track of how many of the strings end in 1 and how many end in 0. For the first iteration, the string is only 1 bit long, and as such both "0" and "1" are allowed. Thus we have one string ending in 1 and one ending in 0. As we lengthen the string, all the strings that previously ended in 0 are able to be preceded by either a 1 or a 0. Meanwhile, the strings ending in 1 are only able to be preceded by a 0, as continuing a string ending in 1 with a 1 would produce the disallowed substring "11". As such, we can make an iterative scheme for updating the amount of strings ending in 1 and the amount ending in 0 in the following way:

<img src="https://latex.codecogs.com/svg.image?\textrm{zeros}_{i&plus;1}&space;=&space;\textrm{ones}_{i}&space;&plus;&space;\textrm{zeros}_{i}" title="\textrm{zeros}_{i+1} = \textrm{ones}_{i} + \textrm{zeros}_{i}" />

<img src="https://latex.codecogs.com/svg.image?\textrm{ones}_{i&plus;1}&space;=&space;\textrm{zeros}_{i}" title="\textrm{ones}_{i+1} = \textrm{zeros}_{i}" />

Now we are able to simple iterate from zeros_1 = 1, ones_1 = 1 up to any n. The total number of strings of length n are then the sum zeros_n + ones_n

With this solution from the easier problem, I tried to come up with ways of generalizing this notion of "ending in 1 or 0" to a concept that would be applicable to any substring b.

What I came up with was a way of counting the amount of strings by ordering them into different groups according to how much of the start of substring b the strings ending matched. That is to say - for a substring of length l, we are keeping track of l different groups or pools; in group j, exactly the last j bits of the strings imagined to be in j match the first j bits of b, and no more. With 0-indexing we have that group 0 counts how many strings have no overlapping between their end and the beginning of b, while in group 1 the last bit matches the first of b and so on. There is obviously only groups up to l-1, as group l would have a complete match between the end of the strings that belong to it and the disallowed substring.

With this framework in place, the problem now becomes figuring out the summation scheme with which to iterate the populations of these different groups. One can imagine that it is *always* possible to continue building the substring (except of course in group l-1). This means group j will always contribute to group j+1 in the next iteration, for 0 \leq j < l-1. To complete the scheme, we simply need to consider what happens any time the substring is *not* continued. To do this for group j, we use the fact that as any string counted in group j must end in the first j bits of b. If the substring is not continued, we are therefor garantueed to have strings that now end in the first j bits of b, followed by the logical negation of the bit at location j+1 in b. This string can then be checked against the longest possible agreement with the start of b.

As such, for any group j we can find the two (one in the case of group j+1) groups that group j contributes to when lengthening the string.

This scheme can be figured out from b alone, and thus only needs to be determined once, after which the string is lengthened from length 1 to length n according to the iterative scheme.