#include "types.h"
#include "html.h"

#define MAKE_JSON_LOG(...) printf(__VA_ARGS__);
#include "json.h"

#define MAKE_BINARY_LOG(...) printf(__VA_ARGS__);
#include "binary.h"

int main(int argc, char** argv)
{
    // write some HTML documentation about the schemas
    WriteHTML("testdata/index.html");

    // serialization testing
    Lifeforms::Root root;
    {
        // Read some data in from a JSON file
        if (!ReadFromJSON(root, "testdata/life.json"))
        {
            printf("Could not read testdata/life.json!!\n");
            return 1;
        }

        // Modify the data and write it as JSON
        root.animals[0].meat = 0.0f;
        if (!WriteToJSON(root, "testdata/life2.json"))
        {
            printf("Could not write testdata/life2.json!!\n");
            return 1;
        }

        // Read the modified data as JSON
        Lifeforms::Root root2;
        if (!ReadFromJSON(root2, "testdata/life2.json"))
        {
            printf("Could not read testdata/life2.json!!\n");
            return 1;
        }

        // Make sure the modified data from the JSON file matches the modified data in memory
        if (root != root2)
        {
            printf("Round trip JSON didn't work correctly.\n");
            return 1;
        }

        // Write the modified data as binary
        if (!WriteToBinary(root, "testdata/life2.dat"))
        {
            printf("Could not write testdata/life2.dat!!\n");
            return 1;
        }

        // Read the modified data
        Lifeforms::Root root3;
        if (!ReadFromBinary(root3, "testdata/life2.dat"))
        {
            printf("Could not read testdata/life2.dat!!\n");
            return 1;
        }

        // Make sure the modified data from the binary file matches the modified data in memory
        if (root != root3)
        {
            printf("Round trip binary didn't work correctly.\n");
            return 1;
        }
    }

    return 0;
}
