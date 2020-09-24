// An enum used by both plants and animals.
ENUM_BEGIN(Lifeforms, DietType, "The type of diets life forms can have")
    ENUM_ITEM(Herbivore, "Eats plants")
    ENUM_ITEM(Carnivore, "Eats animals")
    ENUM_ITEM(Omnivore, "Eats both plants and animals")
    ENUM_ITEM(Photosynthesis, "Uses sublight to produce sugars")
ENUM_END()

// Basic info about any life form. Plants and animals inherit this.
SCHEMA_BEGIN(Lifeforms, Lifeform, "The base class for all life forms")
    SCHEMA_FIELD(TSTRING, name, "", "The name of the life form.")
    SCHEMA_FIELD(TSTRING, description, "", "A description of the life form.")
    SCHEMA_FIELD(uint64_t, uniqueID, 0, "A unique identifier for the life form.")
SCHEMA_END()

// Schemas defined in different files
#include "schema_plant.h"
#include "schema_animal.h"

// A variant which can be a plant, an animal, or nothing
VARIANT_BEGIN(Lifeforms, LifeformVariant, "A lifeform of any type")
    VARIANT_TYPE(Lifeforms::Plant, plant, Lifeforms::Plant{}, "a plant")
    VARIANT_TYPE(Lifeforms::Animal, animal, Lifeforms::Animal{}, "an animal")
VARIANT_END()

// A schema to unify the list of plants and animals into a single thing
SCHEMA_BEGIN(Lifeforms, Root, "The base document type of lifeform descriptions")
    SCHEMA_DYNAMIC_ARRAY(LifeformVariant, lifeForms, "The full list of life forms")
SCHEMA_END()
