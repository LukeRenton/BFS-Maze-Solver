#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

void populate_maze(vector<vector<char>> &maze, int rows, int cols, int &start_row, int &start_col, int &goal_row, int &goal_col){
	string line;
	cin.ignore();
	for (int i = 0;i<rows;i++){
		getline(cin, line);
		vector<char> row;
		for (int j=0;j<cols;j++){
			row.push_back(line[j]);
			
			//Capture start and goal positions
			if(line[j] == 'S'){
				start_row = i;
				start_col = j;
				
			}
			
			if(line[j] == 'G'){
				goal_row = i;
				goal_col = j;				
			}	
		}		
		maze.push_back(row);
	}
}

void display_maze(vector<vector<char>> maze, int rows, int cols){
	for (int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){
			cout << maze[i][j];			
		}
		cout << endl;
	}
}

void dfs(vector<vector<char>> &maze, int rows, int cols, int start_row, int start_col, int goal_row, int goal_col){

	queue<pair<int,int>> locations;
	vector<vector<pair<int,int>>> parent;
	pair<int, int> current;
	locations.push(make_pair(start_row, start_col));
	vector<pair<int, int>> direction = {{1,0},{0,-1},{-1,0},{0,1}};
	//make a grid location of all locations on the grid set to -1, if = -1 hasn't been visited
	vector<vector<int>> tiles;
	for (int i=0;i<rows;i++){
		vector<int> row;
		vector<pair<int,int>> row_pair;
		for (int j=0;j<cols;j++){
			row.push_back(-1);
			row_pair.push_back({0,0});
		}
		tiles.push_back(row);
		parent.push_back(row_pair);
	}
	
	tiles[start_row][start_col] = 0;
	while (locations.empty() != true && (not (locations.front().first == goal_row && locations.front().second == goal_col))){
		current = locations.front();
		locations.pop();
		for (auto couple: direction){			
			int x = current.first + couple.first, y = current.second + couple.second; //move to the next cell going DLUR
			if (maze[x][y] != 'x' && tiles[x][y] == -1 && (x>0 && x < rows) && (y>0 && y < cols)){ //make sure its not been vistied/within bounds		
				tiles[x][y] = 0;
				parent[x][y] = current;
				locations.push(make_pair(x,y));			
			}
		}		
	}
	
	if (locations.empty() == true){ //Not solvable
		cout << "No Path" << endl;
	}
	else{
		current = {goal_row, goal_col};
		//Backtrack to the start writing the path
		while (not(current.first == start_row && current.second == start_col)){
			current = parent[current.first][current.second];
			maze[current.first][current.second] = '*';
		}
		maze[start_row][start_col] = 'S'; //To prevent the start from being replaced by a star
		display_maze(maze, rows, cols);
	}
	
	
}
	
int main(){	
	int rows , cols, start_row, start_col, goal_row, goal_col;
	
	cin >> rows >> cols;
	
	vector<vector<char>> maze;
	
	populate_maze(maze, rows, cols, start_row, start_col, goal_row, goal_col);
	
	dfs(maze, rows, cols, start_row, start_col, goal_row, goal_col);
	
}
