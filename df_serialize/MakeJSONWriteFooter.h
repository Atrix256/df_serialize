bool WriteTextFile(const char* fileName, const std::string& data)
{
    FILE* file = nullptr;
    fopen_s(&file, fileName, "w+b");
    if (!file)
        return false;
    fwrite(data.c_str(), data.length(), 1, file);
    fclose(file);
    return true;
}

// Read a structure from a JSON string
template<typename TROOT>
void WriteToJSON(TROOT& root, std::string& data)
{
    std::stringstream output;
    JSONWrite(root, output, 0);
    data = output.str();
}

// Read a structure from a JSON file
template<typename TROOT>
bool WriteToJSON(TROOT& root, const char* fileName)
{
    std::string data;
    WriteToJSON(root, data);

    if (!WriteTextFile(fileName, data))
    {
        MAKE_JSON_LOG("Could not write file %s", fileName);
        return false;
    }

    return true;
}
