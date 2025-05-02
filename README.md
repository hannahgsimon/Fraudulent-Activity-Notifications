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

## 🧪 Test Cases

This section includes both valid and invalid test cases to help you verify correctness and robustness.

### ✅ Valid Test Cases

🔹 **Case 1: Basic Example (from problem description)**
```yaml
Input:
9 5
2 3 4 2 3 6 8 4 5

Expected Output:
Total notifications: 2
```

🔹 **Case 2: No notifications triggered**
```yaml
Input:
5 4
1 2 3 4 4

Expected Output:
Total notifications: 0
```

🔹 **Case 3: All same values**
```yaml
Input:
6 3
10 10 10 10 10 10

Expected Output:
Total notifications: 0
Explanation: Every value is equal to the median, so value >= 2 × median is false (e.g., 10 < 2×10 = 20).
```

🔹 **Case 4: Large input within range**
```yaml
Input:
10 4
1 2 3 4 100 100 100 100 100 100

Expected Output:
Total notifications: 2
```

🔹 **Case 5: d equals n (only one day checked)**
```yaml
Input:
5 5
1 1 1 1 10

Expected Output:
Total notifications: 0
Explanation: Since d = n, there are no days after the trailing window to trigger a notification.
```

### ❌ Invalid Input Test Cases

🔻 **Case 6: Too few values for n and d**
```yaml
Input:
5

Expected Output:
Invalid input: expected 2 values for n and d, but got 1.
```

🔻 **Case 7: Too many values for n and d**
```yaml
Input:
5 3 1

Expected Output:
Invalid input: expected 2 values for n and d, but got 3.
```

🔻 **Case 8: Non-integer input for n or d**
```yaml
Input:
a b

Expected Output:
Invalid input: both n and d must be integers.
```

🔻 **Case 9: d > n**
```yaml
Input:
3 4

Expected Output:
Invalid input: you entered d=4, but d must be between 1 and n=3.
```

🔻 **Case 10: Too few expenditures**
```yaml
Input:
5 3
1 2 3

Expected Output:
Invalid input: expected n=5 expenditures, but got 3.
```

🔻 **Case 11: Too many expenditures**
```yaml
Input:
5 3
1 2 3 4 5 6

Expected Output:
Invalid input: expected n=5 expenditures, but got 6.
```

🔻 **Case 12: Invalid characters in expenditures**
```yaml
Input:
5 2
10 20 x 30 40

Expected Output:
Invalid input at day 3: 'x' is not an integer.
```

🔻 **Case 13: Expenditure out of range**
```yaml
Input:
5 2
10 20 250 30 40

Expected Output:
Invalid expenditure at day 3: must be between 0 and 200.
```

🔻 **Case 14: Empty input for n and d**

*(User presses Enter without typing anything)*

```yaml
Expected Output:
Invalid input: expected 2 values for n and d, but got 0.
```

---

## ⚠️ Bonus Edge Case: Stress Testing
🔸 **Case 15: Maximum allowed values (stress test — optional)**

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
