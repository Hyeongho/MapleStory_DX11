#include "Navigation.h"
#include "../Component/TileMapComponent.h"
#include "../Component/Tile.h"

CNavigation::CNavigation()
{
}

CNavigation::~CNavigation()
{
	size_t	Size = m_vecNode.size();

	for (size_t i = 0; i < Size; i++)
	{
		SAFE_DELETE(m_vecNode[i]);
	}
}

void CNavigation::CreateNavigationNode(CTileMapComponent* TileMap)
{
	m_TileMap = TileMap;

	m_NodeShape = TileMap->GetTileShape();
	m_CountX = TileMap->GetTileCountX();
	m_CountY = TileMap->GetTileCountY();
	m_TileSize = TileMap->GetTileSize();

	int	Count = m_CountX * m_CountY;

	for (int i = 0; i < Count; i++)
	{
		NavNode* Node = new NavNode;

		Node->TileType = TileMap->GetTile(i)->GetTileType();
		Node->Pos = TileMap->GetTile(i)->GetPos();
		Node->Size = m_TileSize;
		Node->Center = Node->Pos + Node->Size * 0.5f;
		Node->IndexX = TileMap->GetTile(i)->GetIndexX();
		Node->IndexY = TileMap->GetTile(i)->GetIndexY();
		Node->Index = TileMap->GetTile(i)->GetIndex();

		m_vecNode.push_back(Node);
	}
}

bool CNavigation::FindPath(const Vector3& Start, const Vector3& End, std::list<Vector3>& vecPath)
{
	vecPath.clear();

	int	StartIndex = m_TileMap->GetTileIndex(Start);

	if (StartIndex == -1)
	{
		return false;
	}

	int	EndIndex = m_TileMap->GetTileIndex(End);

	if (EndIndex == -1)
	{
		return false;
	}

	// 이전에 사용하던 노드들이 있을수도 있으므로 길을 찾기 전에 사용하던 노드들의 데이터를
	// 초기화한다.
	size_t	Size = m_vecUseNode.size();

	for (size_t i = 0; i < Size; i++)
	{
		m_vecUseNode[i]->NodeType = Nav_Node_Type::None;
		m_vecUseNode[i]->Cost = FLT_MAX;
		m_vecUseNode[i]->Dist = FLT_MAX;
		m_vecUseNode[i]->Total = FLT_MAX;
		m_vecUseNode[i]->Parent = nullptr;
		m_vecUseNode[i]->SearchDirList.clear();
	}

	m_vecUseNode.clear();

	NavNode* StartNode = m_vecNode[StartIndex];
	NavNode* EndNode = m_vecNode[EndIndex];

	if (EndNode->TileType == Tile_Type::Wall)
	{
		return false;
	}

	else if (StartNode == EndNode)
	{
		vecPath.push_back(End);
		return true;
	}

	StartNode->NodeType = Nav_Node_Type::Open;
	StartNode->Cost = 0.f;
	StartNode->Dist = StartNode->Center.Distance(End);
	StartNode->Total = StartNode->Dist;

	for (int i = 0; i < (int)Node_Dir::End; ++i)
	{
		StartNode->SearchDirList.push_back((Node_Dir)i);
	}

	m_vecOpen.push_back(StartNode);

	m_vecUseNode.push_back(StartNode);

	while (!m_vecOpen.empty())
	{
		NavNode* Node = m_vecOpen.back();
		m_vecOpen.pop_back();

		Node->NodeType = Nav_Node_Type::Close;

		// 8방향의 타일을 검사하여 코너를 열린목록에 넣어준다.
		if (FindNode(Node, EndNode, End, vecPath))
		{
			break;
		}

		// 열린목록을 정렬한다. 비용이 작은 노드가 가장 마지막 노드가 되도록 내림차순으로
		// 정렬한다.
		if (!m_vecOpen.empty())
		{
			std::sort(m_vecOpen.begin(), m_vecOpen.end(), CNavigation::SortNode);
		}
	}

	m_vecOpen.clear();

	return !vecPath.empty();
}

bool CNavigation::FindNode(NavNode* Node, NavNode* EndNode, const Vector3& End, std::list<Vector3>& vecPath)
{
	auto iter = Node->SearchDirList.begin();
	auto iterEnd = Node->SearchDirList.end();

	for (; iter != iterEnd; iter++)
	{
		NavNode* Corner = GetCorner(*iter, Node, EndNode, End);

		if (!Corner)
		{
			continue;
		}

		// 찾아준 노드가 도착 노드라면 경로를 만들어준다.
		if (Corner == EndNode)
		{
			m_vecUseNode.push_back(Corner);
			vecPath.push_front(End);

			NavNode* PathNode = Node;

			while (PathNode)
			{
				vecPath.push_front(PathNode->Center);
				PathNode = PathNode->Parent;
			}

			vecPath.pop_front();

			return true;
		}


		// 이동 비용을 구해준다.
		float Cost = 0.f;

		if (m_NodeShape == Tile_Shape::Rect)
		{
			switch (*iter)
			{
			case Node_Dir::T:
			case Node_Dir::B:
				Cost = Node->Cost + abs(Node->Center.y - Corner->Center.y);
				break;
			case Node_Dir::R:
			case Node_Dir::L:
				Cost = Node->Cost + abs(Node->Center.x - Corner->Center.x);
				break;
			case Node_Dir::LT:
			case Node_Dir::RT:
			case Node_Dir::LB:
			case Node_Dir::RB:
				Cost = Node->Cost + Node->Center.Distance(Corner->Center);
				break;
			}
		}

		else
		{
			switch (*iter)
			{
			case Node_Dir::T:
			case Node_Dir::B:
				Cost = Node->Cost + abs(Node->Center.y - Corner->Center.y);
				break;
			case Node_Dir::R:
			case Node_Dir::L:
				Cost = Node->Cost + abs(Node->Center.x - Corner->Center.x);
				break;
			case Node_Dir::LT:
			case Node_Dir::RT:
			case Node_Dir::LB:
			case Node_Dir::RB:
				Cost = Node->Cost + Node->Center.Distance(Corner->Center);
				break;
			}
		}

		// 찾아준 노드가 이미 열린목록에 들어가 있을 경우 비용을 비교하여 좀 더 작은 비용의 경로로 교체한다.
		if (Corner->NodeType == Nav_Node_Type::Open)
		{
			if (Corner->Cost > Cost)
			{
				Corner->Cost = Cost;
				Corner->Total = Corner->Cost + Corner->Dist;
				Corner->Parent = Node;

				AddDir(*iter, Corner);
			}
		}

		else
		{
			Corner->NodeType = Nav_Node_Type::Open;
			Corner->Parent = Node;
			Corner->Cost = Cost;
			Corner->Dist = Corner->Center.Distance(End);
			Corner->Total = Corner->Cost + Corner->Dist;
			Corner->Parent = Node;

			m_vecOpen.push_back(Corner);

			m_vecUseNode.push_back(Corner);

			AddDir(*iter, Corner);

		}
	}

	return false;
}

NavNode* CNavigation::GetCorner(Node_Dir Dir, NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	switch (m_NodeShape)
	{
	case Tile_Shape::Rect:
		switch (Dir)
		{
		case Node_Dir::T:
			return GetRectNodeTop(Node, EndNode, End, false);
		case Node_Dir::RT:
			return GetRectNodeRightTop(Node, EndNode, End);
		case Node_Dir::R:
			return GetRectNodeRight(Node, EndNode, End, false);
		case Node_Dir::RB:
			return GetRectNodeRightBottom(Node, EndNode, End);
		case Node_Dir::B:
			return GetRectNodeBottom(Node, EndNode, End, false);
		case Node_Dir::LB:
			return GetRectNodeLeftBottom(Node, EndNode, End);
		case Node_Dir::L:
			return GetRectNodeLeft(Node, EndNode, End, false);
		case Node_Dir::LT:
			return GetRectNodeLeftTop(Node, EndNode, End);
		}
		break;
	case Tile_Shape::Rhombus:
		switch (Dir)
		{
		case Node_Dir::T:
			return GetRhombusNodeTop(Node, EndNode, End);
		case Node_Dir::RT:
			return GetRhombusNodeRightTop(Node, EndNode, End);
		case Node_Dir::R:
			return GetRhombusNodeRight(Node, EndNode, End);
		case Node_Dir::RB:
			return GetRhombusNodeRightBottom(Node, EndNode, End);
		case Node_Dir::B:
			return GetRhombusNodeBottom(Node, EndNode, End);
		case Node_Dir::LB:
			return GetRhombusNodeLeftBottom(Node, EndNode, End);
		case Node_Dir::L:
			return GetRhombusNodeLeft(Node, EndNode, End);
		case Node_Dir::LT:
			return GetRhombusNodeLeftTop(Node, EndNode, End);
		}
		break;
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeTop(NavNode* Node, NavNode* EndNode, const Vector3& End, bool Digonal)
{
	// 위로 이동할때는 노드를 한칸씩 위로 이동을 시키면서 해당 노드의 오른쪽이 막혀있고 오른쪽 위가 뚫려있거나
	// 왼쪽이 막혀있고 왼쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;

	while (true)
	{
		IndexY++;

		if (IndexY >= m_CountY)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + Node->IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = Node->IndexX + 1;
		int	CornerY = IndexY;

		if (CornerX < m_CountX && CornerY + 1 < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall && 
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = Node->IndexX - 1;
		CornerY = IndexY;

		if (CornerX >= 0 && CornerY + 1 < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeRightTop(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 오른쪽 위로 이동할때는 노드를 한칸씩 오른쪽 위로 이동을 시키면서 해당 노드의 왼이 막혀있고 왼쪽 위가 뚫려있거나
	// 아래쪽이 막혀있고 오른쪽 아래가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexY++;
		IndexX++;

		if (IndexY >= m_CountY || IndexX >= m_CountX)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX - 1;
		int	CornerY = IndexY;

		if (CornerX >= 0 && CornerY + 1 < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = IndexY - 1;

		if (CornerY >= 0 && CornerX + 1 < m_CountX)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 오른쪽 위 대각선 체크시 만약 현 노드가 코너가 아니라면 오른쪽 방향과 위쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRectNodeTop(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRectNodeRight(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeRight(NavNode* Node, NavNode* EndNode, const Vector3& End, bool Digonal)
{
	// 오른쪽으로 이동할때는 가로가 1씩 증가하며 위가 막혀있고 오른쪽 위는 갈 수 있거나
	// 아래가 막혀있고 오른쪽 아래는 갈 수 있을 경우 코너가 된다.
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexX++;

		if (IndexX >= m_CountX)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[Node->IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = Node->IndexY + 1;

		if (CornerY < m_CountY && CornerX + 1 < m_CountX)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = Node->IndexY - 1;

		if (CornerY >= 0 && CornerX + 1 < m_CountX)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeRightBottom(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 오른쪽 아래로 이동할때는 노드를 한칸씩 오른쪽 아래로 이동을 시키면서 해당 노드의 왼쪽이 막혀있고 왼쪽 아래가 뚫려있거나
	// 위쪽이 막혀있고 오른쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexY--;
		IndexX++;

		if (IndexY < 0 || IndexX >= m_CountX)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX - 1;
		int	CornerY = IndexY;

		if (CornerX >= 0 && CornerY - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = IndexY + 1;

		if (CornerY < m_CountY && CornerX + 1 < m_CountX)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 오른쪽 아래 대각선 체크시 만약 현 노드가 코너가 아니라면 오른쪽 방향과 아래쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRectNodeBottom(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRectNodeRight(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeBottom(NavNode* Node, NavNode* EndNode, const Vector3& End, bool Digonal)
{
	// 아래로 이동할때는 노드를 한칸씩 아래로 이동을 시키면서 해당 노드의 오른쪽이 막혀있고 오른쪽 아래가 뚫려있거나
	// 왼쪽이 막혀있고 왼쪽 아래가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;

	while (true)
	{
		IndexY--;

		if (IndexY < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + Node->IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = Node->IndexX + 1;
		int	CornerY = IndexY;

		if (CornerX < m_CountX && CornerY - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = Node->IndexX - 1;
		CornerY = IndexY;

		if (CornerX >= 0 && CornerY - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeLeftBottom(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 왼쪽 아래로 이동할때는 노드를 한칸씩 왼쪽 아래로 이동을 시키면서 해당 노드의 위쪽이 막혀있고 왼쪽 위가 뚫려있거나
	// 오른쪽이 막혀있고 오른쪽 아래가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexY--;
		IndexX--;

		if (IndexY < 0 || IndexX < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = IndexY + 1;

		if (CornerY < m_CountY && CornerX - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX + 1;
		CornerY = IndexY;

		if (CornerX < m_CountX && CornerY - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY - 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 왼쪽 아래 대각선 체크시 만약 현 노드가 코너가 아니라면 왼쪽 방향과 아래쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRectNodeBottom(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRectNodeLeft(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeLeft(NavNode* Node, NavNode* EndNode, const Vector3& End, bool Digonal)
{
	// 왼쪽으로 이동할때는 가로가 1씩 감소하며 위가 막혀있고 왼쪽 위는 갈 수 있거나
	// 아래가 막혀있고 왼쪽 아래는 갈 수 있을 경우 코너가 된다.
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexX--;

		if (IndexX < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[Node->IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = Node->IndexY + 1;

		if (CornerY < m_CountY && CornerX - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;
		CornerY = Node->IndexY - 1;

		if (CornerY >= 0 && CornerX - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRectNodeLeftTop(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 왼쪽 위로 이동할때는 노드를 한칸씩 왼쪽 위로 이동을 시키면서 해당 노드의 아래쪽이 막혀있고 왼쪽 아래가 뚫려있거나
	// 오른쪽이 막혀있고 오른쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexY++;
		IndexX--;

		if (IndexY >= m_CountY || IndexX < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = IndexY - 1;

		if (CornerY >= 0 && CornerX - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[CornerY * m_CountX + (CornerX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX + 1;
		CornerY = IndexY;

		if (CornerX < m_CountX && CornerY + 1 < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(CornerY + 1) * m_CountX + CornerX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 왼쪽 위 대각선 체크시 만약 현 노드가 코너가 아니라면 왼쪽 방향과 위쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRectNodeTop(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRectNodeLeft(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeTop(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 왼쪽 위로 이동할때는 노드를 한칸씩 왼쪽 위로 이동을 시키면서 해당 노드의 아래쪽이 막혀있고 왼쪽 아래가 뚫려있거나
	// 오른쪽이 막혀있고 오른쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexY += 2;

		if (IndexY >= m_CountY)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;

		if (IndexY % 2 == 0)
		{
			CornerX = IndexX - 1;
		}

		int	CornerY = IndexY - 1;

		if (CornerY >= 0 && IndexX - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 1)
		{
			CornerX = IndexX + 1;
		}

		CornerY = IndexY - 1;

		if (IndexX + 1 < m_CountX && CornerY >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 왼쪽 위 대각선 체크시 만약 현 노드가 코너가 아니라면 왼쪽 방향과 위쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRhombusNodeLeftTop(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRhombusNodeRightTop(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeRightTop(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 위로 이동할때는 노드를 한칸씩 위로 이동을 시키면서 해당 노드의 오른쪽이 막혀있고 오른쪽 위가 뚫려있거나
	// 왼쪽이 막혀있고 왼쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		if (IndexY % 2 == 1)
		{
			++IndexX;
		}

		IndexY++;

		if (IndexY >= m_CountY || IndexX >= m_CountX)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = IndexY + 1;

		if (IndexY % 2 == 0)
		{
			CornerX--;
		}

		if (CornerX >= 0 && IndexY + 2 < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY + 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 1)
		{
			CornerX = IndexX + 1;
		}

		CornerY = IndexY - 1;

		if (CornerX < m_CountX && CornerY >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeRight(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 왼쪽 위로 이동할때는 노드를 한칸씩 왼쪽 위로 이동을 시키면서 해당 노드의 아래쪽이 막혀있고 왼쪽 아래가 뚫려있거나
	// 오른쪽이 막혀있고 오른쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexX++;

		if (IndexX >= m_CountX)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;

		if (IndexY % 2 == 0)
		{
			CornerX = IndexX - 1;
		}

		int	CornerY = IndexY + 1;

		if (IndexY + 2 < m_CountY && CornerX >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY + 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 0)
		{
			CornerX = IndexX - 1;
		}

		CornerY = IndexY - 1;

		if (CornerX >= 0 && IndexY - 2 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY - 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 왼쪽 위 대각선 체크시 만약 현 노드가 코너가 아니라면 왼쪽 방향과 위쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRhombusNodeRightTop(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRhombusNodeRightBottom(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeRightBottom(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 위로 이동할때는 노드를 한칸씩 위로 이동을 시키면서 해당 노드의 오른쪽이 막혀있고 오른쪽 위가 뚫려있거나
	// 왼쪽이 막혀있고 왼쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		if (IndexY % 2 == 1)
		{
			IndexX++;
		}

		IndexY--;

		if (IndexY < 0 || IndexX >= m_CountX)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = IndexY + 1;

		if (IndexY % 2 == 1)
		{
			CornerX = IndexX + 1;
		}

		if (IndexX + 1 < m_CountX && CornerY < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 0)
		{
			CornerX = IndexX - 1;
		}

		CornerY = IndexY - 1;

		if (CornerX >= 0 && IndexY - 2 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY - 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeBottom(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 왼쪽 위로 이동할때는 노드를 한칸씩 왼쪽 위로 이동을 시키면서 해당 노드의 아래쪽이 막혀있고 왼쪽 아래가 뚫려있거나
	// 오른쪽이 막혀있고 오른쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexY -= 2;

		if (IndexY < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;

		if (IndexY % 2 == 0)
		{
			CornerX = IndexX - 1;
		}

		int	CornerY = IndexY + 1;

		if (CornerY < m_CountY && IndexX - 1 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 1)
		{
			CornerX = IndexX + 1;
		}

		CornerY = IndexY + 1;

		if (IndexX + 1 < m_CountX && CornerY < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX + 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 왼쪽 위 대각선 체크시 만약 현 노드가 코너가 아니라면 왼쪽 방향과 위쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRhombusNodeLeftBottom(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRhombusNodeRightBottom(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeLeftBottom(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 위로 이동할때는 노드를 한칸씩 위로 이동을 시키면서 해당 노드의 오른쪽이 막혀있고 오른쪽 위가 뚫려있거나
	// 왼쪽이 막혀있고 왼쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		if (IndexY % 2 == 0)
		{
			IndexX--;
		}

		IndexY--;

		if (IndexY < 0 || IndexX < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = IndexY + 1;

		if (IndexY % 2 == 0)
		{
			CornerX--;
		}

		if (IndexX - 1 >= 0 && CornerY < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 1)
		{
			CornerX = IndexX + 1;
		}

		CornerY = IndexY - 1;

		if (CornerX < m_CountX && IndexY - 2 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY - 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeLeft(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 왼쪽 위로 이동할때는 노드를 한칸씩 왼쪽 위로 이동을 시키면서 해당 노드의 아래쪽이 막혀있고 왼쪽 아래가 뚫려있거나
	// 오른쪽이 막혀있고 오른쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		IndexX--;

		if (IndexX < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;

		if (IndexY % 2 == 1)
		{
			CornerX = IndexX + 1;
		}

		int	CornerY = IndexY + 1;

		if (IndexY + 2 < m_CountY && CornerX < m_CountX)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY + 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 1)
		{
			CornerX = IndexX + 1;
		}

		CornerY = IndexY - 1;

		if (CornerX < m_CountX && IndexY - 2 >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY - 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		// 왼쪽 위 대각선 체크시 만약 현 노드가 코너가 아니라면 왼쪽 방향과 위쪽 방향을 체크하여
		// 코너가 있는지를 판단한다.
		NavNode* FindNode = GetRhombusNodeLeftTop(CheckNode, EndNode, End);

		// 위쪽 검사중 노드를 찾았다면 현재의 노드를 코너로 체크한다.
		if (FindNode)
		{
			return CheckNode;
		}

		FindNode = GetRhombusNodeLeftBottom(CheckNode, EndNode, End);

		if (FindNode)
		{
			return CheckNode;
		}
	}

	return nullptr;
}

NavNode* CNavigation::GetRhombusNodeLeftTop(NavNode* Node, NavNode* EndNode, const Vector3& End)
{
	// 위로 이동할때는 노드를 한칸씩 위로 이동을 시키면서 해당 노드의 오른쪽이 막혀있고 오른쪽 위가 뚫려있거나
	// 왼쪽이 막혀있고 왼쪽 위가 뚫려있으면 해당 노드는 코너가 된다.
	int	IndexY = Node->IndexY;
	int	IndexX = Node->IndexX;

	while (true)
	{
		if (IndexY % 2 == 0)
		{
			IndexX--;
		}

		IndexY++;

		if (IndexY >= m_CountY || IndexX < 0)
		{
			return nullptr;
		}

		NavNode* CheckNode = m_vecNode[IndexY * m_CountX + IndexX];

		if (CheckNode == EndNode)
		{
			return CheckNode;
		}

		else if (CheckNode->NodeType == Nav_Node_Type::Close)
		{
			return nullptr;
		}

		else if (CheckNode->TileType == Tile_Type::Wall)
		{
			return nullptr;
		}

		int	CornerX = IndexX;
		int	CornerY = IndexY + 1;

		if (IndexY % 2 == 1)
		{
			CornerX++;
		}

		if (CornerX < m_CountX && IndexY + 2 < m_CountY)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[(IndexY + 2) * m_CountX + IndexX]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}

		CornerX = IndexX;

		if (IndexY % 2 == 0)
		{
			CornerX = IndexX - 1;
		}

		CornerY = IndexY - 1;

		if (IndexX - 1 >= 0 && CornerY >= 0)
		{
			if (m_vecNode[CornerY * m_CountX + CornerX]->TileType == Tile_Type::Wall &&
				m_vecNode[IndexY * m_CountX + (IndexX - 1)]->TileType == Tile_Type::Normal)
			{
				return CheckNode;
			}
		}
	}

	return nullptr;
}

void CNavigation::AddDir(Node_Dir Dir, NavNode* Node)
{
	Node->SearchDirList.clear();

	switch (m_NodeShape)
	{
	case Tile_Shape::Rect:
		switch (Dir)
		{
		case Node_Dir::T:
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::LT);
			Node->SearchDirList.push_back(Node_Dir::RT);
			break;
		case Node_Dir::RT:
			Node->SearchDirList.push_back(Node_Dir::RT);
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::R);
			Node->SearchDirList.push_back(Node_Dir::LT);
			Node->SearchDirList.push_back(Node_Dir::RB);
			break;
		case Node_Dir::R:
			Node->SearchDirList.push_back(Node_Dir::R);
			Node->SearchDirList.push_back(Node_Dir::RB);
			Node->SearchDirList.push_back(Node_Dir::RT);
			break;
		case Node_Dir::RB:
			Node->SearchDirList.push_back(Node_Dir::RB);
			Node->SearchDirList.push_back(Node_Dir::R);
			Node->SearchDirList.push_back(Node_Dir::RT);
			Node->SearchDirList.push_back(Node_Dir::B);
			Node->SearchDirList.push_back(Node_Dir::LB);
			break;
		case Node_Dir::B:
			Node->SearchDirList.push_back(Node_Dir::B);
			Node->SearchDirList.push_back(Node_Dir::LB);
			Node->SearchDirList.push_back(Node_Dir::RB);
			break;
		case Node_Dir::LB:
			Node->SearchDirList.push_back(Node_Dir::LB);
			Node->SearchDirList.push_back(Node_Dir::B);
			Node->SearchDirList.push_back(Node_Dir::RB);
			Node->SearchDirList.push_back(Node_Dir::L);
			Node->SearchDirList.push_back(Node_Dir::LT);
			break;
		case Node_Dir::L:
			Node->SearchDirList.push_back(Node_Dir::L);
			Node->SearchDirList.push_back(Node_Dir::LT);
			Node->SearchDirList.push_back(Node_Dir::LB);
			break;
		case Node_Dir::LT:
			Node->SearchDirList.push_back(Node_Dir::LT);
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::RT);
			Node->SearchDirList.push_back(Node_Dir::L);
			Node->SearchDirList.push_back(Node_Dir::LB);
			break;
		}
		break;
	case Tile_Shape::Rhombus:
		switch (Dir)
		{
		case Node_Dir::T:
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::L);
			Node->SearchDirList.push_back(Node_Dir::LT);
			Node->SearchDirList.push_back(Node_Dir::R);
			Node->SearchDirList.push_back(Node_Dir::RT);
			break;
		case Node_Dir::RT:
			Node->SearchDirList.push_back(Node_Dir::RT);
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::R);
			break;
		case Node_Dir::R:
			Node->SearchDirList.push_back(Node_Dir::R);
			Node->SearchDirList.push_back(Node_Dir::RT);
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::RB);
			Node->SearchDirList.push_back(Node_Dir::B);
			break;
		case Node_Dir::RB:
			Node->SearchDirList.push_back(Node_Dir::RB);
			Node->SearchDirList.push_back(Node_Dir::B);
			Node->SearchDirList.push_back(Node_Dir::R);
			break;
		case Node_Dir::B:
			Node->SearchDirList.push_back(Node_Dir::B);
			Node->SearchDirList.push_back(Node_Dir::L);
			Node->SearchDirList.push_back(Node_Dir::LB);
			Node->SearchDirList.push_back(Node_Dir::R);
			Node->SearchDirList.push_back(Node_Dir::RB);
			break;
		case Node_Dir::LB:
			Node->SearchDirList.push_back(Node_Dir::LB);
			Node->SearchDirList.push_back(Node_Dir::B);
			Node->SearchDirList.push_back(Node_Dir::L);
			break;
		case Node_Dir::L:
			Node->SearchDirList.push_back(Node_Dir::L);
			Node->SearchDirList.push_back(Node_Dir::LT);
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::LB);
			Node->SearchDirList.push_back(Node_Dir::B);
			break;
		case Node_Dir::LT:
			Node->SearchDirList.push_back(Node_Dir::LT);
			Node->SearchDirList.push_back(Node_Dir::T);
			Node->SearchDirList.push_back(Node_Dir::L);
			break;
		}
		break;
	}
}

bool CNavigation::SortNode(NavNode* Src, NavNode* Dest)
{
	return Src->Total > Dest->Total;
}
//
//int CNavigation::SortNode(const void* Src, const void* Dest)
//{
//	NavNode* SrcNode = (NavNode*)Src;
//	NavNode* DestNode = (NavNode*)Dest;
//
//	if (SrcNode->Total < DestNode->Total)
//		return 1;
//
//	else if (SrcNode->Total > DestNode->Total)
//		return -1;
//
//	return 0;
//}
