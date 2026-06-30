#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string courseName;
    float creditHours;
    float pointsEarned;

public:
    Course();
    Course(const std::string& name, float credits, float points);

    std::string getCourseName() const { return courseName; }
    float getCreditHours() const { return creditHours; }
    float getPointsEarned() const { return pointsEarned; }

    void setCourseName(const std::string& name) { courseName = name; }
    void setCreditHours(float credits) { creditHours = credits; }
    void setPointsEarned(float points) { pointsEarned = points; }

    float getQualityPoints() const { return creditHours * pointsEarned; }
};

#endif // COURSE_H