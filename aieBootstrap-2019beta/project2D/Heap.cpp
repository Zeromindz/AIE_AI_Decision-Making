#include <vector>
#include "Heap.h"

#include "DebugNew.h"

using namespace std;

Heap::Heap()
{

}

Heap::~Heap()
{

}

//=========================================================================/
// Push:
// 1) Add new value to the end of the tree
// 2) Check if new data is less than its parent
// 3) If so, swap them, then if swapped node is still out of position 
// set current to old parent and parent to current's parent
//________________________________________________________________/
void Heap::Push(GraphNode* _value)
{
    // Add new value
    m_Data.push_back(_value);

    int currentIndex = Size() - 1;
    int parentIndex = GetParentIndex(currentIndex);

    // Check if child is less than parent
    while (m_Data[currentIndex]->m_FScore < m_Data[parentIndex]->m_FScore)
    {
        // Swap
        GraphNode* temp = m_Data[currentIndex];
        m_Data[currentIndex] = m_Data[parentIndex];
        m_Data[parentIndex] = temp;

        // Current becomes the old parent
        currentIndex = parentIndex;
        parentIndex = GetParentIndex(currentIndex);
    }
}

//============================================/
// Pop:
// 1) Store the value to be popped
// 2) Move the last node to the top
// 3) Reorder the tree
//__________________________________________/

GraphNode* Heap::Pop()
{
    if (Size() == 0)
    {
        return nullptr;
    }
    // Get data so we can return it
    GraphNode* result = m_Data[0];
    // Remove the data
    m_Data[0] = m_Data[Size() - 1];

    // Reorder the tree
    int currentIndex = 0;
    int child1Index = GetChild1Index(currentIndex);
    int child2Index = GetChild2Index(currentIndex);

    // Find smallest child
    int smallestIndex = child1Index;
    // If the 2nd child is less than the smallest child, it becomes the smallest
    if (m_Data[child2Index]->m_FScore < m_Data[smallestIndex]->m_FScore)
    {
        smallestIndex = child2Index;
    }
    // Check if smallest child is less than parent
    while (m_Data[smallestIndex]->m_FScore < m_Data[currentIndex]->m_FScore)
    {
        // If so, swap them
        GraphNode* temp = m_Data[smallestIndex];
        m_Data[smallestIndex] = m_Data[currentIndex];
        m_Data[currentIndex] = temp;

        // Update indices
        currentIndex = smallestIndex;
        child1Index = GetChild1Index(currentIndex);
        child2Index = GetChild2Index(currentIndex);

        // Find smallest child
        smallestIndex = child1Index;
        if (m_Data[child2Index]->m_FScore < m_Data[smallestIndex]->m_FScore)
        {
            smallestIndex = child2Index;
        }

    }
    m_Data.pop_back();
    return result;
}

//============================================/
// Peek:
//
//__________________________________________/
GraphNode* Heap::Peek()
{
    if (Size() > 0)
    {
        return m_Data[0];
    }
    return nullptr;
}

bool Heap::Contains(GraphNode* _node)
{
    bool result = false;
    result = count(m_Data.begin(), m_Data.end(), _node);

    return result;
}

//============================================/
// Size:
//
//__________________________________________/
int Heap::Size()
{
    return (int)m_Data.size();
}

//============================================/
// Clear:
// 
//__________________________________________/
void Heap::Clear()
{
    m_Data.clear();
}

//============================================/
// Get Parent Index:
//
//__________________________________________/
int Heap::GetParentIndex(int _index)
{
    return (_index - 1) / 2;
}

//============================================/
// Get Child 1 Index:
// 
//__________________________________________/
int Heap::GetChild1Index(int _index)
{
    int result = (2 * _index) + 1;
    if (result < Size())
    {
        return result;
    }
    // Out of range/
    return _index;
}

//============================================/
// Get Child 2 Index:
//          
//__________________________________________/
int Heap::GetChild2Index(int _index)
{
    int result = (2 * _index) + 2;
    if (result < Size())
    {
        return result;
    }
    // Out of range
    return _index;
}
