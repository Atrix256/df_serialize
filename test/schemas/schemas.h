// All the schemas are included into this file.
// This way, different schemas can be defined in different files for organization purposes.

// Make sure that any types the schemas represent are defined
#include <string> // needed for names
#include <vector> // needed for arrays

// An enum used by both plants and animals.
ENUM_BEGIN(Lifeforms, DietType)
    ENUM_ITEM(Herbivore, "Eats plants")
    ENUM_ITEM(Carnivore, "Eats animals")
    ENUM_ITEM(Omnivore, "Eats both plants and animals")
    ENUM_ITEM(Photosynthesis, "Uses sublight to produce sugars")
ENUM_END()

// Basic info about any life form. Plants and animals inherit this.
SCHEMA_BEGIN(Lifeforms, Lifeform)
    SCHEMA_FIELD(std::string, name, "", "The name of the life form.")
    SCHEMA_FIELD(std::string, description, "", "A description of the life form.")
    SCHEMA_FIELD(uint64_t, uniqueID, 0, "A unique identifier for the life form.")
SCHEMA_END()

// Other Schemas
#include "schema_plant.h"
#include "schema_animal.h"

// A variant which can be a plant, an animal, or nothing
VARIANT_BEGIN(Lifeforms, LifeformVariant)
    VARIANT_TYPE(Plant, plant, Plant{}, "a plant")
    VARIANT_TYPE(Animal, animal, Animal{}, "an animal")
VARIANT_END()

// A schema to unify the list of plants and animals into a single thing
SCHEMA_BEGIN(Lifeforms, Root)
    SCHEMA_ARRAY(LifeformVariant, lifeForms, "The full list of life forms")
SCHEMA_END()
