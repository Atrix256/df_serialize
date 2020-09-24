// The Animals struct, deriving from Lifeform. Included by schemas.h.

STRUCT_INHERIT_BEGIN(Lifeforms, Animal, Lifeforms::Lifeform, "An animal based life form")
    STRUCT_FIELD(DietType, dietType, Lifeforms::DietType::Herbivore, "What type of food the animal eats.")
    STRUCT_FIELD(float, aggression, 0.5f, "The probability of the animal to attack an animal it sees as equal.")
    STRUCT_FIELD(float, meat, 1.0f, "The number of kilograms of meat on the animal.")
    STRUCT_FIELD(int, litterMin, 1, "The minimum number of babies in a litter.")
    STRUCT_FIELD(int, litterMax, 1, "The maximum number of bablies in a litter.")
STRUCT_END()
