# Ab Initio

https://open.kattis.com/problems/abinitio (Difficulty 7.5)

The problem consists of reading a graph, G, and a list of queries, Q, from input. G should then be modified according to the queries in Q.

My solution models the graph of V vertices as a $V\times V$ boolean matrix, which i will refer to as $M$ for the rest of the document. In $M$, a 1 at position $(i,j)$ represents a connection from vertice $i$ to vertice $j$. Notice that every possible connection in the graph corresponds to an entry in $M$.

With this datastructure, all 6 query types become simple to implement. Query type 1 entails adding an unconnected vertex to the graph, which corresponds to simply increasing the size of the matrix to $V = V + 1$.
Query type 2 entails making a new connection between two vertices $i$ and $j$, corresponding to setting the value of $M$ at $(i, j)$ to 1.
Query type 3 entails removing all connections to and from a vertex $i$, which corresponds to setting all entries in row $i$ to 0 and all entries in column $i$ to 0 as well.
Query type 4 entails removing a single connection, making the implementation identical to query type 2, only instead of setting the entry to 1 we set it to 0.
Query type 5 entails transposing the graph, inverting the direction of every connection in the graph. This corresponds to swapping what is the rows and columns of $M$, meaning that a transposition of the graph is identical to a transposition of $M$.
Query type 6 entails creating every possible connection that was not present before the query, while removing every connection that was present before, though no point is allowed to connect to itself. This corresponds to applying the function "logical not" to $M$ elementwise, after which the entire diagonal of $M$ can be set to 0, ensuring no point connects to itself.

By representing $G$ with $M$