#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  sort(segments.begin(),segments.end(),
        [](const Segment& a, const Segment& b)
        {
            return a.start<b.start;    
        }
      );
      
      
  for (size_t index = 0; index < segments.size(); ++index) {
    int start_of_CommonSegment = segments[index].start;
    int end_of_CommonSegment = segments[index].end;
    size_t offset =1;
    for( ; index+offset<segments.size() &&
        (segments[index+offset].start >= start_of_CommonSegment && segments[index+offset].start <= end_of_CommonSegment) ;
        offset++)
    {
        start_of_CommonSegment = segments[index+offset].start;
        if(segments[index+offset].end<end_of_CommonSegment)
        {
            end_of_CommonSegment = segments[index+offset].end;
        }
    }
    index = index + offset;
    points.push_back(end_of_CommonSegment);
  }    
    
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
