#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <vector>
#include "course.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddCourse();
    void onRemoveCourse();
    void onClearAll();
    void onCalculateGPA();
    void onNumCoursesChanged(int value);
    void onCourseDataChanged();

private:
    void setupUI();
    void updateTable();
    void calculateAndDisplayGPA();
    void createCourseInputRow();

    QSpinBox* numCoursesSpinBox;
    QTableWidget* courseTable;
    QLabel* totalCreditHoursLabel;
    QLabel* semesterGPALabel;
    QPushButton* addCourseButton;
    QPushButton* removeCourseButton;
    QPushButton* clearAllButton;
    QPushButton* calculateButton;
    
    std::vector<Course> courses;
};

#endif // MAINWINDOW_H