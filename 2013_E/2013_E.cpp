//
//  main.cpp
//  AISD_E
//
//  Created by sakydpozrux on 25.05.2013.
//

#include <iostream>
#include <vector>
#include <algorithm>



class IntervalTree
{
public:
    // Constructor. Tree must have size of upper power of two on range.
    // I also reserve N leafs and N-1 other nodes and trash in 0 all zeroed.
    IntervalTree(const int n)
    : N(uppertpowerof2(n)), vecMax(2*N, 0), vecWeig(2*N, 0)
    { }
    
    // Just return actual Max in this IntervalTree. Sometimes it's named top().
    int max() const
    {
        return vecMax[1];
    }
    
    // I changed name to update (from insert) because it has to work with negative values (same as remove).
    void update(int x, int y, int weight)
    {
        update2(x, y, weight, 1, 0, N-1); // By default run this on root (1) and on whole range [0,N-1].
    }

private:
    // Upper power of 2 to fit all needed elements
    const int N;
    
    std::vector< int > vecMax; // Tree of maxes for each node
    std::vector< int > vecWeig; // Tree of weights for each node
    
    void update2(int x, int y, int weight, int node, int a, int b)
    {
        // Finish recurrence after updating weights if range [a,b] contains [x,y].
        if ( a >= x && b <= y )
        {
            vecWeig[node] += weight;
            vecMax[node] += weight;
            return;
        }
        
        // First update the sons of node.
        int mid = (a+b)/2;
        if ( x <= mid ) update2( x, y, weight, 2*node,   a,     mid ); // for left sons
        if ( y > mid  ) update2( x, y, weight, 2*node+1, mid+1, b   ); // for right sons
        
        // When sons are updated it's time to update this node using values just calculated above.
        vecMax[node] = std::max( vecMax[2*node], vecMax[2*node+1] ) + vecWeig[node];
    }
    
    // Return upper power of 2 for n. It has to be unsigned to have 1 on the least significant bit.
    static unsigned int uppertpowerof2(const unsigned int n)
    {
        unsigned int val = 1;
        while (val <= n) val <<= 1;
        return val;
    }
};



struct rect
{
    int x;
    int y1;
    int y2;
    int w; // Values from -10000 to 10000
    
    rect(int x, int y1, int y2, int w)
    : x(x), y1(y1), y2(y2), w(w)
    { }
};

bool rectCompare (const rect a, const rect b)
{
    return (a.x < b.x) || (a.x == b.x && a.w > b.w);
}

bool widthCompare (const int* a, const int* b)
{
    return (*a < *b);
}


int mapIntervals(std::vector<rect>& rectangles)
{
    std::vector<int*> widths;
    
    for (std::vector<rect>::iterator iter = rectangles.begin(); iter != rectangles.end(); ++iter)
    {
        widths.push_back(&(iter->y1));
        widths.push_back(&(iter->y2));
    }
    
    std::sort( widths.begin(), widths.end(), widthCompare );
    
    int widthCounter = 0; // Relative counter of y
    int widthLast = *(widths[0]) = 0; // First y is mapped to 0. That's easy.
    
    for (std::vector<int*>::iterator iter = widths.begin(); iter != widths.end(); ++iter)
    {
        if (**iter == widthLast) // It's still same y, so I'm using same number as before.
        {
            **iter = widthCounter;
        }
        else // It's something else so I'm using next number.
        {
            widthLast = **iter;
            **iter = ++widthCounter;
        }
    }
    
    return *(widths.back());
}


int main()
{
    // Number of clouds
    int n = 0;
    std::cin >> n;
    
    // Vector of beginnings and ends of clouds (rectangles)
    std::vector< rect > rectangles;
    rectangles.reserve(2*n);
    
    // Values describing each cloud
    int x1, y1, x2, y2, w;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> x1 >> y1 >> x2 >> y2 >> w;
        rectangles.push_back( rect(x1, y1, y2, w) ); // Push beginning of the cloud
        rectangles.push_back( rect(x2, y1, y2, -w) ); // Push end of the cloud
    }
    
    // Sort by x1 for beginnings and x2 for ends.
    std::sort( rectangles.begin(), rectangles.end(), rectCompare );
    
    IntervalTree Tree( mapIntervals(rectangles) );
    
    // Below is broom. I sweep rectangles by going through the vector sorted by x.
    int last = -1;
    int finalMax = 0;
    for (std::vector<rect>::iterator iter = rectangles.begin(); iter != rectangles.end(); ++iter)
    {
        if (last != iter->x || iter->w < 0)
            finalMax = std::max(finalMax, Tree.max());
        
        Tree.update( iter->y1 , iter->y2 , iter->w );
        last = iter->x;
    }
    // I think I don't need to worry about updating finalMax after last rectangle.
    // It must be end of rectangle so it only decrease actual Max in the Tree.
    
    std::cout << finalMax << std::endl;
    
    
    return 0;
}

