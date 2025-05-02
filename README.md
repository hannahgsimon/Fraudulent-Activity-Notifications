# Fraudulent Activity Notifications

## 📖 Overview
This repository contains two implementations of a **Fraudulent Activity Notification** system, one written in **C** and the other in **Python 3**. The program simulates a bank alert system that notifies clients when their spending on a given day is at least **twice the median** of spending over a trailing number of days.  

For a detailed explanation of the algorithm, see the original problem on HackerRank:
https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem

---

## 🔍 Description & Comparison of Implementations

### C Version
- **Language**: C
- **Paradigm**: Procedural, low-level, manual memory management
- **Features**:
  - Uses `malloc` and `free` for dynamic memory allocation
  - Includes defensive programming techniques like input validation, buffer safety, and range checks
  - Optimized for performance using a frequency array (counting sort principle)

### Python Version
- **Language**: Python 3
- **Paradigm**: High-level, procedural with some functional style
- **Features**:
  - Uses Python’s built-in types for simplicity
  - Emphasizes readability and rapid development
  - No manual memory management required

### Key Differences
| Aspect                  | C                                | Python                            |
|------------------------|----------------------------------|-----------------------------------|
| Memory Management      | Manual (`malloc`/`free`)         | Automatic (Garbage Collection)    |
| Type System            | Statically typed                 | Dynamically typed                 |
| Input Handling         | Manual parsing, buffer-safe      | Built-in input parsing (`input()`)|
| Portability            | Needs compiler                   | Requires Python interpreter       |
| Runtime Speed          | Generally faster                 | Slower but easier to debug        |
| Code Complexity        | Verbose                          | Concise and expressive            |

---

## 📐 Algorithm Overview

Both implementations use the same underlying algorithm:

- Maintain a **sliding window** of the last `d` expenditures.
- Use a **counting array (0–200)** to track frequencies.
- Efficiently compute the **median** from the count array:
  - O(201) time for median using cumulative counts
- If the current day's spending ≥ `2 × median`, send a notification.

---

## 🛠️ Programming Languages and Paradigms

- **C**: Procedural, static memory-aware programming
- **Python 3**: High-level scripting, dynamic typing

---

## ⚙️ Compilers / Interpreters Used

### C
- **Compiler**: GCC (e.g., `gcc fraud_alert.c -o fraud_alert`)
- **Standard**: C99 or later

### Python
- **Interpreter**: Python 3.6+

---

## ▶️ How to Run the Code

### 1. Clone the Repository
```bash
git clone https://github.com/hannahgsimon/Fraudulent-Activity-Notifications.git
cd Fraudulent-Activity-Notifications
```

### 2. Run the C Version

#### Compile:
```bash
gcc activity_notifications.c -o activity_notifications
```

#### Run:
```bash
./activity_notifications
```

### 3. Run the Python Version
```bash
python3 activity_notifications.py
```

---

## 📝 Sample Input & Output
```
Enter the total number of days (n) and the number of previous/trailing days (d) to calculate the median:
9 5

Enter the expenditures for 9 days (space-separated values):
2 3 4 2 3 6 8 4 5

Total notifications: 2
```

---

## 🧪 Stress Testing

The file `stress_test.txt` contains input designed to test the algorithm under maximum constraints:

- `n = 200000`, `d = 100000`  
- All expenditure values are `1`

### Expected Result
Since all values are equal, the median remains `1` throughout, and no day's spending reaches or exceeds `2 × median`.  
→ **Expected output: `0 notifications`**

This test ensures that both implementations handle large inputs efficiently without performance degradation or memory issues.

### How to Run the Stress Test

1. Generate the Input File (Linux/macOS/WSL)
```bash
echo "200000 100000" > stress_input.txt
python3 -c "print(' '.join(['1'] * 200000))" >> stress_input.txt
```

2. Run with C Version
```bash
./activity_notifications < stress_input.txt
```

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Run with Python Version
```bash
python3 activity_notifications.py < stress_input.txt
```

3. Both versions should output:
```
Total notifications: 0
```

---

## 📜 License

This project is licensed under the MIT License. See the LICENSE file for details.

---

## 📬 Contact
For questions or feedback, please contact Hannah G. Simon at hgsimon2@gmail.com.
