#include <vector>
#include <string>

std::vector<int> Hand::enum() {
    vector<int> ids;
    for (int i = line.size() - 1, i > -1, i--) {
        ids.push_back(line[i]->get_id());
    return ids;
};

