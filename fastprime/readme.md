# FastPrime – Run Instructions

This project contains a C program and a Python script for plotting results.

---

## 1. Compile and Run the C Program

The `main.c` file is located inside the `fastprime` directory.

### Steps

```bash
cd fastprime
gcc main.c
./a.out [leftsidevalue] [rightsidevalue]
```

Replace `[leftsidevalue]` and `[rightsidevalue]` with the required numeric arguments.

### Output

After successful execution, the following files will be created:

- `result.txt`
- `result.csv`

---

## 2. Set Up Python Virtual Environment

Make sure Python 3 is installed.

### Create a virtual environment

```bash
python3 -m venv venv
```

### Activate the virtual environment

**Linux / macOS**
```bash
source venv/bin/activate
```

**Windows**
```bash
venv\Scripts\activate
```

---

## 3. Install Required Python Libraries

```bash
pip install matplotlib pandas
```

---

## 4. Run the Plot Script

Once `result.csv` is generated and dependencies are installed:

```bash
python plot.py
```

This will generate plots based on the data in `result.csv`.