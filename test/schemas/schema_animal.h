// See readme.md for details of describing a schema

SCHEMA_INHERIT_BEGIN(Lifeforms, Animal, Lifeforms::Lifeform)
    SCHEMA_FIELD(DietType, dietType, Lifeforms::DietType::Herbivore, "What type of food the plant eats.")
    SCHEMA_FIELD(float, aggression, 0.5f, "The probability of the animal to attack an animal it sees as equal.")
    SCHEMA_FIELD(float, meat, 1.0f, "The number of kilograms of meat on the animal.")
    SCHEMA_FIELD(int, litterMin, 1, "The minimum number of babies in a litter.")
    SCHEMA_FIELD(int, litterMax, 1, "The maximum number of bablies in a litter.")
SCHEMA_END()
