// See readme.md for details of describing a schema

SCHEMA_INHERIT_BEGIN(Lifeforms, Plant, Lifeforms::Lifeform)
    SCHEMA_FIELD(DietType, dietType, Lifeforms::DietType::Photosynthesis, "What type of food the plant eats.")
    SCHEMA_FIELD(float, edibleMatter, 1.0f, "The number of kilograms of edible matter on the plant.")
    SCHEMA_FIELD(bool, poisonous, false, "Whether the plant is poisonous")
SCHEMA_END()
