#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QString>
#include <QMessageBox>
#include <iomanip>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    setWindowTitle("GPA Calculator");
    resize(700, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // Input Section
    QGroupBox* inputGroup = new QGroupBox("Course Entry", this);
    QVBoxLayout* inputLayout = new QVBoxLayout(inputGroup);

    QHBoxLayout* numCoursesLayout = new QHBoxLayout();
    QLabel* numCoursesLabel = new QLabel("Number of Courses:");
    numCoursesSpinBox = new QSpinBox();
    numCoursesSpinBox->setMinimum(1);
    numCoursesSpinBox->setMaximum(20);
    numCoursesSpinBox->setValue(1);
    numCoursesLayout->addWidget(numCoursesLabel);
    numCoursesLayout->addWidget(numCoursesSpinBox);
    numCoursesLayout->addStretch();

    inputLayout->addLayout(numCoursesLayout);
    mainLayout->addWidget(inputGroup);

    // Table Section
    QGroupBox* tableGroup = new QGroupBox("Courses", this);
    QVBoxLayout* tableLayout = new QVBoxLayout(tableGroup);

    courseTable = new QTableWidget();
    courseTable->setColumnCount(4);
    courseTable->setHorizontalHeaderLabels({"Course Name", "Credit Hours", "Points Earned", "Quality Points"});
    courseTable->horizontalHeader()->setStretchLastSection(false);
    courseTable->setColumnWidth(0, 200);
    courseTable->setColumnWidth(1, 120);
    courseTable->setColumnWidth(2, 120);
    courseTable->setColumnWidth(3, 120);
    courseTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableLayout->addWidget(courseTable);
    mainLayout->addWidget(tableGroup);

    // Buttons Section
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addCourseButton = new QPushButton("Add Course");
    removeCourseButton = new QPushButton("Remove Selected");
    clearAllButton = new QPushButton("Clear All");
    calculateButton = new QPushButton("Calculate GPA");

    buttonLayout->addWidget(addCourseButton);
    buttonLayout->addWidget(removeCourseButton);
    buttonLayout->addWidget(clearAllButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(calculateButton);

    mainLayout->addLayout(buttonLayout);

    // Results Section
    QGroupBox* resultsGroup = new QGroupBox("Semester Report", this);
    QVBoxLayout* resultsLayout = new QVBoxLayout(resultsGroup);

    totalCreditHoursLabel = new QLabel("Total Credit Hours: 0.00");
    semesterGPALabel = new QLabel("Semester GPA: 0.00");

    totalCreditHoursLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    semesterGPALabel->setStyleSheet("font-size: 14px; font-weight: bold; color: darkblue;");

    resultsLayout->addWidget(totalCreditHoursLabel);
    resultsLayout->addWidget(semesterGPALabel);

    mainLayout->addWidget(resultsGroup);

    // Connect signals
    connect(numCoursesSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onNumCoursesChanged);
    connect(addCourseButton, &QPushButton::clicked, this, &MainWindow::onAddCourse);
    connect(removeCourseButton, &QPushButton::clicked, this, &MainWindow::onRemoveCourse);
    connect(clearAllButton, &QPushButton::clicked, this, &MainWindow::onClearAll);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateGPA);
}

void MainWindow::onNumCoursesChanged(int value) {
    int currentRows = courseTable->rowCount();
    
    if (value > currentRows) {
        for (int i = currentRows; i < value; i++) {
            createCourseInputRow();
        }
    } else if (value < currentRows) {
        for (int i = currentRows - 1; i >= value; i--) {
            courseTable->removeRow(i);
        }
    }
}

void MainWindow::createCourseInputRow() {
    int row = courseTable->rowCount();
    courseTable->insertRow(row);

    QLineEdit* courseNameEdit = new QLineEdit();
    QDoubleSpinBox* creditHoursSpinBox = new QDoubleSpinBox();
    QDoubleSpinBox* pointsSpinBox = new QDoubleSpinBox();
    QLabel* qualityPointsLabel = new QLabel("0.00");

    creditHoursSpinBox->setMinimum(0.0);
    creditHoursSpinBox->setMaximum(6.0);
    creditHoursSpinBox->setDecimals(1);
    creditHoursSpinBox->setValue(3.0);

    pointsSpinBox->setMinimum(0.0);
    pointsSpinBox->setMaximum(4.0);
    pointsSpinBox->setDecimals(2);
    pointsSpinBox->setValue(4.0);

    // Update quality points when values change
    connect(creditHoursSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, row, qualityPointsLabel](double) {
        QDoubleSpinBox* credits = qobject_cast<QDoubleSpinBox*>(courseTable->cellWidget(row, 1));
        QDoubleSpinBox* points = qobject_cast<QDoubleSpinBox*>(courseTable->cellWidget(row, 2));
        if (credits && points) {
            double quality = credits->value() * points->value();
            qualityPointsLabel->setText(QString::number(quality, 'f', 2));
        }
    });

    connect(pointsSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this, row, qualityPointsLabel](double) {
        QDoubleSpinBox* credits = qobject_cast<QDoubleSpinBox*>(courseTable->cellWidget(row, 1));
        QDoubleSpinBox* points = qobject_cast<QDoubleSpinBox*>(courseTable->cellWidget(row, 2));
        if (credits && points) {
            double quality = credits->value() * points->value();
            qualityPointsLabel->setText(QString::number(quality, 'f', 2));
        }
    });

    courseTable->setCellWidget(row, 0, courseNameEdit);
    courseTable->setCellWidget(row, 1, creditHoursSpinBox);
    courseTable->setCellWidget(row, 2, pointsSpinBox);
    courseTable->setCellWidget(row, 3, qualityPointsLabel);
}

void MainWindow::onAddCourse() {
    courseTable->insertRow(courseTable->rowCount());
    createCourseInputRow();
}

void MainWindow::onRemoveCourse() {
    int currentRow = courseTable->currentRow();
    if (currentRow >= 0) {
        courseTable->removeRow(currentRow);
    } else {
        QMessageBox::warning(this, "Warning", "Please select a course to remove.");
    }
}

void MainWindow::onClearAll() {
    courseTable->setRowCount(0);
    totalCreditHoursLabel->setText("Total Credit Hours: 0.00");
    semesterGPALabel->setText("Semester GPA: 0.00");
}

void MainWindow::onCalculateGPA() {
    if (courseTable->rowCount() == 0) {
        QMessageBox::warning(this, "Error", "Please add at least one course.");
        return;
    }

    float totalQualityPoints = 0.0f;
    float totalCreditHours = 0.0f;
    bool validData = true;

    for (int row = 0; row < courseTable->rowCount(); row++) {
        QLineEdit* courseNameEdit = qobject_cast<QLineEdit*>(courseTable->cellWidget(row, 0));
        QDoubleSpinBox* creditSpinBox = qobject_cast<QDoubleSpinBox*>(courseTable->cellWidget(row, 1));
        QDoubleSpinBox* pointsSpinBox = qobject_cast<QDoubleSpinBox*>(courseTable->cellWidget(row, 2));

        if (!courseNameEdit || !creditSpinBox || !pointsSpinBox) {
            validData = false;
            break;
        }

        if (courseNameEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a course name for all courses.");
            return;
        }

        float credits = static_cast<float>(creditSpinBox->value());
        float points = static_cast<float>(pointsSpinBox->value());

        if (credits <= 0) {
            QMessageBox::warning(this, "Error", "Credit hours must be greater than 0.");
            return;
        }

        totalCreditHours += credits;
        totalQualityPoints += (credits * points);
    }

    if (totalCreditHours > 0) {
        float gpa = totalQualityPoints / totalCreditHours;
        totalCreditHoursLabel->setText(QString("Total Credit Hours: %1").arg(totalCreditHours, 0, 'f', 2));
        semesterGPALabel->setText(QString("Semester GPA: %1").arg(gpa, 0, 'f', 2));
    } else {
        QMessageBox::warning(this, "Error", "No credit hours recorded. GPA cannot be calculated.");
    }
}
