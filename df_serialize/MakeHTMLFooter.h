    fprintf(file,
        "<html>\n"
        "<style>\n"
        "table, th, td, tr\n"
        "{\n"
        "    border: 1px solid black;\n"
        "    border-collapse: collapse;\n"
        "}\n"
        "</style>\n"
        "\n"
        "<h1>Enums</h1>\n"
        "%s"
        "<h1>Structs</h1>\n"
        "%s\n"
        "</html>\n",
        enums.str().c_str(),
        structs.str().c_str()
    );
    fclose(file);
    return true;
}
