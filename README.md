# Project_Openflight

Project to determine the shortest flight time and total distance for connecting flight using openflight dataset

1)Location of code, data, and results:

Using "airports.dat" and "routes.dat" to store all the airports(Nodes) and all the routes(edges). These datas also include the informations like ID, name, and location.  Airport and Route class help us to access and modify those data. The Airport_Graph class helps us to get the information of adjacent airports.

Using BFS class and Dijkstra class which is our first and second major deliverable, we found out the shortest path between two airports throughout Breadth First Search and Dijkstra's algorithm.

Using PageRank class, we ranked the importance of each airport in the path throughout PageRank algorithm.

2)How to build and run.

  Excutable:
  
    a.First build the target 'all' in the Makefile typing "make all" in terminal.
    b.Execute program typing "./openflight"
    c.Type "default" to use the default dataset
    d.Choose the features you want to execute.
      Found out all the paths from an airport using BFS.
      Found out the paths from an airport with n times stop over using BFS.
      Found out all the paths between airports using BFS.
      Calculate the shortest path between two airports using Dijkstra's algorithm.
      PageRank
    Tests:
      a.First, build the target 'tests' in the Makefile typing "make tests" in terminal.
      b.Execute test typing "./tests"
