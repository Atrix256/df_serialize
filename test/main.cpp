// This switch is to show that it can work without STL
#define ALLOW_STL false

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Include the files we need / do our setup for dynamic array, static array and dynamic string types

#if ALLOW_STL

#include <vector>
#include <array>
#include <string>

#else

#include "stl_alternatives.h"
#define TDYNAMICARRAY MyVector
#define TSTATICARRAY MyArray
#define TSTRING MyString

#define TDYNAMICARRAY_SIZE(x) x.GetSize()

#endif

// Expand the schemas

#include "types.h"
#include "html.h"
#include "json.h"
#include "binary.h"

int main(int argc, char** argv)
{
    // write some HTML documentation about the schemas
    WriteHTML("testdata/index.html");

    // serialization testing
    Lifeforms::Root root;
    {
        // Read some data in from a JSON file
        if (!ReadFromJSONFile(root, "testdata/life.json"))
        {
            printf("Could not read testdata/life.json!!\n");
            return 1;
        }

        // Modify the data
        for (size_t index = 0; index < TDYNAMICARRAY_SIZE(root.lifeForms); ++index)
        {
            Lifeforms::LifeformVariant& variant = root.lifeForms[index];
            switch (variant._index)
            {
                case Lifeforms::LifeformVariant::c_index_plant:
                {
                    variant.plant.edibleMatter = 100.0f;
                    break;
                }
                case Lifeforms::LifeformVariant::c_index_animal:
                {
                    variant.animal.meat = 0.0f;
                    break;
                }
                case Lifeforms::LifeformVariant::c_index_None:
                {
                    // No type, this variant is null
                    break;
                }
                default:
                {
                    printf("Unknown variant type encountered!");
                    return 1;
                }
            }
        }

        // add a new variant entry to the life forms array
        {
            Lifeforms::LifeformVariant newLifeForm;
            newLifeForm._index = Lifeforms::LifeformVariant::c_index_animal;
            newLifeForm.animal.name = "wolf";
            newLifeForm.animal.description = "runs in packs";
            newLifeForm.animal.dietType = Lifeforms::DietType::Carnivore;
            newLifeForm.animal.litterMin = 1;
            newLifeForm.animal.litterMax = 5;
            newLifeForm.animal.meat = 0.1f;
            newLifeForm.animal.uniqueID = 0;  // Note: this is not serialized so if you set it to non default value, it'll make serialize out/in round trip fail equality test
            root.lifeForms.push_back(newLifeForm);
        }

        // write the modified data as JSON
        if (!WriteToJSONFile(root, "testdata/life2.json"))
        {
            printf("Could not write testdata/life2.json!!\n");
            return 1;
        }

        // Read the modified data as JSON
        Lifeforms::Root root2;
        if (!ReadFromJSONFile(root2, "testdata/life2.json"))
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
        if (!WriteToBinaryFile(root, "testdata/life2.dat"))
        {
            printf("Could not write testdata/life2.dat!!\n");
            return 1;
        }

        // Read the modified data
        Lifeforms::Root root3;
        if (!ReadFromBinaryFile(root3, "testdata/life2.dat"))
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

    printf("Success!\n");
    return 0;
}
