# A Vicious Pikeman (Hard)

In the problem a pikeman is an avid competitive programmer, for some reason. When he parttakes in competitions, he also knows exactly how long each problem will take to solve, for some reason. When submitting the answers, he is also penalized by how long the competition has run at the time of handing in each problem, for some reason. Anyways, we are thasked with finding out how many problems he can solve and what his lowest possible penalty for solving them will be. As input, we are given how many problems are on the test, as well as how long time the poor pikeman has to solve this multitude of problems. Along with this, we are also given a set of constants A, B, C and t_0, which govern how long the rest of the problems will take to solve using the iterative formula

<img src="https://latex.codecogs.com/svg.image?t_i=(A&space;t_{i-1}&plus;B)\mod&space;C)&plus;1" title="t_i=(A t_{i-1}+B)\mod C)+1" />

For the easy version of this problem, one could simply calculate all t_i's and sort them and go through the sorted list until the timeconstraint T was possibly met, while calculating the total penalty and counting the number of problems. However, this is intractable for the hard version, since the number of problems is now up to 10^9, making it infeasible to loop through and calculate all the t_i's, *especially* in pure python. Instead, we will have to get clever.

Looking at the iterative formula, we can realize that, since the outermost operation is (\mod C) + 1, every t_i must be in the range [1, C]. In the problem statement, C is bounded by 1 \leq C\leq 10^6. As such, even if we have N = 10^9, we can at most have 10^6 distinct t_i's. Because of this, a tractable strategy could be to find the distinct t_i's and their multiplicity, rather than brute-force calculating all the t_i's.
Finding every distinct t_i entails calculating every t_i the usual way, but stopping once we encounter a t we have already encountered, since the sequence is certain to repeat from that point on.

There are different ways of calculating t's until we find one we've already encountered - a simple approach that first sprang to mind for me was to save all our t's in an expanding list in the order that they were found and searching through this list for each new t to be sure it wasn't contained within already. This approach scales very poorly if we need to calculate many t's, however, as we need to search a very long list many times. As such, a different approach is taken; a list of length C+1 is preallocated and initialized with some value that is not a positive integer. For each found t_i, we save the iteration i at which it was found at the index t_i. With this datastructure, checking if a t has been encountered previously becomes a simple lookup instead of a search. Additionally, the iteration at which our duplicate t was previously found is readily available as the value of the list at index t_i. This will be important for figuring out the multiplicity of each t.

In order to find this multiplicity, we shall consider cyclic nature of the recursive function that generates the t's. There is no garantuee that the first t's found will be part of the repeating pattern, only that once a duplicate t has been found, repeating pattern will be comprised of the list of t's found between the iteration at which the duplicate t was first found, and the iteration just before was found the second time. As such, there may be a sequence of ts before this iteration containing the first instance of the duplicate t, all of which will have multiplicty 1, as they will never again arise in the sequence. To find the multiplicity of the repeating sequence, the number of t's with multiplicty 1 can be subtracted from N and the remaining number of problems can be divided out between the periodic t's, giving their multiplicity.

Once all unique t's and their multiplicty have been determined, they can simply be sorted according to lowest t, and the total number of problems it is possible to solve as well as the total penalty can be calculated.