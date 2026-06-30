# GPA Calculator GUI

An interactive graphical user interface for calculating semester GPA based on course data.

## Features

- **Dynamic Course Entry**: Add or remove courses as needed
- **Real-time Quality Points Calculation**: Watch quality points update as you enter credit hours and points earned
- **Easy Data Input**: Intuitive interface with spinboxes for numerical input
- **GPA Calculation**: Calculates total credit hours and semester GPA
- **Validation**: Ensures all required fields are filled before calculation

## Requirements

- Qt6 (Core, Gui, Widgets)
- CMake 3.16 or higher
- C++17 compatible compiler

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

```bash
./GPACalculator
```

## Usage

1. Set the number of courses you want to enter using the spinbox
2. Fill in each course with:
   - Course Name
   - Credit Hours (0.0 - 6.0)
   - Points Earned (0.0 - 4.0)
3. The Quality Points column updates automatically
4. Click "Calculate GPA" to compute your semester GPA
5. View results in the Semester Report section

## Features

- **Add Course**: Manually add additional courses
- **Remove Selected**: Remove a course from the table
- **Clear All**: Reset all data and results
- **Calculate GPA**: Compute and display semester GPA and total credit hours
