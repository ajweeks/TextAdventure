
#include "structs.h"

#include <iostream>
#include <assert.h>

void Area::Describe() const
{
	std::cout << std::endl << "You are in " << m_Name << std::endl;

	DescribeItems();
	DescribeNeighbors();

	std::cout << std::endl;
}

void Area::DescribeItems() const
{
	if (m_Items.empty())
	{
		std::cout << "There is nothing in this area" << std::endl;
		return;
	}
	std::cout << "In this area you find: " << std::endl;
	for (size_t i = 0; i < m_Items.size(); i++)
	{
		if (i > 0) std::cout << ", ";
		std::cout << m_Items[i]->m_Name;
	}
	std::cout << std::endl;
}

void Area::DescribeNeighbors() const
{
	assert(!m_Neighbors.empty());

	std::cout << "You can go to: " << std::endl;
	int placeCount = 0;
	for (size_t i = 0; i < m_Neighbors.size(); i++)
	{
		if (m_Neighbors[i].first)
		{
			if (placeCount > 0) std::cout << ", ";
			std::cout << *(m_Neighbors[i].first) << " (" << DirectionToShortString(m_Neighbors[i].second) << ")";
			++placeCount;
		}
	}
	std::cout << std::endl;
}


std::ostream& operator<<(std::ostream& stream, const Item& item)
{
	stream << item.m_Name;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Area& area)
{
	stream << area.m_Name;
	return stream;
}
