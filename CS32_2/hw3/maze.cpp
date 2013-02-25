
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec) //reached the end
		return true;

	maze[sr][sc] = '@'; //dropping "crumb" to mark this space as visited
	if (maze[sr-1][sc] == '.') //if the N is unvisited
		return pathExists(maze, sr-1, sc, er, ec);

	if (maze[sr][sc+1] == '.') //if the E is unvisited
		return pathExists(maze, sr, sc+1, er, ec);

	if (maze[sr+1][sc] == '.') //if the S is unvisited
		return pathExists(maze, sr+1, sc, er, ec);

	if (maze[sr][sc-1] == '.') //if the W is unvisited
		return pathExists(maze, sr, sc-1, er, ec);

	return false; //maze is unsolvable
}