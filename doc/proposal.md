# Project Proposal

## Leading Question 

Our group is embarking on a project that involves the use of the "OpenFlights" dataset, which is a comprehensive collection of airport information. The dataset provides detailed data on airport names, locations (including latitude and longitude), unique airport IDs, and other important information. We aim to utilize this dataset to determine the shortest flight time and total distance for connecting flights. To achieve our goals, we have devised a robust methodology that includes utilizing BFS traversal to identify the shortest route between airports based on the least number of connecting flights. We will also leverage Dijkstra's algorithm to calculate the shortest path between airports based on the least distance traveled.
    
Additionally, we intend to implement a landmark algorithm to determine the shortest distance between two airports, considering the distance traveled with connections through a third airport. In order to execute our plan, we will first designate the airports as vertices and use the flight between airports as edges. This will enable us to establish a map with two dimensions as the data structure required for this project. As we proceed with our analysis, we will utilize advanced tools such as Valgrind to prevent memory leaks and computational errors. In conclusion, our project is an ambitious undertaking that requires a meticulous approach to ensure accurate and meaningful results. We are excited about the potential of this project and the insights we can uncover using this dataset and advanced algorithms.

## Major Deliverables

- Breadth-First-Search (BFS)
- Dijkstra's Algorithm (coverd in CS 225)
- Page Rank algorithm

## Dataset Acquisition and Processing

The data set we will use for this project consists of airports as vertices and flights between airports as edges. To obtain this data, we will read CSV files using offstream or ifstream. We will use this data to calculate the shortest distance between airports. Since the project involves plotting the results on a map, we will use 2D coordinates. These coordinates may be identical or different. As for the algorithm, we will find the shortest distance from one vertex to all other vertices. During this process, we will ensure no errors in the mapping process, such as missing airports.

Furthermore, when calculating the distance for airports during the mapping process, we will work on fixing memory leaks, Valgrind errors, or computational errors. It is important to note that data validation will also be a crucial aspect of this project to ensure that the data used is accurate and reliable. We will also consider edge cases, such as airports with multiple terminals or multiple locations. To handle such cases, we will use specific identification codes to differentiate between them. Additionally, to improve the algorithm's efficiency, we may consider implementing data structures such as priority queues or hash tables. This project requires a thorough understanding of data processing, algorithm design, and software engineering principles to ensure accurate results and efficient implementation.

Last, considering potential commonplaceness, we set the project's theme, “What’s your summer plan?” We will be gathering additional information, data rather, on average temperatures, humidities, and GDP around the airports, which are crucial information in deciding a destination for the summer vacation. For example, if a user is unfamiliar with a considerable weather gap, we would filter out the destinations with abnormal weather trends. 
## Algorithms

The program mentioned in the first paragraph allows users to enter their starting and destination airports and provides them with a list of connecting flights with the shortest flight time and total distance. The airport codes that the program uses for identifying locations are three-letter IATA codes. If a user enters an invalid input, the system prompts them to re-enter it.

In order to determine the shortest route between the starting and final destinations, the program uses a traversal algorithm called Breadth-First Search (BFS) on all airports with commercial flights connecting them. The BFS algorithm helps in finding the shortest route between the airports based on the least amount of connecting flights.
There are two versions of the BFS algorithm, and the program chooses one through trial and error before uploading it. The two versions of the BFS algorithm differ in their data structures, namely, adjacency list and adjacency matrix. Firstly, the adjacency list data structure is more efficient regarding memory usage because it only manages the existing edges. To determine the number of all edges in the graph, the program needs to search for all adjacent lists from the header node of each vertex, which takes O(n+e) time. If the program needs to inquire about the edge connecting two vertices or know the order of a vertex, it must search for the adjacent list of vertices, which takes O(degree(v)) time.

On the other hand, the adjacency matrix data structure stores the edge information of all vertices in a two-dimensional arrangement. This allows for an O(1) time complexity when inquiring about the edge connecting two vertices. When the order of the vertex i is obtained, all values of the ith row of the adjacent matrix M are added, and a time complexity of O(n) is obtained. This makes the implementation of the adjacency matrix data structure relatively simple. However, regardless of the number of edges, the program requires a two-dimensional array of n^2 size, which leads to a waste of memory space. To determine the number of all edges in the graph, the program needs to check the adjacent matrix, which takes time for O(n^2).

To calculate the distance between airports, we will use their longitude and latitude coordinates as weights of edges. This method will help us to find the shortest path between two airports by calculating the shortest distance traveled. By implementing Dijkstra's algorithm, we can efficiently calculate the shortest path between two airports based on the distance traveled. The algorithm works by starting at the initial airport and gradually exploring nearby airports greedily until the final destination is reached. The Dijkstra algorithm has a time complexity of O(ElogE) because insertion operations occur for all edges. However, since the graph is sparse, i.e., E<=V^2, we can consider it to take up to O(ElogV) time. This is because the algorithm explores only the connected nodes and edges, avoiding unnecessary exploration of disconnected nodes and edges. When inserting each node into the priority queue, it takes up to O(VlogV) time because it will take up to V nodes. Hence, it will take up to O((V+E)logV) time to calculate the priority queue for all nodes and edges. Using Dijkstra's algorithm with the longitude and latitude coordinates of airports provides an efficient and accurate method of finding the shortest path between two airports. Although the algorithm has a slightly higher time complexity, it is compensated by its ability to explore only the necessary edges, which helps speed up the calculation.

To find the most important airports in the world, we will utilize the Page Rank algorithm. This algorithm will help us determine the significance of each airport in our direct graph by evaluating its relative importance compared to other airports. To implement this, we will take two inputs. Firstly, we will select a node from the direct graph that we are using to store the information on all the airports. Secondly, we will set the range of the airports that we want to be included in the adjacency matrix. After creating the adjacency matrix, we will use C++'s linear algebra library to compute the eigenvalues of the matrix. These eigenvalues will give us the desired results. The time complexity of this algorithm is O(k*N), where k is the number of iterations required to converge, and N is the number of nodes in the graph. The space requirement for this algorithm is O(N). The Personalized PageRank algorithm will be used for computing the importance of each node in the graph with respect to a given set of nodes. This algorithm uses a power iteration method to calculate the importance of each node. By using this algorithm, we will be able to map the most significant airports in the world on a world map.

Reference :
Page Rank: Kanchana, Kanchana, and S. P. Shantharajah. "Comparative Analysis of BFS and DFS for Efficient Graph Traversal." 2016 International Conference on Communication and Signal Processing (ICCSP), IEEE, 2016, pp. 1369-1372. doi: 10.1109/ICCSP.2016.7754334, https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7497841&tag=1 

BFS: "Breadth-First and Depth-First Search." CS 225 Course Website, University of Illinois at Urbana-Champaign, Spring 2023, https://courses.engr.illinois.edu/cs225/sp2023/resources/bfs-dfs/.

Dijkstra's Algorithm: "Dijkstra's Algorithm." CS 225 Course Website, University of Illinois at Urbana-Champaign, Spring 2019, https://courses.engr.illinois.edu/cs225/sp2019/notes/dijkstra/.

## Timeline

Week 1 (March 20 ~ March 26): 
March 20th: 
Decided which dataset to use and discussed Team contract. 
Discussed the method of the algorithm to achieve our project goal.
March 24th: 
Finalized our major deliverables, algorithms, and our timeline. 
March 25th: 
Revised our Final Project Proposal and submitted it to PrairieLearn.. 

Week 2 (March 27 ~ April 2)
March 28th: 
Complete converting data to proper array format and use the array data to graph format. 
March 30th: 
Try using BFS traversals. Debug oblong the way if needed.

Week 3 (April 3 ~ April 9)
April 4th:
Try to finalize BFS traversals and start Dijkstra’s. 
April 6th: 
Try to finalize Dijstra’s with a verification test. Modification on BFS traversals if needed. 

Week 4 (April 10 ~ April 16)
April 11th:
Add visualizations of routes and highlight the shortest path. 
April 13th:
 Ready for the midway check for our project. Modify algorithms if necessary. 

Week 5 (April 17 ~ April 23)
April 18th: 
Try to perfect the project and test the program for performance. 
April 20th:
Draw a conclusion, then start and complete the presentation slides. 

Week 6 (April 24 ~ May 5)
April 25th:
Final review from the beginning and get ready for the presentation. 
April 27th ~ May 4th: 
Complete the project and submit it. 