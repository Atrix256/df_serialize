// The Plant struct, deriving from Lifeform. Included by schemas.h.

STRUCT_INHERIT_BEGIN(Lifeforms, Plant, Lifeforms::Lifeform, "A plant based life form")
    STRUCT_FIELD(DietType, dietType, Lifeforms::DietType::Photosynthesis, "What type of food the plant eats.")
    STRUCT_FIELD(float, edibleMatter, 1.0f, "The number of kilograms of edible matter on the plant.")
    STRUCT_FIELD(bool, poisonous, false, "Whether the plant is poisonous")
    STRUCT_STATIC_ARRAY(float, albedo, 3, { 0.23f COMMA 0.27f COMMA 0.04f }, "RGB albedo of the plant")
STRUCT_END()
