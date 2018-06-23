# Random Contraction Algorithm

Input :- an undirected graph G = (V, E).

Output :- Compute a cut with the fewest number of crossing edges.

Applications :-

-  identify network bottlenecks/weaknesses.
-  community detection in social networks.
-  image segmentation.

Algorithm :-

1.  while there are more than 2 vertices remaining,
2.    pick a remaining edge(u,v) uniformly at random.
3.    merge/ "contract" the vertices (u,v) into a single vertex.
4.    Remove self loops.
5.  Return the cut represented by the final 2 vertices.