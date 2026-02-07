import pandas as pd
import matplotlib.pyplot as plt
import platform
import os


df = pd.read_csv("results.csv")


df["n"] = pd.to_numeric(df["n"], errors="coerce")
df["time_seconds"] = pd.to_numeric(df["time_seconds"], errors="coerce")


df = df.dropna()


os_name = platform.system()
os_version = platform.release()
cpu = platform.processor() or "Unknown CPU"
cores = os.cpu_count()
python_version = platform.python_version()

spec_text = (
    f"OS: {os_name} {os_version}\n"
    f"CPU: {cpu}\n"
    f"Cores: {cores}\n"
    f"Python: {python_version}"
)


plt.figure(figsize=(9, 6))
plt.plot(df["n"], df["time_seconds"], marker='o')

plt.xlabel("Number of Processes (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("n vs Execution Time (Parallel Prime Computation)")
plt.grid(True)


plt.text(
    0.02, 0.98, spec_text,
    transform=plt.gca().transAxes,
    fontsize=9,
    verticalalignment='top',
    bbox=dict(boxstyle="round", alpha=0.3)
)

plt.tight_layout()
plt.show()
