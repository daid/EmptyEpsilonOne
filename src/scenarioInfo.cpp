#include "scenarioInfo.h"

#include <sp2/stringutil/convert.h>
#include <sp2/io/resourceProvider.h>

ScenarioInfo::ScenarioInfo(const sp::string &resource_name)
    : resource_name(resource_name), name(resource_name), author("UNSET"), category("UNSET")
{
    auto stream = sp::io::ResourceProvider::get(resource_name);
    if (!stream)
        return;

    sp::string data;
    while (true)
    {
        auto line = stream->readLine().strip();
        if (!line.startswith("--"))
            break;
        while (line[0] == '-')
            line.erase(line.begin());
        line = line.strip();
        if (line[0] == '@')
        {
            parseData(data);
            data = line.substr(1);
        }
        else
        {
            data = data + "\n" + line;
        }
    }
    parseData(data);
}

void ScenarioInfo::parseData(const sp::string &data)
{
    if (data.empty())
        return;
    int sep = data.find(":");
    auto key = data.substr(0, sep).strip().upper();
    auto value = data.substr(sep + 1).strip();

    if (key == "NAME")
    {
        name = value;
    }
    else if (key == "AUTHOR")
    {
        author = value;
    }
    else if (key == "MINIMAL VERSION")
    {
        required_version = sp::stringutil::convert::toInt(value);
    }
    else if (key == "CATEGORY")
    {
        category = value;
    }
    else if (key == "DESCRIPTION")
    {
        description = value;
    }
    else if (key == "VARIATION")
    {
        if (value.find("\n") == -1)
            variations.emplace_back(value, "");
        else
            variations.emplace_back(value.substr(0, value.find("\n")), value.substr(value.find("\n") + 1));
    }
    else
    {
        LOG(Warning, "Unknown metadata in scenario:", data);
    }
}

std::vector<ScenarioInfo> ScenarioInfo::getAll()
{
    std::vector<ScenarioInfo> result;
    for (const auto &resource_name : sp::io::ResourceProvider::find("scenario/*.lua"))
    {
        ScenarioInfo si(resource_name);
        if (si.required_version > 0)
            result.push_back(si);
    }
    std::sort(result.begin(), result.end());
    return result;
}

bool ScenarioInfo::operator<(const ScenarioInfo &other) const
{
    if (category != other.category)
        return category < other.category;
    return name < other.name;
}
