// The Plant schema, deriving from Lifeform. Included by schemas.h.

SCHEMA_INHERIT_BEGIN(Lifeforms, Plant, Lifeforms::Lifeform, "A plant based life form")
    SCHEMA_FIELD(DietType, dietType, Lifeforms::DietType::Photosynthesis, "What type of food the plant eats.")
    SCHEMA_FIELD(float, edibleMatter, 1.0f, "The number of kilograms of edible matter on the plant.")
    SCHEMA_FIELD(bool, poisonous, false, "Whether the plant is poisonous")
    SCHEMA_STATIC_ARRAY(float, albedo, 3, { 0.23f COMMA 0.27f COMMA 0.04f }, "RGB albedo of the plant")
SCHEMA_END()
