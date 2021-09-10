#pragma once
#include "Node.h"
#include "Pathfinding.h"
#include "PathfindingNode.h"
#include "Colours.h"
#include "UIManager.h"
#include <vector>
#include <SDL.h>
#include <memory>
#include <iostream>
#include <chrono>
#include <fstream>

enum class PathfindingAlgorithms
{
	DFS,
	BFS,
	DIJKSTRA,
	ASTAR,
};

enum class CellType
{
	Origin,
	Destination,
	Ground,
	Water,
	Wall,
};

class Grid
{

public:
	static Grid& getInstance()
	{
		static Grid instance;
		return instance;
	}

	void createGrid(int screenWidth, int screenHeight, int cellSize);
	std::vector<std::vector<std::shared_ptr<Node>>> getGrid() { return _grid; }
	void displayGrid(SDL_Renderer* renderer);
	
	void setCell(int x, int y);
	void setCellTypeAsWater() { _currentCellType = CellType::Water; }
	void setCellTypeAsWall() { _currentCellType = CellType::Wall; }
	void setCellTypeAsGround() { _currentCellType = CellType::Ground; }
	void setCellTypeAsOrigin() { _currentCellType = CellType::Origin; }
	void setCellTypeAsDestination() { _currentCellType = CellType::Destination; }
	bool mouseIneteractinWithGrid(int x, int y);

	int getCellSize() { return _cellSize; }
	
	void getPath();
	void DisplayPathfindingProcess();
	void useDFS() { _currentAlgorithm = PathfindingAlgorithms::DFS; }
	void useBFS() { _currentAlgorithm = PathfindingAlgorithms::BFS; }
	void useDijkstra() { _currentAlgorithm = PathfindingAlgorithms::DIJKSTRA; }
	void useAstar() { _currentAlgorithm = PathfindingAlgorithms::ASTAR; }
	void executePathfinding() { getPath(); showPath(); }

	std::vector<std::shared_ptr<PathfindingLibrary::PathfindingNode>> _path{};
	std::vector<std::shared_ptr<PathfindingLibrary::PathfindingNode>> _nodesSearched{};



private:
	Grid();

	Grid(Grid const&) = delete;
	void operator=(Grid const&) = delete;

	void fillGrid(bool useMaze);
	void setGridAsMaze() { fillGrid(true); }
	void setGridAsSwamp() { fillGrid(false); }
	void setGridNeighbours();


	void resetGridForPathfinding();
	void clearGrid();
	void checkOriginAndDestination(std::shared_ptr<Node> node);

	void setOrigin(int x, int y);
	void setDestination(int x, int y);
	void setWall(int x, int y);
	void setWater(int x, int y);
	void setGround(int x, int y);

	void changeNodeColour(std::shared_ptr<Node> node, int* colour);
	void changeNodeColour(std::shared_ptr<Node> node, Colours::Colour colour);

	
	void showNextNodeInPath();
	void showNextNodeInSearched();
	void showSearchedNodes();
	void showPath();


	std::vector<std::vector<std::shared_ptr<Node>>> _grid;
	int _nodeIndex{ 0 };
	int _nodeSearchedIndex{ 0 };

	std::shared_ptr<Node> _origin{};
	std::shared_ptr<Node> _destination{};

	PathfindingAlgorithms _currentAlgorithm{ PathfindingAlgorithms::ASTAR};
	CellType _currentCellType{ CellType::Origin};

	bool _showPath{ false };
	bool _showSearchedNodes{ false };

	bool _displayNodes{ false };
	float timerStarted{};
	std::chrono::steady_clock::time_point begin{};
	std::chrono::steady_clock::time_point interval{};
	
	int _cellSize{};
	int _gridWidth{};
	int _gridHeight{};
};
