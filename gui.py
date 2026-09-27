import tkinter as tk
from tkinter import ttk
import subprocess
import os
import threading


# ============================================================
# CONFIGURATION
# ============================================================

PROJECT_DIR = os.path.dirname(os.path.abspath(__file__))
EXECUTABLE = os.path.join(PROJECT_DIR, "os_demo")


# ============================================================
# MAIN GUI CLASS
# ============================================================

class MemoryMappedFileSystemGUI:

    def __init__(self, root):

        self.root = root

        self.root.title("Linux Memory-Mapped File System")

        self.root.geometry("1100x700")

        self.root.minsize(900, 600)

        self.create_styles()
        self.create_header()
        self.create_main_area()
        self.create_footer()

    # ========================================================
    # STYLES
    # ========================================================

    def create_styles(self):

        style = ttk.Style()

        try:
            style.theme_use("clam")
        except tk.TclError:
            pass

        style.configure(
            "Title.TLabel",
            font=("Arial", 24, "bold")
        )

        style.configure(
            "Subtitle.TLabel",
            font=("Arial", 11)
        )

        style.configure(
            "Menu.TButton",
            font=("Arial", 11, "bold"),
            padding=12
        )

        style.configure(
            "Action.TButton",
            font=("Arial", 11, "bold"),
            padding=12
        )

    # ========================================================
    # HEADER
    # ========================================================

    def create_header(self):

        header = ttk.Frame(
            self.root,
            padding=20
        )

        header.pack(fill="x")

        title = ttk.Label(
            header,
            text="Linux Memory-Mapped File System",
            style="Title.TLabel"
        )

        title.pack()

        subtitle = ttk.Label(
            header,
            text="Memory Management • File Operations • Processes • IPC • Concurrency",
            style="Subtitle.TLabel"
        )

        subtitle.pack(pady=(5, 0))

    # ========================================================
    # MAIN AREA
    # ========================================================

    def create_main_area(self):

        main = ttk.Frame(
            self.root,
            padding=(20, 10)
        )

        main.pack(
            fill="both",
            expand=True
        )

        # ----------------------------------------------------
        # LEFT PANEL
        # ----------------------------------------------------

        left = ttk.LabelFrame(
            main,
            text="System Operations",
            padding=15
        )

        left.pack(
            side="left",
            fill="y",
            padx=(0, 15)
        )

        self.create_operation_buttons(left)

        # ----------------------------------------------------
        # RIGHT PANEL
        # ----------------------------------------------------

        right = ttk.LabelFrame(
            main,
            text="System Output",
            padding=10
        )

        right.pack(
            side="right",
            fill="both",
            expand=True
        )

        self.output = tk.Text(
            right,
            wrap="word",
            font=("Courier New", 10),
            state="disabled"
        )

        scrollbar = ttk.Scrollbar(
            right,
            orient="vertical",
            command=self.output.yview
        )

        self.output.configure(
            yscrollcommand=scrollbar.set
        )

        self.output.pack(
            side="left",
            fill="both",
            expand=True
        )

        scrollbar.pack(
            side="right",
            fill="y"
        )

    # ========================================================
    # OPERATION BUTTONS
    # ========================================================

    def create_operation_buttons(self, parent):

        operations = [
            ("System Call Operations", 1),
            ("Process Management", 2),
            ("Inter-Process Communication", 3),
            ("Memory Mapping", 4),
            ("File Operations", 5),
            ("Concurrent Access", 6)
        ]

        for name, number in operations:

            button = ttk.Button(
                parent,
                text=name,
                style="Menu.TButton",
                command=lambda n=number: self.run_operation(n)
            )

            button.pack(
                fill="x",
                pady=5
            )

        separator = ttk.Separator(parent)

        separator.pack(
            fill="x",
            pady=15
        )

        run_all_button = ttk.Button(
            parent,
            text="Run Complete System Test",
            style="Action.TButton",
            command=lambda: self.run_operation(7)
        )

        run_all_button.pack(
            fill="x",
            pady=5
        )

        clear_button = ttk.Button(
            parent,
            text="Clear Output",
            command=self.clear_output
        )

        clear_button.pack(
            fill="x",
            pady=(15, 5)
        )

    # ========================================================
    # FOOTER
    # ========================================================

    def create_footer(self):

        footer = ttk.Frame(
            self.root,
            padding=10
        )

        footer.pack(fill="x")

        self.status = ttk.Label(
            footer,
            text="Ready",
            anchor="w"
        )

        self.status.pack(
            side="left"
        )

        project_label = ttk.Label(
            footer,
            text="Linux OS Project",
            anchor="e"
        )

        project_label.pack(
            side="right"
        )

    # ========================================================
    # CLEAR OUTPUT
    # ========================================================

    def clear_output(self):

        self.output.configure(
            state="normal"
        )

        self.output.delete(
            "1.0",
            "end"
        )

        self.output.configure(
            state="disabled"
        )

        self.status.config(
            text="Ready"
        )

    # ========================================================
    # APPEND OUTPUT
    # ========================================================

    def append_output(self, text):

        self.output.configure(
            state="normal"
        )

        self.output.insert(
            "end",
            text
        )

        self.output.see("end")

        self.output.configure(
            state="disabled"
        )

    # ========================================================
    # RUN OPERATION
    # ========================================================

    def run_operation(self, operation):

        # Clear previous result
        self.clear_output()

        # Check whether C executable exists
        if not os.path.exists(EXECUTABLE):

            self.append_output(
                "ERROR: os_demo executable was not found.\n\n"
                "Please run:\n"
                "    make\n\n"
                "Then start the GUI again."
            )

            self.status.config(
                text="Executable not found"
            )

            return

        self.status.config(
            text="Running operation..."
        )

        self.append_output(
            "============================================================\n"
        )

        # Run C program in background
        thread = threading.Thread(
            target=self.execute_backend,
            args=(operation,),
            daemon=True
        )

        thread.start()

    # ========================================================
    # EXECUTE C BACKEND
    # ========================================================

    def execute_backend(self, operation):

        try:

            process = subprocess.run(
                [EXECUTABLE, str(operation)],
                cwd=PROJECT_DIR,
                capture_output=True,
                text=True
            )

            output = process.stdout

            if process.stderr:

                output += (
                    "\nERROR OUTPUT:\n"
                    + process.stderr
                )

            self.root.after(
                0,
                lambda: self.display_result(
                    output,
                    process.returncode
                )
            )

        except Exception as error:

            self.root.after(
                0,
                lambda: self.display_result(
                    "Unable to execute the C backend.\n\n"
                    + str(error),
                    1
                )
            )

    # ========================================================
    # DISPLAY RESULT
    # ========================================================

    def display_result(
        self,
        output,
        return_code
    ):

        self.append_output(
            output
            + "\n"
        )

        if return_code == 0:

            self.status.config(
                text="Operation completed successfully"
            )

        else:

            self.status.config(
                text="Operation completed with errors"
            )


# ============================================================
# START APPLICATION
# ============================================================

if __name__ == "__main__":

    root = tk.Tk()

    app = MemoryMappedFileSystemGUI(root)

    root.mainloop()
