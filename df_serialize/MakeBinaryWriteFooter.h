bool WriteBinaryFile(const char* fileName, std::vector<char>& data)
{
    FILE* file = nullptr;
    fopen_s(&file, fileName, "w+b");
    if (!file)
        return false;
    fwrite(data.data(), data.size(), 1, file);
    fclose(file);
    return true;
}

template<typename TROOT>
void WriteToBinary(TROOT& root, std::vector<char>& output)
{
    BinaryWrite(root, output);
}

// Read a structure from a JSON file
template<typename TROOT>
bool WriteToBinary(TROOT& root, const char* fileName)
{
    std::vector<char> out;
    WriteToBinary(root, out);

    if (!WriteBinaryFile(fileName, out))
    {
        MAKE_BINARY_LOG("Could not write file %s", fileName);
        return false;
    }

    return true;
}
