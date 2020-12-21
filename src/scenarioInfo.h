#pragma once

#include <sp2/string.h>

class ScenarioInfo
{
public:
    ScenarioInfo(const sp::string &resource_name);

    sp::string resource_name;
    sp::string name;
    sp::string author;
    sp::string category;
    sp::string description;
    uint64_t required_version{0};
    std::vector<std::pair<sp::string, sp::string>> variations;

    static std::vector<ScenarioInfo> getAll();

    bool operator<(const ScenarioInfo &other) const;

private:
    void parseData(const sp::string &data);
};
