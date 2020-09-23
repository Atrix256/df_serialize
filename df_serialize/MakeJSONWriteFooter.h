bool WriteTextFile(const char* fileName, const TSTRING& data)
{
    FILE* file = nullptr;
    fopen_s(&file, fileName, "w+b");
    if (!file)
        return false;
    fwrite(data.c_str(), data.length(), 1, file);
    fclose(file);
    return true;
}

// Write a structure to a JSON string
template<typename TROOT>
void WriteToJSONBuffer(TROOT& root, TSTRING& data)
{
    // make the document
    rapidjson::Document document;
    rapidjson::Value rootValue = MakeJSONValue(root, document.GetAllocator());

    // make the string
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    rootValue.Accept(writer);
    data = buffer.GetString();
}

// Write a structure to a JSON file
template<typename TROOT>
bool WriteToJSONFile(TROOT& root, const char* fileName)
{
    TSTRING data;
    WriteToJSONBuffer(root, data);
    if (!WriteTextFile(fileName, data))
    {
        DFS_LOG("Could not write file %s", fileName);
        return false;
    }

    return true;
}
