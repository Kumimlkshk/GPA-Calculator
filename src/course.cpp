#include "course.h"

Course::Course()
    : courseName("N/A"), creditHours(0.0f), pointsEarned(0.0f) {}

Course::Course(const std::string& name, float credits, float points)
    : courseName(name), creditHours(credits), pointsEarned(points) {}