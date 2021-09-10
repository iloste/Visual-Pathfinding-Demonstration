#include "Grid.h"

Grid::Grid()
{
	// -160 to make room at the right of the screen
	createGrid(800 - 200, 600, 20);

	UIManager::getInstance().addButton(new int[2]{ 615, 45 }, 150, 40, "Origin",30, std::bind(&Grid::setCellTypeAsOrigin, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 90 }, 150, 40, "Destination",30, std::bind(&Grid::setCellTypeAsDestination, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 135 }, 150, 40, "Ground",30, std::bind(&Grid::setCellTypeAsGround, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 180 }, 150, 40, "Wall",30, std::bind(&Grid::setCellTypeAsWall, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 225 }, 150, 40, "Water",30, std::bind(&Grid::setCellTypeAsWater, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 270 }, 50, 40, "Clear",15, std::bind(&Grid::clearGrid, this));
	UIManager::getInstance().addButton(new int[2]{ 675, 270 }, 50, 40, "Maze",15, std::bind(&Grid::setGridAsMaze, this));
	UIManager::getInstance().addButton(new int[2]{ 735, 270 }, 50, 40, "Swamp",15, std::bind(&Grid::setGridAsSwamp, this));

	UIManager::getInstance().addButton(new int[2]{ 615, 335 }, 150, 40, "AStar",30, std::bind(&Grid::useAstar, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 380 }, 150, 40, "Dijkstra",30, std::bind(&Grid::useDijkstra, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 425 }, 150, 40, "BFS", 30,std::bind(&Grid::useBFS, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 470 }, 150, 40, "DFS",30, std::bind(&Grid::useDFS, this));
	UIManager::getInstance().addButton(new int[2]{ 615, 550 }, 150, 40, "Find Path",30, std::bind(&Grid::executePathfinding, this));
}

void Grid::createGrid(int width, int height, int cellSize)
{
	_cellSize = cellSize;
	_gridWidth = width / cellSize;
	_gridHeight = height / cellSize;

	_grid.clear();

	for (size_t i = 0; i < _gridWidth; i++)
	{
		_grid.push_back(std::vector<std::shared_ptr<Node>>());

		for (int j = 0; j < _gridHeight; j++)
		{
			_grid[i].push_back(std::shared_ptr<Node>(new Node()));
		}
	}

	fillGrid(false);
	setGridNeighbours();
}


void Grid::fillGrid(bool useMaze)
{
	std::string fileName{};

	// ToDo: implement tab to load maze/other layouts
	if (useMaze)
	{
		fileName = "res/Maze.txt";
	}
	else
	{
		fileName = "res/Grid.txt";
	}

	std::ifstream fileStream{};
	fileStream.open(fileName);

	for (size_t i = 0; i < _gridWidth; i++)
	{
		std::string line{};
		std::getline(fileStream, line);

		for (int j = 0; j < _gridHeight; j++)
		{
			_grid[i][j]->_rect.w = _cellSize - 1;
			_grid[i][j]->_rect.h = _cellSize - 1;
			_grid[i][j]->_rect.x = (j * _cellSize) + 1;
			_grid[i][j]->_rect.y = (i * _cellSize) + 1;
			_grid[i][j]->_pos[0] = i;
			_grid[i][j]->_pos[1] = j;

			switch (line[j])
			{
			case 'o':
				setOrigin(i, j);
				break;
			case 'd':
				setDestination(i, j);
				break;
			case 'w':
				setWall(i, j);
				break;
			case 'a':
				setWater(i, j);
				break;
			case 'g':
				setGround(i, j);
				break;
			default:
				setGround(i, j);
				break;
			}
		}
	}
}

void Grid::setGridNeighbours()
{
	for (int i = 0; i < _grid.size(); i++)
	{
		for (int j = 0; j < _grid[i].size(); j++)
		{
			//// north neighbour
			if (i - 1 >= 0)
			{
				_grid[i][j]->_neighbours.push_back(_grid[i - 1][j]);
			}
			//// east neighnour
			if (j + 1 < _grid[i].size())
			{
				_grid[i][j]->_neighbours.push_back(_grid[i][j + 1]);
			}
			//// south neighnour
			if (i + 1 < _grid.size())
			{
				_grid[i][j]->_neighbours.push_back(_grid[i + 1][j]);

			}
			//// west neighnour
			if (j - 1 >= 0)
			{
				_grid[i][j]->_neighbours.push_back(_grid[i][j - 1]);

			}
		}
	}
}


void Grid::clearGrid()
{
	for (size_t i = 0; i < _grid.size(); i++)
	{
		for (size_t j = 0; j < _grid[i].size(); j++)
		{
			setGround(i, j);
		}
	}

	setOrigin(4, 15);
	setDestination(25, 15);
}


void Grid::showNextNodeInPath()
{
	if (_nodeIndex < _path.size())
	{
		if (!_path[_nodeIndex]->_isDestination && _path[_nodeIndex]->_isWalkable)
		{
			Colours::tintColour(_grid[_path[_nodeIndex]->_pos[0]][_path[_nodeIndex]->_pos[1]]->_colour, 0.3f);
			_nodeIndex++;
		}
	}
	else
	{
		_displayNodes = false;
		_showPath = false;
	}
}


void Grid::showNextNodeInSearched()
{
	if (_nodeSearchedIndex < _nodesSearched.size())
	{
		if (_nodesSearched[_nodeSearchedIndex]->_isWalkable)
		{
			Colours::tintColour(_grid[_nodesSearched[_nodeSearchedIndex]->_pos[0]][_nodesSearched[_nodeSearchedIndex]->_pos[1]]->_colour, 0.4f);
		}
	}
	else
	{
		_showSearchedNodes = false;
		_showPath = true;
	}

	_nodeSearchedIndex++;
}


void Grid::changeNodeColour(std::shared_ptr<Node> node, int* colour)
{
	node->_colour.r = colour[0];
	node->_colour.g = colour[1];
	node->_colour.b = colour[2];
	node->_colour.a = colour[3];
}

void Grid::changeNodeColour(std::shared_ptr<Node> node, Colours::Colour colour)
{
	changeNodeColour(node, Colours::getColour(colour));
}


void Grid::displayGrid(SDL_Renderer* renderer)
{
	std::vector<std::vector<std::shared_ptr<Node>>> grid2 = Grid::getInstance().getGrid();

	for (size_t i = 0; i < grid2.size(); i++)
	{
		for (size_t j = 0; j < grid2[i].size(); j++)
		{
			// set a new draw colour
			SDL_SetRenderDrawColor(renderer, grid2[i][j]->_colour.r, grid2[i][j]->_colour.g, grid2[i][j]->_colour.b, grid2[i][j]->_colour.a);
			//fill the rect with the draw colour
			SDL_RenderFillRect(renderer, &grid2[i][j]->_rect);
		}
	}
}


void Grid::DisplayPathfindingProcess()
{
	if (_displayNodes)
	{
		if (!timerStarted)
		{
			begin = std::chrono::steady_clock::now();
			timerStarted = true;
		}

		interval = std::chrono::steady_clock::now();

		if (_showSearchedNodes)
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(interval - begin).count() >= 20)
			{
				begin = std::chrono::steady_clock::now();
				showNextNodeInSearched();
			}
		}
		else if (_showPath)
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(interval - begin).count() >= 20)
			{
				begin = std::chrono::steady_clock::now();
				showNextNodeInPath();
			}
		}
	}
}


void Grid::showSearchedNodes()
{
	for (size_t i = 1; i < _nodesSearched.size(); i++)
	{
		if (!_nodesSearched[i]->_isDestination && !_nodesSearched[i]->_isOrigin && _nodesSearched[i]->_isWalkable)
		{
			Colours::shadeColour(_grid[_nodesSearched[_nodeSearchedIndex]->_pos[0]][_nodesSearched[_nodeSearchedIndex]->_pos[1]]->_colour, 0.25f);
		}
	}
}


void Grid::showPath()
{
	_displayNodes = true;
	_showSearchedNodes = true;
	_showPath = false;
	_nodeIndex = 0;
	_nodeSearchedIndex = 0;
}


void Grid::getPath()
{
	std::cout << _path.size() << "\n";
	resetGridForPathfinding();
	
	_path.clear();
	_nodesSearched.clear();

	if (_origin != nullptr && _destination != nullptr)
	{
		PathfindingLibrary::Pathfinding pf{};
		switch (_currentAlgorithm)
		{
		case PathfindingAlgorithms::DFS:
			_nodesSearched = pf.DFSNodesSearched(_origin, _destination);
			resetGridForPathfinding();
			_path = pf.DFS(_origin, _destination);
			break;
		case PathfindingAlgorithms::BFS:
			_nodesSearched = pf.BFSNodesSearched(_origin, _destination);
			resetGridForPathfinding();
			_path = pf.BFS(_origin, _destination);
			break;
		case PathfindingAlgorithms::DIJKSTRA:
			_nodesSearched = pf.DijkstraNodesSearched(_origin, _destination);
			resetGridForPathfinding();
			_path = pf.Dijkstra(_origin, _destination);
			break;
		case PathfindingAlgorithms::ASTAR:
			_nodesSearched = pf.AStarNodesSearched(_origin, _destination);
			resetGridForPathfinding();
			_path = pf.AStar(_origin, _destination);
			break;
		}
	}
}

void Grid::setOrigin(int x, int y)
{
	if (_origin != nullptr)
	{
		_origin->resetConditions();
		changeNodeColour(_origin, Colours::Colour::Black);
	}

	_origin = _grid[x][y];
	_origin->resetConditions();
	_origin->_isOrigin = true;
	changeNodeColour(_origin, Colours::Colour::Green);
}

void Grid::checkOriginAndDestination(std::shared_ptr<Node> node)
{
	if (node->_isOrigin)
	{
		setGround(_origin->_pos[0], _origin->_pos[1]);
		_origin = nullptr;
	}
	if (node->_isDestination)
	{
		setGround(_destination->_pos[0], _destination->_pos[1]);
		_destination = nullptr;
	}
}


void Grid::setDestination(int x, int y)
{
	if (_destination != nullptr)
	{
		_destination->resetConditions();
		changeNodeColour(_destination, Colours::Colour::Black);
	}

	_destination = _grid[x][y];
	_destination->resetConditions();
	_destination->_isDestination = true;
	changeNodeColour(_destination, Colours::Colour::Red);
}

void Grid::setWall(int x, int y)
{
	_grid[x][y]->resetConditions();
	_grid[x][y]->_isWalkable = false;
	changeNodeColour(_grid[x][y], Colours::Colour::Brown);

}

void Grid::setWater(int x, int y)
{
	_grid[x][y]->resetConditions();
	_grid[x][y]->_cost = 4;
	_grid[x][y]->_isWater = true;
	changeNodeColour(_grid[x][y], Colours::Colour::NavyBlue);
}

void Grid::setGround(int x, int y)
{
	_grid[x][y]->resetConditions();
	changeNodeColour(_grid[x][y], Colours::Colour::Black);
}

void Grid::setCell(int x, int y)
{
	x /= _cellSize;
	y /= _cellSize;

	checkOriginAndDestination(_grid[x][y]);

	switch (_currentCellType)
	{
	case CellType::Origin:
		setOrigin(x, y);
		break;
	case CellType::Destination:
		setDestination(x, y);
		break;
	case CellType::Ground:
		setGround(x, y);
		break;
	case CellType::Water:
		setWater(x, y);
		break;
	case CellType::Wall:
		setWall(x, y);
		break;
	}
}

void Grid::resetGridForPathfinding()
{
	for (size_t i = 0; i < _grid.size(); i++)
	{
		for (size_t j = 0; j < _grid[i].size(); j++)
		{
			_grid[i][j]->_visited = false;
			_grid[i][j]->_inLine = false;
			_grid[i][j]->_parent = nullptr;

			if (_grid[i][j]->_isOrigin)
			{
				changeNodeColour(_grid[i][j], Colours::Colour::Green);
			}
			else if (_grid[i][j]->_isDestination)
			{
				changeNodeColour(_grid[i][j], Colours::Colour::Red);
			}
			else if (!_grid[i][j]->_isWalkable)
			{
				changeNodeColour(_grid[i][j], Colours::Colour::Brown);
			}
			else if (_grid[i][j]->_isWater)
			{
				changeNodeColour(_grid[i][j], Colours::Colour::NavyBlue);
			}
			else
			{
				changeNodeColour(_grid[i][j], Colours::Colour::Black);
			}
		}
	}
}

bool Grid::mouseIneteractinWithGrid(int x, int y)
{
	if (x > 0 && x < _gridWidth * _cellSize)
	{
		if (y > 0 && y < _gridHeight * _cellSize)
		{
			return true;
		}
	}

	return false;
}
