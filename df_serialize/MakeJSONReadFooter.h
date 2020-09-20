inline bool LoadTextFile(const char* fileName, std::vector<char>& data)
{
    // open the file if we can
    FILE* file = nullptr;
    fopen_s(&file, fileName, "rb");
    if (!file)
        return false;

    // get the file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // read the file into memory and return success.
    // don't forget the null terminator
    data.resize(size + 1);
    fread(data.data(), 1, size, file);
    fclose(file);
    data[data.size() - 1] = 0;
    return true;
}

// Read a structure from a JSON string
template<typename TROOT>
bool ReadFromJSON(TROOT& root, std::vector<char>& data)
{
    rapidjson::Document document;
    rapidjson::ParseResult ok = document.Parse<rapidjson::kParseCommentsFlag | rapidjson::kParseTrailingCommasFlag>(data.data());
    if (!ok)
    {
        size_t errorOffset = ok.Offset();

        // count what line we are on
        int lineNumber = 1;
        {
            size_t index = errorOffset;
            while (index > 0)
            {
                if (data[index] == '\n')
                    lineNumber++;
                index--;
            }
        }

        // back up to the beginning of the line
        while (errorOffset > 0 && data[errorOffset] != '\n')
            errorOffset--;
        errorOffset++;

        // get the next couple lines from the error
        size_t end = errorOffset;
        for (int i = 0; i < 4; ++i)
        {
            while (data[end] != 0 && data[end] != '\n')
                end++;
            if (data[end] != 0)
                end++;
        }

        std::string s(end - errorOffset + 1, 0);
        memcpy(&s[0], &data[errorOffset], end - errorOffset);

        MAKE_JSON_LOG("JSON parse error line %i\n%s\n%s\n", lineNumber, GetParseError_En(ok.Code()), s.c_str());
        return false;
    }

    return JSONRead(root, document);
}

// Read a structure from a JSON file
template<typename TROOT>
bool ReadFromJSON(TROOT& root, const char* fileName)
{
    std::vector<char> fileData;
    if (!LoadTextFile(fileName, fileData))
    {
        MAKE_JSON_LOG("Could not read file %s", fileName);
        return false;
    }

    return ReadFromJSON(root, fileData);
}
