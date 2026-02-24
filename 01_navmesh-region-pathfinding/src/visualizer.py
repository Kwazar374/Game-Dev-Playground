import tkinter as tk

path = "./grid.txt"
with open(path, "r") as f:
    grid_width, grid_height, start_x, start_y, goal_x, goal_y = [int(x) for x in f.readline().split()]
    rows = [row.strip() for row in f]

root = tk.Tk()

width = 750
height = 750

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

x = (screen_width - width) // 2
y = (screen_height - height) // 2

root.geometry(f"{width}x{height}+{x}+{y}")

root.title("Grid visualization")
root.configure(bg="white")

cell_size = 7
canvas = tk.Canvas(
    root,
    width = grid_width * cell_size,
    height = grid_height * cell_size,
    bg = "white",
    highlightthickness=0,
    bd=0
)

canvas.pack(expand = "true")

for y, row in enumerate(rows):
    for x, cell in enumerate(row):
        color = "black" if cell == "#" else "white"

        x1 = x * cell_size
        y1 = y * cell_size
        x2 = x1 + cell_size
        y2 = y1 + cell_size

        canvas.create_rectangle(
            x1, y1, x2, y2,
            fill = color,
            outline = "gray"
        )

print(start_x, start_y)

canvas.create_rectangle(
    start_x * cell_size, start_y * cell_size, start_x * cell_size + cell_size, start_y * cell_size + cell_size,
    fill="green2",
    outline="gray"
)

canvas.create_rectangle(
    goal_x * cell_size, goal_y * cell_size, goal_x * cell_size + cell_size, goal_y * cell_size + cell_size,
    fill="red",
    outline="gray"
)

root.mainloop()