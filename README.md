The data used in this project comes from Open Flights. The data is downloaded as CSV files with each line representing an airport or flight. The dataset stores an Airport Id, Airport name, longitude and latitude coordinates for each airport. The airport object contains an unordered_map to hold adjacent airports and its paths. The airport will be mapped to vertices and directed edges will connect airports if there is a flight from one to the other. The edges are weighted by the distance which will be calculated by using longitude and latitude. 

For the traversal, we use Breadth First Search to traverse the graph to find all airports that are connected to the starting airport. This can also be used to find the path with the fewest flight transfer or the shortest path.

	We use Dijkstra’s Algorithm to find the shortest path. We also allow user inputs of two airport IDs, where we will run BFS on the first ID, and then find the shortest path between the first airport and the second. 
