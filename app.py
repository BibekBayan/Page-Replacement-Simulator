import tkinter as tk
from tkinter import messagebox
import subprocess

BG = "#0f172a"
CARD = "#1e293b"
INPUT = "#334155"
BTN = "#22c55e"
BTN_HOVER = "#16a34a"
TEXT = "#e2e8f0"
HEADER = "#1d4ed8"

backend_path = r"D:\PageReplacementSimulator\backend\simulator.exe"

def explain(best):
    if best == "OPTIMAL":
        return "Optimal minimizes faults using future knowledge."
    elif best == "LRU":
        return "LRU removes least recently used pages."
    elif best == "LFU":
        return "LFU removes least frequently used pages."
    elif best == "FIFO":
        return "FIFO replaces pages in arrival order."
    return ""

def run_simulation():
    frames = frame_entry.get().strip()
    pages = page_entry.get().strip()

    if not frames or not pages:
        messagebox.showwarning("Input Error", "Please fill all fields")
        return

    result = subprocess.run(
        [backend_path, frames, pages, "COMPARE"],
        capture_output=True,
        text=True
    )

    output = result.stdout
    best = ""

    for line in output.splitlines():
        if "Best Algorithm" in line:
            best = line.split(":")[1].strip()

    explanation = explain(best)

    formatted = "===== RESULT =====\n\n"
    formatted += output
    formatted += "\nExplanation: " + explanation

    output_box.delete("1.0", tk.END)
    output_box.insert(tk.END, formatted)

    lines = formatted.count("\n") + 2
    output_box.config(height=min(max(lines, 10), 20))

    root.update_idletasks()
    root.geometry(f"800x{500 + lines*10}")


def on_enter(e):
    run_btn.config(bg=BTN_HOVER)

def on_leave(e):
    run_btn.config(bg=BTN)


root = tk.Tk()
root.title("Page Replacement Simulator")
root.geometry("800x600")
root.configure(bg=BG)

header = tk.Frame(root, bg=HEADER, height=60)
header.pack(fill="x")

tk.Label(header, text="⚙ Page Replacement Simulator",
         bg=HEADER, fg="white",
         font=("Segoe UI", 18, "bold")).pack(pady=12)

card = tk.Frame(root, bg=CARD, padx=25, pady=20)
card.pack(padx=20, pady=15, fill="both", expand=True)

input_frame = tk.Frame(card, bg=CARD)
input_frame.pack(pady=10)

tk.Label(input_frame, text="Number of Frames",
         bg=CARD, fg=TEXT).pack()

frame_entry = tk.Entry(input_frame, bg=INPUT, fg="white", justify="center")
frame_entry.pack(pady=5)

tk.Label(input_frame, text="Page Sequence",
         bg=CARD, fg=TEXT).pack()

page_entry = tk.Entry(input_frame, bg=INPUT, fg="white", justify="center")
page_entry.pack(pady=5)

run_btn = tk.Button(card, text="Compare Algorithms",
                    bg=BTN, fg="black",
                    command=run_simulation)
run_btn.pack(pady=15)

run_btn.bind("<Enter>", on_enter)
run_btn.bind("<Leave>", on_leave)

output_box = tk.Text(card,
                     bg="#020617", fg="white",
                     font=("Consolas", 10),
                     height=10)
output_box.pack(fill="both", expand=True)

root.mainloop()