import tkinter as tk

grid_path = "./grid.txt"
with open(grid_path, "r") as f:
    grid_width, grid_height = [int(x) for x in f.readline().split()]
    rows = [row.rstrip("\n") for row in f]

pathfinding_path = "./pathfinding.txt"
with open(pathfinding_path, "r") as f:
    pgrid_width, pgrid_height, start_x, start_y, goal_x, goal_y = [int(x) for x in f.readline().split()]
    closed = [int(x) for x in f.readline().split()]
    path = [int(x) for x in f.readline().split()]

    assert(pgrid_height == grid_height and pgrid_width == grid_width)
    assert len(closed) == grid_width * grid_height
    assert len(path) == grid_width * grid_height

root = tk.Tk()

width = 750
height = 7501

screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

x = (screen_width - width) // 2
y = (screen_height - height) // 2

root.geometry(f"{width}x{height}+{x}+{y}")

root.title("Grid and A* visualization")
root.configure(bg="white")

if (max(grid_height, grid_width) > 100):
    print("Grid is too large to visualize using this script")
    print("Grid's size should not be bigger than 100x100")
else:
    cell_size = (width - 50) / max(grid_height, grid_width)
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
            index = y * grid_width + x
            if cell == "#":
                color = "black"
            else:
                color = "white"
                if closed[index] == 1: color = "cyan2"
                if path[index] == 1: color = "blue2"

            x1 = x * cell_size
            y1 = y * cell_size
            x2 = x1 + cell_size
            y2 = y1 + cell_size

            canvas.create_rectangle(
                x1, y1, x2, y2,
                fill = color,
                outline = "whitesmoke"
            )

    canvas.create_rectangle(
        start_x * cell_size, start_y * cell_size, start_x * cell_size + cell_size, start_y * cell_size + cell_size,
        fill="green3",
        outline="green3"
    )

    canvas.create_rectangle(
        goal_x * cell_size, goal_y * cell_size, goal_x * cell_size + cell_size, goal_y * cell_size + cell_size,
        fill="red",
        outline="red"
    )

    root.mainloop()